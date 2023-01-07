#include "NbtType.hpp"

#include<src/Header/MC/CompoundTag.hpp>

namespace LiteLoader::RemoteCall
{
    inline NbtType::NbtType(MC::CompoundTag^ tag)
        : ClassTemplate(new ::RemoteCall::NbtType(tag->NativePtr), true)
    {
    }

    inline NbtType::NbtType(::RemoteCall::NbtType const& v)
        : ClassTemplate(new ::RemoteCall::NbtType(v), true)
    {
    }

    inline MC::CompoundTag^ NbtType::Get()
    {
        return gcnew MC::CompoundTag(NativePtr->get<CompoundTag*>());
    }

    inline NbtType::operator NbtType ^ (MC::CompoundTag^ v)
    {
        return gcnew NbtType(v);
    }

    inline NbtType::operator MC::CompoundTag ^ (NbtType^ v)
    {
        return v->Get();
    }

    String^ NbtType::ToString()
    {
        return marshalString(NativePtr->get<::CompoundTag*>()->toSNBT());
    }
}