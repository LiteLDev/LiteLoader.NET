#pragma once

namespace LLNET::Event::Effective
{
	interface class IEvent;
}

namespace LLNET::Event::Effective
{
	generic<typename TEvent>
	where TEvent:IEvent

	public value class EventListener
	{
	private:
		int listenerId;
		bool deleted;
	public:
		EventListener(int listenerId)
			:listenerId(listenerId), deleted(false) {}
	};
}
