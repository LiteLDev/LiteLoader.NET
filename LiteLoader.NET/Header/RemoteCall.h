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
	internal:
		BlockType(::RemoteCall::BlockType const& v)
			:ClassTemplate(new ::RemoteCall::BlockType(v), true)
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
	internal:
		NumberType(__int64 i, double f)
			: i(i), f(f) {};

	public:

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
			: ClassTemplate(new _T(::RemoteCall::NumberType(num)), true)
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
	public:

		Value^ SetNull() {
			*NativePtr = nullptr_t(nullptr);
			return this;
		}

		Value^ operator=(NumberType v) {
			*NativePtr = ::RemoteCall::NumberType(v);
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
	};

	public
	ref class Value_Type : ClassTemplate<Value_Type, ::RemoteCall::ValueType>
	{
		using _T = ::RemoteCall::ValueType;

	public:
		Value_Type()
			: ClassTemplate(new _T(), true)
		{
		}
		/// <summary>
		/// Copy
		/// </summary>
		/// <param name="v"></param>
		Value_Type(Value_Type% v)
			: ClassTemplate(new _T(*v.NativePtr), true)
		{
		}
		Value_Type(Value^ v)
			: ClassTemplate(new _T(*v->NativePtr), true)
		{
		}
		Value_Type(array<Value_Type^>^ v)
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
		Value_Type(List<Value_Type^>^ v)
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
		Value_Type(Dictionary<String^, Value_Type^>^ v)
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
		Value_Type^ Clone() {
			return gcnew Value_Type(*this);
		};
	internal:
		Value_Type(::RemoteCall::ValueType const& v)
			:ClassTemplate(new _T(v), true)
		{
		}

	public:
		using __ObjectType = Dictionary< String^, Value_Type^>;
		using __ArrayType = List<Value_Type^>;

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
			ObjectType(Dictionary<String^, Value_Type^>^ v)
				: value(v)
			{
			}
			operator Dictionary<String^, Value_Type^> ^ () {
				return value;
			};
			Dictionary<String^, Value_Type^>^ value;
		};

		[RemoteCallValueType(InstanceType::ArrayType)]
		ref class ArrayType : IValueType
		{
		public:
			ArrayType(List<Value_Type^>^ v)
				:value(v)
			{
			}
			operator List<Value_Type^> ^ () {
				return value;
			}
			List<Value_Type^>^ value;
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
				ret->Add(marshalString(k), gcnew Value_Type(v));
			}
			return ret;
		}
		static __ArrayType^ Parse(::RemoteCall::ValueType::ArrayType const& v) {
			auto len = (int)v.size();
			auto ret = gcnew __ArrayType(len);
			for (auto& i : v) {
				ret->Add(gcnew Value_Type(i));
			}
			return ret;
		}
	};


} // namespace LLNET::RemoteCall


namespace LLNET::RemoteCall
{
	public
	ref class RemoteCallAPI abstract
	{
	public:
		delegate Value_Type^ CallbackFn(List<Value_Type^>^);
		static bool ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ fn);
		static bool ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ fn, IntPtr handler);

		static CallbackFn^ ImportFunc(String^ nameSpace, String^ funcName);

		static bool HasFunc(String^ nameSpace, String^ funcName);
		static bool RemoveFunc(String^ nameSpace, String^ funcName);
		static bool RemoveNameSpace(String^ nameSpace);
		static bool RemoveFuncs(List<Pair<String^, String^>>^ funcs);

		generic<typename TDelegate>
		where TDelegate:System::Delegate
			static bool ExportAs(String^ nameSpace, String^ funcName, TDelegate f)
		{
			return RemoteCallFunctionManager::_ExportAs<TDelegate>(nameSpace, funcName, f);
		}
	internal:
		ref class RemoteCallFunctionManager sealed {
		public:
			generic<typename TDelegate>
			where TDelegate : System::Delegate
				static bool _ExportAs(String^ nameSpace, String^ funcName, TDelegate f)
			{
				auto func = gcnew Function(nameSpace, funcName, f);
				auto ret = ExportFunc(nameSpace, funcName, gcnew CallbackFn(func, &Function::Invoke));
				if (ret)
				{
					RemoteCallFunction->Add(func);
				}
				return ret;
			}
		private:
			ref class Function {
			public:
				Function(String^ nameSpace, String^ funcName, System::Delegate^ f)
					:NameSpace(nameSpace), FuncName(funcName), delfunc(f)
				{
				}

				String^ NameSpace;
				String^ FuncName;
				System::Delegate^ delfunc;
			public:
				Value_Type^ Invoke(List<Value_Type^>^ args) {
					throw gcnew System::NotImplementedException;
				}
			};
		private:
			static bool IsElementType(System::Type^ type) {
				for each (auto var in Simple_ElementType) {
					if (type == var)
						return true;
				}
				return false;
			}
			static List<Function^>^ RemoteCallFunction = gcnew List<Function^>;
			static array<System::Type^>^ Simple_ElementType = gcnew array<System::Type^>
			{
				void::typeid,
					bool::typeid,
					String::typeid,
					NumberType::typeid,
					MC::Player::typeid,
					MC::Actor::typeid,
					MC::BlockActor::typeid,
					MC::Container::typeid,
					MC::Vec3::typeid,
					MC::BlockPos::typeid,
					ItemType::typeid,
					BlockType::typeid,
					NbtType::typeid
			};
		};

	public:
		//防止gc回收
		static Dictionary<uint64_t, NativeCallbackHandler^>^ CallbackData = gcnew Dictionary<uint64_t, NativeCallbackHandler^>;

	private:
		ref class RemoteCallHelper
		{
		private:
			::RemoteCall::CallbackFn const* pFunc;
			Value_Type^ Invoke(List<Value_Type^>^ list) {
				NULL_ARG_CHEEK(list);

				auto count = (size_t)list->Count;
				std::vector<::RemoteCall::ValueType> stdvector;
				stdvector.resize(count);
				for (auto i = 0; i < count; ++i)
				{
					stdvector.emplace_back(*list[i]->NativePtr);
				}
				auto ret = (*pFunc)(stdvector);
				return gcnew Value_Type(ret);
			};
			RemoteCallHelper(::RemoteCall::CallbackFn const* p)
				: pFunc(p)
			{
			}

		public:
			static Pair<RemoteCallHelper^, CallbackFn^> Create(::RemoteCall::CallbackFn const* p) {
				auto instance = gcnew RemoteCallHelper(p);
				return Pair< RemoteCallHelper^, CallbackFn^>(instance, gcnew CallbackFn(instance, &RemoteCallHelper::Invoke));
			}
		};

	};
} // namespace LLNET::RemoteCall

#endif // REMOTECALL_FIXED
