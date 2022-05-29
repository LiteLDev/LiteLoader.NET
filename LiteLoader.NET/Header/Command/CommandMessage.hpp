#pragma once
#include <MC/CommandMessage.hpp>
#include "../MC/Types.hpp"

namespace MC {
	ref class CommandOrigin;
}

namespace MC 
{
	ref class CommandMessage
		:ClassTemplate<CommandMessage, ::CommandMessage> 
	{
		__ctor(CommandMessage, ::CommandMessage);
	public:
		CommandMessage^ Create();

		String^ GetMessage(CommandOrigin^ origin);
	};
}
