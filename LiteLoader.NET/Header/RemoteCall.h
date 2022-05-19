#pragma once
#include "../Extra/mutex.h"


#define REMOTECALL_FIXED

#ifdef REMOTECALL_FIXED

#include <RemoteCallAPI.h>
#include "../Main/.NETGlobal.hpp"
#include "../Tools/NativeCallbackConverter.hpp"
#include "../Main/ClassTemplate.h"

#include "../Header/MC/CompoundTag.hpp"
#include "../Header/MC/ItemStack.hpp"
#include "../Header/MC/BlockInstance.hpp"
#include "../Header/MC/Player.hpp"
#include "../Header/MC/Actor.hpp"
#include "../Header/MC/BlockActor.hpp"
#include "../Header/MC/Container.hpp"
#include "../Header/MC/Vec3.hpp"
#include "../Header/MC/BlockPos.hpp"

namespace LLNET::RemoteCall
{
	public
	ref class RemoteCallAPI abstract
	{
	public:
		delegate String^ CallbackFn(List<String^>^);
		static bool ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ fn);
		static bool ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ fn, IntPtr handler);

		static CallbackFn^ ImportFunc(String^ nameSpace, String^ funcName);

		static bool HasFunc(String^ nameSpace, String^ funcName);
		static bool RemoveFunc(String^ nameSpace, String^ funcName);
		static bool RemoveNameSpace(String^ nameSpace);
		static bool RemoveFuncs(List<Pair<String^, String^>>^ funcs);

	public:
		using ValueType = ::RemoteCall::ValueType;
		//防止gc回收
		static Dictionary<uint64_t, NativeCallbackHandler^>^ CallbackData = gcnew Dictionary<uint64_t, NativeCallbackHandler^>;
	};
} // namespace LLNET::RemoteCall


namespace LLNET::RemoteCall
{


	interface class IValue
	{
	};

	interface class IValueType
	{
	};

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
	};

	public
	ref class BlockType : ClassTemplate<BlockType, ::RemoteCall::BlockType>, IValue
	{
		BlockType(MC::BlockInstance^ block)
			: ClassTemplate(new ::RemoteCall::BlockType(*block->NativePtr), true)
		{
		}
	};


	public
	value class NumberType : IValue
	{
		__int64 i;
		double f;

	public:
		NumberType(double v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(float v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(__int64 v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(int v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(short v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(char v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(unsigned __int64 v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(unsigned int v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(unsigned short v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(unsigned char v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};

		generic<typename T>
		T Get()
		{
			if (T::typeid == double ::typeid || T::typeid == float ::typeid)
				return T(f);
			return T(i);
		}

	internal:
		operator ::RemoteCall::NumberType()
		{
			return ::RemoteCall::NumberType{ i, f };
		}
	};

	public
	ref class Value : ClassTemplate<Value, ::RemoteCall::Value>, IValueType
	{
		using _T = ::RemoteCall::Value;

	public:
		Value()
			: ClassTemplate(new _T(), true)
		{
		}
		/// <summary>
		/// Copy
		/// </summary>
		/// <param name="val"></param>
		Value(Value% val)
			: ClassTemplate(new _T(*val.NativePtr), true)
		{
		}
		Value(nullptr_t null)
			: ClassTemplate(new _T(null), true)
		{
		}
		Value(NumberType num)
			: ClassTemplate(new _T(num.operator ::RemoteCall::NumberType()), true)
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
			: ClassTemplate(new _T(*blockType->NativePtr))
		{
		}
		Value(NbtType^ nbtType)
			: ClassTemplate(new _T(*nbtType->NativePtr), true)
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
	};

	public
	ref class ValueType : ClassTemplate<ValueType, ::RemoteCall::ValueType>
	{
		using _T = ::RemoteCall::ValueType;

	public:
		ValueType()
			: ClassTemplate(new _T(), true)
		{
		}
		/// <summary>
		/// Copy
		/// </summary>
		/// <param name="v"></param>
		ValueType(ValueType% v)
			: ClassTemplate(new _T(*v.NativePtr), true)
		{
		}
		ValueType(Value^ v)
			: ClassTemplate(new _T(*v->NativePtr), true)
		{
		}
		ValueType(array<ValueType^>^ v)
		{
			auto len = (int)v->Length;
			std::vector<_T> vec;
			vec.resize(len);
			for (int i = 0; i < len; i++)
			{
				vec.emplace_back(*v[i]->NativePtr);
			}
			NativePtr = new _T(std::move(vec));
			OwnsNativeInstance = true;
		}
		ValueType(List<ValueType^>^ v)
		{
			auto len = v->Count;
			std::vector<_T> vec;
			vec.resize(len);
			for (int i = 0; i < len; i++)
			{
				vec.emplace_back(*v[i]->NativePtr);
			}
			NativePtr = new _T(std::move(vec));
			OwnsNativeInstance = true;
		}
		ValueType(Dictionary<String^, ValueType^>^ v)
		{
			auto len = v->Count;
			std::unordered_map<std::string, _T> umap;

			auto enumerator = v->GetEnumerator();
			while (enumerator.MoveNext())
			{
				auto% pair = enumerator.Current;
				umap.emplace(marshalString(pair.Key), *pair.Value->NativePtr);
			}
			NativePtr = new _T(std::move(umap));
			OwnsNativeInstance = true;
		}
		ValueType^ Clone() {
			return gcnew ValueType(*this);
		};
	internal:
		ValueType(::RemoteCall::ValueType const& v)
			:ClassTemplate(new _T(v), true)
		{
		}

	public:
		using __ObjectType = Dictionary< String^, ValueType^>;
		using __ArrayType = List<ValueType^>;

		enum class InstanceType : size_t
		{
			Value = 0,
			ObjectType = 1,
			ArrayType = 2,
		};

		[System::AttributeUsage(System::AttributeTargets::Class)]
		ref class RemoteCallValueTypeAttribute : System::Attribute
		{
		public:
			InstanceType type;
			RemoteCallValueTypeAttribute(InstanceType t)
				: type(t)
			{
			}
		};

		[RemoteCallValueType(InstanceType::ObjectType)]
		ref class ObjectType : IValueType
		{
		public:
			ObjectType(Dictionary<String^, ValueType^>^ v)
				: value(v)
			{
			}
			operator Dictionary<String^, ValueType^> ^ () {
				return value;
			};
			Dictionary<String^, ValueType^>^ value;
		};

		[RemoteCallValueType(InstanceType::ArrayType)]
		ref class ArrayType : IValueType
		{
		public:
			ArrayType(List<ValueType^>^ v)
				:value(v)
			{
			}
			operator List<ValueType^> ^ () {
				return value;
			}
			List<ValueType^>^ value;
		};

	public:
		generic<typename T> where T : IValueType
			T Get()
		{
			auto attrs
				= (T::typeid)->GetCustomAttributes(RemoteCallValueTypeAttribute::typeid, false);
			if (attrs->Length == 0)
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			auto attr = static_cast<RemoteCallValueTypeAttribute^>(attrs[0]);
			switch (attr->type)
			{

			case InstanceType::ArrayType:
			{
				if (NativePtr->value.index() != (size_t)InstanceType::ArrayType)
					throw gcnew LLNET::Core::InvalidRemoteCallTypeException;

				auto& vec = std::get<::RemoteCall::ValueType::ArrayType>(NativePtr->value);
				auto ret = gcnew ArrayType(Parse(vec));
				return T(ret);
			}
			break;

			case InstanceType::ObjectType:
			{
				if (NativePtr->value.index() != (size_t)InstanceType::ObjectType)
					throw gcnew LLNET::Core::InvalidRemoteCallTypeException;

				auto& umap = std::get<::RemoteCall::ValueType::ObjectType>(NativePtr->value);
				auto ret = gcnew ObjectType(Parse(umap));
				return T(ret);
			}
			break;

			case InstanceType::Value:
			{
				if (NativePtr->value.index() != (size_t)InstanceType::Value)
					throw gcnew LLNET::Core::InvalidRemoteCallTypeException;

				auto& val = std::get<::RemoteCall::Value>(NativePtr->value);
				auto ret = gcnew Value(val);
				return T(ret);
			}
			break;

			}
			throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
		}
	private:

		static __ObjectType^ Parse(::RemoteCall::ValueType::ObjectType const& val) {
			auto ret = gcnew __ObjectType;
			for (auto& [k, v] : val) {
				ret->Add(marshalString(k), gcnew ValueType(v));
			}
			return ret;
		}
		static __ArrayType^ Parse(::RemoteCall::ValueType::ArrayType const& v) {
			auto len = (int)v.size();
			auto ret = gcnew __ArrayType(len);
			for (auto& i : v) {
				ret->Add(gcnew ValueType(i));
			}
			return ret;
		}
	};


} // namespace LLNET::RemoteCall

#endif // REMOTECALL_FIXED
