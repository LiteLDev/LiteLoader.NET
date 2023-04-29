#include <mutex>
#include <src/Header/MC/ItemStack.hpp>
#include <memory>
namespace MC
{

    inline ItemStack^ ItemStack::Create()
    {
        return gcnew ItemStack(::ItemStack::create());
    }

    inline ItemStack^ ItemStack::Create(String^ type, int count)
    {
        return gcnew ItemStack(::ItemStack::create(marshalString(type), count), true);
    }

    inline ItemStack^ ItemStack::Create(CompoundTag^ tag)
    {
        return gcnew ItemStack(::ItemStack::create(std::unique_ptr<::CompoundTag>((::CompoundTag*)tag->ReleasePointer())), true);
    }

    inline ItemStack^ ItemStack::Create(short itemId, int aux)
    {
        return gcnew ItemStack(::ItemStack::create(itemId, aux), true);
    }

    inline ItemStack^ ItemStack::Create(short itemId, int aux, int count)
    {
        return gcnew ItemStack(::ItemStack::create(itemId, aux, count), true);
    }

    inline ItemStack^ ItemStack::FromItemInstance(ItemInstance^ ins)
    {
        return gcnew ItemStack(&::ItemStack::fromItemInstance(ins), true);
    }

    inline ItemStack^ ItemStack::Clone_s()
    {
        return gcnew ItemStack(NativePtr->clone_s());
    }

    inline String^ ItemStack::TypeName::get()
    {
        return marshalString(NativePtr->getTypeName());
    }

    inline int ItemStack::Aux::get()
    {
        return NativePtr->getAux();
    }

    inline int ItemStack::Count::get()
    {
        return NativePtr->getCount();
    }

    inline bool ItemStack::SetItem(ItemStack^ newItem)
    {
        return NativePtr->setItem(newItem->NativePtr);
    }

    bool ItemStack::SetLore(array<String^>^ lores)
    {
        std::vector<std::string> stdlores;
        for (int i = 0; i < lores->Length; ++i)
        {
            auto str = lores[i];
            stdlores.emplace_back(marshalString((str)));
        }
        return NativePtr->setLore(stdlores);
    }

    inline CompoundTag^ ItemStack::GetNbt()
    {
        return gcnew CompoundTag(NativePtr->getNbt().release(), true);
    }

    inline bool ItemStack::SetNbt(CompoundTag^ nbt)
    {
        return NativePtr->setNbt(nbt->NativePtr);
    }
} // namespace MC


#ifdef MANUAL_MAINTENANCE

void MC::ItemStack::SetNull()
{
    NativePtr->setNull({});
}

::String^ MC::ItemStack::ToString()
{
    return marshalString(NativePtr->toString());
}

::String^ MC::ItemStack::ToDebugString()
{
    return marshalString(NativePtr->toDebugString());
}

// void MC::ItemStack::Autoclassinit2(unsigned long long _0)
//{
//     NativePtr->__autoclassinit2(_0);
// }

void MC::ItemStack::AssignNetIdVariant(MC::ItemStack^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");

    NativePtr->_assignNetIdVariant(*_0->NativePtr);
}

MC::ItemStack^ MC::ItemStack::Clone()
{
    return gcnew ::MC::ItemStack(new ::ItemStack(NativePtr->clone()), true);
}

bool MC::ItemStack::MatchesAndNetIdVariantMatches(MC::ItemStack^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto __arg0 = _0->NativePtr;
    auto __ret = NativePtr->matchesAndNetIdVariantMatches(*__arg0);
    return __ret;
}

bool MC::ItemStack::MatchesNetIdVariant(MC::ItemStack^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto __arg0 = _0->NativePtr;
    auto __ret = NativePtr->matchesNetIdVariant(*__arg0);
    return __ret;
}

bool MC::ItemStack::SameItemAndAuxAndBlockData(MC::ItemStack^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto __arg0 = _0->NativePtr;
    auto __ret = NativePtr->sameItemAndAuxAndBlockData(*__arg0);
    return __ret;
}

void MC::ItemStack::ServerInitNetId()
{
    NativePtr->serverInitNetId();
}

void MC::ItemStack::UseAsFuel()
{
    NativePtr->useAsFuel();
}

// MC::ItemStackNetIdVariant ^ MC::ItemStack::ItemStackNetIdVariant::get()
//{
//     auto& __ret = NativePtr->getItemStackNetIdVariant();
//     return (MC::ItemStackNetIdVariant ^)((&__ret == nullptr) ? nullptr : gcnew ::MC::ItemStackNetIdVariant((struct ::ItemStackNetIdVariant*)&__ret));
// }

int MC::ItemStack::MaxUseDuration::get()
{
    auto __ret = NativePtr->getMaxUseDuration();
    return __ret;
}

MC::ItemStack^ MC::ItemStack::StrippedNetworkItem::get()
{
    auto __ret = NativePtr->getStrippedNetworkItem();
    auto ____ret = new class ::ItemStack(__ret);
    return (____ret == nullptr) ? nullptr : gcnew ::MC::ItemStack((class ::ItemStack*)____ret, true);
}

bool MC::ItemStack::HasItemStackNetId::get()
{
    return NativePtr->hasItemStackNetId();
}

MC::ItemStack^ MC::ItemStack::EMPTY_ITEM::get()
{
    return gcnew ::MC::ItemStack(new ::ItemStack(::ItemStack::EMPTY_ITEM));
}

#endif // INCLUDE_MCAPI
