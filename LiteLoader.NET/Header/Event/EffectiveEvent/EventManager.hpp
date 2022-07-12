#pragma once
#include "include.hpp"

namespace LLNET::Event::Effective
{
	public ref class EventManager sealed
	{
	public:
		generic<typename TEvent> where TEvent : IEvent
			static void RegisterEvent();
		generic<typename TListener> where TListener : IEventListener
			static void RegisterListener();
		generic<typename TEvent> where TEvent : IEvent
			static void CallEvent(TEvent ev);
	private:

		const int LOWEST = 0;
		const int LOW = 1;
		const int NORMAL = 2;
		const int HIGH = 3;
		const int HIGHEST = 4;
		const int MONITOR = 5;

		using CallBackFunctionPointer = IntPtr;
		using PermissionWithCallbackFunctions = array<List<CallBackFunctionPointer>^>;
		using EventId = size_t;
		using EventManagerData = Dictionary<EventId, PermissionWithCallbackFunctions^>;

		using EventIds = Dictionary<System::Type^, EventId>;

		static EventManagerData eventManagerData;
		static EventIds eventIds;
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
				eventId = EventId(rand.Next()) ^ EventId(rand.Next() & 7);
			} while (!eventIds.ContainsValue(eventId));

			goto SKIP_CHECK;
		}

		if (eventIds.ContainsValue(eventId))
			throw gcnew RegisterEventException("EventId is already exists!  at Event:<" + eventType->Name + ">");

	SKIP_CHECK:

		eventIds.Add(eventType, eventId);
		eventManagerData.Add(eventId, gcnew PermissionWithCallbackFunctions(6) { nullptr });
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
				callbackFuncArr[eventPriority] = gcnew List<CallBackFunctionPointer>;

			callbackFuncArr[eventPriority]->Add(method->MethodHandle.GetFunctionPointer());
		}
	}


	generic<typename TEvent> where TEvent : IEvent
		inline void EventManager::CallEvent(TEvent ev)
	{
		throw gcnew System::NotImplementedException();
	}
}
