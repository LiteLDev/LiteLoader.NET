#include <src/Header/Event/EventManager.hpp>
#include <src/Main/PluginOwnData.hpp>


namespace LiteLoader::Event
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
        } while (eventIds.ContainsValue(eventId) || _isNativeEventId(eventId));

        eventIds.TryAdd(eventType, eventId);
        eventManagerData.TryAdd(eventIds[eventType], gcnew __PermissionWithCallbackFunctions(6) { nullptr });

        auto module = (IntPtr)GlobalClass::GetCurrentModule(eventType->Assembly);

        LiteLoader::NET::PluginOwnData::AddRegisteredEvent(module, eventType, eventId);
    }


    generic <typename TEvent> where TEvent : IEvent
        void EventManager::_registerNativeEvent(__EventId id)
    {
        eventIds.Add(TEvent::typeid, id);
        eventManagerData.Add(id, gcnew __PermissionWithCallbackFunctions(6) { nullptr });
    }


    generic <typename TListener> where TListener : IEventListener
        void EventManager::RegisterListener()
    {
        RegisterListener<TListener>(IntPtr(CALLING_MODULE));
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
                        throw gcnew LiteLoader::NET::RegisterEventListenerException(
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
                throw gcnew LiteLoader::NET::RegisterEventListenerException(
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
            throw gcnew LiteLoader::NET::RegisterEventListenerException(
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
                        if (!ev->IsCancelled)
                            static_cast<void(*)(TEvent)>(static_cast<void*>(func.Item1))(ev);
                        break;

                    case IS_INSTANCE:
                        if (!ev->IsCancelled)
                            static_cast<void(*)(Object^, TEvent)>(static_cast<void*>(func.Item1))(
                                System::Activator::CreateInstance(func.Item5), ev);
                        break;

                    case IS_REF:
                        if (!ev->IsCancelled)
                            static_cast<void(*)(TEvent%)>(static_cast<void*>(func.Item1))(ev);
                        break;

                    case IS_IGNORECANCELLED:
                        static_cast<void(*)(TEvent)>(static_cast<void*>(func.Item1))(ev);
                        break;

                    case IS_INSTANCE_AND_REF:
                        if (!ev->IsCancelled)
                            static_cast<void(*)(Object^, TEvent%)>(static_cast<void*>(func.Item1))(
                                System::Activator::CreateInstance(func.Item5), ev);
                        break;

                    case IS_INSTANCE_AND_IGNORECANCELLED:
                        static_cast<void(*)(Object^, TEvent)>(static_cast<void*>(func.Item1))(
                            System::Activator::CreateInstance(func.Item5), ev);
                        break;

                    case IS_REF_AND_IGNORECANCELLED:
                        static_cast<void(*)(TEvent%)>(static_cast<void*>(func.Item1))(ev);
                        break;

                    case IS_INSTANCE_AND_REF_AND_IGNORECANCELLED:
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

    generic <typename TEvent> where TEvent : IEvent
        void EventManager::_callNativeEvent(TEvent ev, __EventId eventId)
    {
        auto functions = eventManagerData[eventId];
        pin_ptr<List<__CallbackFunctionInfo>^> pfunctions = &functions[0];

        return _callEvent(ev, pfunctions);
    }


    inline void EventBase::Call()
    {
        EventManager::CallEvent(this);
    }
}
