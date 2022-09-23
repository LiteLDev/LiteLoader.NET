#pragma once
#include <mc/CommandMessage.hpp>
#include <LiteLoader.NET/Header/MC/Types.hpp>

namespace MC {
	ref class CommandOrigin;
}

namespace MC 
{
	public ref class CommandMessage
		:ClassTemplate<CommandMessage, ::CommandMessage> 
	{
	public:
		__ctor(CommandMessage, ::CommandMessage);
	public:
		CommandMessage();

		CommandMessage^ Create();

		String^ GetMessage(CommandOrigin^ origin);
	};
}
