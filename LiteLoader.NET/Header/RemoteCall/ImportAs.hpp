#pragma once
#include "RemoteCallFunctionRegisterBase.hpp"
using namespace System::Reflection::Emit;

constexpr int retIndex = 0;
constexpr int nativeParamIndex = 1;

namespace LLNET::RemoteCall {
	ref class ImportFunctionRegister
		:RemoteCallFunctionRegisterBase
	{
	internal:
		/// <summary>
		/// <para>stack+=2</para>
		/// <para>[Push]</para>
		/// <para>£­local ::RemoteCall::ValueType pointer</para>
		/// <para>£­arg</para>
		/// </summary>
		inline static void loadParameter(ILGenerator^ il, int localIndex, int paramIndex, Dictionary<int, LocalBuilder^>% locals);
		/// <summary>
		/// <para>stack+=0</para>
		/// <para>[None]</para>
		/// </summary>
		inline static void emplaceBack(ILGenerator^ il, int localIndex, Dictionary<int, LocalBuilder^>% locals);
		/// <summary>
		/// <para>stack-=2</para>
		/// <para>[Using]</para>
		/// <para>£­local ::RemoteCall::ValueType pointer</para>
		/// <para>£­object</para>
		/// </summary>
		inline static void parseParameter(ILGenerator^ il, FunctionInfo::TypeInfo% info, Dictionary<int, LocalBuilder^>% locals);
		inline static void parseReturnval(ILGenerator^ il, FunctionInfo::TypeInfo% returnvalinfo, Dictionary<int, LocalBuilder^>% locals);

		//ref class Listhelper {
		//public:
		//	inline static void* _create_RemoteCall_ArrayType();
		//	inline static void _ArrayType_emplace_back(void* arrType, void* val);

		//	__METHOD_INFO(create_RemoteCall_ArrayType, _create_RemoteCall_ArrayType);
		//	__METHOD_INFO(ArrayType_emplace_back, _ArrayType_emplace_back);
		//};

		ref struct ImportedFunc {
			String^ nameSpace;
			String^ funcName;
			::RemoteCall::CallbackFn* pfunc;

			void* _Invoke(void* vec);

			static initonly MethodInfo^ Invoke = ImportedFunc::typeid->GetMethod("_Invoke");


			~ImportedFunc() {
				delete pfunc;
			}

			Object^ TEST(int a, String^ str) {
				auto vec = _create_ArrayType();
				auto val1 = _int32_t2Native(a);
				_emplace_back(&vec, &val1);
				auto val2 = _string2Native(str);
				_emplace_back(&vec, &val2);
				auto _ret = _Invoke(&vec);
				auto ret = _Native2int32_t(_ret);
				_delete_ArrayType(&vec);
				_delete_ValueType(&_ret);

				return nullptr;
			}
		};
	public:
		generic<typename TDelegate>
		where TDelegate : System::Delegate
		static TDelegate RegisterImportFunction(String^ nameSpace, String^ funcName) {


			NULL_ARG_CHEEK(nameSpace);
			NULL_ARG_CHEEK(funcName);

			auto& _func = ::RemoteCall::importFunc(marshalString(nameSpace), marshalString(funcName));
			if (!_func)
				throw gcnew LLNET::Core::RemoteCallImportFunctionException(String::Format("Fail to import!Function[{0}.{1}] has not been exported", nameSpace, funcName));

			auto func = gcnew ImportedFunc;
			func->nameSpace = nameSpace;
			func->funcName = funcName;
			func->pfunc = new ::RemoteCall::CallbackFn(std::move(_func));

			auto delegateType = TDelegate::typeid;
			auto invokeMethod = delegateType->GetMethod("Invoke");
			auto params = invokeMethod->GetParameters();

			//generate funcinfo
			auto funcinfo = gcnew FunctionInfo;
			funcinfo->parameters = gcnew array<FunctionInfo::TypeInfo>(params->Length);
			funcinfo->returnType = _generateTypeInfo(invokeMethod->ReturnType);
			for (int i = 0; i < params->Length; ++i) {
				funcinfo->parameters[i] = _generateTypeInfo(params[i]->ParameterType);
			}
			//end


			auto methodArgs = gcnew array<System::Type^>(funcinfo->parameters->Length + 1);
			methodArgs[0] = ImportedFunc::typeid;
			for (int i = 1; i < methodArgs->Length; ++i) {
				methodArgs[i] = funcinfo->parameters[i - 1]._type;
			}

			auto method = gcnew DynamicMethod(funcName, invokeMethod->ReturnType, methodArgs);
			auto il = method->GetILGenerator();


#define oc OpCodes

			/*
			* local:
			* 0£­ret				(::RemoteCall::ValueType*)
			* 1£­nativeParameters	(std::vector<::RemoteCall::ValueType>)
			* 2£­arg1				(::RemoteCall::ValueType)
			*
			* ...					(::RemoteCall::ValueType)
			*
			* N£­argN				(::RemoteCall::ValueType)
			*/

			/*
			* parameter:
			* 0£­this				(ImportedFunc class)
			* 1£­delegate arg1		(Unknown)
			*
			* ...					(Unknown)
			*
			* N£­delegate argN		(Unknown)
			*/



			//declare local
			Dictionary<int, LocalBuilder^> locals;
			locals.Add(0, il->DeclareLocal(::RemoteCall::ValueType::typeid->MakePointerType(), true));
			locals.Add(1, il->DeclareLocal(std::vector<::RemoteCall::ValueType>::typeid, true));
			for (int i = 0; i < funcinfo->parameters->Length; ++i)
				locals.Add(i + 2, il->DeclareLocal(::RemoteCall::ValueType::typeid, true));
			//declare local end

			//il code start
			//	init memblock
			il->Emit(oc::Ldloca_S, locals[nativeParamIndex]);
			il->Emit(oc::Ldc_I4_0);
			il->Emit(oc::Ldc_I4_S, 24);
			il->Emit(oc::Conv_I8);
			//		>stack:3<
			il->Emit(oc::Initblk);
			//		>stack:0<
			//	init block end
			//	init std::vector start
			il->Emit(oc::Ldloca_S, locals[nativeParamIndex]);
			il->EmitCall(oc::Call, create_ArrayType, nullptr);
			//		>stack:1<
			il->Emit(oc::Pop);
			//		>stack:0<
			//	init std::vector end
			//	prase args start

#ifdef REMOTECALL_DEBUG
			il->EmitWriteLine("[RemoteCall.Import]Try parse parameter");
#endif // REMOTECALL_DEBUG
			for (int i = 0; i < funcinfo->parameters->Length; ++i) {
				int currentParamIndex = i + 1;
				int currentlocalIndex = i + 2;

				loadParameter(il, currentlocalIndex, currentParamIndex, locals);
				parseParameter(il, funcinfo->parameters[i], locals);
				emplaceBack(il, currentlocalIndex, locals);
			}
			//		>stack:0<
			//	prase args end
			//	invoke this->_Invoke(std::vector<::RemoteCall::ValueType>*) start
			il->Emit(oc::Ldarg_0);
			il->Emit(oc::Ldloca_S, locals[nativeParamIndex]);
			//		>stack:2<
#ifdef REMOTECALL_DEBUG
			il->EmitWriteLine("[RemoteCall.Import]Try invoke");
#endif // REMOTECALL_DEBUG
			il->EmitCall(oc::Call, ImportedFunc::Invoke, nullptr);
			//		>stack:1<
			//	invoke this->_Invoke(std::vector<::RemoteCall::ValueType>*) end
			//	store ret(::RemoteCall::ValueType pointer) start
			il->Emit(oc::Stloc_0);
			//		>stack:0<
			//	store ret(::RemoteCall::ValueType pointer) end
			//	parse return val start
			il->Emit(oc::Ldloc_0);
			//		>stack:1<
#ifdef REMOTECALL_DEBUG
			il->EmitWriteLine("[RemoteCall.Import]Try parse return val");
#endif // REMOTECALL_DEBUG
			parseReturnval(il, funcinfo->returnType, locals);
			//		>stack:1(if return type == void:0)<
			//	parse return val end
			//	delete start
			il->Emit(oc::Ldloc_0);
			il->EmitCall(oc::Call, delete_ValueType, nullptr);
			//		>stack:1(if return type == void:0)<
			il->Emit(oc::Ldloca_S, locals[nativeParamIndex]);
			il->EmitCall(oc::Call, delete_ArrayType, nullptr);
			//		>stack:1(if return type == void:0)<
			//	delete end

#ifdef REMOTECALL_DEBUG
			il->EmitWriteLine("[RemoteCall.Import]Try ret");
#endif // REMOTECALL_DEBUG

			//	return start
			il->Emit(oc::Ret);
			//	return end
			//il code end



			auto ret = (TDelegate)method->CreateDelegate(TDelegate::typeid, func);
			return ret;
		}
	};
}

inline void LLNET::RemoteCall::ImportFunctionRegister::parseParameter(ILGenerator^ il, FunctionInfo::TypeInfo% info, Dictionary<int, LocalBuilder^>% locals)
{
	//>stack:2<

	switch (info.type)
	{
	case ValidType::Invalid:
		throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
		break;
	case ValidType::Double:
		il->EmitCall(OpCodes::Call, double2Native, nullptr);
		break;
	case ValidType::Float:
		il->EmitCall(OpCodes::Call, float2Native, nullptr);
		break;
	case ValidType::Int64:
		il->EmitCall(OpCodes::Call, int64_t2Native, nullptr);
		break;
	case ValidType::Int32:
		il->EmitCall(OpCodes::Call, int32_t2Native, nullptr);
		break;
	case ValidType::Int16:
		il->EmitCall(OpCodes::Call, int16_t2Native, nullptr);
		break;
	case ValidType::Int8:
		il->EmitCall(OpCodes::Call, int8_t2Native, nullptr);
		break;
	case ValidType::UInt64:
		il->EmitCall(OpCodes::Call, uint64_t2Native, nullptr);
		break;
	case ValidType::UInt32:
		il->EmitCall(OpCodes::Call, uint32_t2Native, nullptr);
		break;
	case ValidType::UInt16:
		il->EmitCall(OpCodes::Call, uint16_t2Native, nullptr);
		break;
	case ValidType::UInt8:
		il->EmitCall(OpCodes::Call, uint8_t2Native, nullptr);
		break;
	case ValidType::Bool:
		il->EmitCall(OpCodes::Call, bool2Native, nullptr);
		break;
	case ValidType::String:
		il->EmitCall(OpCodes::Call, string2Native, nullptr);
		break;
	case ValidType::NumberType:
		il->EmitCall(OpCodes::Call, NumberType2Native, nullptr);
		break;
	case ValidType::Player:
		il->EmitCall(OpCodes::Call, Player2Native, nullptr);
		break;
	case ValidType::Actor:
		il->EmitCall(OpCodes::Call, Actor2Native, nullptr);
		break;
	case ValidType::BlockActor:
		il->EmitCall(OpCodes::Call, BlockActor2Native, nullptr);
		break;
	case ValidType::Container:
		il->EmitCall(OpCodes::Call, Container2Native, nullptr);
		break;
	case ValidType::Vec3:
		il->EmitCall(OpCodes::Call, Vec32Native, nullptr);
		break;
	case ValidType::BlockPos:
		il->EmitCall(OpCodes::Call, BlockPos2Native, nullptr);
		break;
	case ValidType::WorldPosType:
		il->EmitCall(OpCodes::Call, WorldPosType2Native, nullptr);
		break;
	case ValidType::BlockPosType:
		il->EmitCall(OpCodes::Call, BlockPosType2Native, nullptr);
		break;
	case ValidType::ItemType:
		il->EmitCall(OpCodes::Call, ItemType2Native, nullptr);
		break;
	case ValidType::BlockType:
		il->EmitCall(OpCodes::Call, BlockType2Native, nullptr);
		break;
	case ValidType::NbtType:
		il->EmitCall(OpCodes::Call, NbtType2Native, nullptr);
		break;
	case ValidType::List:
	{
		//	>stack:2<
		//	£­RemoteCall::ValueType pointer
		//	£­arg

		auto getEnumeratorMethod = info._type->GetMethod("GetEnumerator");
		auto enumeratorType = getEnumeratorMethod->ReturnType;

		//add local Enumerator variable
		auto local_enumerator_index = locals.Count;
		locals.Add(local_enumerator_index, il->DeclareLocal(enumeratorType));

		//add local ::RemoteCall::ValueType::ArrayType
		auto local_ArrayType_index = locals.Count;
		locals.Add(local_ArrayType_index, il->DeclareLocal(::RemoteCall::ValueType::ArrayType::typeid, true));


		//add local ::RemoteCall::ValueType
		auto local_ValueType_index = locals.Count;
		locals.Add(local_ValueType_index, il->DeclareLocal(::RemoteCall::ValueType::typeid, true));


		il->EmitCall(oc::Call, getEnumeratorMethod, nullptr);
		//	>stack:2<

		//store enumerator
		il->Emit(oc::Stloc_S, locals[local_enumerator_index]);
		//	>stack:1<

		il->Emit(oc::Ldloca_S, locals[local_ArrayType_index]);
		il->Emit(oc::Ldc_I4_0);
		il->Emit(oc::Ldc_I4_S, 24);
		il->Emit(oc::Conv_I8);
		//		>stack:4<
		il->Emit(oc::Initblk);

		il->Emit(oc::Ldloca_S, locals[local_ArrayType_index]);
		//create ::RemoteCall::ValueType::ArrayType
		il->EmitCall(oc::Call, create_ArrayType, nullptr);
		il->Emit(oc::Pop);
		//	>stack:1<
		//	£­RemoteCall::ValueType pointer

		auto loop_start_label = il->DefineLabel();
		auto loop_body_label = il->DefineLabel();
		//jump to loop
		il->Emit(oc::Br_S, loop_start_label);
		il->MarkLabel(loop_body_label);
		//loop body	{   ///////////////////////////////////////////////////////////////////////

		il->Emit(oc::Ldloca_S, locals[local_ValueType_index]);
		il->Emit(oc::Ldloca_S, locals[local_enumerator_index]);
		il->EmitCall(oc::Call, enumeratorType->GetProperty("Current")->GetMethod, nullptr);
		//	>stack:3<
		//	1£­argN ::RemoteCall::ValueType pointer
		//	2£­local ::RemoteCall::ValueType pointer
		//	3£­enumerator->Current

		parseParameter(il, info.genericArgs[0], locals);
		//	>stack:1<
		//	1£­argN ::RemoteCall::ValueType pointer

		//emplace back to ArrayType
		il->Emit(oc::Ldloca_S, locals[local_ArrayType_index]);
		il->Emit(oc::Ldloca_S, locals[local_ValueType_index]);
		il->EmitCall(oc::Call, emplace_back, nullptr);
		//	>stack:1<
		//emplace back end

		//loop body	}   ///////////////////////////////////////////////////////////////////////
		//(while enumerator.MoveNext())
		il->MarkLabel(loop_start_label);
		il->Emit(oc::Ldloca_S, locals[local_enumerator_index]);
		il->EmitCall(oc::Call, enumeratorType->GetMethod("MoveNext"), nullptr);
		il->Emit(oc::Brtrue_S, loop_body_label);
		//loop end

		//	>stack:1<
		//	1£­argN ::RemoteCall::ValueType pointer

		il->Emit(oc::Ldloca_S, locals[local_ArrayType_index]);
		//	>stack:2<
		//	1£­argN ::RemoteCall::ValueType pointer
		//	2£­local ::RemoteCall::ArrayType pointer

		il->EmitCall(oc::Call, ArrayType2ValueType, nullptr);
		//	>stack:1<
		//	1£­returned pointer
	}
	break;
	case ValidType::Dictionary:
		throw gcnew System::NotSupportedException("NotSupported Type [Dictinary]");
		break;
	case ValidType::Void:
		throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
		break;
	}
	//stack:1
	il->Emit(oc::Pop);
	//stack:0
}

inline void LLNET::RemoteCall::ImportFunctionRegister::parseReturnval(ILGenerator^ il, FunctionInfo::TypeInfo% returnvalinfo, Dictionary<int, LocalBuilder^>% locals)
{
	switch (returnvalinfo.type)
	{
	case ValidType::Invalid:
		throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
		break;
	case ValidType::Double:
		il->EmitCall(OpCodes::Call, Native2double, nullptr);
		break;
	case ValidType::Float:
		il->EmitCall(OpCodes::Call, Native2float, nullptr);
		break;
	case ValidType::Int64:
		il->EmitCall(OpCodes::Call, Native2int64_t, nullptr);
		break;
	case ValidType::Int32:
		il->EmitCall(OpCodes::Call, Native2int32_t, nullptr);
		break;
	case ValidType::Int16:
		il->EmitCall(OpCodes::Call, Native2int16_t, nullptr);
		break;
	case ValidType::Int8:
		il->EmitCall(OpCodes::Call, Native2int8_t, nullptr);
		break;
	case ValidType::UInt64:
		il->EmitCall(OpCodes::Call, Native2uint64_t, nullptr);
		break;
	case ValidType::UInt32:
		il->EmitCall(OpCodes::Call, Native2uint32_t, nullptr);
		break;
	case ValidType::UInt16:
		il->EmitCall(OpCodes::Call, Native2uint16_t, nullptr);
		break;
	case ValidType::UInt8:
		il->EmitCall(OpCodes::Call, Native2uint8_t, nullptr);
		break;
	case ValidType::Bool:
		il->EmitCall(OpCodes::Call, Native2bool, nullptr);
		break;
	case ValidType::String:
		il->EmitCall(OpCodes::Call, Native2string, nullptr);
		break;
	case ValidType::NumberType:
		il->EmitCall(OpCodes::Call, Native2NumberType, nullptr);
		break;
	case ValidType::Player:
		il->EmitCall(OpCodes::Call, Native2Player, nullptr);
		break;
	case ValidType::Actor:
		il->EmitCall(OpCodes::Call, Native2Actor, nullptr);
		break;
	case ValidType::BlockActor:
		il->EmitCall(OpCodes::Call, Native2BlockActor, nullptr);
		break;
	case ValidType::Container:
		il->EmitCall(OpCodes::Call, Native2Container, nullptr);
		break;
	case ValidType::Vec3:
		il->EmitCall(OpCodes::Call, Native2Vec3, nullptr);
		break;
	case ValidType::BlockPos:
		il->EmitCall(OpCodes::Call, Native2BlockPos, nullptr);
		break;
	case ValidType::WorldPosType:
		il->EmitCall(OpCodes::Call, Native2WorldPosType, nullptr);
		break;
	case ValidType::BlockPosType:
		il->EmitCall(OpCodes::Call, Native2BlockPosType, nullptr);
		break;
	case ValidType::ItemType:
		il->EmitCall(OpCodes::Call, Native2ItemType, nullptr);
		break;
	case ValidType::BlockType:
		il->EmitCall(OpCodes::Call, Native2BlockType, nullptr);
		break;
	case ValidType::NbtType:
		il->EmitCall(OpCodes::Call, Native2NbtType, nullptr);
		break;
	case ValidType::List:
	{
		auto AddMethod = returnvalinfo._type->GetMethod("Add");

		auto ret_list_index = locals.Count;
		locals.Add(ret_list_index, il->DeclareLocal(returnvalinfo._type));

		auto loop_size_index = locals.Count;
		locals.Add(loop_size_index, il->DeclareLocal(int::typeid));

		auto loop_i_index = locals.Count;
		locals.Add(loop_i_index, il->DeclareLocal(int::typeid));

		//	>stack:1<
		//	1£­returned ::RemoteCall::ValueType pointer
		il->EmitCall(oc::Call, get_ValueArrayType_size, nullptr);
		//	>stack:1<
		//	1£­size int
		il->Emit(oc::Stloc_S, locals[loop_size_index]);
		il->Emit(oc::Ldloc_S, locals[loop_size_index]);
		//new list start
		il->Emit(oc::Newobj, returnvalinfo._type->GetConstructor(gcnew array<System::Type^>(1) { int::typeid }));
		//	>stack:1<
		//	1£­list
		//new list end
		//store list instance
		il->Emit(oc::Stloc_S, locals[ret_list_index]);
		//	>stack:0<

		//	(int i = 0)
		il->Emit(oc::Ldc_I4_0);
		il->Emit(oc::Stloc_S, locals[loop_i_index]);

		auto loop_start_label = il->DefineLabel();
		auto loop_body_label = il->DefineLabel();

		//loop(for)
		il->Emit(oc::Br_S, loop_start_label);
		il->MarkLabel(loop_body_label);
		//loop body	{	//////////////////////////////////////////////////////

		il->Emit(oc::Ldloc_S, locals[ret_list_index]);
		//	>stack:1<
		//	1£­list instance
		il->Emit(oc::Ldloca_S, locals[retIndex]);
		il->Emit(oc::Ldloc_S, locals[loop_i_index]);
		//	>stack:3<
		//	1£­list instance
		//	2£­ret ::RemoteCall::ValueType pointer
		//	3£­i

		il->EmitCall(oc::Call, get_pValueType_from_ValueArrayType_by_index, nullptr);
		//	>stack:2<
		//	1£­list instance
		//	2£­returned ::RemoteCall::ValueType pointer

		parseReturnval(il, returnvalinfo.genericArgs[0], locals);
		//	>stack:2<
		//	1£­list instance
		//	2£­returned object

		il->EmitCall(oc::Call, AddMethod, nullptr);
		//	>stack:0<

		//loop body	}	//////////////////////////////////////////////////////
		//	(++i)
		il->Emit(oc::Ldloc_S, locals[loop_i_index]);
		il->Emit(oc::Ldc_I4_1);
		il->Emit(oc::Add);
		il->Emit(oc::Stloc_S, locals[loop_i_index]);
		//	(i < size)
		il->MarkLabel(loop_start_label);
		il->Emit(oc::Ldloc_S, locals[loop_i_index]);
		il->Emit(oc::Ldloc_S, locals[loop_size_index]);
		il->Emit(oc::Clt);
		il->Emit(oc::Brtrue_S, loop_body_label);
		//loop end
		//	>stack:0<

		il->Emit(oc::Ldloc_S, locals[ret_list_index]);
		//	>stack:0<
		//	1£­return val
	}
	break;
	case ValidType::Dictionary:
		throw gcnew System::NotSupportedException("NotSupported Type [Dictinary]");
		break;
	case ValidType::Void:
		il->Emit(oc::Pop);
		break;
	}
}

void* LLNET::RemoteCall::ImportFunctionRegister::ImportedFunc::_Invoke(void* vec)
{
	return new ::RemoteCall::ValueType((*pfunc)(std::move(*(std::vector<::RemoteCall::ValueType>*)vec)));
}


inline void LLNET::RemoteCall::ImportFunctionRegister::loadParameter(ILGenerator^ il, int localIndex, int paramIndex, Dictionary<int, LocalBuilder^>% locals)
{
	//load pointer
	il->Emit(OpCodes::Ldloca_S, locals[localIndex]);

	switch (paramIndex)
	{
	case 0:throw gcnew LLNET::Core::RemoteCallImportFunctionException("arg[0]->this");
	case 1:il->Emit(oc::Ldarg_1); break;
	case 2:il->Emit(oc::Ldarg_2); break;
	case 3:il->Emit(oc::Ldarg_3); break;
	default: il->Emit(oc::Ldarg_S, paramIndex); break;
	}
	//stack:2;
}

inline void LLNET::RemoteCall::ImportFunctionRegister::emplaceBack(ILGenerator^ il, int localIndex, Dictionary<int, LocalBuilder^>% locals) {

	//emplace_back start
	il->Emit(oc::Ldloca_S, locals[nativeParamIndex]);
	il->Emit(oc::Ldloca_S, locals[localIndex]);
	//	stack:2
	il->EmitCall(oc::Call, emplace_back, nullptr);
	//	stack:0
	//emplace_back end
}

//inline void* LLNET::RemoteCall::ImportFunctionRegister::Listhelper::_create_RemoteCall_ArrayType()
//{
//	return new ::RemoteCall::ValueType::ArrayType();
//}
//
//inline void LLNET::RemoteCall::ImportFunctionRegister::Listhelper::_ArrayType_emplace_back(void* arrType, void* val)
//{
//	((::RemoteCall::ValueType::ArrayType*)arrType)->emplace_back(std::move(*(::RemoteCall::ValueType*)val));
//}

#undef oc