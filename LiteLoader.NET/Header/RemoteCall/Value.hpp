#pragma once

#include "include.hpp"
#include "Interfaces.hpp"
#include "ExtendType.hpp"
#include "NumberType.hpp"
namespace LLNET::RemoteCall {
	public
	ref class Value : ClassTemplate<Value, ::RemoteCall::Value>, IValueType
	{
		using _T = ::RemoteCall::Value;

		//ctor
	public:
		/// <summary>
		/// Copy
		/// </summary>
		/// <param name="val"></param>
		Value(Value% val)
			: ClassTemplate(new _T(*val.NativePtr), true)
		{
		}
		explicit Value(bool b)
			:ClassTemplate(new _T(b), true)
		{
		}
		Value(String^ str)
			:ClassTemplate(new _T(marshalString(str)), true)
		{
		}
		Value()
			: ClassTemplate(new _T(nullptr_t(nullptr)), true)
		{
		}
		Value(NumberType num)
			: ClassTemplate(new _T(num._toNative()), true)
		{
		}
		Value(MC::Player^ player)
			: ClassTemplate(new _T(player->NativePtr), true)
		{
		}
		Value(MC::Actor^ actor)
			: ClassTemplate(new _T(actor->NativePtr), true)
		{
		}
		Value(MC::BlockActor^ bloackActor)
			: ClassTemplate(new _T(bloackActor->NativePtr), true)
		{
		}
		Value(MC::Container^ container)
			: ClassTemplate(new _T(container->NativePtr), true)
		{
		}
		Value(MC::Vec3^ vec3)
			: ClassTemplate(new _T(*vec3->NativePtr), true)
		{
		}
		Value(MC::BlockPos^ blockPos)
			: ClassTemplate(new _T(*blockPos->NativePtr), true)
		{
		}
		Value(ItemType^ itemType)
			: ClassTemplate(new _T(*itemType->NativePtr), true)
		{
		}
		Value(BlockType^ blockType)
			: ClassTemplate(new _T(*blockType->NativePtr), true)
		{
		}
		Value(NbtType^ nbtType)
			: ClassTemplate(new _T(*nbtType->NativePtr), true)
		{
		}
		Value(double num)
			: ClassTemplate(new _T(::RemoteCall::NumberType(num)), true)
		{
		}
		Value(float num)
			: ClassTemplate(new _T(::RemoteCall::NumberType(num)), true)
		{
		}
		Value(__int64 num)
			: ClassTemplate(new _T(::RemoteCall::NumberType(num)), true)
		{
		}
		Value(int num)
			: ClassTemplate(new _T(::RemoteCall::NumberType(num)), true)
		{
		}
		Value(short num)
			: ClassTemplate(new _T(::RemoteCall::NumberType(num)), true)
		{
		}
		Value(char num)
			: ClassTemplate(new _T(::RemoteCall::NumberType(num)), true)
		{
		}
		Value(unsigned __int64 num)
			: ClassTemplate(new _T(::RemoteCall::NumberType(num)), true)
		{
		}
		Value(unsigned int num)
			: ClassTemplate(new _T(::RemoteCall::NumberType(num)), true)
		{
		}
		Value(unsigned short num)
			: ClassTemplate(new _T(::RemoteCall::NumberType(num)), true)
		{
		}
		Value(unsigned char num)
			: ClassTemplate(new _T(::RemoteCall::NumberType(num)), true)
		{
		}
		Value^ Clone() {
			return gcnew Value(*this);
		}
	internal:
		Value(::RemoteCall::Value const& v)
			:ClassTemplate(new _T(v), true)
		{
		}
	public:
		enum class InstanceType {
			Bool = 0,
			String = 1,
			Null = 2,
			NumberType = 3,
			Player = 4,
			Actor = 5,
			BlockActor = 6,
			Container = 7,
			Vec3 = 8,
			BlockPos = 9,
			ItemType = 10,
			BlockType = 11,
			NbtType = 12
		};
		//method
	public:
		property InstanceType Type {
			InstanceType get() {
				return InstanceType(NativePtr->index());
			}
		}

		bool IsNull() {
			return NativePtr->index() == (size_t)InstanceType::Null;
		}

		bool AsBool([System::Runtime::InteropServices::Out] bool% v) {
			if (NativePtr->index() != (size_t)InstanceType::Bool)
				return false;
			v = std::get<bool>(*NativePtr);
			return true;
		}

		bool AsString([System::Runtime::InteropServices::Out] String^% v) {
			if (NativePtr->index() != (size_t)InstanceType::String)
				return false;
			auto& _v = std::get<std::string>(*NativePtr);
			v = marshalString(_v);
			return true;
		}

		bool AsNumberType([System::Runtime::InteropServices::Out] NumberType% v) {
			v = NumberType();
			if (NativePtr->index() != (size_t)InstanceType::NumberType)
				return false;
			auto& _v = std::get<::RemoteCall::NumberType>(*NativePtr);
			v = NumberType(*(__int64*)&_v, *(double*)(((uintptr_t)&_v) + sizeof(__int64)));
			return true;
		}

		bool AsPlayer([System::Runtime::InteropServices::Out] MC::Player^% v) {
			v = nullptr;
			if (NativePtr->index() != (size_t)InstanceType::Player)
				return false;
			v = gcnew MC::Player(std::get<::Player*>(*NativePtr));
			return true;
		}

		bool AsActor([System::Runtime::InteropServices::Out] MC::Actor^% v) {
			v = nullptr;
			if (NativePtr->index() != (size_t)InstanceType::Actor)
				return false;
			v = gcnew MC::Actor(std::get<::Actor*>(*NativePtr));
			return true;
		}

		bool AsBlockActor([System::Runtime::InteropServices::Out] MC::BlockActor^% v) {
			v = nullptr;
			if (NativePtr->index() != (size_t)InstanceType::BlockActor)
				return false;
			v = gcnew MC::BlockActor(std::get<::BlockActor*>(*NativePtr));
			return true;
		}

		bool AsContainer([System::Runtime::InteropServices::Out] MC::Container^% v) {
			v = nullptr;
			if (NativePtr->index() != (size_t)InstanceType::Container)
				return false;
			v = gcnew MC::Container(std::get<::Container*>(*NativePtr));
			return true;
		}

		bool AsVec3([System::Runtime::InteropServices::Out] MC::Vec3^% v) {
			v = nullptr;
			if (NativePtr->index() != (size_t)InstanceType::Vec3)
				return false;
			v = gcnew MC::Vec3(std::get<::Vec3>(*NativePtr));
			return true;
		}

		bool AsBlockPos([System::Runtime::InteropServices::Out] MC::BlockPos^% v) {
			v = nullptr;
			if (NativePtr->index() != (size_t)InstanceType::BlockPos)
				return false;
			v = gcnew MC::BlockPos(std::get<::BlockPos>(*NativePtr));
			return true;
		}

		bool AsItemType([System::Runtime::InteropServices::Out] ItemType^% v) {
			v = nullptr;
			if (NativePtr->index() != (size_t)InstanceType::ItemType)
				return false;
			v = gcnew ItemType(std::get<::RemoteCall::ItemType>(*NativePtr));
			return true;
		}

		bool AsBlockType([System::Runtime::InteropServices::Out] BlockType^% v) {
			v = nullptr;
			if (NativePtr->index() != (size_t)InstanceType::BlockType)
				return false;
			v = gcnew BlockType(std::get<::RemoteCall::BlockType>(*NativePtr));
			return true;
		}

		bool AsNbtType([System::Runtime::InteropServices::Out] NbtType^% v) {
			v = nullptr;
			if (NativePtr->index() != (size_t)InstanceType::NbtType)
				return false;
			v = gcnew NbtType(std::get<::RemoteCall::NbtType>(*NativePtr));
			return true;
		}

		bool AsContainer([System::Runtime::InteropServices::Out] BlockType^% v) {
			v = nullptr;
			if (NativePtr->index() != (size_t)InstanceType::BlockType)
				return false;
			v = gcnew BlockType(std::get<::RemoteCall::BlockType>(*NativePtr));
			return true;
		}
		//opeator
	public:

		Value^ SetNull() {
			*NativePtr = nullptr_t(nullptr);
			return this;
		}

		Value^ operator=(bool v) {
			*NativePtr = v;
			return this;
		}

		Value^ operator=(String^ v) {
			*NativePtr = marshalString(v);
			return this;
		}

		Value^ operator=(NumberType v) {
			*NativePtr = v._toNative();
			return this;
		}

		Value^ operator=(MC::Player^ player) {
			*NativePtr = player->NativePtr;
			return this;
		}

		Value^ operator=(MC::Actor^ actor) {
			*NativePtr = actor->NativePtr;
			return this;
		}

		Value^ operator=(MC::BlockActor^ blockActor) {
			*NativePtr = blockActor->NativePtr;
			return this;
		}

		Value^ operator=(MC::Container^ container) {
			*NativePtr = container->NativePtr;
			return this;
		}

		Value^ operator=(MC::Vec3^ vec3) {
			*NativePtr = *vec3->NativePtr;
			return this;
		}

		Value^ operator=(MC::BlockPos^ blockPos) {
			*NativePtr = *blockPos->NativePtr;
			return this;
		}

		Value^ operator=(ItemType^ itemType) {
			*NativePtr = *itemType->NativePtr;
			return this;
		}

		Value^ operator=(BlockType^ blockType) {
			*NativePtr = *blockType->NativePtr;
			return this;
		}

		Value^ operator=(NbtType^ nbtType) {
			*NativePtr = *nbtType->NativePtr;
			return this;
		}

		static operator Value ^ (bool v) {
			return gcnew Value(v);
		}
		static operator Value ^ (String^ v) {
			return gcnew Value(v);
		}

		static operator Value ^ (NumberType v) {
			return gcnew Value(v);
		}
		static operator Value ^ (MC::Player^ v) {
			return gcnew Value(v);
		}
		static operator Value ^ (MC::Actor^ v) {
			return gcnew Value(v);
		}
		static operator Value ^ (MC::BlockActor^ v) {
			return gcnew Value(v);
		}
		static operator Value ^ (MC::Container^ v) {
			return gcnew Value(v);
		}
		static operator Value ^ (MC::Vec3^ v) {
			return gcnew Value(v);
		}
		static operator Value ^ (MC::BlockPos^ v) {
			return gcnew Value(v);
		}
		static operator Value ^ (ItemType^ v) {
			return gcnew Value(v);
		}
		static operator Value ^ (BlockType^ v) {
			return gcnew Value(v);
		}
		static operator Value ^ (NbtType^ v) {
			return gcnew Value(v);
		}

		static operator bool(Value^ v) {
			bool ret;
			if (!v->AsBool(ret))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return ret;
		}
		static operator String ^ (Value^ v) {

			String^ ret;
			if (!v->AsString(ret))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return ret;
		}
		static operator NumberType (Value^ v) {
			NumberType ret;
			if (!v->AsNumberType(ret))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return ret;
		}
		static operator MC::Player ^ (Value^ v) {

			MC::Player^ ret;
			if (!v->AsPlayer(ret))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return ret;
		}
		static operator MC::Actor ^ (Value^ v) {
			MC::Actor^ ret;
			if (!v->AsActor(ret))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return ret;
		}
		static operator MC::BlockActor ^ (Value^ v) {
			MC::BlockActor^ ret;
			if (!v->AsBlockActor(ret))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return ret;
		}
		static operator MC::Container ^ (Value^ v) {
			MC::Container^ ret;
			if (!v->AsContainer(ret))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return ret;
		}
		static operator MC::Vec3 ^ (Value^ v) {
			MC::Vec3^ ret;
			if (!v->AsVec3(ret))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return ret;
		}
		static operator MC::BlockPos ^ (Value^ v) {
			MC::BlockPos^ ret;
			if (!v->AsBlockPos(ret))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return ret;
		}
		static operator ItemType ^ (Value^ v) {
			ItemType^ ret;
			if (!v->AsItemType(ret))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return ret;
		}
		static operator BlockType ^ (Value^ v) {
			BlockType^ ret;
			if (!v->AsBlockType(ret))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return ret;
		}
		static operator NbtType ^ (Value^ v) {
			NbtType^ ret;
			if (!v->AsNbtType(ret))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return ret;
		}

#define Value2SimpleType_Implicit(type)												\
		static operator type(Value^ v) {											\
			if(v->NativePtr->index() != (size_t)InstanceType::NumberType)			\
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;			\
			return std::get<::RemoteCall::NumberType>(*v->NativePtr).get<type>();	\
		};

		Value2SimpleType_Implicit(double);
		Value2SimpleType_Implicit(float);
		Value2SimpleType_Implicit(__int64);
		Value2SimpleType_Implicit(int);
		Value2SimpleType_Implicit(short);
		Value2SimpleType_Implicit(char);
		Value2SimpleType_Implicit(unsigned __int64);
		Value2SimpleType_Implicit(unsigned int);
		Value2SimpleType_Implicit(unsigned short);
		Value2SimpleType_Implicit(unsigned char);

	public:
		virtual String^ ToString() override {
			auto type = InstanceType(NativePtr->index());
			String^ info;
			switch (type)
			{
			case LLNET::RemoteCall::Value::InstanceType::Bool:
				info = std::get<bool>(*NativePtr).ToString();
				break;
			case LLNET::RemoteCall::Value::InstanceType::String:
				info = marshalString(std::get<std::string>(*NativePtr));
				break;
			case LLNET::RemoteCall::Value::InstanceType::Null:
				info = "Null";
				break;
			case LLNET::RemoteCall::Value::InstanceType::NumberType:
			{
				auto& number = std::get<::RemoteCall::NumberType>(*NativePtr);
				info = String::Format("<{0},{1}>", number.f, number.i);
			}
			break;
			case LLNET::RemoteCall::Value::InstanceType::Player:
			{
				auto p = std::get<::Player*>(*NativePtr);
				info = String::Format("{0},{1}", marshalString(p->getRealName()), marshalString(p->getPos().toString()));
			}
			break;
			case LLNET::RemoteCall::Value::InstanceType::Actor:
			{
				auto p = std::get<::Actor*>(*NativePtr);
				info = String::Format("{0},{1}", marshalString(p->getTypeName()), marshalString(p->getPos().toString()));
			}
			break;
			case LLNET::RemoteCall::Value::InstanceType::BlockActor:
			{
				auto p = std::get<::BlockActor*>(*NativePtr);
				info = String::Format("{0},{1}", marshalString(p->getName()), marshalString(p->getPosition().toString()));

			}
			break;
			case LLNET::RemoteCall::Value::InstanceType::Container:
			{
				auto p = std::get<::Container*>(*NativePtr);
				info = String::Format("{0},{1}", marshalString(p->getTypeName()), MC::ContainerType(p->getContainerType()));
			}
			break;
			case LLNET::RemoteCall::Value::InstanceType::Vec3:
			{
				auto& vec3 = std::get<::Vec3>(*NativePtr);
				info = marshalString(vec3.toString());
			}
			break;
			case LLNET::RemoteCall::Value::InstanceType::BlockPos:
			{
				auto& pos = std::get<::BlockPos>(*NativePtr);
				info = marshalString(pos.toString());
				break;
			}
			case LLNET::RemoteCall::Value::InstanceType::ItemType:
			{
				ItemType^ item;
				this->AsItemType(item);
				info = item->ToString();
			}
			break;
			case LLNET::RemoteCall::Value::InstanceType::BlockType:
			{
				BlockType^ block;
				this->AsBlockType(block);
				info = block->ToString();
			}
			break;
			case LLNET::RemoteCall::Value::InstanceType::NbtType:
			{
				NbtType^ nbt;
				this->AsNbtType(nbt);
				info = nbt->ToString();
			}
			break;
			default:
				break;
			}
			return String::Format("InstanceType:{0},{1}", type, info);
		}
	};
}