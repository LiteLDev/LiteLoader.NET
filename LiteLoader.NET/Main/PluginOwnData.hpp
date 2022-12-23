#pragma once

#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <LiteLoader.NET/Header/Hook/HookHelper.hpp>
#include <LiteLoader.NET/Header/Event/IEvent.hpp>
#include <LiteLoader.NET/Header/Event/EventListener.hpp>
//#include <LiteLoader.NET/Header/DynamicCommand/ICommand.hpp>

namespace LiteLoader::DynamicCommand
{
	interface class ICommand;
	ref class DynamicCommandInstance;
}

namespace LiteLoader::Schedule
{
	ref class ScheduleTask;
}


namespace LiteLoader::NET
{
	using LiteLoader::Event::IEvent;
	using LiteLoader::Event::INativeEventListener;
	using LiteLoader::DynamicCommand::DynamicCommandInstance;
	using LiteLoader::Schedule::ScheduleTask;

	using __HMODULE = IntPtr;
	using __EventId = size_t;

	using __Hook = Delegate^;
	using __Address = IntPtr;
	using __PHook = IntPtr;
	using __POriginal = IntPtr;

	private ref class PluginOwnData __static
	{

	public:

		static Dictionary<Assembly^, List<String^>^>^ CustomLibPath = gcnew Dictionary<Assembly^, List<String^>^>;
		static Dictionary<Assembly^, __HMODULE>^ ManagedAssemblyHandle = gcnew Dictionary<Assembly^, __HMODULE>;
		static Dictionary<__HMODULE, List<VALUE_TUPLE<__Hook, __Address, __PHook, __POriginal>>^>^ HookedFunction = gcnew Dictionary<__HMODULE, List<VALUE_TUPLE<__Hook, __Address, __PHook, __POriginal>>^>;
		static Dictionary<__HMODULE, List<VALUE_TUPLE<System::Type^, __EventId>>^>^ RegisteredEvent = gcnew Dictionary<__HMODULE, List<VALUE_TUPLE<System::Type^, __EventId>>^>;
		static Dictionary<__HMODULE, List<INativeEventListener^>^>^ SubscribedNativeEvent = gcnew Dictionary<__HMODULE, List<INativeEventListener^>^>;
		static Dictionary<__HMODULE, List<String^>^>^ RegisteredCommand = gcnew Dictionary<__HMODULE, List<String^>^>;
		static Dictionary<__HMODULE, List<VALUE_TUPLE<ScheduleTask^, GCHandle>>^>^ RegisteredSchedule = gcnew Dictionary<__HMODULE, List<VALUE_TUPLE<ScheduleTask^, GCHandle>>^>;
	};
}
