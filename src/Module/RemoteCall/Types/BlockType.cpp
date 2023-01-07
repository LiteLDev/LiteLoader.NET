#include "BlockType.hpp"

#include<src/Header/MC/BlockInstance.hpp>

namespace LiteLoader::RemoteCall
{
    inline BlockType::BlockType(MC::BlockInstance^ block)
        : ClassTemplate(new ::RemoteCall::BlockType(*block->NativePtr), true)
    {
    }

    inline BlockType::BlockType(::RemoteCall::BlockType const& v)
        : ClassTemplate(new ::RemoteCall::BlockType(v), true)
    {
    }

    inline MC::BlockInstance^ BlockType::Get()
    {
        return gcnew MC::BlockInstance(NativePtr->get<::BlockInstance>());
    }

    inline BlockType::operator BlockType ^ (MC::BlockInstance^ v)
    {
        return gcnew BlockType(v);
    }

    inline BlockType::operator MC::BlockInstance ^ (BlockType^ v)
    {
        return v->Get();
    }

    String^ BlockType::ToString()
    {
        auto& p = NativePtr->get<::BlockInstance>();
        return String::Format("{0},{1}", marshalString(p.getBlock()->getTypeName()), marshalString(p.getPosition().toString()));
    }
}