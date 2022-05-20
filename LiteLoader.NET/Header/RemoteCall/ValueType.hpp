#pragma once
#include "include.hpp"
#include "Value.hpp"

namespace LLNET::RemoteCall {
	public
	ref class Valuetype : ClassTemplate<Valuetype, ::RemoteCall::ValueType>
	{
		using _T = ::RemoteCall::ValueType;
		using _TValue = ::RemoteCall::Value;

	public:
		Valuetype()
			: ClassTemplate(new _T(), true)
		{
		}
		/// <summary>
		/// Copy
		/// </summary>
		/// <param name="v"></param>
		Valuetype(Valuetype% v)
			: ClassTemplate(new _T(*v.NativePtr), true)
		{
		}
		Valuetype(Value^ v)
			: ClassTemplate(new _T(*v->NativePtr), true)
		{
		}
		Valuetype(array<Valuetype^>^ v)
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
		Valuetype(List<Valuetype^>^ v)
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
		Valuetype(Dictionary<String^, Valuetype^>^ v)
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

		Valuetype(bool v)
			:ClassTemplate(new _T(v), true)
		{
		}
		Valuetype(String^ v)
			:ClassTemplate(new _T(marshalString(v)), true)
		{
		}
		Valuetype(NumberType v)
			:ClassTemplate(new _T(v._toNative()), true)

		{
		}
		Valuetype(MC::Player^ v)
			:ClassTemplate(new _T(v->NativePtr), true)
		{
		}
		Valuetype(MC::Actor^ v)
			:ClassTemplate(new _T(v->NativePtr), true)
		{
		}
		Valuetype(MC::BlockActor^ v)
			:ClassTemplate(new _T(v->NativePtr), true)
		{
		}
		Valuetype(MC::Container^ v)
			:ClassTemplate(new _T(v->NativePtr), true)
		{
		}
		Valuetype(MC::Vec3^ v)
			:ClassTemplate(new _T(*v->NativePtr), true)
		{
		}
		Valuetype(MC::BlockPos^ v)
			:ClassTemplate(new _T(*v->NativePtr), true)
		{
		}
		Valuetype(ItemType^ v)
			:ClassTemplate(new _T(*v->NativePtr), true)
		{
		}
		Valuetype(BlockType^ v)
			:ClassTemplate(new _T(*v->NativePtr), true)
		{
		}
		Valuetype(NbtType^ v)
			:ClassTemplate(new _T(*v->NativePtr), true)
		{
		}

		Valuetype^ Clone() {
			return gcnew Valuetype(*this);
		};
	internal:
		Valuetype(::RemoteCall::ValueType const& v)
			:ClassTemplate(new _T(v), true)
		{
		}

	public:
		using __ObjectType = Dictionary< String^, Valuetype^>;
		//operator
		using __ArrayType = List<Valuetype^>;
	public:
		static operator Valuetype ^ (Value^ v) {
			return gcnew Valuetype(v);
		}
		static operator Valuetype ^ (array<Valuetype^>^ v) {
			return gcnew Valuetype(v);
		}
		static operator Valuetype ^ (List<Valuetype^>^ v) {
			return gcnew Valuetype(v);
		}
		static operator Valuetype ^ (Dictionary<String^, Valuetype^>^ v) {
			return gcnew Valuetype(v);
		}



		static operator Valuetype ^ (bool v) {
			return gcnew Valuetype(v);
		}
		static operator Valuetype ^ (String^ v) {
			return gcnew Valuetype(v);
		}
		static operator Valuetype ^ (NumberType v) {
			return gcnew Valuetype(v);
		}
		static operator Valuetype ^ (MC::Player^ v) {
			return gcnew Valuetype(v);
		}
		static operator Valuetype ^ (MC::Actor^ v) {
			return gcnew Valuetype(v);
		}
		static operator Valuetype ^ (MC::BlockActor^ v) {
			return gcnew Valuetype(v);
		}
		static operator Valuetype ^ (MC::Container^ v) {
			return gcnew Valuetype(v);
		}
		static operator Valuetype ^ (MC::Vec3^ v) {
			return gcnew Valuetype(v);
		}
		static operator Valuetype ^ (MC::BlockPos^ v) {
			return gcnew Valuetype(v);
		}
		static operator Valuetype ^ (ItemType^ v) {
			return gcnew Valuetype(v);
		}
		static operator Valuetype ^ (BlockType^ v) {
			return gcnew Valuetype(v);
		}
		static operator Valuetype ^ (NbtType^ v) {
			return gcnew Valuetype(v);
		}

		static operator Valuetype ^ (double v) {
			return gcnew Valuetype(gcnew Value(v));
		}
		static operator Valuetype ^ (float v) {
			return gcnew Valuetype(gcnew Value(v));
		}
		static operator Valuetype ^ (__int64 v) {
			return gcnew Valuetype(gcnew Value(v));
		}
		static operator Valuetype ^ (int v) {
			return gcnew Valuetype(gcnew Value(v));
		}
		static operator Valuetype ^ (short v) {
			return gcnew Valuetype(gcnew Value(v));
		}
		static operator Valuetype ^ (char v) {
			return gcnew Valuetype(gcnew Value(v));
		}
		static operator Valuetype ^ (unsigned __int64 v) {
			return gcnew Valuetype(gcnew Value(v));
		}
		static operator Valuetype ^ (unsigned int v) {
			return gcnew Valuetype(gcnew Value(v));
		}
		static operator Valuetype ^ (unsigned short v) {
			return gcnew Valuetype(gcnew Value(v));
		}
		static operator Valuetype ^ (signed char v) {
			return gcnew Valuetype(gcnew Value(v));
		}



		static operator bool(Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (bool)val;
		}
		static operator String ^ (Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (String^)val;
		}
		static operator Valuetype ^ (Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (Valuetype^)val;
		}
		static operator MC::Player ^ (Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (MC::Player^)val;
		}
		static operator MC::Actor ^ (Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (MC::Actor^)val;
		}
		static operator MC::BlockActor ^ (Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (MC::BlockActor^)val;
		}
		static operator MC::Container ^ (Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (MC::Container^)val;
		}
		static operator MC::Vec3 ^ (Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (MC::Vec3^)val;
		}
		static operator MC::BlockPos ^ (Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (MC::BlockPos^)val;
		}
		static operator ItemType ^ (Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (ItemType^)val;
		}
		static operator BlockType ^ (Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (BlockType^)val;
		}
		static operator NbtType ^ (Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (NbtType^)val;
		}
		static operator double(Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (double)val;
		}
		static operator float(Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (float)val;
		}
		static operator __int64(Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (__int64)val;
		}
		static operator int(Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (int)val;
		}
		static operator short(Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (short)val;
		}
		static operator char(Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (char)val;
		}
		static operator unsigned __int64(Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (unsigned __int64)val;
		}
		static operator unsigned int(Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (unsigned int)val;
		}
		static operator unsigned short(Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (unsigned short)val;
		}
		static operator signed char(Valuetype^ v) {
			Value^ val;
			v->AsValue(val);
			return (char)val;
		}
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

		bool AsArrayType([System::Runtime::InteropServices::Out] ArrayType^% v) {
			v = nullptr;
			if (NativePtr->value.index() != (size_t)InstanceType::ArrayType)
				return false;

			auto& vec = std::get<::RemoteCall::ValueType::ArrayType>(NativePtr->value);
			v = gcnew ArrayType(Parse(vec));
			return true;
		}
		bool AsObjectType([System::Runtime::InteropServices::Out] ObjectType^% v) {
			v = nullptr;
			if (NativePtr->value.index() != (size_t)InstanceType::ObjectType)
				return false;

			auto& umap = std::get<::RemoteCall::ValueType::ObjectType>(NativePtr->value);
			v = gcnew ObjectType(Parse(umap));
			return true;
		}
		bool AsValue([System::Runtime::InteropServices::Out] Value^% v) {
			v = nullptr;
			if (NativePtr->value.index() != (size_t)InstanceType::Value)
				return false;

			v = gcnew Value(std::get<::RemoteCall::Value>(NativePtr->value));
			return true;
		}
	private:

		static __ObjectType^ Parse(::RemoteCall::ValueType::ObjectType const& val) {
			auto ret = gcnew __ObjectType;
			for (auto& [k, v] : val) {
				ret->Add(marshalString(k), gcnew Valuetype(v));
			}
			return ret;
		}
		static __ArrayType^ Parse(::RemoteCall::ValueType::ArrayType const& v) {
			auto len = (int)v.size();
			auto ret = gcnew __ArrayType(len);
			for (auto& i : v) {
				ret->Add(gcnew Valuetype(i));
			}
			return ret;
		}
	};
}
