#include <src/Header/MC/Container.hpp>

#include <src/Header/MC/ItemStack.hpp>
#include <src/Header/MC/Vec3.hpp>

namespace MC
{

    inline bool Container::AddItem_s(ItemStack^ item)
    {
        return NativePtr->addItem_s(item->NativePtr);
    }

    inline bool Container::AddItemToFirstEmptySlot_s(ItemStack^ item)
    {
        return NativePtr->addItemToFirstEmptySlot_s(item->NativePtr);
    }

    inline bool Container::RemoveItem_s(int slot, unsigned int number)
    {
        return NativePtr->removeItem_s(slot, number);
    }

    inline ItemStack^ Container::GetItem(int slot)
    {
        return gcnew ItemStack((::ItemStack*)&NativePtr->getItem(slot));
    }

    inline bool Container::HasContainer(Vec3 pos, int dim)
    {
        return NativePtr->hasContainer(::Vec3(pos), dim);
    }

    inline Container^ Container::GetContainerAt(Vec3 pos, int dim)
    {
        return gcnew Container(NativePtr->getContainerAt(::Vec3(pos), dim));
    }

    inline int Container::FindFirstSlotForItem(ItemStack^ item)
    {
        return NativePtr->findFirstSlotForItem(*item->NativePtr);
    }
} // namespace MC


#ifdef MANUAL_MAINTENANCE

void MC::Container::Init()
{
    NativePtr->init();
}

void MC::Container::RemoveItem(int _0, int _1)
{
    NativePtr->removeItem(_0, _1);
}

void MC::Container::RemoveAllItems()
{
    NativePtr->removeAllItems();
}

//void MC::Container::UnkVfn22()
//{
//    NativePtr->__unk_vfn_22();
//}
//
//void MC::Container::UnkVfn23()
//{
//    NativePtr->__unk_vfn_23();
//}

void MC::Container::SetContainerChanged(int _0)
{
    NativePtr->setContainerChanged(_0);
}

void MC::Container::SetContainerMoved()
{
    NativePtr->setContainerMoved();
}

void MC::Container::SetCustomName(::System::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    NativePtr->setCustomName(__arg0);
}

//void MC::Container::UnkVfn31()
//{
//    NativePtr->__unk_vfn_31();
//}

void MC::Container::InitRuntimeId()
{
    NativePtr->initRuntimeId();
}

MC::ContainerType MC::Container::GetContainerTypeId(::System::String^ _0)
{
    return (MC::ContainerType)::Container::getContainerTypeId(marshalString(_0));
}

::System::String^ MC::Container::GetContainerTypeName(MC::ContainerType _0)
{
    return marshalString(::Container::getContainerTypeName((::ContainerType)_0));
}

String^ MC::Container::TypeName::get() 
{
    return marshalString(NativePtr->getTypeName());
}

List<MC::ItemStack^>^ MC::Container::AllSlots::get()
{
    auto& vec = NativePtr->getAllSlots();
    auto ret = gcnew List<MC::ItemStack^>();

    for (auto i = 0; i < vec.size(); ++i) {
        ret[i] = gcnew MC::ItemStack((::ItemStack*)vec[i]);
    }
    return ret;
}

int MC::Container::Size::get()
{
    return NativePtr->getSize();
}

int MC::Container::ContainerSize::get()
{
    return NativePtr->getContainerSize();
}

int MC::Container::MaxStackSize::get()
{
    return NativePtr->getMaxStackSize();
}

List<MC::ItemStack^>^ MC::Container::SlotCopies::get()
{
    auto& vec = NativePtr->getSlotCopies();
    auto ret = gcnew List<MC::ItemStack^>();

    for (auto i = 0; i < vec.size(); ++i) {
        ret[i] = gcnew MC::ItemStack(new ::ItemStack(vec[i]), true);
    }
    return ret;
}

bool MC::Container::HasCustomName::get()
{
    return NativePtr->hasCustomName();
}

bool MC::Container::IsEmpty::get()
{
    return NativePtr->isEmpty();
}

MC::ContainerType MC::Container::ContainerType::get()
{
    return (MC::ContainerType)NativePtr->getContainerType();
}

MC::ContainerType MC::Container::GameplayContainerType::get()
{
    return (MC::ContainerType)NativePtr->getGameplayContainerType();
}

void MC::Container::GameplayContainerType::set(MC::ContainerType containerType)
{
    NativePtr->setGameplayContainerType((::ContainerType)containerType);
}
#endif // INCLUDE_MCAPI
