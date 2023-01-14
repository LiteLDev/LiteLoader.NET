#include "PluginOwnData.hpp"

namespace LiteLoader::NET
{
    inline void PluginOwnData::AddHookedFunction(nint_t handle, __Hook hook, __Address address, __PHook pHook, __POriginal pOriginal)
    {
        using HookedFunctionDataType = List<System::ValueTuple<Delegate^, nint_t, nint_t, nint_t>>;

        HookedFunctionDataType^ data = nullptr;

        if (LiteLoader::NET::PluginOwnData::HookedFunction->ContainsKey(handle))
        {
            data = LiteLoader::NET::PluginOwnData::HookedFunction[handle];
        }
        else
        {
            data = gcnew HookedFunctionDataType;
            LiteLoader::NET::PluginOwnData::HookedFunction->Add(handle, data);
        }

        data->Add(System::ValueTuple<Delegate^, nint_t, nint_t, nint_t>{
            hook,
                nint_t(address),
                nint_t(pHook),
                nint_t(pOriginal)});
    }

    void PluginOwnData::AddRegisteredEvent(nint_t handle, SystemType^ type, __EventId id)
    {
        using EventList = List<System::ValueTuple<System::Type^, __EventId>>;

        EventList^ events = nullptr;

        if (!LiteLoader::NET::PluginOwnData::RegisteredEvent->ContainsKey(handle))
        {
            events = gcnew EventList;
            LiteLoader::NET::PluginOwnData::RegisteredEvent->Add(handle, events);
        }
        else
        {
            events = LiteLoader::NET::PluginOwnData::RegisteredEvent[handle];
        }

        events->Add(System::ValueTuple<System::Type^, __EventId>(type, id));
    }

    void PluginOwnData::AddSubscribedNativeEvent(nint_t handle, INativeEventListener^ listener)
    {
        using NativeEventList = List<INativeEventListener^>;

        NativeEventList^ list = nullptr;

        if (!LiteLoader::NET::PluginOwnData::SubscribedNativeEvent->ContainsKey(handle))
        {
            list = gcnew NativeEventList;
            LiteLoader::NET::PluginOwnData::SubscribedNativeEvent->Add(handle, list);
        }
        else
        {
            list = LiteLoader::NET::PluginOwnData::SubscribedNativeEvent[handle];
        }

        list->Add(listener);
    }

    inline void PluginOwnData::AddRegisteredCommand(nint_t handle, String^ name)
    {
        List<String^>^ commands = nullptr;

        if (PluginOwnData::RegisteredCommand->ContainsKey(handle))
        {
            commands = PluginOwnData::RegisteredCommand[handle];
        }
        else
        {
            commands = gcnew List<String^>;
            PluginOwnData::RegisteredCommand->Add(handle, commands);
        }

        commands->Add(name);
    }

    void PluginOwnData::AddRegisteredSchedule(nint_t handle, ScheduleTask^ task, GCHandle gch)
    {
        List<VALUE_TUPLE<ScheduleTask^, GCHandle>>^ schedules = nullptr;

        if (LiteLoader::NET::PluginOwnData::RegisteredSchedule->ContainsKey(handle))
        {
            schedules = LiteLoader::NET::PluginOwnData::RegisteredSchedule[handle];
        }
        else
        {
            schedules = gcnew List<VALUE_TUPLE<ScheduleTask^, GCHandle>>;
            LiteLoader::NET::PluginOwnData::RegisteredSchedule->Add(handle, schedules);
        }

        schedules->Add(VALUE_TUPLE<ScheduleTask^, GCHandle>{task, gch});
    }

    void PluginOwnData::AddRemoteCallData(uint64_t hashVal, nint_t handle, IFunctionCaller^ funcHandle)
    {
        LiteLoader::NET::PluginOwnData::RemoteCallData->TryAdd(hashVal, VALUE_TUPLE<nint_t, IFunctionCaller^>(handle, funcHandle));
    }

    void PluginOwnData::AddExportedRemoteCallFunctions(nint_t handle, ExportedFuncInstance^ instance)
    {
        List<ExportedFuncInstance^>^ instances = nullptr;

        if (LiteLoader::NET::PluginOwnData::ExportedRemoteCallFunctions->ContainsKey(handle))
        {
            instances = LiteLoader::NET::PluginOwnData::ExportedRemoteCallFunctions[handle];
        }
        else
        {
            instances = gcnew List<ExportedFuncInstance^>;
            LiteLoader::NET::PluginOwnData::ExportedRemoteCallFunctions->Add(handle, instances);
        }

        instances->Add(instance);
    }
    
    void PluginOwnData::AddImportedRemoteCallFunctions(nint_t handle, ImportedFuncInstance^ instance)
    {
        List<ImportedFuncInstance^>^ instances = nullptr;

        if (LiteLoader::NET::PluginOwnData::ImportedRemoteCallFunctions->ContainsKey(handle))
        {
            instances = LiteLoader::NET::PluginOwnData::ImportedRemoteCallFunctions[handle];
        }
        else
        {
            instances = gcnew List<ImportedFuncInstance^>;
            LiteLoader::NET::PluginOwnData::ImportedRemoteCallFunctions->Add(handle, instances);
        }

        instances->Add(instance);
    }
}