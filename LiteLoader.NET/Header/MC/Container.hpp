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
	ref class Container : ClassTemplate<Container, ::Container>, System::Collections::IEnumerable
	{
	public:
		__ctor(Container, ::Container);

		inline String^ GetTypeName();
		inline bool AddItem_s(ItemStack^ item);
		inline bool AddItemToFirstEmptySlot_s(ItemStack^ item);
		inline bool RemoveItem_s(int slot, unsigned int number);
		inline ItemStack^ GetSlot(int slot);
		List<ItemStack^>^ GetAllSlots();
		inline int GetSize();
		inline bool HasContainer(Vec3 pos, int dim);
		inline Container^ GetContainerAt(Vec3 pos, int dim);

#ifdef MANUAL_MAINTENANCE

        property ::System::String^ TypeName
        {
            ::System::String^ get();
        }

        property List<MC::ItemStack^>^ AllSlots
        {
            List<MC::ItemStack^>^ get();
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

        property List<MC::ItemStack^>^ SlotCopies
        {
            List<MC::ItemStack^>^ get();
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

	    property MC::ItemStack^ default[int]
	    {
	        MC::ItemStack^ get(int index);
	        void set(int index, MC::ItemStack^ value);
	    }

        virtual void Init();

	    virtual bool AddItem(ItemStack^ item);

	    virtual bool AddItemToFirstEmptySlot(ItemStack^ item);

        virtual bool RemoveItem(int slot, unsigned int number);

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
	    
        virtual System::Collections::IEnumerator^ GetEnumerator();

	protected:
        ref class ContainerEnumerator : System::Collections::IEnumerator
        {
        private:
            List<MC::ItemStack^>^ allSlots;
            int currentSlot;
        public:
            ContainerEnumerator(List<MC::ItemStack^>^ slots)
            {
                allSlots = slots;
            }
            virtual bool MoveNext();
            virtual void Reset();
            property Object^ Current { virtual Object^ get(); }
        };

#endif // INCLUDE_MCAPI
	};
} // namespace MC
