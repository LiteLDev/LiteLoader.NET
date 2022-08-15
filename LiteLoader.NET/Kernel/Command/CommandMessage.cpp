#include <LiteLoader.NET/Header/Command/CommandMessage.hpp>
#include <LiteLoader.NET/Header/Command/CommandOrigin.hpp>

namespace MC
{
	inline CommandMessage^ CommandMessage::Create()
	{
		return gcnew CommandMessage(new ::CommandMessage(), true);
	}

	inline CommandMessage::CommandMessage()
		:ClassTemplate(new ::CommandMessage(), true)
	{
	}

	inline String^ MC::CommandMessage::GetMessage(CommandOrigin^ origin)
	{
		return marshalString(NativePtr->getMessage(*origin->NativePtr));
	}
}