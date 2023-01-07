#include <src/Header/LLAPI.hpp>
#include <src/Main/PluginManager.hpp>

LiteLoader::Version::Version(::ll::Version& v)
{
    _this = new ::ll::Version(std::move(v));
}

LiteLoader::Version::Version()
{
    _this = new ::ll::Version;
}

LiteLoader::Version::Version(int major)
{
    _this = new ::ll::Version(major);
}

LiteLoader::Version::Version(int major, int minor)
{
    _this = new ::ll::Version(major, minor);
}

LiteLoader::Version::Version(int major, int minor, int revision)
{
    _this = new ::ll::Version(major, minor, revision);
}

LiteLoader::Version::Version(int major, int minor, int revision, StatusEnum status)
{
    _this = new ::ll::Version(major, minor, revision, ::ll::Version::Status(status));
}

LiteLoader::Version::!Version()
{
    delete _this;
}

LiteLoader::Version::~Version()
{
    this->!Version();
}

bool LiteLoader::Version::operator<(Version^ a, Version^ b)
{
    return *a->_this < *b->_this;
}

bool LiteLoader::Version::operator==(Version^ a, Version^ b)
{
    return *a->_this == *b->_this;
}

bool LiteLoader::Version::operator<=(Version^ a, Version^ b)
{
    return a < b || a == b;
}

bool LiteLoader::Version::operator>(Version^ a, Version^ b)
{
    return b < a;
}

bool LiteLoader::Version::operator>=(Version^ a, Version^ b)
{
    return b < a || b == a;
}

LiteLoader::Version::operator::ll::Version ()
{
    return *_this;
}

::ll::Version* LiteLoader::Version::ToPointer()
{
    return _this;
}

System::IntPtr LiteLoader::Version::ToIntPtr()
{
    return System::IntPtr((void*)_this);
}

System::String^ LiteLoader::Version::ToString()
{
    return marshalString(_this->toString());
}

LiteLoader::Version^ LiteLoader::Version::Parse(System::String^ str)
{
    return gcnew Version(::ll::Version::parse(marshalString(str)));
}

System::String^ LiteLoader::LLAPI::GetLoaderVersionString()
{
    return marshalString(::ll::getLoaderVersionString());
}

LiteLoader::Version^ LiteLoader::LLAPI::GetLoaderVersion()
{
    return gcnew Version(::ll::getLoaderVersion());
}

bool LiteLoader::LLAPI::IsDebugMode()
{
    return ::ll::isDebugMode();
}

System::String^ LiteLoader::LLAPI::GetDataPath(System::String^ pluginName)
{
    return marshalString(::ll::getDataPath(marshalString(pluginName)));
}

inline bool LiteLoader::LLAPI::RegisterPlugin(System::String ^ name, System::String ^ desc, System::Version ^ version)
{
    return LiteLoader::LLAPI::RegisterPlugin(name, desc, gcnew Version(version->Major, version->Minor, version->Build));
}

inline bool LiteLoader::LLAPI::RegisterPlugin(System::String ^ name, System::String ^ desc, System::Version ^ version, System::String ^ git, System::String ^ license, System::String ^ website)
{
    return LiteLoader::LLAPI::RegisterPlugin(name, desc, 
        gcnew Version(
            version->Major, 
            version->Minor, 
            version->Build
        ), git, license, website);
}

inline bool LiteLoader::LLAPI::RegisterPlugin(System::String ^ name, System::String ^ desc, System::Version ^ version, Dictionary<String ^, String ^> ^ others)
{
    return LiteLoader::LLAPI::RegisterPlugin(name, desc, gcnew Version(version->Major, version->Minor, version->Build), others);
}

inline bool LiteLoader::LLAPI::RegisterPlugin(System::String^ name, System::String^ introduction, Version^ version)
{
    return LiteLoader::NET::PluginManager::registerPlugin(name, introduction, version, nullptr, Assembly::GetCallingAssembly());
}

inline bool LiteLoader::LLAPI::RegisterPlugin(System::String^ name, System::String^ introduction, Version^ version, System::String^ git, System::String^ license, System::String^ website)
{
    auto others = gcnew Dictionary<String^, String^>;
    if (!String::IsNullOrEmpty(git)) others->Add("Git", git);
    if (!String::IsNullOrEmpty(license)) others->Add("License", license);
    if (!String::IsNullOrEmpty(website)) others->Add("Website", website);
    return LiteLoader::NET::PluginManager::registerPlugin(name, introduction, version, others, Assembly::GetCallingAssembly());
}

inline bool LiteLoader::LLAPI::RegisterPlugin(System::String^ name, System::String^ introduction, Version^ version, Dictionary<String^, String^>^ others)
{
    return LiteLoader::NET::PluginManager::registerPlugin(name, introduction, version, others, Assembly::GetCallingAssembly());
}

inline LiteLoader::Plugin^ LiteLoader::LLAPI::GetPlugin(System::String^ name)
{
    return LiteLoader::NET::PluginManager::getPlugin(name, true, true);
}

inline LiteLoader::Plugin^ LiteLoader::LLAPI::GetPlugin(System::String^ name, bool includeNativePlugin)
{
    return LiteLoader::NET::PluginManager::getPlugin(name, includeNativePlugin, true);
}

inline LiteLoader::Plugin^ LiteLoader::LLAPI::GetPlugin(System::String^ name, bool includeNativePlugin, bool includeScriptPlugin)
{
    return LiteLoader::NET::PluginManager::getPlugin(name, includeNativePlugin, includeScriptPlugin);
}

inline LiteLoader::Plugin^ LiteLoader::LLAPI::GetPlugin(System::IntPtr% handle)
{
    return LiteLoader::NET::PluginManager::getPlugin(handle);
}

inline Assembly^ LiteLoader::LLAPI::GetPluginAssembly(System::String^ name)
{
    return LiteLoader::NET::PluginManager::getPluginAssembly(name);
}

inline Assembly^ LiteLoader::LLAPI::GetPluginAssembly(Plugin^ plugin)
{
    return LiteLoader::NET::PluginManager::getPluginAssembly(plugin);
}

inline Dictionary<String^, LiteLoader::Plugin^>^ LiteLoader::LLAPI::GetAllPlugins(bool includeNativePlugin, bool includeScriptPlugin)
{
    return LiteLoader::NET::PluginManager::getAllPlugins(includeNativePlugin, includeScriptPlugin);
}

inline Dictionary<String^, LiteLoader::Plugin^>^ LiteLoader::LLAPI::GetAllPlugins(bool includeNativePlugin)
{
    return GetAllPlugins(includeNativePlugin, true);
}

inline Dictionary<String^, LiteLoader::Plugin^>^ LiteLoader::LLAPI::GetAllPlugins()
{
    return GetAllPlugins(true, true);
}

inline bool LiteLoader::LLAPI::HasPlugin(System::String^ name, bool includeNativePlugin, bool includeScriptPlugin)
{
    return LiteLoader::NET::PluginManager::hasPlugin(name, includeNativePlugin, includeScriptPlugin);
}

inline bool LiteLoader::LLAPI::HasPlugin(System::String^ name, bool includeNativePlugin)
{
    return HasPlugin(name, includeNativePlugin, true);
}

inline bool LiteLoader::LLAPI::HasPlugin(System::String^ name)
{
    return HasPlugin(name, true, true);
}

bool LiteLoader::Plugin::IsManagedPlugin()
{
    return LiteLoader::NET::PluginManager::ManagedPluginData->ContainsKey(this->Name);
}

LiteLoader::Plugin::Plugin(::ll::Plugin& p)
    :_this(new ::ll::Plugin(std::move(p))),
    ownsNativeInstance(true)
{
}

LiteLoader::Plugin::Plugin(::ll::Plugin* p)
    : _this(p),
    ownsNativeInstance(false)
{
}

LiteLoader::Plugin::~Plugin()
{
    if (ownsNativeInstance)
        delete _this;
}
