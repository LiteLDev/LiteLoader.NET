#include <LiteLoader.NET/Header/LLAPI.hpp>
#include <LiteLoader.NET/Main/PluginManager.hpp>

LLNET::LL::Version::Version(::ll::Version& v)
{
    _this = new ::ll::Version(std::move(v));
}

LLNET::LL::Version::Version()
{
    _this = new ::ll::Version;
}

LLNET::LL::Version::Version(int major)
{
    _this = new ::ll::Version(major);
}

LLNET::LL::Version::Version(int major, int minor)
{
    _this = new ::ll::Version(major, minor);
}

LLNET::LL::Version::Version(int major, int minor, int revision)
{
    _this = new ::ll::Version(major, minor, revision);
}

LLNET::LL::Version::Version(int major, int minor, int revision, StatusEnum status)
{
    _this = new ::ll::Version(major, minor, revision, ::ll::Version::Status(status));
}

LLNET::LL::Version::!Version()
{
    delete _this;
}

LLNET::LL::Version::~Version()
{
    this->!Version();
}

bool LLNET::LL::Version::operator<(Version^ a, Version^ b)
{
    return *a->_this < *b->_this;
}

bool LLNET::LL::Version::operator==(Version^ a, Version^ b)
{
    return *a->_this == *b->_this;
}

bool LLNET::LL::Version::operator<=(Version^ a, Version^ b)
{
    return a < b || a == b;
}

bool LLNET::LL::Version::operator>(Version^ a, Version^ b)
{
    return b < a;
}

bool LLNET::LL::Version::operator>=(Version^ a, Version^ b)
{
    return b < a || b == a;
}

LLNET::LL::Version::operator::ll::Version ()
{
    return *_this;
}

::ll::Version* LLNET::LL::Version::ToPointer()
{
    return _this;
}

System::IntPtr LLNET::LL::Version::ToIntPtr()
{
    return System::IntPtr((void*)_this);
}

System::String^ LLNET::LL::Version::ToString()
{
    return marshalString(_this->toString());
}

LLNET::LL::Version^ LLNET::LL::Version::Parse(System::String^ str)
{
    return gcnew Version(::ll::Version::parse(marshalString(str)));
}

System::String^ LLNET::LL::LLAPI::GetLoaderVersionString()
{
    return marshalString(::ll::getLoaderVersionString());
}

LLNET::LL::Version^ LLNET::LL::LLAPI::GetLoaderVersion()
{
    return gcnew Version(::ll::getLoaderVersion());
}

bool LLNET::LL::LLAPI::IsDebugMode()
{
    return ::ll::isDebugMode();
}

System::String^ LLNET::LL::LLAPI::GetDataPath(System::String^ pluginName)
{
    return marshalString(::ll::getDataPath(marshalString(pluginName)));
}

inline bool LLNET::LL::LLAPI::RegisterPlugin(System::String ^ name, System::String ^ desc, System::Version ^ version)
{
    return LLNET::LL::LLAPI::RegisterPlugin(name, desc, gcnew Version(version->Major, version->Minor, version->Build));
}

inline bool LLNET::LL::LLAPI::RegisterPlugin(System::String ^ name, System::String ^ desc, System::Version ^ version, System::String ^ git, System::String ^ license, System::String ^ website)
{
    return LLNET::LL::LLAPI::RegisterPlugin(name, desc, 
        gcnew Version(
            version->Major, 
            version->Minor, 
            version->Build
        ), git, license, website);
}

inline bool LLNET::LL::LLAPI::RegisterPlugin(System::String ^ name, System::String ^ desc, System::Version ^ version, Dictionary<String ^, String ^> ^ others)
{
    return LLNET::LL::LLAPI::RegisterPlugin(name, desc, gcnew Version(version->Major, version->Minor, version->Build), others);
}

inline bool LLNET::LL::LLAPI::RegisterPlugin(System::String^ name, System::String^ introduction, Version^ version)
{
    return PluginManager::registerPlugin(name, introduction, version, nullptr, Assembly::GetCallingAssembly());
}

inline bool LLNET::LL::LLAPI::RegisterPlugin(System::String^ name, System::String^ introduction, Version^ version, System::String^ git, System::String^ license, System::String^ website)
{
    auto others = gcnew Dictionary<String^, String^>;
    if (!String::IsNullOrEmpty(git)) others->Add("Git", git);
    if (!String::IsNullOrEmpty(license)) others->Add("License", license);
    if (!String::IsNullOrEmpty(website)) others->Add("Website", website);
    return PluginManager::registerPlugin(name, introduction, version, others, Assembly::GetCallingAssembly());
}

inline bool LLNET::LL::LLAPI::RegisterPlugin(System::String^ name, System::String^ introduction, Version^ version, Dictionary<String^, String^>^ others)
{
    return PluginManager::registerPlugin(name, introduction, version, others, Assembly::GetCallingAssembly());
}

inline LLNET::LL::Plugin^ LLNET::LL::LLAPI::GetPlugin(System::String^ name)
{
    return PluginManager::getPlugin(name, true, true);
}

inline LLNET::LL::Plugin^ LLNET::LL::LLAPI::GetPlugin(System::String^ name, bool includeNativePlugin)
{
    return PluginManager::getPlugin(name, includeNativePlugin, true);
}

inline LLNET::LL::Plugin^ LLNET::LL::LLAPI::GetPlugin(System::String^ name, bool includeNativePlugin, bool includeScriptPlugin)
{
    return PluginManager::getPlugin(name, includeNativePlugin, includeScriptPlugin);
}

inline LLNET::LL::Plugin^ LLNET::LL::LLAPI::GetPlugin(System::IntPtr% handle)
{
    return PluginManager::getPlugin(handle);
}

inline Assembly^ LLNET::LL::LLAPI::GetPluginAssembly(System::String^ name)
{
    return PluginManager::getPluginAssembly(name);
}

inline Assembly^ LLNET::LL::LLAPI::GetPluginAssembly(Plugin^ plugin)
{
    return PluginManager::getPluginAssembly(plugin);
}

inline Dictionary<String^, LLNET::LL::Plugin^>^ LLNET::LL::LLAPI::GetAllPlugins(bool includeNativePlugin, bool includeScriptPlugin)
{
    return PluginManager::getAllPlugins(includeNativePlugin, includeScriptPlugin);
}

inline Dictionary<String^, LLNET::LL::Plugin^>^ LLNET::LL::LLAPI::GetAllPlugins(bool includeNativePlugin)
{
    return GetAllPlugins(includeNativePlugin, true);
}

inline Dictionary<String^, LLNET::LL::Plugin^>^ LLNET::LL::LLAPI::GetAllPlugins()
{
    return GetAllPlugins(true, true);
}

inline bool LLNET::LL::LLAPI::HasPlugin(System::String^ name, bool includeNativePlugin, bool includeScriptPlugin)
{
    return PluginManager::hasPlugin(name, includeNativePlugin, includeScriptPlugin);
}

inline bool LLNET::LL::LLAPI::HasPlugin(System::String^ name, bool includeNativePlugin)
{
    return HasPlugin(name, includeNativePlugin, true);
}

inline bool LLNET::LL::LLAPI::HasPlugin(System::String^ name)
{
    return HasPlugin(name, true, true);
}

bool LLNET::LL::Plugin::IsManagedPlugin()
{
    return PluginManager::ManagedPluginData->ContainsKey(this->Name);
}

LLNET::LL::Plugin::Plugin(::ll::Plugin& p)
    :_this(new ::ll::Plugin(std::move(p))),
    ownsNativeInstance(true)
{
}

LLNET::LL::Plugin::Plugin(::ll::Plugin* p)
    : _this(p),
    ownsNativeInstance(false)
{
}

LLNET::LL::Plugin::~Plugin()
{
    if (ownsNativeInstance)
        delete _this;
}
