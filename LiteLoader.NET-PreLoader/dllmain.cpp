#include <LLAPI.h>
#include <I18nAPI.h>
#include "Version.h"
#include <LoggerAPI.h>
#include <LiteLoader.NET/Main/Config.h>
#include "hostfxr.h"
#include "coreclr_delegates.h"
#include "nethost.h"

#pragma comment(lib, "../SDK/Lib/SymDBHelper.lib")
#pragma comment(lib, "../SDK/Lib/LiteLoader.lib")

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

Logger logger(LLNET_LOADER_NAME);

void error_writer(const char_t* message)
{
	logger.warn("hostfxr: {}", TextEncoding::fromUnicode(std::wstring(message)));
}

std::vector<std::filesystem::path> GetAllAssemblies();

extern "C" _declspec(dllexport) void onPostInit()
{


	if (!std::filesystem::exists(DOTNET_RUNTIME_DIR))
	{
		logger.error("Cannot find local .NET runtime!");
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

		auto set_error_writer_fptr = reinterpret_cast<hostfxr_set_error_writer_fn>(
			GetProcAddress(hostfxr_dll, "hostfxr_set_error_writer"));



		if (init_fptr == nullptr || get_delegate_fptr == nullptr || close_fptr == nullptr || set_error_writer_fptr == nullptr)
		{
			logger.error("Cannot get exported function from <hostfxr.dll>!");
			throw std::exception();
		}



		auto fptr = set_error_writer_fptr(error_writer);

		if (fptr != nullptr)
		{
			logger.warn("QAQ");
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
			TEXT("LLNET.__Entry.EntryPropotype"),
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

