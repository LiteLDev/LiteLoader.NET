#pragma once
#include <LLAPI.h>
#include <Utils/Hash.h>
#include "../Main/.NETGlobal.hpp"
#include "../Tools/PropertryHelper.h"
#include "../Tools/clix.hpp"
namespace LLNET::LL
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

	public:
		Version(::LL::Version& v);
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
		Property_Enum(StatusEnum, ::LL::Version::Status, status, Status);

		operator ::LL::Version();

		::LL::Version* ToPointer();
		System::IntPtr ToIntPtr();

		String^ ToString() override;
		static Version^ parse(String^ str);

	private:
		::LL::Version* _this;
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
		Plugin(::LL::Plugin& p);
		Plugin(::LL::Plugin* p);
		~Plugin();

		Property_String(name, Name);
		Property_String(desc, Desc);
		Property_String(filePath, FilePath);
		property System::IntPtr Handler
		{
			System::IntPtr get()
			{
				return System::IntPtr(_this->handler);
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
					ret->Add(marshalString<Encoding::E_UTF8>(kv.first), marshalString<Encoding::E_UTF8>(kv.second));
				return ret;
			}
		} Property_Enum(PluginTypeEnum, ::LL::Plugin::PluginType, type, Type);

		// Get a Function by Symbol String
		generic<typename TDelegate>
		where TDelegate : System::Delegate inline TDelegate GetFunction(String^ functionName)
		{
			if (_this->handler == NULL)
				return TDelegate();
			void* address = GetProcAddress(_this->handler, marshalString<Encoding::E_UTF8>(functionName).c_str());
			if (!address)
				return TDelegate();
			return Marshal::GetDelegateForFunctionPointer<TDelegate>(System::IntPtr(address));
		}

	private:
		bool ownsNativeInstance;
		::LL::Plugin* _this;
	};

	public
	ref class LLAPI abstract
	{
	public:
		static String^ GetLoaderVersionString();
		static Version^ GetLoaderVersion();
		static bool IsDebugMode();

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
		inline static Plugin^ GetPlugin(System::IntPtr% handler);
		inline static Assembly^ GetPluginAssembly(String^ name);
		inline static Assembly^ GetPluginAssembly(Plugin^ plugin);

		inline static Dictionary<String^, Plugin^>^ GetAllPlugins(bool includeNativePlugin, bool includeScriptPlugin);
		inline static Dictionary<String^, Plugin^>^ GetAllPlugins(bool includeNativePlugin);
		inline static Dictionary<String^, Plugin^>^ GetAllPlugins();

		inline static bool HasPlugin(String^ name, bool includeNativePlugin, bool includeScriptPlugin);
		inline static bool HasPlugin(String^ name, bool includeNativePlugin);
		inline static bool HasPlugin(String^ name);
	};
} // namespace LLNET::LL