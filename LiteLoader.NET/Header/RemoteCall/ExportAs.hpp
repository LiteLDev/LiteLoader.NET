#pragma once
#include "ValueType.hpp"

namespace LLNET::RemoteCall {



	ref class ExportFunctionRegister {
	internal:
		delegate ::RemoteCall::ValueType delNative(std::vector<::RemoteCall::ValueType>);
		typedef ::RemoteCall::ValueType(*pNative)(std::vector<::RemoteCall::ValueType>);

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

			WorldPosType,
			BlockPosType,
			ItemType,
			BlockType,
			NbtType,

			List,
			Dictionary,

			Void
		};
		ref struct FunctionInfo {
			value struct TypeInfo {
				System::Type^ _type;
				ValidType type;
				array<TypeInfo>^ genericArgs;
			};
			TypeInfo returnType;
			array<TypeInfo>^ parameters;
		};
		ref class ExportFunc {
			String^ nameSpace;
			String^ funcName;
			FunctionInfo^ info;
			System::Delegate^ func;
			GCHandle gch;
		private:
			inline ExportFunc(String^ nameSpace, String^ funcName, FunctionInfo^ info, System::Delegate^ del);

			inline NATIVECALLBACK::RemoteCall::ValueType _nativeFunc(std::vector<::RemoteCall::ValueType> vec);
		public:
			static Pair<ExportFunc^, delNative^> Create(String^ nameSpace, String^ funcName, FunctionInfo^ info, System::Delegate^ del);

			virtual String^ ToString() override
			{
				return String::Format("NameSpace:{0},FunctionName:{1}", nameSpace, funcName);
			}
		};

		static Pair<bool, ValidType> _tryGetValidType(System::Type^ t);

		static FunctionInfo::TypeInfo _generateTypeInfo(System::Type^ t);

		static Object^ _parseParameter(FunctionInfo::TypeInfo const% info, ::RemoteCall::ValueType& val);

		static ::RemoteCall::ValueType _parseReturnVal(FunctionInfo::TypeInfo const% info, Object^ val);

		static List<ExportFunc^>^ ExportFunctions = gcnew List<ExportFunc^>;
	public:
		generic<typename TDelegate>
		where TDelegate : System::Delegate
			static bool RegisterExportFunction(String^ nameSpace, String^ funcName, TDelegate func) {
			NULL_ARG_CHEEK(nameSpace);
			NULL_ARG_CHEEK(funcName);
			NULL_ARG_CHEEK(func);

			auto funcinfo = gcnew FunctionInfo;
			auto method = func->Method;
			auto params = method->GetParameters();
			funcinfo->parameters = gcnew array<FunctionInfo::TypeInfo>(params->Length);
			funcinfo->returnType = _generateTypeInfo(method->ReturnType);
			for (int i = 0; i < params->Length; ++i) {
				funcinfo->parameters[i] = _generateTypeInfo(params[i]->ParameterType);
			}

			auto exportfunc = ExportFunc::Create(nameSpace, funcName, funcinfo, func);
			ExportFunctions->Add(exportfunc.Key);
			auto pfunc = static_cast<pNative>((void*)Marshal::GetFunctionPointerForDelegate(exportfunc.Value));
			return ::RemoteCall::exportFunc(marshalString(nameSpace), marshalString(funcName), pfunc, Global::__GetCurrentModule(Assembly::GetCallingAssembly()));

			//debug
			//Console::WriteLine(succeed);
			/*Console::WriteLine("{0},{1}", typeinfo.type, typeinfo.genericArgs->Length);*/

		}
	};
}

#include <stdint.h>

namespace LLNET::RemoteCall {
	Pair<bool, ExportFunctionRegister::ValidType> ExportFunctionRegister::_tryGetValidType(System::Type^ t)
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


		if (t == WorldPosType::typeid)
			return RTN(true, ValidType::WorldPosType);
		if (t == BlockPosType::typeid)
			return RTN(true, ValidType::BlockPosType);
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
	ExportFunctionRegister::FunctionInfo::TypeInfo ExportFunctionRegister::_generateTypeInfo(System::Type^ t)
	{

		auto type = _tryGetValidType(t);
		if (!type.Key)
			throw gcnew LLNET::Core::InvalidRemoteCallTypeException;

		auto ret = FunctionInfo::TypeInfo();
		ret._type = t;
		ret.type = type.Value;

		switch (type.Value)
		{
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::List:
		{
			ret.genericArgs = gcnew array<FunctionInfo::TypeInfo>(1);

			ret.genericArgs[0] = _generateTypeInfo(t->GenericTypeArguments[0]);
		}
		break;

		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Dictionary:
		{
			ret.genericArgs = gcnew array<FunctionInfo::TypeInfo>(2);

			ret.genericArgs[0] = _generateTypeInfo(t->GenericTypeArguments[0]);
			ret.genericArgs[1] = _generateTypeInfo(t->GenericTypeArguments[1]);
		}
		break;

		default:
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Invalid:
			throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
		}

		return ret;
	}
	inline System::Object^ ExportFunctionRegister::_parseParameter(FunctionInfo::TypeInfo const% info, ::RemoteCall::ValueType& val)
	{

#define _VALUE std::get<::RemoteCall::Value>(val.value)
#define _NUMBERTYPE std::get<::RemoteCall::NumberType>(_VALUE)

		switch (info.type)
		{
		case ExportFunctionRegister::ValidType::Invalid:
			throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
		case ExportFunctionRegister::ValidType::Double:
		{
			return _NUMBERTYPE.get<double>();
		}
		break;
		case ExportFunctionRegister::ValidType::Float:
		{
			return _NUMBERTYPE.get<float>();
		}
		break;
		case ExportFunctionRegister::ValidType::Int64:
		{
			return _NUMBERTYPE.get<int64_t>();
		}
		break;
		case ExportFunctionRegister::ValidType::Int32:
		{
			return _NUMBERTYPE.get<int32_t>();
		}
		break;
		case ExportFunctionRegister::ValidType::Int16:
		{
			return _NUMBERTYPE.get<int16_t>();
		}
		break;
		case ExportFunctionRegister::ValidType::Int8:
		{
			return _NUMBERTYPE.get<int8_t>();
		}
		break;
		case ExportFunctionRegister::ValidType::UInt64:
		{
			return _NUMBERTYPE.get<uint64_t>();
		}
		break;
		case ExportFunctionRegister::ValidType::UInt32:
		{
			return _NUMBERTYPE.get<uint32_t>();
		}
		break;
		case ExportFunctionRegister::ValidType::UInt16:
		{
			return _NUMBERTYPE.get<uint16_t>();
		}
		break;
		case ExportFunctionRegister::ValidType::UInt8:
		{
			return _NUMBERTYPE.get<uint8_t>();
		}
		break;
		case ExportFunctionRegister::ValidType::Bool:
		{
			return std::get<bool>(_VALUE);
		}
		break;
		case ExportFunctionRegister::ValidType::String:
		{
			return marshalString(std::get<std::string>(_VALUE));
		}
		break;
		case ExportFunctionRegister::ValidType::NumberType:
			return NumberType(_NUMBERTYPE);
			break;
		case ExportFunctionRegister::ValidType::Player:
			return gcnew MC::Player(std::get<::Player*>(_VALUE));
			break;
		case ExportFunctionRegister::ValidType::Actor:
			return gcnew MC::Actor(std::get<::Actor*>(_VALUE));
			break;
		case ExportFunctionRegister::ValidType::BlockActor:
			return gcnew MC::BlockActor(std::get<::BlockActor*>(_VALUE));
			break;
		case ExportFunctionRegister::ValidType::Container:
			return gcnew MC::Container(std::get<::Container*>(_VALUE));
			break;
		case ExportFunctionRegister::ValidType::Vec3:
			return MC::Vec3(std::get<::RemoteCall::WorldPosType>(_VALUE).pos);
			break;
		case ExportFunctionRegister::ValidType::BlockPos:
			return MC::BlockPos(std::get<::RemoteCall::BlockPosType>(_VALUE).pos);
			break;
		case ExportFunctionRegister::ValidType::WorldPosType:
			return gcnew WorldPosType(std::get<::RemoteCall::WorldPosType>(_VALUE));
			break;
		case ExportFunctionRegister::ValidType::BlockPosType:
			return gcnew BlockPosType(std::get<::RemoteCall::BlockPosType>(_VALUE));
			break;
		case ExportFunctionRegister::ValidType::ItemType:
			return gcnew ItemType(std::get<::RemoteCall::ItemType>(_VALUE));
			break;
		case ExportFunctionRegister::ValidType::BlockType:
			return gcnew BlockType(std::get<::RemoteCall::BlockType>(_VALUE));
			break;
		case ExportFunctionRegister::ValidType::NbtType:
			return gcnew NbtType(std::get<::RemoteCall::NbtType>(_VALUE));
			break;
		case ExportFunctionRegister::ValidType::List:
		{
			auto& vec = std::get<::RemoteCall::ValueType::ArrayType>(val.value);
			auto ret = System::Activator::CreateInstance(info._type, gcnew array<System::Object^>{(int)vec.size()});
			auto addMethod = info._type->GetMethod("Add");
			for (auto& val : vec) {
				addMethod->Invoke(ret, gcnew array<System::Object^>{_parseParameter(info.genericArgs[0], val)});
			}
			return ret;
		}
		break;
		case ExportFunctionRegister::ValidType::Dictionary:
		{
			auto& umap = std::get<::RemoteCall::ValueType::ObjectType>(val.value);
			auto ret = System::Activator::CreateInstance(info._type, gcnew array<System::Object^>{(int)umap.size()});
			auto addMethod = info._type->GetMethod("Add");
			for (auto& val : umap) {
				addMethod->Invoke(ret, gcnew array<System::Object^>{marshalString(val.first), _parseParameter(info.genericArgs[1], val.second)});
			}
			return ret;
		}
		break;
		case ExportFunctionRegister::ValidType::Void:
		default:
			return nullptr;
			break;
		}
	}
	inline ::RemoteCall::ValueType ExportFunctionRegister::_parseReturnVal(FunctionInfo::TypeInfo const% info, Object^ val)
	{
		switch (info.type)
		{
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Invalid:
			throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Double:
			return ::RemoteCall::NumberType((double)val);
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Float:
			return ::RemoteCall::NumberType((float)val);
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Int64:
			return ::RemoteCall::NumberType((long long)val);
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Int32:
			return ::RemoteCall::NumberType((int)val);
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Int16:
			return ::RemoteCall::NumberType((short)val);
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Int8:
			return ::RemoteCall::NumberType((signed char)val);
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::UInt64:
			return ::RemoteCall::NumberType((unsigned long long)val);
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::UInt32:
			return ::RemoteCall::NumberType((unsigned int)val);
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::UInt16:
			return ::RemoteCall::NumberType((unsigned short)val);
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::UInt8:
			return ::RemoteCall::NumberType((unsigned char)val);
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Bool:
			return ::RemoteCall::packValue((bool)val);
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::String:
			return marshalString((String^)(val));
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::NumberType:
			return static_cast<NumberType>(val)._toNative();
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Player:
			return static_cast<MC::Player^>(val)->NativePtr;
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Actor:
			return static_cast<MC::Actor^>(val)->NativePtr;
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::BlockActor:
			return static_cast<MC::BlockActor^>(val)->NativePtr;
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Container:
			return static_cast<MC::Container^>(val)->NativePtr;
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Vec3:
			return ::RemoteCall::packValue(std::make_pair(::Vec3(static_cast<MC::Vec3>(val)), 0));
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::BlockPos:
			return ::RemoteCall::packValue(std::make_pair(::BlockPos(static_cast<MC::BlockPos>(val)), 0));
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::WorldPosType:
			return *static_cast<WorldPosType^>(val)->NativePtr;
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::BlockPosType:
			return *static_cast<BlockPosType^>(val)->NativePtr;
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::ItemType:
			return *static_cast<ItemType^>(val)->NativePtr;
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::BlockType:
			return *static_cast<BlockType^>(val)->NativePtr;
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::NbtType:
			return *static_cast<NbtType^>(val)->NativePtr;
			break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::List:
		{
			auto list = static_cast<List<Object^>^>(val);
			auto ret = ::RemoteCall::ValueType::ArrayType();
			for (int i = 0; i < list->Count; ++i)
			{
#ifdef REMOTECALL_DEBUG
				REMOTECALL_DEBUG_INFO(list[i]);
#endif // REMOTECALL_DEBUG

				ret[i] = std::move(_parseReturnVal(info.genericArgs[0], list[i]));
			}
			return ret;
		}
		break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Dictionary:
		{
			auto dic = static_cast<Dictionary<String^, Object^>^>(val);
			auto ret = ::RemoteCall::ValueType::ObjectType();
			for each (auto var in dic)
			{
				ret[marshalString(var.Key)] = std::move(_parseReturnVal(info.genericArgs[2], var.Value));
			}
			return ret;
		}
		break;
		case LLNET::RemoteCall::ExportFunctionRegister::ValidType::Void:
		default:
			return ::RemoteCall::ValueType(nullptr);
			break;
		}
	}
	inline ExportFunctionRegister::ExportFunc::ExportFunc(String^ nameSpace, String^ funcName, FunctionInfo^ info, System::Delegate^ del)
		:nameSpace(nameSpace), funcName(funcName), info(info), func(del)
	{
	}
	inline Pair<ExportFunctionRegister::ExportFunc^, ExportFunctionRegister::delNative^> ExportFunctionRegister::ExportFunc::Create(String^ nameSpace, String^ funcName, FunctionInfo^ info, System::Delegate^ del) {
		auto instance = gcnew ExportFunc(nameSpace, funcName, info, del);
		auto delnative = gcnew delNative(instance, &ExportFunc::_nativeFunc);
		instance->gch = GCHandle::Alloc(delnative);
		return Pair<ExportFunc^, delNative^>(instance, delnative);
	}
	inline NATIVECALLBACK::RemoteCall::ValueType ExportFunctionRegister::ExportFunc::_nativeFunc(std::vector<::RemoteCall::ValueType> vec) {
		auto args = gcnew array<Object^>(info->parameters->Length);
		for (int i = 0; i < info->parameters->Length; ++i)
		{
			args[i] = _parseParameter(info->parameters[i], vec[i]);
		}

		auto ret = func->DynamicInvoke(args);

		return std::move(_parseReturnVal(info->returnType, ret));
	}
}
