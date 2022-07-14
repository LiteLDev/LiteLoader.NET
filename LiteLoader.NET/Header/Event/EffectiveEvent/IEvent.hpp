#pragma once
#include "../../../Main/.NETGlobal.hpp"

namespace LLNET::Event::Effective
{
	using namespace LLNET::Core;

	public interface class ICancellable
	{
	};

	public interface class IEvent
	{
		property bool IsCancelled {bool get();};
		void Cancel();
	};

	public ref class EventBase abstract : IEvent
	{
	private:
		bool isCancelled;
	public:
		property bool IsCancelled
		{
			bool get() { return isCancelled; }
		}
		
		void Cancel()
		{
			if (dynamic_cast<ICancellable^>(this) != nullptr)
				isCancelled = true;
			else
				throw gcnew LLNET::Core::CancelEventException;
		}
		
		void Call() 
		{
			EventManager::CallEvent(safe_cast<IEvent>(this));
		}
	};
}
