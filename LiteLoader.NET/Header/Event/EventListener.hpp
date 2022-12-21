#pragma once
namespace LiteLoader::Event
{
	public enum class EventPriority : int
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

	private interface class INativeEventListener 
	{
		void Remove();
	};
}
