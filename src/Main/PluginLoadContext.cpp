#include "PluginLoadContext.hpp"

extern Assembly^ ResolveAssembly(Assembly^ requestingAssembly, AssemblyName% assemblyName);

namespace LiteLoader::NET
{
    PluginLoadContext::PluginLoadContext(String^ pluginPath)
    {
        resolver = gcnew AssemblyDependencyResolver(pluginPath);
        plugin = LoadFromAssemblyPath(pluginPath);
    }

    Assembly^ PluginLoadContext::Load(AssemblyName^ assemblyName)
    {
        Assembly^ ret = nullptr;

        ret = ResolveAssembly(plugin, *assemblyName);

        if (ret == nullptr)
        {
            auto path = resolver->ResolveAssemblyToPath(assemblyName);

            if (path != nullptr)
            {
                ret = LoadFromAssemblyPath(path);
            }
        }

        return ret;
    }

    nint_t PluginLoadContext::LoadUnmanagedDll(String^ unmanagedDllName)
    {
        using System::IO::File;
        using System::IO::Path;

        auto libraryPath = resolver->ResolveUnmanagedDllToPath(unmanagedDllName);

        if (libraryPath != nullptr)
        {
            return LoadUnmanagedDllFromPath(libraryPath);
        }
        else
        {
            auto path = Path::Combine(LITELOADER_LIBRARY_DIR, unmanagedDllName);
            if (File::Exists(path))
            {
                return LoadUnmanagedDllFromPath(path);
            }
        }

        return nint_t::Zero;
    }
}
