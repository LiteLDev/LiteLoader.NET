#pragma once
#include "../Header/LLAPI.h"
namespace LLNET {
	using namespace LLNET::LL;
	private ref class PluginManager abstract
	{
	public:
		static bool registerPlugin(System::String^ name, System::String^ introduction,
			Version^ version, Dictionary<System::String^, System::String^>^ others, Assembly^ Asm);

		static Plugin^ getPlugin(System::IntPtr handle);
		static Plugin^ getPlugin(System::String^ name, bool includeNativePlugin, bool includeScriptPlugin);
		static Assembly^ getPluginAssembly(System::String^ name);
		static Assembly^ getPluginAssembly(Plugin^ plugin);
		static bool hasPlugin(System::String^ name, bool includeNativePlugin, bool includeScriptPlugin);
		static Dictionary<System::String^, Plugin^>^ getAllPlugins(bool includeNativePlugin, bool includeScriptPlugin);
		static bool unRegisterPlugin(System::String^ name);
	internal:
		using PluginTuple = System::Tuple< Plugin^, Assembly^>;
		static Dictionary<String^, PluginTuple^>^ ManagedPluginData = gcnew Dictionary<String^, PluginTuple^>;
	};
}


