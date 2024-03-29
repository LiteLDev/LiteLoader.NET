#pragma once
#include <mc/Container.hpp>
#include "Types.hpp"

namespace MC
{
    ref class ItemStack;
    value class Vec3;
}

namespace MC
{
    public
    ref class Container : ClassTemplate<Container, ::Container>
    {
    public:
        __ctor(Container, ::Container);
        __ctor_default(Container, ::Container);

        inline bool AddItem_s(ItemStack^ item);
        inline bool AddItemToFirstEmptySlot_s(ItemStack^ item);
        inline bool RemoveItem_s(int slot, unsigned int number);
        inline ItemStack^ GetItem(int slot);
        inline void SetItem(int, ItemStack^);
        inline bool HasContainer(Vec3 pos, int dim);
        inline Container^ GetContainerAt(Vec3 pos, int dim);
        inline int FindFirstSlotForItem(ItemStack^ item);

#ifdef MANUAL_MAINTENANCE

        property ::System::String^ TypeName
        {
            ::System::String^ get();
        }

        property array<MC::ItemStack^>^ AllSlots
        {
            array<MC::ItemStack^>^ get();
        }

        property int Size
        {
            int get();
        }

        property int ContainerSize
        {
            int get();
        }

        property int MaxStackSize
        {
            int get();
        }

        property array<MC::ItemStack^>^ SlotCopies
        {
            array<MC::ItemStack^>^ get();
        }

        property bool HasCustomName
        {
            bool get();
        }

        property bool IsEmpty
        {
            bool get();
        }

        property MC::ContainerType ContainerType
        {
            MC::ContainerType get();
        }

        property MC::ContainerType GameplayContainerType
        {
            MC::ContainerType get();
            void set(MC::ContainerType);
        }

        virtual void Init();

        virtual void RemoveItem(int _0, int _1);

        virtual void RemoveAllItems();

        //virtual void UnkVfn22();

        //virtual void UnkVfn23();

        virtual void SetContainerChanged(int _0);

        virtual void SetContainerMoved();

        virtual void SetCustomName(::System::String^ _0);

        //virtual void UnkVfn31();

        void InitRuntimeId();

        static MC::ContainerType GetContainerTypeId(::System::String^ _0);

        static ::System::String^ GetContainerTypeName(MC::ContainerType _0);

#endif // INCLUDE_MCAPI
    };
} // namespace MC
