#pragma once
namespace LLNET::Event::Effective
{
	public enum class EventPriority :int
	{
		LOWEST = 0,
		LOW = 1,
		NORMAL = 2,
		HIGH = 3,
		HIGHEST = 4,
		MONITOR = 5,
	};
	public interface class IEventListener
	{

	};
}
