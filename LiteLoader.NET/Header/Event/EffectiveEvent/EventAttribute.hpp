#pragma once
#include "include.hpp"
namespace LLNET::Event::Effective
{
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
