#pragma once
#include "include.hpp"

constexpr int LOWEST = 0;
constexpr int LOW = 1;
constexpr int NORMAL = 2;
constexpr int HIGH = 3;
constexpr int HIGHEST = 4;
constexpr int MONITOR = 5;

#define CALL_FUNCTIONS(_eventPriority)								\
	auto _eventPriority##funcs = functions[_eventPriority];			\
	for each (auto func in _eventPriority##funcs)					\
	{																\
		if (func.Item2)												\
			((void(*)(Object^))(void*)func.Item1)(ev);				\
		else														\
		{															\
			if (!ev->IsCancelled)									\
				((void(*)(Object^))(void*)func.Item1)(ev);			\
		}															\
	}




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
	private:

		using __IgnoreCancelled = bool;
		using __CallBackFunctionPointer = IntPtr;
		using __CallbackFunctionInfo = System::ValueTuple<__CallBackFunctionPointer, __IgnoreCancelled>;
		using __PermissionWithCallbackFunctions = array<List<__CallbackFunctionInfo>^>;
		using __EventId = size_t;
		using __EventManagerData = Dictionary<__EventId, __PermissionWithCallbackFunctions^>;

		using __EventIds = Dictionary<System::Type^, __EventId>;

		static __EventManagerData eventManagerData;
		static __EventIds eventIds;
		static System::Random rand;

	private:
		static void _registerEvent(System::Type^ eventType);
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
		auto eventAttrArr = eventType->GetCustomAttributes(EventAttribute::typeid, false);
		if (eventAttrArr->Length < 1)
			throw gcnew RegisterEventException("Missing EventAttribute!  at Event:<" + eventType->Name + ">");

		auto eventAttr = static_cast<EventAttribute^>(eventAttrArr[0]);
		auto eventId = eventAttr->Id;
		if (eventId == 0)
		{
			do
			{
				eventId = __EventId(rand.Next()) ^ __EventId(rand.Next() & 7);
			} while (!eventIds.ContainsValue(eventId));

			goto SKIP_CHECK;
		}

		if (eventIds.ContainsValue(eventId))
			throw gcnew RegisterEventException("EventId is already exists!  at Event:<" + eventType->Name + ">");

	SKIP_CHECK:

		eventIds.Add(eventType, eventId);
		eventManagerData.Add(eventId, gcnew __PermissionWithCallbackFunctions(6) { nullptr });
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

		auto listenerMethodDatas = gcnew List<System::ValueTuple<MethodInfo^, EventPriority, bool>>;

		for each (auto method in Methods)
		{
			auto evHandlerAttrArr = method->GetCustomAttributes(EventHandlerAttribute::typeid, false);
			if (evHandlerAttrArr->Length == 0)
				continue;
			else
			{
				if (!method->IsStatic)
					throw gcnew RegisterEventListenerException("Listener must be static!  at Listener:<" + listenerType->Name + "." + method->Name + ">");

				auto evHandlerAttr = static_cast<EventHandlerAttribute^>(evHandlerAttrArr[0]);
				listenerMethodDatas->Add(System::ValueTuple<MethodInfo^, EventPriority, bool>
				{
					method,
						evHandlerAttr->Priority,
						evHandlerAttr->IgnoreCancelled
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

			auto paramInterfaces = methodParam[0]->ParameterType->GetInterfaces();
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

			auto  eventType = methodParam[0]->ParameterType;

			if (!eventIds.ContainsKey(eventType))
				_registerEvent(eventType);

			auto eventId = eventIds[eventType];
			auto eventPriority = (int)methodData.Item2;

			auto callbackFuncArr = eventManagerData[eventId];

			if (callbackFuncArr[eventPriority] == nullptr)
				callbackFuncArr[eventPriority] = gcnew List<__CallbackFunctionInfo>;

			callbackFuncArr[eventPriority]->Add(__CallbackFunctionInfo(method->MethodHandle.GetFunctionPointer(), methodData.Item3));
		}
	}



	generic<typename TEvent> where TEvent : IEvent
		inline EventCode EventManager::CallEvent(TEvent ev)
	{
		auto eventType = TEvent::typeid;
		if (!eventIds.ContainsKey(eventType))
			return EventCode::UNREGISTERED;

		auto functions = eventManagerData[eventIds[eventType]];

		CALL_FUNCTIONS(LOWEST);
		CALL_FUNCTIONS(LOW);
		CALL_FUNCTIONS(NORMAL);
		CALL_FUNCTIONS(HIGH);
		CALL_FUNCTIONS(HIGHEST);
		CALL_FUNCTIONS(MONITOR);

		return EventCode::SUCCESS;
	}
}
