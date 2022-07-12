#pragma once
#include "include.hpp"

namespace LLNET::Event::Effective
{
	ref class EventManager sealed
	{
	public:
		generic<typename TEvent> where TEvent : IEvent
			void RegisterEvent();
		generic<typename TListener> where TListener : IEventListener
			void RegisterListener();
		generic<typename TEvent>where TEvent : IEvent
			void CallEvent(TEvent ev);
	private:
		Dictionary<size_t,List<int,EventCallbackHandler>
	};
}
