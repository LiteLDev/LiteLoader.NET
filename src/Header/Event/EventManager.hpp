#pragma once
#include "include.hpp"
#include <src/Header/Logger/Logger.hpp>

constexpr int LOWEST = 0;
constexpr int LOW = 1;
constexpr int NORMAL = 2;
constexpr int HIGH = 3;
constexpr int HIGHEST = 4;
constexpr int MONITOR = 5;


constexpr int IS_NORMAL = 0;
constexpr int IS_INSTANCE = 64;
constexpr int IS_REF = 128;
constexpr int IS_IGNORECANCELLED = 256;
constexpr int IS_INSTANCE_AND_REF = IS_INSTANCE | IS_REF;
constexpr int IS_INSTANCE_AND_IGNORECANCELLED = IS_INSTANCE | IS_IGNORECANCELLED;
constexpr int IS_REF_AND_IGNORECANCELLED = IS_REF | IS_IGNORECANCELLED;
constexpr int IS_INSTANCE_AND_REF_AND_IGNORECANCELLED = IS_INSTANCE | IS_REF | IS_IGNORECANCELLED;


namespace LiteLoader::Event
{
    public ref class EventManager __static
    {
    internal:
        using __IgnoreCancelled = bool;
        using __IsRef = bool;
        using __IsInstance = bool;
        using __CallBackFunctionPointer = nint_t;
        using __ListenerType = System::Type;
        using __HMODULE = nint_t;
        using __CallbackFunctionInfo = System::ValueTuple<
            __CallBackFunctionPointer, __IgnoreCancelled, __IsRef, __IsInstance, __ListenerType^, __HMODULE>;
        using __PermissionWithCallbackFunctions = array<List<__CallbackFunctionInfo>^>;
        using __EventId = size_t;
        using __EventManagerData = Dictionary<__EventId, __PermissionWithCallbackFunctions^>;

        using __EventIds = Dictionary<System::Type^, __EventId>;

        static __EventManagerData eventManagerData;
        static __EventIds eventIds;
        static System::Random rand;
        static List<__EventId> initializedNativeEvents;
        static Logger::Logger^ logger = gcnew Logger::Logger(LLNET_INFO_LOADER_NAME);

    public:
        //public API
        generic <typename TListener> where TListener : IEventListener
        static void RegisterListener(__HMODULE handle);

        generic <typename TListener> where TListener : IEventListener
        static void RegisterListener();

        static void CallEvent(IEvent^ ev);

    private:
        static void _registerEvent(System::Type^ eventType);

        generic <typename TEvent> where TEvent : IEvent
        static void _callEvent(TEvent ev, List<__CallbackFunctionInfo>^* pfuncs);

        static bool _isNativeEventId(__EventId eventId);

    internal:
        generic <typename TEvent> where TEvent : IEvent
        static void _callNativeEvent(TEvent ev, __EventId eventId);

        generic <typename TEvent> where TEvent : IEvent
        static void _registerNativeEvent(__EventId id);
    };
}