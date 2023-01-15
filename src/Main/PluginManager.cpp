#include "PluginManager.hpp"
#include <src/Module/Core/Exceptions.hpp>
#include <src/Extra/PluginManager.hpp>
#include <llapi/utils/StringHelper.h>
#include "PluginOwnData.hpp"
#include <filesystem>

namespace LiteLoader::NET
{
    bool PluginManager::registerPlugin(System::String^ name, System::String^ introduction, Version^ version, Dictionary<System::String^, System::String^>^ others, Assembly^ Asm)
    {
        // remove LL auto registed plugin.
        unRegisterPlugin(Asm->GetName()->Name + ".dll");

        std::map<std::string, std::string> stdmap;
        if (others == nullptr)
            goto null;
        for each (auto % var in others)
            stdmap.emplace(marshalString(var.Key), marshalString(var.Value));
    null:
        auto _name = marshalString(name);

        auto plugin = ::ll::getPlugin(_name);
        HMODULE handle = nullptr;
        if (plugin != nullptr)
            handle = plugin->handle;
        else
        {
            handle = GetModuleHandle(str2wstr(marshalString(Asm->Location)).c_str());
        }
        if (handle == nullptr)
            handle = MODULE;

        auto ret = ::RegisterPlugin(handle, _name, marshalString(introduction), (::ll::Version)version, stdmap);
        if (ret)
        {
            PluginManager::ManagedPluginData->TryAdd(name, PluginTuple(gcnew Plugin(::ll::getPlugin(_name)), Asm));
            LiteLoader::NET::PluginOwnData::ManagedAssemblyHandle->TryAdd(Asm, nint_t(handle));
        }

        return ret;
    }
    Plugin^ PluginManager::getPlugin(nint_t handle)
    {
        auto pPlugin = ::ll::getPlugin((HMODULE)handle.ToPointer());
        if (pPlugin == nullptr)
            return nullptr;
        return gcnew Plugin(pPlugin);
    }
    Plugin^ PluginManager::getPlugin(System::String^ name, bool includeNativePlugin, bool includeScriptPlugin)
    {
        if (ManagedPluginData->ContainsKey(name))
        {
            auto ret = ManagedPluginData[name];
            return ret.Item1;
        }

        auto pPlugin = ::ll::getPlugin(marshalString(name));
        if (pPlugin == nullptr)
            return nullptr;
        if (!includeScriptPlugin && pPlugin->type == ::ll::Plugin::PluginType::ScriptPlugin)
            return nullptr;
        if (!includeNativePlugin && pPlugin->type == ::ll::Plugin::PluginType::DllPlugin)
            return nullptr;
        return gcnew Plugin(pPlugin);
    }
    Assembly^ PluginManager::getPluginAssembly(System::String^ name)
    {
        if (PluginManager::ManagedPluginData->ContainsKey(name))
            return PluginManager::ManagedPluginData[name].Item2;
        return nullptr;
    }
    Assembly^ PluginManager::getPluginAssembly(Plugin^ plugin)
    {
        if (!plugin->IsManagedPlugin())
            throw gcnew NativePluginException;
        for each (auto % var in PluginManager::ManagedPluginData)
        {
            if (var.Value.Item1->Equals(plugin))
                return var.Value.Item2;
        }
        return nullptr;
    }
    bool PluginManager::hasPlugin(System::String^ name, bool includeNativePlugin, bool includeScriptPlugin)
    {
        auto ret = false;
        ret = PluginManager::ManagedPluginData->ContainsKey(name);
        if (ret)
            return ret;
        auto pPlugin = ::ll::getPlugin(marshalString(name));
        if (pPlugin == nullptr)
            return false;
        if (!includeScriptPlugin && pPlugin->type == ::ll::Plugin::PluginType::ScriptPlugin)
            return false;
        if (!includeNativePlugin && pPlugin->type == ::ll::Plugin::PluginType::DllPlugin)
            return false;
        return true;
    }
    Dictionary<System::String^, Plugin^>^ PluginManager::getAllPlugins(bool includeNativePlugin, bool includeScriptPlugin)
    {
        auto ret = gcnew Dictionary<System::String^, Plugin^>;
        auto& PluginMap = ::ll::getAllPlugins();
        for (auto& kv : PluginMap)
        {
            switch (kv.second->type)
            {
            case ::ll::Plugin::PluginType::DllPlugin:
                if (includeNativePlugin)
                    ret->Add(marshalString(kv.first), gcnew Plugin(kv.second));
                break;
            case ::ll::Plugin::PluginType::ScriptPlugin:
                if (includeScriptPlugin)
                    ret->Add(marshalString(kv.first), gcnew Plugin(kv.second));
                break;
            }
        }
        return ret;
    }
    bool PluginManager::unRegisterPlugin(System::String^ name)
    {
        PluginManager::ManagedPluginData->Remove(name);
        return ::ll::PluginManager::unRegisterPlugin(marshalString(name));
    }
} // namespace LiteLoader::NET
