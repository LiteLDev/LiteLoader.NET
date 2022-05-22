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


		Valuetype(List<String^>^ v)
		{
			auto len = v->Count;
			std::vector<_T> vec;
			vec.resize(len);
			for (int i = 0; i < len; i++)
			{
				vec.emplace_back(marshalString(v[i]));
			}
			NativePtr = new _T(std::move(vec));
			OwnsNativeInstance = true;
		}
		Valuetype(List<NumberType>^ v)
		{
			auto len = v->Count;
			std::vector<_T> vec;
			vec.resize(len);
			for (int i = 0; i < len; i++)
			{
				vec.emplace_back(v[i]._toNative());
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

		explicit Valuetype(bool v)
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
	public:


		static operator Dictionary<String^, Valuetype^> ^ (Valuetype^ v) {
			ObjectType^ dic;
			if (!v->AsObjectType(dic))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return dic->value;
		}

		static operator List<Valuetype^> ^ (Valuetype^ v) {
			ArrayType^ arr;
			if (!v->AsArrayType(arr))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return arr->value;
		}

		static operator Value ^ (Valuetype^ v) {
			Value^ val;
			if (!v->AsValue(val))
				throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			return val;
		}

#define ctor_List_NumberType(type)				\
		Valuetype(List<type>^ v)				\
		{										\
			auto len = v->Count;				\
			std::vector<_T> vec;				\
			vec.resize(len);					\
			for (int i = 0; i < len; i++)		\
			{									\
				vec.emplace_back(v[i]);			\
			}									\
			NativePtr = new _T(std::move(vec));	\
			OwnsNativeInstance = true;			\
		};

		ctor_List_NumberType(bool);
		ctor_List_NumberType(double);
		ctor_List_NumberType(float);
		ctor_List_NumberType(__int64);
		ctor_List_NumberType(int);
		ctor_List_NumberType(short);
		ctor_List_NumberType(char);
		ctor_List_NumberType(unsigned __int64);
		ctor_List_NumberType(unsigned int);
		ctor_List_NumberType(unsigned short);
		ctor_List_NumberType(unsigned char);


#define ctor_List_RefType_Ptr(type)					\
		Valuetype(List<type>^ v)					\
		{											\
			auto len = v->Count;					\
			std::vector<_T> vec;					\
			vec.resize(len);						\
			for (int i = 0; i < len; i++)			\
			{										\
				vec.emplace_back(v[i]->NativePtr);	\
			}										\
			NativePtr = new _T(std::move(vec));		\
			OwnsNativeInstance = true;				\
		};
#define ctor_List_RefType_Instance(type)			\
		Valuetype(List<type>^ v)					\
		{											\
			auto len = v->Count;					\
			std::vector<_T> vec;					\
			vec.resize(len);						\
			for (int i = 0; i < len; i++)			\
			{										\
				vec.emplace_back(*v[i]->NativePtr);	\
			}										\
			NativePtr = new _T(std::move(vec));		\
			OwnsNativeInstance = true;				\
		};


		ctor_List_RefType_Ptr(MC::Player^);
		ctor_List_RefType_Ptr(MC::Actor^);
		ctor_List_RefType_Ptr(MC::BlockActor^);
		ctor_List_RefType_Ptr(MC::Container^);

		ctor_List_RefType_Instance(MC::Vec3^);
		ctor_List_RefType_Instance(MC::BlockPos^);
		ctor_List_RefType_Instance(ItemType^);
		ctor_List_RefType_Instance(BlockType^);
		ctor_List_RefType_Instance(NbtType^);

#define List_Type2Valuetype(type)					\
		static operator Valuetype^ (List<type>^ v) {	\
			return gcnew Valuetype(v);					\
		};

		List_Type2Valuetype(double);
		List_Type2Valuetype(float);
		List_Type2Valuetype(__int64);
		List_Type2Valuetype(int);
		List_Type2Valuetype(short);
		List_Type2Valuetype(char);
		List_Type2Valuetype(unsigned __int64);
		List_Type2Valuetype(unsigned int);
		List_Type2Valuetype(unsigned short);
		List_Type2Valuetype(unsigned char);
		List_Type2Valuetype(bool);
		List_Type2Valuetype(NumberType);
		List_Type2Valuetype(String^);
		List_Type2Valuetype(MC::Player^);
		List_Type2Valuetype(MC::Actor^);
		List_Type2Valuetype(MC::BlockActor^);
		List_Type2Valuetype(MC::Container^);
		List_Type2Valuetype(MC::Vec3^);
		List_Type2Valuetype(MC::BlockPos^);
		List_Type2Valuetype(ItemType^);
		List_Type2Valuetype(BlockType^);
		List_Type2Valuetype(NbtType^);

#define ElementType2Valuetype_Implicit(type)	\
		static operator Valuetype ^ (type v) {	\
			return gcnew Valuetype(v);			\
		}

		ElementType2Valuetype_Implicit(bool);
		ElementType2Valuetype_Implicit(String^);
		ElementType2Valuetype_Implicit(NumberType);
		ElementType2Valuetype_Implicit(MC::Player^);
		ElementType2Valuetype_Implicit(MC::Actor^);
		ElementType2Valuetype_Implicit(MC::BlockActor^);
		ElementType2Valuetype_Implicit(MC::Container^);
		ElementType2Valuetype_Implicit(MC::Vec3^);
		ElementType2Valuetype_Implicit(MC::BlockPos^);
		ElementType2Valuetype_Implicit(ItemType^);
		ElementType2Valuetype_Implicit(BlockType^);
		ElementType2Valuetype_Implicit(NbtType^);


#define NumberType2Valuetype_Implicit(type)	\
        static operator Valuetype ^(type v) {		\
            return gcnew Valuetype(gcnew Value(v));	\
        }

		NumberType2Valuetype_Implicit(double);
		NumberType2Valuetype_Implicit(float);
		NumberType2Valuetype_Implicit(__int64);
		NumberType2Valuetype_Implicit(int);
		NumberType2Valuetype_Implicit(short);
		NumberType2Valuetype_Implicit(char);
		NumberType2Valuetype_Implicit(unsigned __int64);
		NumberType2Valuetype_Implicit(unsigned int);
		NumberType2Valuetype_Implicit(unsigned short);
		NumberType2Valuetype_Implicit(unsigned char);


#define Valuetype2ElementType_Implicit(type)	\
        static operator type(Valuetype ^ v) {	\
            Value ^ val;						\
            v->AsValue(val);					\
            return (type)val;					\
        }

		Valuetype2ElementType_Implicit(bool);
		Valuetype2ElementType_Implicit(String^);
		Valuetype2ElementType_Implicit(NumberType);
		Valuetype2ElementType_Implicit(MC::Player^);
		Valuetype2ElementType_Implicit(MC::Actor^);
		Valuetype2ElementType_Implicit(MC::BlockActor^);
		Valuetype2ElementType_Implicit(MC::Container^);
		Valuetype2ElementType_Implicit(MC::Vec3^);
		Valuetype2ElementType_Implicit(MC::BlockPos^);
		Valuetype2ElementType_Implicit(ItemType^);
		Valuetype2ElementType_Implicit(BlockType^);
		Valuetype2ElementType_Implicit(NbtType^);

#define Valuetype2SimpleType_Implicit(type)		\
		static operator type(Valuetype^ v) {	\
			return (type)(NumberType)v;			\
		};

		Valuetype2SimpleType_Implicit(double);
		Valuetype2SimpleType_Implicit(float);
		Valuetype2SimpleType_Implicit(__int64);
		Valuetype2SimpleType_Implicit(int);
		Valuetype2SimpleType_Implicit(short);
		Valuetype2SimpleType_Implicit(char);
		Valuetype2SimpleType_Implicit(unsigned __int64);
		Valuetype2SimpleType_Implicit(unsigned int);
		Valuetype2SimpleType_Implicit(unsigned short);
		Valuetype2SimpleType_Implicit(unsigned char);


#define Valuetype2List_Implicit(type)						\
		static operator List<type> ^ (Valuetype^ v) {		\
			auto list = (List<Valuetype^>^)(v);				\
			auto ret = gcnew List<type>(list->Count);		\
			for each (auto var in list)						\
			{												\
				ret->Add((type)var);						\
			}												\
			return ret;										\
		}


		Valuetype2List_Implicit(String^);
		Valuetype2List_Implicit(MC::Player^);
		Valuetype2List_Implicit(MC::Actor^);
		Valuetype2List_Implicit(MC::BlockActor^);
		Valuetype2List_Implicit(MC::Container^);
		Valuetype2List_Implicit(MC::Vec3^);
		Valuetype2List_Implicit(MC::BlockPos^);
		Valuetype2List_Implicit(ItemType^);
		Valuetype2List_Implicit(BlockType^);
		Valuetype2List_Implicit(NbtType^);
		Valuetype2List_Implicit(bool);
		Valuetype2List_Implicit(NumberType);
		Valuetype2List_Implicit(double);
		Valuetype2List_Implicit(float);
		Valuetype2List_Implicit(__int64);
		Valuetype2List_Implicit(int);
		Valuetype2List_Implicit(short);
		Valuetype2List_Implicit(char);
		Valuetype2List_Implicit(unsigned __int64);
		Valuetype2List_Implicit(unsigned int);
		Valuetype2List_Implicit(unsigned short);
		Valuetype2List_Implicit(unsigned char);


#define List2Valuetype_Implicit(type)						\
		static operator Valuetype^ ( List<type> ^ v) {		\
			auto list = (List<Valuetype^>^)(v);				\
			auto ret = gcnew List<type>(list->Count);		\
			for each (auto var in list)						\
			{												\
				ret->Add((type)var);						\
			}												\
			return ret;										\
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
	public:
		virtual String^ ToString() override {
			auto type = InstanceType(NativePtr->value.index());

			String^ info = nullptr;
			switch (type)
			{
			case InstanceType::Value:
			{
				Value^ val;
				this->AsValue(val);
				info = "<" + "Value" + L',' + val->ToString() + ">";

			}
			break;
			case InstanceType::ArrayType:
			{
				ArrayType^ arr;
				this->AsArrayType(arr);
				info = "<" + "ArrayType" + L',' + arr->ToString() + ">";
			}
			break;
			case InstanceType::ObjectType:
			{
				ObjectType^ obj;
				this->AsObjectType(obj);
				info = "<" + "ObjectType" + L',' + obj->ToString() + ">";
			}
			break;
			}
			return info;
		}
		property InstanceType Type {
			InstanceType get() {
				return InstanceType(NativePtr->value.index());
			}
		}
	};
}
