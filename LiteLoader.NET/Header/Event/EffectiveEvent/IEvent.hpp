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
		virtual property bool IsCancelled
		{
			bool get() { return isCancelled; }
		}
		
		virtual void Cancel()
		{
			if (dynamic_cast<ICancellable^>(this) != nullptr)
				isCancelled = true;
			else
				throw gcnew LLNET::Core::CancelEventException;
		}
		
		void Call();
	};
}
