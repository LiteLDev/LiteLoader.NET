#pragma once
#include "../../../Main/.NETGlobal.hpp"

namespace LLNET::Event::Effective
{
	using namespace LLNET::Core;

	public interface class ICancellable
	{
		property bool IsCancelled;
	};

	public interface class IEvent
	{
		property bool IsCancelled;
	};

	public ref class EventBase abstract : IEvent
	{
		bool isCancelled;

	public:
		virtual property bool IsCancelled
		{
			bool get() { return isCancelled; }
			void set(const bool value)
			{
				if (dynamic_cast<ICancellable^>(this) == nullptr)
					throw gcnew CancelEventException;

				isCancelled = value;
			}
		}
		
		void Call();
	};
}
