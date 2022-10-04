#include "PluginLoadContext.hpp"

namespace LLNET
{
	PluginLoadContext::PluginLoadContext(String^ pluginPath)
	{
		throw gcnew System::NotImplementedException;
	}

	Assembly^ PluginLoadContext::Load(AssemblyName^ assemblyName)
	{
		throw gcnew System::NotImplementedException;
	}

	IntPtr PluginLoadContext::LoadUnmanagedDll(String^ unmanagedDllName)
	{
		throw gcnew System::NotImplementedException;
	}
}