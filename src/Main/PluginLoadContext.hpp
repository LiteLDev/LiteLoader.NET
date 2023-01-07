#pragma once
#include <src/Main/DotNETGlobal.hpp>

namespace LiteLoader::NET
{
    using System::Runtime::Loader::AssemblyLoadContext;
    using System::Runtime::Loader::AssemblyDependencyResolver;

    private ref class PluginLoadContext : AssemblyLoadContext
    {
    private:
        AssemblyDependencyResolver^ resolver;
        Assembly^ plugin;

    public:
        PluginLoadContext(String^ pluginPath);

    protected:
        virtual Assembly^ Load(AssemblyName^ assemblyName) override;
        virtual IntPtr LoadUnmanagedDll(String^ unmanagedDllName) override;
    };
}
