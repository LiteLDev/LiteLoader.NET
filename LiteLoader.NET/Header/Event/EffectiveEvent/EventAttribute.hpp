#pragma once
#include "include.hpp"
namespace LLNET::Event::Effective
{
	public ref class EventHandlerAttribute :System::Attribute
	{
	public:
		property EventPriority Priority;
		property bool IgnoreCancelled;
		property bool CanModifyEvent;
		EventHandlerAttribute()
		{
			Priority = EventPriority::NORMAL;
			IgnoreCancelled = false;
			CanModifyEvent = false;
		}
	};
}
