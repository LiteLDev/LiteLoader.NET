#pragma once

#include <src/Main/DotNETGlobal.hpp>
#include <src/Header/Event/IEvent.hpp>
#include <src/Header/Event/EventListener.hpp>

namespace LiteLoader::DynamicCommand
{
    interface class ICommand;
    ref class DynamicCommandInstance;
}

namespace LiteLoader::Schedule
{
    ref class ScheduleTask;
}

namespace LiteLoader::NET
{
    interface class IFunctionCaller;
}

namespace LiteLoader::RemoteCall::Helper
{
    ref struct ExportedFuncInstance;
    ref struct ImportedFuncInstance;
}


namespace LiteLoader::NET
{
    using LiteLoader::Event::IEvent;
    using LiteLoader::Event::INativeEventListener;
    using LiteLoader::DynamicCommand::DynamicCommandInstance;
    using LiteLoader::Schedule::ScheduleTask;
    using LiteLoader::RemoteCall::Helper::ExportedFuncInstance;
    using LiteLoader::RemoteCall::Helper::ImportedFuncInstance;

    using __HMODULE = nint_t;
    using __EventId = size_t;

    using __Hook = Delegate^;
    using __Address = nint_t;
    using __PHook = nint_t;
    using __POriginal = nint_t;

    private ref class PluginOwnData __static
    {

    public:

        static Dictionary<Assembly^, List<String^>^>^ CustomLibPath = gcnew Dictionary<Assembly^, List<String^>^>;
        static Dictionary<Assembly^, __HMODULE>^ ManagedAssemblyHandle = gcnew Dictionary<Assembly^, __HMODULE>;

        static Dictionary<__HMODULE, List<VALUE_TUPLE<__Hook, __Address, __PHook, __POriginal>>^>^ HookedFunction = gcnew Dictionary<__HMODULE, List<VALUE_TUPLE<__Hook, __Address, __PHook, __POriginal>>^>;
        static Dictionary<__HMODULE, List<VALUE_TUPLE<System::Type^, __EventId>>^>^ RegisteredEvent = gcnew Dictionary<__HMODULE, List<VALUE_TUPLE<System::Type^, __EventId>>^>;
        static Dictionary<__HMODULE, List<INativeEventListener^>^>^ SubscribedNativeEvent = gcnew Dictionary<__HMODULE, List<INativeEventListener^>^>;
        static Dictionary<__HMODULE, List<String^>^>^ RegisteredCommand = gcnew Dictionary<__HMODULE, List<String^>^>;
        static Dictionary<__HMODULE, List<VALUE_TUPLE<ScheduleTask^, GCHandle>>^>^ RegisteredSchedule = gcnew Dictionary<__HMODULE, List<VALUE_TUPLE<ScheduleTask^, GCHandle>>^>;

        static Dictionary<__HMODULE, List<ExportedFuncInstance^>^>^ ExportedRemoteCallFunctions = gcnew Dictionary<__HMODULE, List<ExportedFuncInstance^>^>;
        static Dictionary<__HMODULE, List<ImportedFuncInstance^>^>^ ImportedRemoteCallFunctions = gcnew Dictionary<__HMODULE, List<ImportedFuncInstance^>^>;

        static Dictionary<uint64_t, VALUE_TUPLE<__HMODULE, IFunctionCaller^>>^ RemoteCallData = gcnew Dictionary<uint64_t, VALUE_TUPLE<__HMODULE, IFunctionCaller^>>;


        static void AddHookedFunction(nint_t handle, __Hook hook, __Address address, __PHook pHook, __POriginal pOriginal);
        static void AddRegisteredEvent(nint_t handle, SystemType^ type, __EventId id);
        static void AddSubscribedNativeEvent(nint_t handle, INativeEventListener^ listener);
        static void AddRegisteredCommand(nint_t handle, String^ name);
        static void AddRegisteredSchedule(nint_t handle, ScheduleTask^ task, GCHandle gch);
        static void AddRemoteCallData(uint64_t hashVal, nint_t handle, IFunctionCaller^ funcHandle);
        static void AddExportedRemoteCallFunctions(nint_t handle, ExportedFuncInstance^ instance);
        static void AddImportedRemoteCallFunctions(nint_t handle, ImportedFuncInstance^ instance);
    };
}
