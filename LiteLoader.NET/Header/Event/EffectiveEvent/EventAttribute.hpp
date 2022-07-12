#pragma once
#include "include.hpp"
namespace LLNET::Event::Effective
{
	public ref class EventAttribute :System::Attribute
	{
	private:
		size_t id;
	public:
		property size_t Id {size_t get() { return id; }};
		EventAttribute(size_t id)
			:id(id) {}
		EventAttribute()
			:id(0) {}
	};

	public ref class EventHandlerAttribute :System::Attribute
	{
	public:
		property EventPriority Priority;
		property bool IgnoreCancelled;
		EventHandlerAttribute()
		{
			Priority = EventPriority::NORMAL;
			IgnoreCancelled = false;
		}
	};
}
