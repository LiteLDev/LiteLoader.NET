#include <LiteLoader.NET/Header/Command/CommandOutputMessage.hpp>

enum class CommandOutputMessageType;

namespace MC
{
inline CommandOutputMessage ^ MC::CommandOutputMessage::Create(CommandOutputMessage ^ cm)
{
    return gcnew CommandOutputMessage(*(cm->NativePtr));
}
inline CommandOutputMessage ^ CommandOutputMessage::Create(int _EnumCommandOutputMessageType, String^ a0, List<String^> ^ a1)
{
    int len = a1->Count;
    std::vector<std::string> stdvector((int)len);
    for (int i = 0; i < len; i++)
        stdvector[i] = marshalString(a1[i]);
    return gcnew CommandOutputMessage(::CommandOutputMessage(CommandOutputMessageType(_EnumCommandOutputMessageType), marshalString(a0), std::move(stdvector)));
    /*::CommandOutputMessageType(_EnumCommandOutputMessageType), marshalString(a0), std::move(stdvector))*/
}

inline String^ CommandOutputMessage::GetMessageId()
{
    return marshalString(NativePtr->getMessageId());
}
inline List<String^> ^ CommandOutputMessage::GetParams()
{
    auto& stdvector = NativePtr->getParams();
    auto len = (int)stdvector.size();
    auto ret = gcnew List<String^>(len);
    for (int i = 0; i < len; ++i)
        ret[i] = marshalString(stdvector[i]);
    return ret;
}
inline int CommandOutputMessage::GetType()
{
    return int(NativePtr->getType());
}
} // namespace MC
