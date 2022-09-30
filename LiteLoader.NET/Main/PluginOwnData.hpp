#pragma once

#include <LiteLoader.NET/Main/DotNETGlobal.hpp>

namespace LLNET
{
	private ref class PluginOwnData sealed
	{
		static Dictionary<Assembly^, List<String^>^>^ CustomLibPath = gcnew Dictionary<Assembly^, List<String^>^>;
		static Dictionary<Assembly^, IntPtr>^ ManagedModuleHandler = gcnew Dictionary<Assembly^, IntPtr>;
	};
}
