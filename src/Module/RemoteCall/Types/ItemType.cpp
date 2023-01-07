#include "ItemType.hpp"

#include<src/Header/MC/ItemStack.hpp>

namespace LiteLoader::RemoteCall
{
    inline ItemType::ItemType(MC::ItemStack^ item)
        : ClassTemplate(new ::RemoteCall::ItemType(item->NativePtr), true)
    {
    }

    inline ItemType::ItemType(::RemoteCall::ItemType const& v)
        : ClassTemplate(new ::RemoteCall::ItemType(v), true)
    {
    }

    inline MC::ItemStack^ ItemType::Get()
    {
        return gcnew MC::ItemStack(NativePtr->get<::ItemStack*>());
    }

    inline ItemType::operator ItemType ^ (MC::ItemStack^ v)
    {
        return gcnew ItemType(v);
    }

    inline ItemType::operator MC::ItemStack ^ (ItemType^ v)
    {
        return v->Get();
    }

    String^ ItemType::ToString()
    {
        auto p = NativePtr->get<ItemStack*>();
        return String::Format("{0},{1}", marshalString(p->getTypeName()), p->getCount());
    }
}