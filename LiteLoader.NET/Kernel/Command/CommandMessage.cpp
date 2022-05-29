#include "../../Header/Command/CommandMessage.hpp"
#include "../../Header/Command/CommandOrigin.hpp"

namespace MC
{
	CommandMessage^ CommandMessage::Create()
	{
		return gcnew CommandMessage(new ::CommandMessage(), true);
	}

	String^ MC::CommandMessage::GetMessage(CommandOrigin^ origin)
	{
		return marshalString(NativePtr->getMessage(*origin->NativePtr));
	}
}