#pragma once
#include "../../../Main/.NETGlobal.hpp"

namespace LLNET::Event::Effective
{
	using namespace LLNET::Core;

	public interface class IEvent
	{
		property bool IsCancelled;
		void Cancell();
	};
}