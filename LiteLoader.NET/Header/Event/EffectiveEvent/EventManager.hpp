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
		generic<typename TEvent>where TEvent : IEvent
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
	};
}






namespace LLNET::Event::Effective
{
	generic<typename TEvent>
	inline void EventManager::RegisterEvent()
	{
		auto eventType = TEvent::typeid;
		auto eventAttrArr = eventType->GetCustomAttributes(EventAttribute::typeid, false);
		if (eventAttrArr == nullptr || eventAttrArr->Length < 1)
			throw gcnew RegisterEventException("Missing EventAttribute!");

		auto eventAttr = static_cast<EventAttribute^>(eventAttrArr[0]);
		auto currentEventId = eventAttr->Id != 0 ? eventAttr->Id : EventId(eventIds.Count) + 1;
		eventIds.Add(eventType, currentEventId);

		eventManagerData.Add(currentEventId, gcnew PermissionWithCallbackFunctions(6) { nullptr });
	}


	generic<typename TListener>
	inline void EventManager::RegisterListener()
	{
		throw gcnew System::NotImplementedException();
	}


	generic<typename TEvent>
	inline void EventManager::CallEvent(TEvent ev)
	{
		throw gcnew System::NotImplementedException();
	}
}
