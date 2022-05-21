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
	public:
		virtual String^ ToString() override {
			return marshalString(NativePtr->get<::CompoundTag*>()->toSNBT());
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
	public:
		virtual String^ ToString() override {
			auto p = NativePtr->get<ItemStack*>();
			return String::Format("{0},{1}", marshalString(p->getTypeName()), p->getCount());
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
	public:
		virtual String^ ToString() override {
			auto& p = NativePtr->get<::BlockInstance>();
			return String::Format("{0},{1}", marshalString(p.getBlock()->getTypeName()), marshalString(p.getPosition().toString()));
		}
	};



	ref class Valuetype;

	enum class InstanceType : size_t
	{
		Value = 0,
		ObjectType = 1,
		ArrayType = 2,
	};

	[System::AttributeUsage(System::AttributeTargets::Class)]
	public ref class RemoteCallValueTypeAttribute : System::Attribute
	{
	public:
		InstanceType type;
		RemoteCallValueTypeAttribute(InstanceType t)
			: type(t)
		{
		}
	};

	[RemoteCallValueType(InstanceType::ObjectType)]
	public ref class ObjectType : IValueType
	{
	public:
		ObjectType(Dictionary<String^, Valuetype^>^ v)
			: value(v)
		{
		}
		operator Dictionary<String^, Valuetype^> ^ () {
			return value;
		};
		Dictionary<String^, Valuetype^>^ value;
	public:
		virtual String^ ToString() override {
			return value->Count.ToString();
		}
	};

	[RemoteCallValueType(InstanceType::ArrayType)]
	public ref class ArrayType : IValueType
	{
	public:
		ArrayType(List<Valuetype^>^ v)
			:value(v)
		{
		}
		operator List<Valuetype^> ^ () {
			return value;
		}
		List<Valuetype^>^ value;
	public:
		virtual String^ ToString() override {
			return value->Count.ToString();
		}
	};
}
