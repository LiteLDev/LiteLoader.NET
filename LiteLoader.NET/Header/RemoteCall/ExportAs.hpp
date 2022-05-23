#pragma once
#include "ValueType.hpp"

namespace LLNET::RemoteCall {

	ref class ExportRegister {
	internal:
		enum class ValidType {
			Invalid,

			Double,
			Float,
			Int64,
			Int32,
			Int16,
			Int8,
			UInt64,
			UInt32,
			UInt16,
			UInt8,

			Bool,
			String,
			NumberType,
			Player,
			Actor,
			BlockActor,
			Container,
			Vec3,
			BlockPos,
			ItemType,
			BlockType,
			NbtType,

			List,
			Dictionary,

			Void
		};
		ref struct FunctionInfo {
			value struct TypeInfo {
				ValidType type;
				array<TypeInfo>^ genericArgs;
			};
			TypeInfo returnType;
			array<TypeInfo>^ paramters;
		};
		ref class ExportFunc {
			String^ nameSpace;
			String^ funcName;
			FunctionInfo^ info;
			System::Delegate^ func;
			GCHandle gch;
		public:
			delegate ::RemoteCall::ValueType delNative(std::vector<::RemoteCall::ValueType>);
			typedef ::RemoteCall::ValueType(*pNative)(std::vector<::RemoteCall::ValueType>);
		private:
			inline ExportFunc(String^ nameSpace, String^ funcName, FunctionInfo^ info, System::Delegate^ del);
			inline NATIVECALLBACK::RemoteCall::ValueType _nativeFunc(std::vector<::RemoteCall::ValueType> vec);
		public:
			static Pair<ExportFunc^, delNative^> Create(String^ nameSpace, String^ funcName, FunctionInfo^ info, System::Delegate^ del);

		};

		static Pair<bool, ValidType> _tryGetValidType(System::Type^ t);
		static FunctionInfo::TypeInfo _generateTypeInfo(System::Type^ t);
		static Object^ _parseParamter(FunctionInfo::TypeInfo const% info, ::RemoteCall::ValueType& val);
		static ::RemoteCall::ValueType _parseReturnVal(FunctionInfo::TypeInfo const% info, Object^ val);
		static List<ExportFunc^>^ ExportFunctions = gcnew List<ExportFunc^>;
	public:
		generic<typename TDelegate>
		where TDelegate : System::Delegate
			static void RegisterFunction(String^ nameSpace, String^ funcName, TDelegate func) {
			NULL_ARG_CHEEK(nameSpace);
			NULL_ARG_CHEEK(funcName);
			NULL_ARG_CHEEK(func);

			auto funcinfo = gcnew FunctionInfo;
			auto method = func->Method;
			auto params = method->GetParameters();
			funcinfo->paramters = gcnew array<FunctionInfo::TypeInfo>(params->Length);
			funcinfo->returnType = _generateTypeInfo(method->ReturnType);
			for (int i = 0; i < params->Length; ++i) {
				funcinfo->paramters[i] = _generateTypeInfo(params[i]->ParameterType);
			}

			auto exportfunc = ExportFunc::Create(nameSpace, funcName, funcinfo, func);
			ExportFunctions->Add(exportfunc.Key);
			auto pfunc = static_cast<ExportFunc::pNative>((void*)Marshal::GetFunctionPointerForDelegate(exportfunc.Value));
			auto succeed = ::RemoteCall::exportFunc(marshalString(nameSpace), marshalString(funcName), pfunc, MODULE);

			//debug
			Console::WriteLine(succeed);
			/*Console::WriteLine("{0},{1}", typeinfo.type, typeinfo.genericArgs->Length);*/

		}
	};
}

#include <stdint.h>

namespace LLNET::RemoteCall {
	Pair<bool, ExportRegister::ValidType> ExportRegister::_tryGetValidType(System::Type^ t)
	{
		using RTN = Pair<bool, ValidType>;

		if (t == double::typeid)
			return RTN(true, ValidType::Double);
		if (t == float::typeid)
			return RTN(true, ValidType::Float);
		if (t == int64_t::typeid)
			return RTN(true, ValidType::Int64);
		if (t == int32_t::typeid)
			return RTN(true, ValidType::Int32);
		if (t == int16_t::typeid)
			return RTN(true, ValidType::Int16);
		if (t == int8_t::typeid)
			return RTN(true, ValidType::Int8);
		if (t == uint64_t::typeid)
			return RTN(true, ValidType::UInt64);
		if (t == uint32_t::typeid)
			return RTN(true, ValidType::UInt32);
		if (t == uint16_t::typeid)
			return RTN(true, ValidType::UInt16);
		if (t == uint8_t::typeid)
			return RTN(true, ValidType::UInt8);

		if (t == bool::typeid)
			return RTN(true, ValidType::Bool);
		if (t == String::typeid)
			return RTN(true, ValidType::String);
		if (t == NumberType::typeid)
			return RTN(true, ValidType::NumberType);
		if (t == MC::Player::typeid)
			return RTN(true, ValidType::Player);
		if (t == MC::Actor::typeid)
			return RTN(true, ValidType::Actor);
		if (t == MC::BlockActor::typeid)
			return RTN(true, ValidType::BlockActor);
		if (t == MC::Container::typeid)
			return RTN(true, ValidType::Container);
		if (t == MC::Vec3::typeid)
			return RTN(true, ValidType::Vec3);
		if (t == MC::BlockPos::typeid)
			return RTN(true, ValidType::BlockPos);
		if (t == ItemType::typeid)
			return RTN(true, ValidType::ItemType);
		if (t == BlockType::typeid)
			return RTN(true, ValidType::BlockType);
		if (t == NbtType::typeid)
			return RTN(true, ValidType::NbtType);
		if (t == void::typeid)
			return RTN(true, ValidType::Void);

		if (t->Namespace == "System.Collections.Generic" && t->Name == "List`1")
			return RTN(true, ValidType::List);

		if (t->Namespace == "System.Collections.Generic" && t->Name == "Dictionary`2") {
			auto genericTypes = t->GenericTypeArguments;
			if (genericTypes[0] != String::typeid) {
				return RTN(false, ValidType::Invalid);
			}
			return RTN(true, ValidType::Dictionary);

		}
		return RTN(false, ValidType::Invalid);
	}
	ExportRegister::FunctionInfo::TypeInfo ExportRegister::_generateTypeInfo(System::Type^ t)
	{

		auto type = _tryGetValidType(t);
		if (!type.Key)
			throw gcnew LLNET::Core::InvalidRemoteCallTypeException;

		auto ret = FunctionInfo::TypeInfo();
		ret.type = type.Value;

		switch (type.Value)
		{
		case LLNET::RemoteCall::ExportRegister::ValidType::List:
		{
			ret.genericArgs = gcnew array<FunctionInfo::TypeInfo>(1);

			ret.genericArgs[0] = _generateTypeInfo(t->GenericTypeArguments[0]);
		}
		break;

		case LLNET::RemoteCall::ExportRegister::ValidType::Dictionary:
		{
			ret.genericArgs = gcnew array<FunctionInfo::TypeInfo>(2);

			ret.genericArgs[0] = _generateTypeInfo(t->GenericTypeArguments[0]);
			ret.genericArgs[1] = _generateTypeInfo(t->GenericTypeArguments[1]);
		}
		break;

		default:
			break;
		case LLNET::RemoteCall::ExportRegister::ValidType::Invalid:
			throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
		}

		return ret;
	}
	inline System::Object^ ExportRegister::_parseParamter(FunctionInfo::TypeInfo const% info, ::RemoteCall::ValueType& val)
	{
		throw gcnew System::NotImplementedException;
		//switch (info.type)
		//{
		//case LLNET::RemoteCall::ExportRegister::ValidType::Invalid:
		//	throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
		//case LLNET::RemoteCall::ExportRegister::ValidType::Double:
		//{
		//	return(Object^)std::get<::RemoteCall::NumberType>(std::get<::RemoteCall::Value>(val.value)).get<double>();
		//}
		//break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::Float:
		//{
		//	return (Object^)std::get<float>(val.value);
		//}
		//break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::Int64:
		//{
		//	return (Object^)std::get<int64_t>(val.value);
		//}
		//break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::Int32:
		//{
		//	return (Object^)std::get<int32_t>(val.value);
		//}
		//break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::Int16:
		//{
		//	return (Object^)std::get<int16_t>(val.value);
		//}
		//break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::Int8:
		//{
		//	return (Object^)std::get<int8_t>(val.value);
		//}
		//break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::UInt64:
		//{
		//	return (Object^)std::get<uint64_t>(val.value);
		//}
		//break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::UInt32:
		//{
		//	return (Object^)std::get<uint32_t>(val.value);
		//}
		//break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::UInt16:
		//{
		//	return (Object^)std::get<uint16_t>(val.value);
		//}
		//break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::UInt8:
		//{
		//	return (Object^)std::get<uint8_t>(val.value);
		//}
		//break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::Bool:
		//{
		//	return (Object^)std::get<bool>(val.value);
		//}
		//break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::String:
		//{
		//	return (Object^)marshalString(std::get<std::string>(val.value));
		//}
		//break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::NumberType:
		//	break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::Player:
		//	break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::Actor:
		//	break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::BlockActor:
		//	break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::Container:
		//	break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::Vec3:
		//	break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::BlockPos:
		//	break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::ItemType:
		//	break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::BlockType:
		//	break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::NbtType:
		//	break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::List:
		//	break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::Dictionary:
		//	break;
		//case LLNET::RemoteCall::ExportRegister::ValidType::Void:
		//	break;
		//default:
		//	break;
		//}
	}
	inline ::RemoteCall::ValueType ExportRegister::_parseReturnVal(FunctionInfo::TypeInfo const% info, Object^ val)
	{
		throw gcnew System::NotImplementedException;
	}
	inline ExportRegister::ExportFunc::ExportFunc(String^ nameSpace, String^ funcName, FunctionInfo^ info, System::Delegate^ del)
		:nameSpace(nameSpace), funcName(funcName), info(info), func(del)
	{
	}
	inline Pair<ExportRegister::ExportFunc^, ExportRegister::ExportFunc::delNative^> ExportRegister::ExportFunc::Create(String^ nameSpace, String^ funcName, FunctionInfo^ info, System::Delegate^ del) {
		auto instance = gcnew ExportFunc(nameSpace, funcName, info, del);
		auto delnative = gcnew ExportFunc::delNative(instance, &ExportFunc::_nativeFunc);
		instance->gch = GCHandle::Alloc(delnative);
		return Pair<ExportFunc^, ExportFunc::delNative^>(instance, delnative);
	}

	inline NATIVECALLBACK::RemoteCall::ValueType ExportRegister::ExportFunc::_nativeFunc(std::vector<::RemoteCall::ValueType> vec) {
		auto args = gcnew array<Object^>(info->paramters->Length);
		for (int i = 0; i < info->paramters->Length; ++i)
		{
			args[i] = _parseParamter(info->paramters[i], vec[i]);
		}

		auto ret = func->DynamicInvoke(args);

		return std::move(_parseReturnVal(info->returnType, ret));
	}
}
