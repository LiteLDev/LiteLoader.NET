#include <LoggerAPI.h>
#include ".NETGlobal.hpp"
#include "PluginAttribute.h"
#include "PluginManager.h"
#include "IPluginInitializer.hpp"



#pragma managed

//managed
Assembly^ OnAssemblyResolve(System::Object^ sender, System::ResolveEventArgs^ args);

//managed
void Init();

//inline void InitializePluginHandler(std::filesystem::path const& path, Assembly^ Asm);

//managed
bool LoadByDefaultEntry(Logger& logger, Assembly^ Asm);

//managed
bool LoadByCustomEntry(Logger& logger, Assembly^ Asm);

//managed
void LoadPlugins(std::vector<std::filesystem::path> const& assemblyPaths, Logger& logger);

//managed
List<String^>^ ParsePluginLibraryPath(Assembly^ Asm);


namespace LLNET {
	public ref class __Entry
	{
	public:
		delegate void EntryPropotype(void*, void*);

		static void InitAndLoadPlugins(void* pLogger, void* std_vector_assemblies)
		{
			Init();

			reinterpret_cast<::Logger*>(pLogger)->info("Loading .NET plugins...");

			LoadPlugins(
				*reinterpret_cast<std::vector<std::filesystem::path>*>(std_vector_assemblies),
				*reinterpret_cast<::Logger*>(pLogger));
		}
	};
}

void __entry(void* pLogger, void* std_vector_assemblies) { LLNET::__Entry::InitAndLoadPlugins(pLogger, std_vector_assemblies); }

#pragma unmanaged
#include "Global.hpp"
#include <Utils/Hash.h>
#include <sstream>

#pragma unmanaged

std::vector<std::filesystem::path> GetAllAssemblies();

void LoadMain()
{
	Logger logger(LLNET_INFO_LOADER_NAME);

	logger.consoleLevel = 5;

	__entry(&logger, &GetAllAssemblies());
}

std::vector<std::filesystem::path> GetAllAssemblies()
{
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
	return assemblies;
}

#pragma managed
extern void InitEvents();

void Init()
{
	InitEvents();
	System::AppDomain::CurrentDomain->AssemblyResolve += gcnew System::ResolveEventHandler(&OnAssemblyResolve);
	auto LLNET_Asm = Assembly::GetExecutingAssembly();
	GlobalClass::ManagedModuleHandler->TryAdd(LLNET_Asm, IntPtr(::LL::getPlugin(LLNET_INFO_LOADER_NAME)->handle));
}


Assembly^ OnAssemblyResolve(System::Object^ sender, System::ResolveEventArgs^ args) {
	using System::IO::Path;
	using System::IO::File;

	AssemblyName assemblyName(args->Name);
	if (assemblyName.Name == LLNET_INFO_LOADER_NAME)
		return Assembly::GetExecutingAssembly();

	auto llLibPath = Path::Combine(LITELOADER_LIBRARY_DIR, assemblyName.Name + ".dll");
	if (File::Exists(llLibPath))
	{
		return Assembly::LoadFrom(llLibPath);
	}

	auto llLibPathManaged = Path::Combine(LLNET_LIBRARY_DIR_DOTNETONLY, assemblyName.Name + ".dll");
	if (File::Exists(llLibPathManaged))
	{
		return Assembly::LoadFrom(llLibPathManaged);
	}

	if (GlobalClass::RUNTIME_SHARED_LIB_DIR != nullptr)
	{
		auto runtimeSharedLibPath = Path::Combine(const_cast<String^>(GlobalClass::RUNTIME_SHARED_LIB_DIR), assemblyName.Name + ".dll");
		if (File::Exists(runtimeSharedLibPath))
		{
			return Assembly::LoadFrom(runtimeSharedLibPath);
		}
	}

	List<String^>^ customPaths = nullptr;
	if (GlobalClass::CustomLibPath->TryGetValue(args->RequestingAssembly, customPaths))
	{
		for each (auto customPath in customPaths)
		{
			auto libPath = System::IO::Path::Combine(customPath, assemblyName.Name + ".dll");
			if (File::Exists(libPath))
			{

				auto Asm = System::Reflection::Assembly::LoadFrom(libPath);
				auto handle = GetModuleHandle(std::filesystem::path(marshalString(Asm->Location)).wstring().c_str());
				GlobalClass::ManagedModuleHandler->Add(Asm, IntPtr(handle));
				return Asm;
			}

			auto libPathWithPlugin = Path::Combine("plugins", customPath, assemblyName.Name + ".dll");
			if (File::Exists(libPathWithPlugin))
			{
				auto Asm = Assembly::LoadFrom(libPathWithPlugin);
				auto handle = GetModuleHandle(std::filesystem::path(marshalString(Asm->Location)).wstring().c_str());
				GlobalClass::ManagedModuleHandler->Add(Asm, IntPtr(handle));
				return Asm;
			}
		}
	}

	return nullptr;
}


void LoadPlugins(std::vector<std::filesystem::path> const& assemblyPaths, Logger& logger)
{
	using System::Reflection::PortableExecutable::PEReader;
	using System::IO::File;
	using System::IO::FileStream;
	using System::IO::FileMode;
	using System::IO::FileAccess;
	using System::IO::FileShare;

	size_t count = 0;
	for (auto iter = assemblyPaths.begin(); iter != assemblyPaths.end(); ++iter)
	{
		if (iter->filename() == LLNET_INFO_LOADER_NAME)
			continue;

		auto path = marshalString(iter->string());

		try
		{


			bool isManagedAssembly = false;
			auto file = gcnew FileStream(path, FileMode::Open, FileAccess::Read, FileShare::ReadWrite);
			auto reader = gcnew PEReader(file);

			if (reader->HasMetadata)
				isManagedAssembly = true;

			file->Close();

			if (!isManagedAssembly)
			{
				continue;
			}


			auto Asm = Assembly::LoadFrom(path);

			LLNET::PluginManager::registerPlugin(Asm->GetName()->Name, "", gcnew LLNET::LL::Version(1, 0, 0), nullptr, Asm);

			GlobalClass::CustomLibPath->Add(Asm, ParsePluginLibraryPath(Asm));

			auto succeed = LoadByDefaultEntry(logger, Asm);
			if (!succeed)
				succeed = LoadByCustomEntry(logger, Asm);


			if (succeed)
			{
				logger.info(".NET plugin <{}> loaded", iter->filename().string());
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


	}
	logger.info("{} .NET plugin(s) loaded", count);
}


bool LoadByDefaultEntry(Logger& logger, Assembly^ Asm)
{

	try
	{
		auto plugin = Asm->GetType(TEXT(LLNET_PLUGIN_ENTRY_CLASS));
		if (plugin == nullptr)
			return false;

		auto method = plugin->GetMethod(TEXT(LLNET_PLUGIN_ENTRY_METHOD));
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
}