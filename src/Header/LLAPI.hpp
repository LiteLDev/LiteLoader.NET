#pragma once
#include <LLAPI.h>
#include <Utils/Hash.h>
#include <src/Main/DotNETGlobal.hpp>
#include <src/Tools/PropertryHelper.hpp>
#include <src/Tools/clix.hpp>
namespace LiteLoader
{
    using namespace clix;

    public
    ref struct Version
    {
    public:
        enum class StatusEnum
        {
            Dev,
            Beta,
            Release
        };

    internal:
        Version(::ll::Version& v);
    public:
        Version();
        Version(int major);
        Version(int major, int minor);
        Version(int major, int minor, int revision);
        Version(int major, int minor, int revision, StatusEnum status);
        !Version();
        ~Version();

        static bool operator<(Version^ a, Version^ b);
        static bool operator==(Version^ a, Version^ b);
        static bool operator<=(Version^ a, Version^ b);
        static bool operator>(Version^ a, Version^ b);
        static bool operator>=(Version^ a, Version^ b);

        Property(int, major, Major);
        Property(int, minor, Minor);
        Property(int, revision, Revision);
        Property_Enum(StatusEnum, ::ll::Version::Status, status, Status);

    internal:
        operator ::ll::Version();
    public:
        ::ll::Version* ToPointer();
        nint_t ToIntPtr();

        String^ ToString() override;
        static Version^ Parse(String^ str);

    private:
        ::ll::Version* _this;
    };

    public
    ref struct Plugin
    {
    public:
        enum class PluginTypeEnum
        {
            DllPlugin,
            ScriptPlugin
        };

    public:
        bool IsManagedPlugin();

    public:
        Plugin(::ll::Plugin& p);
        Plugin(::ll::Plugin* p);
        ~Plugin();

        Property_String(name, Name);
        Property_String(desc, Desc);
        Property_String(filePath, FilePath);
        property nint_t Handler
        {
            nint_t get()
            {
                return nint_t(_this->handle);
            }
        }
        property Version^ version {
            Version^ get() { return gcnew Version(_this->version); }
        };
        property Dictionary<String^, String^>^
            Others {
            Dictionary<String^, String^>^ get() {
                auto len = (int)_this->others.size();
                auto ret = gcnew Dictionary<String^, String^>(len);
                for (auto& kv : _this->others)
                    ret->Add(marshalString(kv.first), marshalString(kv.second));
                return ret;
            }
        } Property_Enum(PluginTypeEnum, ::ll::Plugin::PluginType, type, Type);

        // Get a Function by Symbol String
        generic<typename TDelegate>
        where TDelegate : System::Delegate inline TDelegate GetFunction(String^ functionName)
        {
            if (_this->handle == NULL)
                return TDelegate();
            void* address = GetProcAddress(_this->handle, marshalString(functionName).c_str());
            if (!address)
                return TDelegate();
            return Marshal::GetDelegateForFunctionPointer<TDelegate>(nint_t(address));
        }

    private:
        bool ownsNativeInstance;
        ::ll::Plugin* _this;
    };

    public
    ref class LLAPI __static
    {
    public:
        property static String^ LoaderVersionString
        {
            String^ get();
        }
        property static Version^ LoaderVersion
        {
            Version^ get();
        }
        property static bool IsDebugMode
        {
            bool get();
        }

        static String^ GetDataPath(String^ pluginName);

        inline static bool RegisterPlugin(String^ name, String^ desc, System::Version^ version);
        inline static bool RegisterPlugin(String ^ name, String ^ desc, System::Version ^ version,
            String^ git, String^ license, String^ website);
        inline static bool RegisterPlugin(String ^ name, String ^ desc, System::Version ^ version,
            Dictionary<String^, String^>^ others);
        inline static bool RegisterPlugin(String^ name, String^ desc, Version^ version);
        inline static bool RegisterPlugin(String^ name, String^ desc, Version^ version,
            String^ git, String^ license, String^ website);
        inline static bool RegisterPlugin(String^ name, String^ desc, Version^ version,
            Dictionary<String^, String^>^ others);

        inline static Plugin^ GetPlugin(String^ name);
        inline static Plugin^ GetPlugin(String^ name, bool includeNativePlugin);
        inline static Plugin^ GetPlugin(String^ name, bool includeNativePlugin, bool includeScriptPlugin);
        inline static Plugin^ GetPlugin(nint_t% handle);
        inline static Assembly^ GetPluginAssembly(String^ name);
        inline static Assembly^ GetPluginAssembly(Plugin^ plugin);

        inline static Dictionary<String^, Plugin^>^ GetAllPlugins(bool includeNativePlugin, bool includeScriptPlugin);
        inline static Dictionary<String^, Plugin^>^ GetAllPlugins(bool includeNativePlugin);
        inline static Dictionary<String^, Plugin^>^ GetAllPlugins();

        inline static bool HasPlugin(String^ name, bool includeNativePlugin, bool includeScriptPlugin);
        inline static bool HasPlugin(String^ name, bool includeNativePlugin);
        inline static bool HasPlugin(String^ name);
    };
} // namespace LiteLoader