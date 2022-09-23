#include <LiteLoader.NET/Header/Command/CommandOutput.hpp>
#include <LiteLoader.NET/Header/Command/CommandOutputParameter.hpp>
#include <LiteLoader.NET/Header/Command/CommandOutputMessage.hpp>
#include <LiteLoader.NET/Header/Command/CommandPropertyBag.hpp>
#include <LiteLoader.NET/Header/MC/Actor.hpp>
#include <memory>

enum class CommandOutputType;

namespace MC
{
inline void CommandOutput::AddMessage(String^ str)
{
    NativePtr->addMessage(marshalString(str));
}
inline void CommandOutput::Success(String^ str)
{
    NativePtr->success(marshalString(str));
}
inline void CommandOutput::Error(String^ str)
{
    NativePtr->error(marshalString(str));
}
inline CommandOutput ^ CommandOutput::Create(CommandOutput ^ co)
{
    return gcnew CommandOutput(::CommandOutput(co));
}

inline void CommandOutput::AddToResultList(String^ str0, String^ str1)
{
    NativePtr->addToResultList(marshalString(str0), marshalString(str1));
}

inline void CommandOutput::AddToResultList(String^ str, Actor ^ ac)
{
    NativePtr->addToResultList(marshalString(str), ac);
}

inline bool CommandOutput::IsEmpty::get()
{
    return NativePtr->empty();
}

inline void CommandOutput::Error(String^ str, List<CommandOutputParameter ^> ^ coplist)
{
    auto len = coplist->Count;
    std::vector<::CommandOutputParameter> stdvector;
    for (int i = 0; i < len; i++)
        stdvector.emplace_back(std::move(*(coplist[i]->NativePtr)));
    NativePtr->error(marshalString(str), stdvector);
}

inline void CommandOutput::ForceOutput(String^ str, List<CommandOutputParameter ^> ^ coplist)
{
    auto len = coplist->Count;
    std::vector<::CommandOutputParameter> stdvector;
    for (int i = 0; i < len; i++)
        stdvector.emplace_back(*(coplist[i]->NativePtr));
    NativePtr->forceOutput(marshalString(str), stdvector);
}

inline CommandPropertyBag ^ CommandOutput::Data::get()
{
    return gcnew CommandPropertyBag((::CommandPropertyBag*)&NativePtr->getData());
}

inline List<CommandOutputMessage ^> ^ CommandOutput::Messages::get()
{
    auto& stdvector = NativePtr->getMessages();
    auto len = (int)stdvector.size();
    auto ret = gcnew List<CommandOutputMessage ^>(len);
    for (int i = 0; i < len; i++)
        ret->Add(gcnew CommandOutputMessage((::CommandOutputMessage)stdvector[i]));
    return ret;
}

inline int CommandOutput::SuccessCount::get()
{
    return NativePtr->getSuccessCount();
}

inline int CommandOutput::OutPutType::get()
{
    return int(NativePtr->getType());
}

inline void CommandOutput::Load(int _EnumCommandOutputType, int a0, List<CommandOutputMessage ^> ^ comlist, CommandPropertyBag ^ cpb)
{
    auto len = comlist->Count;
    std::vector<::CommandOutputMessage> stdvector;
    for (int i = 0; i < len; i++)
        stdvector.emplace_back((::CommandOutputMessage&)comlist[i]);
    NativePtr->load(::CommandOutputType(_EnumCommandOutputType), a0, std::move(stdvector), std::unique_ptr<::CommandPropertyBag>(cpb->Release()));
}

inline void CommandOutput::SetHasPlayerText()
{
    NativePtr->setHasPlayerText();
}

inline void CommandOutput::Success(String^ str, List<CommandOutputParameter ^> ^ coplist)
{
    auto len = coplist->Count;
    std::vector<::CommandOutputParameter> stdvector;
    for (int i = 0; i < len; i++)
        stdvector.emplace_back(*coplist[i]->NativePtr);
    NativePtr->success(marshalString(str), stdvector);
}

inline void CommandOutput::Success()
{
    NativePtr->success();
}

inline bool CommandOutput::WantsData()
{
    return NativePtr->wantsData();
}

} // namespace MC