#pragma once
#include <LiteLoader.NET/Header/LLAPI.hpp>
namespace LiteLoader::NET {
    using namespace LiteLoader;
    private ref class PluginManager __static
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
