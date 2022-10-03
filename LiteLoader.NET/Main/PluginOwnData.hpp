#pragma once

#include <LiteLoader.NET/Main/DotNETGlobal.hpp>

namespace LLNET
{
	private ref class PluginOwnData sealed
	{
		using __HMODULE = IntPtr;

	public:

		static Dictionary<Assembly^, List<String^>^>^ CustomLibPath = gcnew Dictionary<Assembly^, List<String^>^>;
		static Dictionary<Assembly^, __HMODULE>^ ManagedPluginHandle = gcnew Dictionary<Assembly^, IntPtr>;
	};
}
