#pragma once
#include "include.hpp"
#include "Value.hpp"

namespace LLNET::RemoteCall {
	public
	ref class Valuetype : ClassTemplate<Valuetype, ::RemoteCall::ValueType>
	{
		using _T = ::RemoteCall::ValueType;

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
			ObjectType(Dictionary<String^, Valuetype^>^ v)
				: value(v)
			{
			}
			operator Dictionary<String^, Valuetype^> ^ () {
				return value;
			};
			Dictionary<String^, Valuetype^>^ value;
		};

		[RemoteCallValueType(InstanceType::ArrayType)]
		ref class ArrayType : IValueType
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
