#include "DotNETGlobal.hpp"

#include <src/Header/Logger/Logger.hpp>
#include "PluginOwnData.hpp"

inline void GlobalClass::Init()
{
    using namespace System::Text::RegularExpressions;
    using namespace System::IO;

    logger = gcnew LiteLoader::Logger::Logger(LLNET_INFO_LOADER_NAME);

    auto runtimeLibPathDir = DOTNET_RUNTIME_DIR + "/shared/Microsoft.NETCore.App";
    if (!Directory::Exists(runtimeLibPathDir))
    {
        goto SHARED_LIBRARY_NOT_FOUND_WARNING;
    }

    auto dirs = Directory::GetDirectories(runtimeLibPathDir);

    for each (auto var in dirs)
    {
        var = var->Replace("\\", "/");

        auto arr = var->Split(L'/');

        if (arr->Length > 0 && arr[arr->Length - 1]->StartsWith("7.0."))
        {
            if (File::Exists(Path::Combine(var, "coreclr.dll")))
            {
                RUNTIME_SHARED_LIB_DIR = var;
                return;
            }
        }
    }


SHARED_LIBRARY_NOT_FOUND_WARNING:

    logger->warn->WriteLine(".NET shared library not found!");
}

inline HMODULE GlobalClass::GetCurrentModule(Assembly^ asm_)
{
    auto ret = IntPtr::Zero;
    if (LiteLoader::NET::PluginOwnData::ManagedAssemblyHandle->TryGetValue(asm_, ret) && ret != IntPtr::Zero)
        return HMODULE(ret.ToPointer());
    else
        return MODULE;
}
