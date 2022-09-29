#include <LoggerAPI.h>
#include <LiteLoader.NET/Main/Config.hpp>
#include "coreclr_delegates.hpp"
#include "hostfxr.hpp"
#include "nethost.hpp"
#include <Utils/StringHelper.h>

//#define NETHOST_USE_AS_STATIC
#include "nethost.hpp"

#pragma comment(lib, "../SDK/Lib/SymDBHelper.lib")
#pragma comment(lib, "../SDK/Lib/LiteLoader.lib")
#pragma comment(lib, "../Lib/nethost.lib")




Logger logger(LLNET_INFO_LOADER_NAME);



enum StatusCode
{
	// Success
	_Success = 0,
	Success_HostAlreadyInitialized = 0x00000001,
	Success_DifferentRuntimeProperties = 0x00000002,

	// Failure
	InvalidArgFailure = 0x80008081,
	CoreHostLibLoadFailure = 0x80008082,
	CoreHostLibMissingFailure = 0x80008083,
	CoreHostEntryPointFailure = 0x80008084,
	CoreHostCurHostFindFailure = 0x80008085,
	// unused                           = 0x80008086,
	CoreClrResolveFailure = 0x80008087,
	CoreClrBindFailure = 0x80008088,
	CoreClrInitFailure = 0x80008089,
	CoreClrExeFailure = 0x8000808a,
	ResolverInitFailure = 0x8000808b,
	ResolverResolveFailure = 0x8000808c,
	LibHostCurExeFindFailure = 0x8000808d,
	LibHostInitFailure = 0x8000808e,
	// unused                           = 0x8000808f,
	LibHostExecModeFailure = 0x80008090,
	LibHostSdkFindFailure = 0x80008091,
	LibHostInvalidArgs = 0x80008092,
	InvalidConfigFile = 0x80008093,
	AppArgNotRunnable = 0x80008094,
	AppHostExeNotBoundFailure = 0x80008095,
	FrameworkMissingFailure = 0x80008096,
	HostApiFailed = 0x80008097,
	HostApiBufferTooSmall = 0x80008098,
	LibHostUnknownCommand = 0x80008099,
	LibHostAppRootFindFailure = 0x8000809a,
	SdkResolverResolveFailure = 0x8000809b,
	FrameworkCompatFailure = 0x8000809c,
	FrameworkCompatRetry = 0x8000809d,
	// unused                           = 0x8000809e,
	BundleExtractionFailure = 0x8000809f,
	BundleExtractionIOError = 0x800080a0,
	LibHostDuplicateProperty = 0x800080a1,
	HostApiUnsupportedVersion = 0x800080a2,
	HostInvalidState = 0x800080a3,
	HostPropertyNotFound = 0x800080a4,
	CoreHostIncompatibleConfig = 0x800080a5,
	HostApiUnsupportedScenario = 0x800080a6,
	HostFeatureDisabled = 0x800080a7,
};



void error_writer(const char_t* message)
{
	logger.warn("<hostfxr.dll>: {}", TextEncoding::fromUnicode(std::wstring(message)));
}



std::vector<std::filesystem::path> GetAllAssemblies();



void entry()
{
    logger.consoleLevel = 5;


    auto hostfxr_path = new char_t[MAX_PATH];
    size_t buffer_size = sizeof(char_t[MAX_PATH]) / sizeof(char_t);

	get_hostfxr_parameters get_hostfxr_params
	{
        sizeof(get_hostfxr_parameters),
        nullptr,
		nullptr
	};

    auto rc = (StatusCode)get_hostfxr_path(hostfxr_path, &buffer_size, &get_hostfxr_params);

    if (rc != StatusCode::_Success)
    {
        logger.warn("Cannot fine global .NET runtime, try using the local runtime.");
        get_hostfxr_params.dotnet_root = TEXT(DOTNET_RUNTIME_DIR);
        rc = (StatusCode)get_hostfxr_path(hostfxr_path, &buffer_size, &get_hostfxr_params);


        if (rc != StatusCode::_Success || hostfxr_path == nullptr)
        {
            logger.error("Cannot find .NET runtime!");
            throw std::exception();
        }
    }


    auto hostfxr_dll = LoadLibrary(hostfxr_path);

    delete[] hostfxr_path;

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


    if (set_error_writer_fptr(error_writer) != nullptr)
    {
        logger.warn("<hostfxr.dll>: Set error writer failed.");
    }


    load_assembly_and_get_function_pointer_fn load_assembly_and_get_function_pointer = nullptr;

    hostfxr_handle cxt = nullptr;


    rc = (StatusCode)init_fptr(TEXT(LLNET_RUNTIME_CONFIG_JSON_PATH), nullptr, &cxt);


    if (rc != 0 || cxt == nullptr)
    {
        logger.error("Init failed: {}", IntToHexStr(rc, true, false, false));
        close_fptr(cxt);
        throw std::exception();
    }

    rc = (StatusCode)get_delegate_fptr(
        cxt,
        hdt_load_assembly_and_get_function_pointer,
        reinterpret_cast<void**>(&load_assembly_and_get_function_pointer));

    if (rc != 0 || load_assembly_and_get_function_pointer == nullptr)
    {
        logger.error("Get delegate failed: {}", IntToHexStr(rc, true, false, false));
        close_fptr(cxt);
        throw std::exception();
    }



	void(*initAndLoadPlugins_fptr)(Logger*, std::vector<std::filesystem::path>*) = nullptr;

    rc = (StatusCode)load_assembly_and_get_function_pointer(
        std::filesystem::path(LLNET_LOADER_PATH).c_str(),
        TEXT(LLNET_MANAGED_ENTRY_CLASS),
        TEXT(LLNET_MANAGED_ENTRY_METHOD),
        TEXT(LLNET_MANAGED_ENTRY_DELEGATE_TYPE),
        nullptr,
        reinterpret_cast<void**>(&initAndLoadPlugins_fptr));


    if (rc != 0 || initAndLoadPlugins_fptr == nullptr)
    {
        logger.error("Load LiteLoader.NET failed: {}", IntToHexStr(rc, true, false, false));

        close_fptr(cxt);
        throw std::exception();
    }


    auto assemblies = GetAllAssemblies();

    initAndLoadPlugins_fptr(&logger, &assemblies);
}

extern "C" _declspec(dllexport) void onPostInit()
{
    entry();
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

