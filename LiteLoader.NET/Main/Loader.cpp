#include <LoggerAPI.h>
#include ".NETGlobal.hpp"
#include "PluginAttribute.h"
#include "PluginManager.h"
#include "IPluginInitializer.hpp"
#include "FixCLRFatalError.h"


Assembly^ OnAssemblyResolve(System::Object^ sender, System::ResolveEventArgs^ args);

void Init(Logger& logger);

//inline void InitializePluginHandler(std::filesystem::path const& path, Assembly^ Asm);

bool LoadByDefaultEntry(Logger& logger, Assembly^ Asm);

bool LoadByCustomEntry(Logger& logger, Assembly^ Asm);

void LoadPlugins(std::vector<std::filesystem::path> const& assemblyPaths, Logger& logger);

List<String^>^ ParsePluginLibraryPath(Assembly^ Asm);

#pragma unmanaged
#include "Global.hpp"
#include <Utils/Hash.h>

#pragma unmanaged
void LoadMain()
{
	Logger logger(LLNET_LOADER_NAME);

	Init(logger);

	logger.info("Loading plugins...");
	std::filesystem::directory_iterator files(LLNET_PLUGINS_LOAD_DIR);
	std::vector<std::filesystem::path> assemblies;
	for (auto& file : files)
	{
		auto& filePath = file.path();
		if (filePath.extension() == ".dll")
		{
			if (filePath.filename() == LLNET_LOADER_NAME_WITH_EXTENSION)
				continue;
			assemblies.emplace_back(filePath);
		}
	}

	LoadPlugins(assemblies, logger);
}

#pragma managed
extern void InitEvents();

void Init(Logger& logger)
{
	InitEvents();
	System::AppDomain::CurrentDomain->AssemblyResolve += gcnew System::ResolveEventHandler(&OnAssemblyResolve);
	GlobalClass::ManagedPluginHandler->TryAdd(Assembly::GetExecutingAssembly(), IntPtr(::LL::getPlugin(LLNET_LOADER_NAME)->handle));
}


Assembly^ OnAssemblyResolve(System::Object^ sender, System::ResolveEventArgs^ args) {
	using Path = System::IO::Path;
	using File = System::IO::File;

	AssemblyName assemblyName(args->Name);
	if (assemblyName.Name == LLNET_LOADER_NAME)
		return Assembly::GetExecutingAssembly();

	auto llLibPath = Path::Combine(LITELOADER_LIBRARY_DIR, assemblyName.Name + ".dll");
	if (File::Exists(llLibPath))
	{
		return Assembly::LoadFrom(llLibPath);
	}

	auto customPaths = GlobalClass::CustomLibPath[args->RequestingAssembly];
	for each (auto customPath in customPaths)
	{
		auto libPath = System::IO::Path::Combine(customPath, assemblyName.Name + ".dll");
		if (File::Exists(libPath))
		{
			return System::Reflection::Assembly::LoadFrom(libPath);
		}

		auto libPathWithPlugin = Path::Combine("plugins", customPath, assemblyName.Name + ".dll");
		if (File::Exists(libPathWithPlugin))
		{
			return Assembly::LoadFrom(libPathWithPlugin);
		}
	}

	return nullptr;
}


void LoadPlugins(std::vector<std::filesystem::path> const& assemblyPaths, Logger& logger)
{ 
	FixCLRFatalError();
	size_t count = 0;
	for (auto iter = assemblyPaths.begin(); iter != assemblyPaths.end(); ++iter)
	{
		if (iter->filename() == LLNET_LOADER_NAME)
			continue;
		try
		{
			auto Asm = Assembly::LoadFrom(marshalString(iter->string()));

			LLNET::PluginManager::registerPlugin(Asm->GetName()->Name, "", gcnew LLNET::LL::Version(1, 0, 0), nullptr, Asm);

			GlobalClass::CustomLibPath->Add(Asm, ParsePluginLibraryPath(Asm));

			auto succeed = LoadByDefaultEntry(logger, Asm);
			if (!succeed)
				succeed = LoadByCustomEntry(logger, Asm);


			if (succeed)
			{
				logger.info("Plugin <{}> loaded", iter->filename().string());
				++count;
			}
		}
		catch (System::BadImageFormatException^)
		{
			continue;
		}
		catch (System::Reflection::TargetInvocationException^ ex)
		{
			logger.error("Uncaught {} Detected!", marshalString(ex->InnerException->GetType()->ToString()));
			logger.error(marshalString(ex->InnerException->ToString()));
		}
		catch (System::Exception^ ex)
		{
			logger.error("Uncaught {} Detected!", marshalString(ex->GetType()->ToString()));
			logger.error(marshalString(ex->ToString()));
		}
		catch (const std::exception& ex)
		{
			logger.error("Uncaught std::exception Detected!");
			logger.error(ex.what());
		}
		catch (...)
		{
			logger.error("Uncaught exception Detected!");
		}
	}
	logger.info << count << " plugin(s) loaded" << logger.endl;
}


bool LoadByDefaultEntry(Logger& logger, Assembly^ Asm)
{
	try
	{
		auto plugin = Asm->GetType(TEXT(LLNET_ENTRY_CLASS));
		if (plugin == nullptr)
			return false;

		auto method = plugin->GetMethod(TEXT(LLNET_ENTRY_METHOD));
		if (method == nullptr)
			return false;

		method->Invoke(nullptr, nullptr);

		return true;
	}
	catch (System::NullReferenceException^)
	{
		return false;
	}
	catch (System::Reflection::TargetInvocationException^ ex)
	{
		logger.error("Uncaught {} Detected!", marshalString(ex->InnerException->GetType()->ToString()));
		logger.error(marshalString(ex->InnerException->ToString()));
		return false;
	}
	catch (System::Exception^ ex)
	{
		logger.error("Uncaught {} Detected!", marshalString(ex->GetType()->ToString()));
		logger.error(marshalString(ex->ToString()));
		return false;
	}
	catch (const std::exception& ex)
	{
		logger.error("Uncaught std::exception Detected!");
		logger.error(ex.what());
		return false;
	}
	catch (...)
	{
		logger.error("Uncaught exception Detected!");
		return false;
	}
}


List<String^>^ ParsePluginLibraryPath(Assembly^ Asm)
{
	using LLNET::Core::LibPathAttribute;

	auto libAttrType = LibPathAttribute::typeid;
	auto ret = gcnew List<String^>;

	auto asmLibPathAttrArr = Asm->GetCustomAttributes(libAttrType, false);

	if (asmLibPathAttrArr == nullptr)
		return ret;

	for each (auto attr in asmLibPathAttrArr)
	{
		ret->Add(static_cast<LibPathAttribute^>(attr)->Path);
	}

	return ret;
}

bool LoadByCustomEntry(Logger& logger, Assembly^ Asm)
{
	using IPluginInitializer = LLNET::Core::IPluginInitializer;
	using PluginMainAttribute = LLNET::Core::PluginMainAttribute;
	using LibPathAttribute = LLNET::Core::LibPathAttribute;

	try
	{
		auto types = Asm->GetExportedTypes();
		System::String^ pluginName = Asm->GetName()->Name;
		IPluginInitializer^ initializer = nullptr;
		for each (auto type in types)
		{
			if (type->Equals(IPluginInitializer::typeid))
				continue;

			auto pluginMainAttr = System::Attribute::GetCustomAttribute(type, PluginMainAttribute::typeid);
			auto customLibPathAttribute = System::Attribute::GetCustomAttribute(type, LibPathAttribute::typeid);

			if (pluginMainAttr != nullptr)
			{
				pluginName = static_cast<PluginMainAttribute^>(pluginMainAttr)->Name;
				auto ctor = type->GetConstructor(System::Type::EmptyTypes);
				if (ctor != nullptr)
				{
					pluginName = static_cast<PluginMainAttribute^>(pluginMainAttr)->Name;
					initializer = static_cast<IPluginInitializer^>(ctor->Invoke(nullptr));
					break;
				}
			}
		}

		if (initializer != nullptr)
		{
			initializer->OnInitialize();
			String^ introduction = initializer->Introduction;
			auto version = gcnew LLNET::LL::Version(
				initializer->Version->Major,
				initializer->Version->Minor,
				initializer->Version->Build
			);
			auto others = initializer->MetaData;
			LLNET::PluginManager::registerPlugin(pluginName, introduction, version, others, Asm);
		}
		return true;
	}
	catch (System::Reflection::TargetInvocationException^ ex)
	{
		logger.error("Uncaught {} Detected!", marshalString(ex->InnerException->GetType()->ToString()));
		logger.error(marshalString(ex->InnerException->ToString()));
		return false;
	}
	catch (System::Exception^ ex)
	{
		logger.error("Uncaught {} Detected!", marshalString(ex->GetType()->ToString()));
		logger.error(marshalString(ex->ToString()));
		return false;
	}
	catch (const std::exception& ex)
	{
		logger.error("Uncaught std::exception Detected!");
		logger.error(ex.what());
		return false;
	}
	catch (...)
	{
		logger.error("Uncaught exception Detected!");
		return false;
	}
}