#pragma once

#include <mc/ItemStack.hpp>
#include <mc/ItemInstance.hpp>
#include "ItemStackBase.hpp"
#include "ItemInstance.hpp"
#include "Types.hpp"
#include "CompoundTag.hpp"

namespace MC
{
	ref class ItemStackBase;
	ref class ItemInstance;
}

namespace MC
{
	public
	ref class ItemStack : ItemStackBase
	{
	public:
		__ctor_base(ItemStack, ::ItemStack, ItemStackBase);

		inline static ItemStack^ Create();
		inline static ItemStack^ Create(String^ type, int count);
		inline static ItemStack^ Create(CompoundTag^ tag);
		inline static ItemStack^ Create(short itemId, int aux);
		inline static ItemStack^ Create(short itemId, int aux, int count);
		inline static ItemStack^ FromItemInstance(ItemInstance^ ins);

		inline ItemStack^ Clone_s();
		inline bool SetItem(ItemStack^ newItem);
		bool SetLore(array<String^>^ lores);
		inline CompoundTag^ GetNbt();
		inline bool SetNbt(CompoundTag^ nbt);

		property String^ TypeName { String^ get(); };

		property int Aux
		{
			int get();
		}
		property int Count
		{
			int get();
		}

#ifdef MANUAL_MAINTENANCE

		// property MC::ItemStackNetIdVariant ^ ItemStackNetIdVariant {
		//     MC::ItemStackNetIdVariant ^ get();
		// }

		property int MaxUseDuration
		{
			int get();
		}

		property MC::ItemStack^ StrippedNetworkItem {
			MC::ItemStack^ get();
		}

		property bool HasItemStackNetId
		{
			bool get();
		}

		virtual void SetNull(String^) override;

		virtual ::String^ ToString() override;

		virtual ::String^ ToDebugString() override;

		// void Autoclassinit2(unsigned long long _0);

		void AssignNetIdVariant(MC::ItemStack^ _0);

		MC::ItemStack^ Clone();

		bool MatchesAndNetIdVariantMatches(MC::ItemStack^ _0);

		bool MatchesNetIdVariant(MC::ItemStack^ _0);

		bool SameItemAndAuxAndBlockData(MC::ItemStack^ _0);

		void ServerInitNetId();

		void UseAsFuel();

		static property MC::ItemStack^ EMPTY_ITEM {
			MC::ItemStack^ get();
		}
#endif // INCLUDE_MCAPI
	};
} // namespace MC
