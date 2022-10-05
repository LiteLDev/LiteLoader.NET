#include "PluginLoadContext.hpp"

extern Assembly^ ResolveAssembly(Assembly^ requestingAssembly, AssemblyName% assemblyName);

namespace LLNET
{
	PluginLoadContext::PluginLoadContext(String^ pluginPath)
	{
		resolver = gcnew AssemblyDependencyResolver(pluginPath);
		plugin = LoadFromAssemblyPath(pluginPath);
	}

	Assembly^ PluginLoadContext::Load(AssemblyName^ assemblyName)
	{
		return ResolveAssembly(plugin, *assemblyName);
	}

	IntPtr PluginLoadContext::LoadUnmanagedDll(String^ unmanagedDllName)
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

		return IntPtr::Zero;
	}
}