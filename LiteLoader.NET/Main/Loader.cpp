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
		static void InitAndLoadPlugins(void* pLogger, void* std_vector_assemblies)
		{
			Init();
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
#include "../Extra/nethost.h"
#include "../Extra/hostfxr.h"
#include "../Extra/coreclr_delegates.h"

std::vector<std::filesystem::path> GetAllAssemblies();

void LoadMain()
{
	Logger logger(LLNET_LOADER_NAME);

	auto nethost_dll = LoadLibrary(TEXT(DOTNET_NETHOST_DLL_PATH));

	if (nethost_dll == nullptr)
	{
		logger.error("Cannot load nethost.dll!");
		throw std::exception();
	}

	auto get_hostfxr_path_fn = reinterpret_cast<
		int(__stdcall*)(char_t*, size_t*, const struct get_hostfxr_parameters*)>(
			GetProcAddress(nethost_dll, "get_hostfxr_path"));

	if (get_hostfxr_path_fn == nullptr)
	{
		logger.error("Cannot get exported function from <nethost.dll>!");
		throw std::exception();
	}

	char_t buffer[MAX_PATH];
	size_t buffer_size = sizeof(buffer) / sizeof(char_t);
	int rc = get_hostfxr_path_fn(buffer, &buffer_size, nullptr);

	FreeLibrary(nethost_dll);



	if (rc == 0)
	{
		auto assemblies = GetAllAssemblies();
		__entry(&logger, &assemblies);
	}
	else
	{
		if (!std::filesystem::exists(DOTNET_RUNTIME_DIR))
		{
			logger.error("Cannot find local .NET runtime path!");
			throw std::exception();
		}
		else
		{
			auto hostfxr_dll = LoadLibrary(TEXT(DOTNET_RUNTINE_HOSTFXR_DLL_PATH));

			if (hostfxr_dll == nullptr)
			{
				logger.error("Cannot load hostfxr.dll!");
				throw std::exception();
			}

			auto init_fptr = reinterpret_cast<hostfxr_initialize_for_runtime_config_fn>(
				GetProcAddress(hostfxr_dll, "hostfxr_initialize_for_runtime_config"));

			auto get_delegate_fptr = reinterpret_cast<hostfxr_get_runtime_delegate_fn>(
				GetProcAddress(hostfxr_dll, "hostfxr_get_runtime_delegate"));

			auto close_fptr = reinterpret_cast<hostfxr_close_fn>(
				GetProcAddress(hostfxr_dll, "hostfxr_close"));

			if (init_fptr == nullptr || get_delegate_fptr == nullptr || close_fptr == nullptr)
			{
				logger.error("Cannot get exported function from <hostfxr.dll>!");
				throw std::exception();
			}



			load_assembly_and_get_function_pointer_fn load_assembly_and_get_function_pointer = nullptr;
			hostfxr_handle cxt = nullptr;

			int rc = init_fptr(TEXT(LLNET_RUNTIME_CONFIG_JSON_PATH), nullptr, &cxt);

			constexpr auto to_hex_string = [](int i)->std::string
			{
				std::stringstream ioss;
				string s_temp;
				ioss << std::setiosflags(std::ios::uppercase) << std::hex << std::showbase << i;
				ioss >> s_temp;
				return s_temp;
			};

			if (rc != 0 || cxt == nullptr)
			{
				logger.error("Init failed: {}", to_hex_string(rc));
				close_fptr(cxt);
				throw std::exception();
			}

			rc = get_delegate_fptr(
				cxt,
				hdt_load_assembly_and_get_function_pointer,
				reinterpret_cast<void**>(&load_assembly_and_get_function_pointer));

			if (rc != 0 || load_assembly_and_get_function_pointer == nullptr)
			{
				logger.error("Get delegate failed: {}", to_hex_string(rc));
				close_fptr(cxt);
				throw std::exception();
			}



			component_entry_point_fn initAndLoadPlugins_fptr = nullptr;

			rc = load_assembly_and_get_function_pointer(
				TEXT(LLNET_LOADER_PATH),
				TEXT(LLNET_MANAGED_ENTRY_CLASS),
				TEXT(LLNET_MANAGED_ENTRY_METHOD),
				nullptr,
				nullptr,
				reinterpret_cast<void**>(&initAndLoadPlugins_fptr));


			if (rc != 0 || initAndLoadPlugins_fptr == nullptr)
			{
				logger.error("Load LiteLoader.NET failed: {}", to_hex_string(rc));
				close_fptr(cxt);
				throw std::exception();
			}



			auto assemblies = GetAllAssemblies();

			struct managed_entry_args
			{
				void* pLogger;
				void* std_vector_assemblies;
			}
			args{ &logger,&assemblies };

			initAndLoadPlugins_fptr(&args, sizeof(managed_entry_args));
		}
	}

	logger.info("Loading .NET plugins...");
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
	GlobalClass::ManagedModuleHandler->TryAdd(LLNET_Asm, IntPtr(::LL::getPlugin(LLNET_LOADER_NAME)->handle));
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

	auto llLibPath_dotnet = Path::Combine(LLNET_LIBRARY_DIR_DOTNETONLY, assemblyName.Name + ".dll");
	if (File::Exists(llLibPath_dotnet))
	{
		return Assembly::LoadFrom(llLibPath_dotnet);
	}

	auto customPaths = GlobalClass::CustomLibPath[args->RequestingAssembly];
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

	return nullptr;
}


void LoadPlugins(std::vector<std::filesystem::path> const& assemblyPaths, Logger& logger)
{
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
	logger.info << count << " .NET plugin(s) loaded" << logger.endl;
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