#pragma once
#include "include.hpp"
#include "LiteLoader.NET/Header/Logger.hpp"

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


namespace LLNET::Event::Effective
{
    ref class NativeEventIsCancelledManager sealed
    {
    internal:
        static bool current = false;

        inline static void set(bool isCancelled);
        inline static bool get();
    };

    public ref class EventManager abstract sealed
    {
    internal:
        using __IgnoreCancelled = bool;
        using __IsRef = bool;
        using __IsInstance = bool;
        using __CallBackFunctionPointer = IntPtr;
        using __ListenerType = System::Type;
        using __HMODULE = IntPtr;
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
        static Logger::Logger^ logger;

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
        generic <typename TEvent> where TEvent : IEvent, INativeEvent
        static void _callNativeEvent(TEvent% ev, __EventId eventId);

        generic <typename TEvent> where TEvent : IEvent, INativeEvent
        static void _registerNativeEvent(__EventId id);

        static void _setLogger(::Logger& logger);
    };
}


//#include "LLNETEvents.hpp"

namespace LLNET::Event::Effective
{
    inline bool EventManager::_isNativeEventId(__EventId eventId)
    {
        return 0 < eventId && eventId <= 128;
    }

    inline void EventManager::_registerEvent(System::Type^ eventType)
    {
        __EventId eventId = 0;

        do
        {
            eventId = static_cast<__EventId>(rand.Next()) ^ static_cast<__EventId>(rand.Next() & 7);
        }
        while (eventIds.ContainsValue(eventId) || _isNativeEventId(eventId));

        eventIds.TryAdd(eventType, eventId);
        eventManagerData.TryAdd(eventIds[eventType], gcnew __PermissionWithCallbackFunctions(6){nullptr});
    }


    generic <typename TEvent> where TEvent : IEvent, INativeEvent
    void EventManager::_registerNativeEvent(__EventId id)
    {
        eventIds.Add(TEvent::typeid, id);
        eventManagerData.Add(id, gcnew __PermissionWithCallbackFunctions(6){nullptr});
    }


    generic <typename TListener> where TListener : IEventListener
    void EventManager::RegisterListener()
    {
        RegisterListener<TListener>(IntPtr(GlobalClass::__GetCurrentModule(Assembly::GetCallingAssembly())));
    }


    generic <typename TListener> where TListener : IEventListener
    void EventManager::RegisterListener(__HMODULE handle)
    {
        using __IgnoreCancelled = bool;
        using __IsStatic = bool;
        using __IsByRef = bool;


        auto listenerType = TListener::typeid;
        auto Methods = listenerType->GetMethods(
            BindingFlags::Public |
            BindingFlags::NonPublic |
            BindingFlags::Static |
            BindingFlags::Instance);

        auto listenerMethodDatas = gcnew List<System::ValueTuple<
            MethodInfo^, EventPriority, __IgnoreCancelled, __IsStatic, __IsByRef>>;

        for each (auto method in Methods)
        {
            auto evHandlerAttrArr = method->GetCustomAttributes(EventHandlerAttribute::typeid, false);
            if (evHandlerAttrArr->Length == 0)
                continue;
            else
            {
                if (!method->IsStatic)
                {
                    auto defaultCtor = listenerType->GetConstructor(System::Array::Empty<System::Type^>());
                    if (defaultCtor == nullptr)
                        throw gcnew RegisterEventListenerException(
                            "Handler must be static or it's class must have default constructor!  at Handler:<" +
                            listenerType->Name + "." + method->Name + ">");
                }

                auto evHandlerAttr = static_cast<EventHandlerAttribute^>(evHandlerAttrArr[0]);
                listenerMethodDatas->Add(
                    System::ValueTuple<MethodInfo^, EventPriority, __IgnoreCancelled, __IsStatic, __IsByRef>
                    {
                        method,
                        evHandlerAttr->Priority,
                        evHandlerAttr->IgnoreCancelled,
                        !method->IsStatic,
                        false
                    });
            }
        }

        for each (auto methodData in listenerMethodDatas)
        {
            auto method = methodData.Item1;

            auto methodRetType = method->ReturnType;

            if (methodRetType != void::typeid)
                throw gcnew RegisterEventListenerException(
                    "Handler.ReturnType must be System.Void!  at Handler:<" + listenerType->Name + "." + method->Name +
                    ">");


            auto methodParam = method->GetParameters();

            if (methodParam->Length != 1)
                goto PARAM_CHECK_STEP1_FAILED;

            __IsRef isref = false;
            auto paramType = methodParam[0]->ParameterType;
            auto elementParamType = paramType;

            if (paramType->IsByRef)
            {
                isref = true;
                elementParamType = paramType->GetElementType();
            }

            auto paramInterfaces = elementParamType->GetInterfaces();
            for each (auto Interface in paramInterfaces)
            {
                if (Interface == IEvent::typeid)
                    goto PARAM_CHECK_STEP1_SUCCEED;
            }


        PARAM_CHECK_STEP1_FAILED:
            throw gcnew RegisterEventListenerException(
                "Handler can only have one parameter which the type is based on IEvent!  at Handler:<" + listenerType->
                Name + "." + method->Name + ">");

        PARAM_CHECK_STEP1_SUCCEED:

            if (!eventIds.ContainsKey(elementParamType))
                _registerEvent(elementParamType);

            auto eventId = eventIds[elementParamType];
            bool isNativeEventHandler = _isNativeEventId(eventId);

            if (isref)
            {
                methodData.Item5 = true;
            }
            else
            {
                if (isNativeEventHandler)
                {
                    throw gcnew RegisterEventListenerException(
                        "Parameter of the native event handler must be passed by reference (use 'in' or 'ref' keyword in C#)!  at Handler:<"
                        + listenerType->Name + "." + method->Name + ">");
                }
            }

            auto eventPriority = static_cast<int>(methodData.Item2);

            auto callbackFuncArr = eventManagerData[eventId];

            if (callbackFuncArr[eventPriority] == nullptr)
                callbackFuncArr[eventPriority] = gcnew List<__CallbackFunctionInfo>;

            callbackFuncArr[eventPriority]->Add(
                __CallbackFunctionInfo(
                    method->MethodHandle.GetFunctionPointer(),
                    methodData.Item3,
                    isref,
                    methodData.Item4,
                    methodData.Item4 ? listenerType : nullptr,
                    handle));

            if (isNativeEventHandler)
            {
                if (!initializedNativeEvents.Contains(eventId))
                    elementParamType
                        ->GetMethod("_init", BindingFlags::Static | BindingFlags::NonPublic)
                        ->Invoke(nullptr, System::Array::Empty<System::Type^>());
                initializedNativeEvents.Add(eventId);
            }
        }
    }

    inline void EventManager::CallEvent(IEvent^ ev)
    {
        for (auto eventType = ev->GetType(); eventType != EventBase::typeid && eventType != Object::typeid; eventType =
             eventType->BaseType)
        {
            if (!eventIds.ContainsKey(eventType))
                continue;

            auto funcs = eventManagerData[eventIds[eventType]];
            const pin_ptr<List<__CallbackFunctionInfo>^> pFuncs = &funcs[0];

            _callEvent(ev, pFuncs);
        }
    }

    generic <typename TEvent> where TEvent : IEvent
    void EventManager::_callEvent(TEvent ev, List<__CallbackFunctionInfo>^* pfuncs)
    {
        for (int i = 0; i < 6; i++)
        {
            auto funcs = pfuncs[i];
            if (funcs == nullptr)
                continue;

            for each (auto func in funcs)
            {
                String^ handlerName = func.Item1.ToString();

                int callingmode = (func.Item2 ? IS_IGNORECANCELLED : 0) | (func.Item3 ? IS_REF : 0) | (
                    func.Item4 ? IS_INSTANCE : 0);

                try
                {
                    switch (callingmode)
                    {
                    case IS_NORMAL:

                        static_cast<void(*)(TEvent)>(static_cast<void*>(func.Item1))(ev);
                        break;

                    case IS_INSTANCE:

                        static_cast<void(*)(Object^, TEvent)>(static_cast<void*>(func.Item1))(
                            System::Activator::CreateInstance(func.Item5), ev);
                        break;

                    case IS_REF:

                        static_cast<void(*)(TEvent%)>(static_cast<void*>(func.Item1))(ev);
                        break;

                    case IS_IGNORECANCELLED:

                        if (!ev->IsCancelled)
                            static_cast<void(*)(TEvent)>(static_cast<void*>(func.Item1))(ev);
                        break;

                    case IS_INSTANCE_AND_REF:

                        static_cast<void(*)(Object^, TEvent%)>(static_cast<void*>(func.Item1))(
                            System::Activator::CreateInstance(func.Item5), ev);
                        break;

                    case IS_INSTANCE_AND_IGNORECANCELLED:

                        if (!ev->IsCancelled)
                            static_cast<void(*)(Object^, TEvent)>(static_cast<void*>(func.Item1))(
                                System::Activator::CreateInstance(func.Item5), ev);
                        break;

                    case IS_REF_AND_IGNORECANCELLED:

                        if (!ev->IsCancelled)
                            static_cast<void(*)(TEvent%)>(static_cast<void*>(func.Item1))(ev);
                        break;

                    case IS_INSTANCE_AND_REF_AND_IGNORECANCELLED:

                        if (!ev->IsCancelled)
                            static_cast<void(*)(Object^, TEvent%)>(static_cast<void*>(func.Item1))(
                                System::Activator::CreateInstance(func.Item5), ev);
                        break;
                    }
                }
                catch (Exception^ ex)
                {
                    if (logger != nullptr)
                        logger->error->WriteLine(
                            "Exception thrown when handling an event:" + System::Environment::NewLine + ex);
                }
            }
        }
    }

    generic <typename TEvent> where TEvent : IEvent, INativeEvent
    void EventManager::_callNativeEvent(TEvent% ev, __EventId eventId)
    {
        auto functions = eventManagerData[eventId];
        pin_ptr<List<__CallbackFunctionInfo>^> pfunctions = &functions[0];

        return _callEvent(ev, pfunctions);
    }


    inline void NativeEventIsCancelledManager::set(bool isCancelled)
    {
        current = isCancelled;
    }

    inline bool NativeEventIsCancelledManager::get()
    {
        return current;
    }

    inline void EventBase::Call()
    {
        EventManager::CallEvent(this);
    }

    inline void EventManager::_setLogger(::Logger& value)
    {
        logger = gcnew Logger::Logger(marshalString(value.title));
    }
}
