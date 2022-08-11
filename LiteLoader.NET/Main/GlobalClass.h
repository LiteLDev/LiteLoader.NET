#pragma once
#include ".NETGlobal.hpp"

namespace LLNET::Logger
{
	ref class Logger;
}

ref class GlobalClass {
internal:

	static Dictionary<Assembly^, List<String^>^>^ CustomLibPath = gcnew Dictionary<Assembly^, List<String^>^>;
	static Dictionary<Assembly^, IntPtr>^ ManagedModuleHandler = gcnew Dictionary<Assembly^, IntPtr>;
	static const String^ RUNTIME_SHARED_LIB_DIR;
	static const LLNET::Logger::Logger^ logger;
	static void Init();
	static GlobalClass() { Init(); }
	static HMODULE GetCurrentModule(Assembly^ asm_);
};

