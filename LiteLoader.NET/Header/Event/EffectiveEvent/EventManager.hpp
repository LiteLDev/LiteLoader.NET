#pragma once
#include "include.hpp"

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



#define CALL_FUNCTIONS(_eventPriority)								\
	auto _eventPriority##funcs = functions[_eventPriority];			\
	if(_eventPriority##funcs == nullptr)							\
		goto SKIP_CALL_##_eventPriority;							\
	for each (auto func in _eventPriority##funcs)					\
	{																\
		if(!func.Item3)												\
		{															\
			if (func.Item2)											\
				((void(*)(TEvent))(void*)func.Item1)(ev);			\
			else													\
			{														\
				if (!ev->IsCancelled)								\
					((void(*)(TEvent))(void*)func.Item1)(ev);		\
			}														\
		}															\
		else														\
		{															\
			if (func.Item2)											\
				((void(*)(TEvent%))(void*)func.Item1)(ev);			\
			else													\
			{														\
				if (!ev->IsCancelled)								\
					((void(*)(TEvent%))(void*)func.Item1)(ev);		\
			}														\
		}															\
	}																\
	SKIP_CALL_##_eventPriority:




namespace LLNET::Event::Effective
{
	public enum class EventCode
	{
		SUCCESS = 0,
		UNREGISTERED,
		UNKNOWN
	};

	public ref class EventManager sealed
	{
	public:
		generic<typename TEvent> where TEvent : IEvent
			static void RegisterEvent();
		generic<typename TListener> where TListener : IEventListener
			static void RegisterListener();
		generic<typename TEvent> where TEvent : IEvent
			static EventCode CallEvent(TEvent ev);
	internal:

		using __IgnoreCancelled = bool;
		using __IsRef = bool;
		using __IsInstance = bool;
		using __CallBackFunctionPointer = IntPtr;
		using __ListenerType = System::Type;
		using __CallbackFunctionInfo = System::ValueTuple<__CallBackFunctionPointer, __IgnoreCancelled, __IsRef, __IsInstance, __ListenerType^>;
		using __PermissionWithCallbackFunctions = array<List<__CallbackFunctionInfo>^>;
		using __EventId = size_t;
		using __EventManagerData = Dictionary<__EventId, __PermissionWithCallbackFunctions^>;

		using __EventIds = Dictionary<System::Type^, __EventId>;

		static __EventManagerData eventManagerData;
		static __EventIds eventIds;
		static System::Random rand;

	private:
		static void _registerEvent(System::Type^ eventType);
	internal:
		generic<typename TEvent> where TEvent : IEvent, INativeEvent
			static void RegisterEventInternal(__EventId id);
	};
}






namespace LLNET::Event::Effective
{
	generic<typename TEvent> where TEvent : IEvent
		inline void EventManager::RegisterEvent()
	{
		_registerEvent(TEvent::typeid);
	}

	void EventManager::_registerEvent(System::Type^ eventType)
	{
		__EventId eventId = 0;

	RE_GENERATE_EVENTID:
		do
		{
			eventId = __EventId(rand.Next()) ^ __EventId(rand.Next() & 7);
		} while (eventIds.ContainsValue(eventId));

		if (0 < eventId && eventId <= 128)
		{
			goto RE_GENERATE_EVENTID;
		}

		eventIds.Add(eventType, eventId);
		eventManagerData.Add(eventId, gcnew __PermissionWithCallbackFunctions(6) { nullptr });
	}

	generic<typename TEvent> where TEvent : IEvent, INativeEvent
		inline void EventManager::RegisterEventInternal(__EventId id)
	{
		eventIds.Add(TEvent::typeid, id);
		eventManagerData.Add(id, gcnew __PermissionWithCallbackFunctions(6) { nullptr });
	}


	generic<typename TListener> where TListener : IEventListener
		inline void EventManager::RegisterListener()
	{
		auto listenerType = TListener::typeid;
		auto Methods = listenerType->GetMethods(
			BindingFlags::Public |
			BindingFlags::NonPublic |
			BindingFlags::Static |
			BindingFlags::Instance);

		auto listenerMethodDatas = gcnew List<System::ValueTuple<MethodInfo^, EventPriority, bool, bool>>;

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
						throw gcnew RegisterEventListenerException("Listener must be static or it's class must have default constructor!");
				}

				auto evHandlerAttr = static_cast<EventHandlerAttribute^>(evHandlerAttrArr[0]);
				listenerMethodDatas->Add(System::ValueTuple<MethodInfo^, EventPriority, bool, bool>
				{
					method,
						evHandlerAttr->Priority,
						evHandlerAttr->IgnoreCancelled,
						!method->IsStatic
				});
			}
		}

		for each (auto methodData in listenerMethodDatas)
		{
			auto method = methodData.Item1;

			auto methodRetType = method->ReturnType;

			if (methodRetType != void::typeid)
				throw gcnew RegisterEventListenerException("Listener.ReturnType must be System.Void!  at Listener:<" + listenerType->Name + "." + method->Name + ">");


			auto methodParam = method->GetParameters();

			if (methodParam->Length != 1)
				goto PARAM_CHECK_FAILED;

			__IsRef isref = false;
			auto paramType = methodParam[0]->ParameterType;

			if (paramType->IsByRef)
			{
				isref = true;
				paramType = paramType->GetElementType();
			}

			auto paramInterfaces = paramType->GetInterfaces();
			for each (auto Interface in paramInterfaces)
			{
				if (Interface == IEvent::typeid)
					goto PARAM_CHECK_SUCCEED;
			}

			{
			PARAM_CHECK_FAILED:
				throw gcnew RegisterEventListenerException("Listener can only have one parameter which the type is based on IEvent!  at Listener:<" + listenerType->Name + "." + method->Name + ">");
			}
		PARAM_CHECK_SUCCEED:

			if (!eventIds.ContainsKey(paramType))
				_registerEvent(paramType);

			auto eventId = eventIds[paramType];
			auto eventPriority = (int)methodData.Item2;

			auto callbackFuncArr = eventManagerData[eventId];

			if (callbackFuncArr[eventPriority] == nullptr)
				callbackFuncArr[eventPriority] = gcnew List<__CallbackFunctionInfo>;

			callbackFuncArr[eventPriority]->Add(__CallbackFunctionInfo(method->MethodHandle.GetFunctionPointer(), methodData.Item3, isref, methodData.Item4, methodData.Item4 ? listenerType : nullptr));
		}
	}



	generic<typename TEvent> where TEvent : IEvent
		inline EventCode EventManager::CallEvent(TEvent ev)
	{
		auto eventType = TEvent::typeid;
		if (!eventIds.ContainsKey(eventType))
			return EventCode::UNREGISTERED;

		auto functions = eventManagerData[eventIds[eventType]];
		pin_ptr<List<__CallbackFunctionInfo>^> pfunctions = &functions[0];

		for (int i = 0; i < 6; i++)
		{
			auto funcs = pfunctions[i];
			if (funcs == nullptr)
				continue;
			for each (auto func in funcs)
			{
				int callingmode = (func.Item2 ? IS_IGNORECANCELLED : 0) | (func.Item3 ? IS_REF : 0) | (func.Item4 ? IS_INSTANCE : 0);
				switch (callingmode)
				{
				case NORMAL:

					((void(*)(TEvent))(void*)func.Item1)(ev);
					break;

				case IS_INSTANCE:

					((void(*)(Object^, TEvent))(void*)func.Item1)(System::Activator::CreateInstance(func.Item5), ev);
					break;

				case IS_REF:

					((void(*)(TEvent%))(void*)func.Item1)(ev);
					break;

				case IS_IGNORECANCELLED:

					if (!ev->IsCancelled)
						((void(*)(TEvent))(void*)func.Item1)(ev);
					break;

				case IS_INSTANCE_AND_REF:

					((void(*)(Object^, TEvent%))(void*)func.Item1)(System::Activator::CreateInstance(func.Item5), ev);
					break;

				case IS_INSTANCE_AND_IGNORECANCELLED:

					if (!ev->IsCancelled)
						((void(*)(Object^, TEvent))(void*)func.Item1)(System::Activator::CreateInstance(func.Item5), ev);
					break;

				case IS_REF_AND_IGNORECANCELLED:

					if (!ev->IsCancelled)
						((void(*)(TEvent%))(void*)func.Item1)(ev);
					break;

				case IS_INSTANCE_AND_REF_AND_IGNORECANCELLED:

					if (!ev->IsCancelled)
						((void(*)(Object^, TEvent%))(void*)func.Item1)(System::Activator::CreateInstance(func.Item5), ev);
					break;
				}
			}
		}


		return EventCode::SUCCESS;
	}
}
