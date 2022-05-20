#pragma once
#include "include.hpp"
#include "Interfaces.hpp"

namespace LLNET::RemoteCall {
	public
	ref class NbtType : ClassTemplate<NbtType, ::RemoteCall::NbtType>, IValue
	{
	public:
		NbtType(MC::CompoundTag^ tag)
			: ClassTemplate(new ::RemoteCall::NbtType(tag->NativePtr), true)
		{
		}

		MC::CompoundTag^ Get() {
			return gcnew MC::CompoundTag(NativePtr->get<CompoundTag*>());
		}

	public:
		static operator NbtType ^ (MC::CompoundTag^ v) {
			return gcnew NbtType(v);
		}
		static operator MC::CompoundTag ^ (NbtType^ v) {
			return v->Get();
		}
	internal:
		NbtType(::RemoteCall::NbtType const& v)
			:ClassTemplate(new ::RemoteCall::NbtType(v), true)
		{
		}
	};

	public
	ref class ItemType : ClassTemplate<ItemType, ::RemoteCall::ItemType>, IValue
	{
	public:
		ItemType(MC::ItemStack^ item)
			: ClassTemplate(new ::RemoteCall::ItemType(item->NativePtr), true)
		{
		}

		MC::ItemStack^ Get() {
			return gcnew MC::ItemStack(NativePtr->get<::ItemStack*>());
		}
	public:
		static operator ItemType ^ (MC::ItemStack^ v) {
			return gcnew ItemType(v);
		}
		static operator MC::ItemStack ^ (ItemType^ v) {
			return v->Get();
		}
	internal:
		ItemType(::RemoteCall::ItemType const& v)
			:ClassTemplate(new ::RemoteCall::ItemType(v), true)
		{
		}
	};

	public
	ref class BlockType : ClassTemplate<BlockType, ::RemoteCall::BlockType>, IValue
	{
		BlockType(MC::BlockInstance^ block)
			: ClassTemplate(new ::RemoteCall::BlockType(*block->NativePtr), true)
		{
		}
		MC::BlockInstance^ Get() {
			return gcnew MC::BlockInstance(NativePtr->get<::BlockInstance>());
		}
	public:
		static operator BlockType ^ (MC::BlockInstance^ v) {
			return gcnew BlockType(v);
		}
		static operator MC::BlockInstance ^ (BlockType^ v) {
			return v->Get();
		}
	internal:
		BlockType(::RemoteCall::BlockType const& v)
			:ClassTemplate(new ::RemoteCall::BlockType(v), true)
		{
		}
	};
}
