#pragma once
#include "ValueType.hpp"
using namespace System::Reflection::Emit;

namespace LLNET::RemoteCall {



	ref class ExportFunctionRegister
		:RemoteCallFunctionRegisterBase
	{
	internal:
		delegate ::RemoteCall::ValueType delNative(std::vector<::RemoteCall::ValueType>);
		delegate void* DynamicMethodDelegate(void*);
		delegate void* TEST(void*);
		typedef ::RemoteCall::ValueType(*pNative)(std::vector<::RemoteCall::ValueType>);

		ref struct ExportedFunc {
			String^ nameSpace;
			String^ funcName;
			System::Delegate^ func;
			GCHandle gch;
			TEST^ dynamicMethod;
			::RemoteCall::ValueType _Invoke(std::vector<::RemoteCall::ValueType> vec);
		};

		inline static void parseParameter(ILGenerator^ il, FunctionInfo::TypeInfo% info, Dictionary<int, LocalBuilder^>% locals);

		inline static void parseReturnVal(ILGenerator^ il, FunctionInfo::TypeInfo% info, Dictionary<int, LocalBuilder^>% locals);

		static List<ExportedFunc^>^ ExportFunctions = gcnew List<ExportedFunc^>;
	public:
		generic<typename TDelegate>
		where TDelegate : System::Delegate
			static bool RegisterExportFunction(String^ nameSpace, String^ funcName, TDelegate function, HMODULE handler) {
			NULL_ARG_CHEEK(nameSpace);
			NULL_ARG_CHEEK(funcName);
			NULL_ARG_CHEEK(function);

			auto func = gcnew ExportedFunc;
			func->nameSpace = nameSpace;
			func->funcName = funcName;
			func->func = function;

			auto invokemethod = function->Method;
			auto params = invokemethod->GetParameters();

			auto funcinfo = gcnew FunctionInfo;
			funcinfo->parameters = gcnew array<FunctionInfo::TypeInfo>(params->Length);
			funcinfo->returnType = _generateTypeInfo(invokemethod->ReturnType);
			for (int i = 0; i < params->Length; ++i) {
				funcinfo->parameters[i] = _generateTypeInfo(params[i]->ParameterType);
			}

			auto methodArgs = gcnew array<System::Type^>(2);
			methodArgs[0] = ExportedFunc::typeid;
			methodArgs[1] = void::typeid->MakePointerType();

#define oc OpCodes

			auto method = gcnew DynamicMethod(funcName, void::typeid->MakePointerType(), methodArgs);
			auto il = method->GetILGenerator();
			il->EmitWriteLine("QAQ");

			//void* func(void*)
			//ret:	::RemoteCall::ValueType pointer
			//arg:	::std::vector<RemoteCall::ValueType> pointer


			//auto method = gcnew DynamicMethod(funcName, void::typeid->MakePointerType(), methodArgs);
			//auto il = method->GetILGenerator();



			//declare local
			Dictionary<int, LocalBuilder^> locals;
			for (int i = 0; i < funcinfo->parameters->Length; ++i)
				locals.Add(i, il->DeclareLocal(funcinfo->parameters[i]._type));

			auto local_ValueType_index = locals.Count;
			locals.Add(local_ValueType_index, il->DeclareLocal(::RemoteCall::ValueType::typeid, true));
			//declare local end

			//	>stack:0<

			//check std::vector size
			//il->Emit(oc::Ldarg_1);
			//il->EmitCall(oc::Call, get_ArrayType_size, nullptr);
			//il->Emit(oc::Ldloc_S, funcinfo->parameters->Length);
			//il->Emit(oc::Ceq);
			//auto skip_exception_label = il->DefineLabel();
			//il->Emit(oc::Brtrue_S, skip_exception_label);
			//il->Emit(oc::Ldstr, "Parameter quantity dos not match.");
			//il->Emit(oc::Newobj, LLNET::Core::RemoteCallExportFunctionException::typeid->GetConstructor(gcnew array<System::Type^>(1) { String::typeid }));
			//il->ThrowException(LLNET::Core::RemoteCallExportFunctionException::typeid);
			//il->MarkLabel(skip_exception_label);
			//check std::vector size end

			//	>stack:0<

//#ifdef REMOTECALL_DEBUG
			il->EmitWriteLine("[RemoteCall.Export]Try parse parameter");
			//#endif // REMOTECALL_DEBUG
			for (int i = 0; i < funcinfo->parameters->Length; i++)
			{
				il->Emit(oc::Ldarg_1);
				il->Emit(oc::Ldc_I4_S, 0);
				il->EmitCall(oc::Call, get_pValueType_from_ArrayType_by_index, nullptr);

				parseParameter(il, funcinfo->parameters[i], locals);

				il->Emit(oc::Stloc_S, i);
				//	>stack:0<
			}

#ifdef REMOTECALL_DEBUG
			il->EmitWriteLine("[RemoteCall.Export]Try invoke");
#endif // REMOTECALL_DEBUG
			il->Emit(oc::Ldloca_S, locals[local_ValueType_index]);
			//this
			il->Emit(oc::Ldarg_0);
			il->Emit(oc::Ldfld, ExportedFunc::typeid->GetField("func"));
			for (int i = 0; i < funcinfo->parameters->Length; i++)
				il->Emit(oc::Ldloc_S, i);

			il->EmitCall(oc::Call, TDelegate::typeid->GetMethod("Invoke"), nullptr);

#ifdef REMOTECALL_DEBUG
			il->EmitWriteLine("[RemoteCall.Export]Try parse return val");
#endif // REMOTECALL_DEBUG

			//	>stack:2<
			
			parseReturnVal(il, funcinfo->returnType, locals);
			
			//
			//#ifdef REMOTECALL_DEBUG
			il->EmitWriteLine("[RemoteCall.Export]Try ret");
			//#endif // REMOTECALL_DEBUG

			il->Emit(oc::Ldloca_S, locals[local_ValueType_index]);
			il->Emit(oc::Ret);

			//func->dynamicMethod = (DynamicMethodDelegate^)method->CreateDelegate(DynamicMethodDelegate::typeid);
			func->dynamicMethod = (TEST^)method->CreateDelegate(TEST::typeid, func);
			auto delfunc = gcnew delNative(func, &ExportedFunc::_Invoke);
			func->gch = GCHandle::Alloc(delfunc);
			auto pfunc = static_cast<pNative>((void*)Marshal::GetFunctionPointerForDelegate(delfunc));
			return ::RemoteCall::exportFunc(marshalString(nameSpace), marshalString(funcName), pfunc, handler);
		}
	};
}

#include <stdint.h>

namespace LLNET::RemoteCall {

	inline void LLNET::RemoteCall::ExportFunctionRegister::parseParameter(ILGenerator^ il, FunctionInfo::TypeInfo% info, Dictionary<int, LocalBuilder^>% locals)
	{
		//>stack:2<

		switch (info.type)
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
			//	>stack:1<
			auto AddMethod = info._type->GetMethod("Add");

			auto local_pValueArrayType_index = locals.Count;
			locals.Add(local_pValueArrayType_index, il->DeclareLocal(void::typeid->MakePointerType()));

			il->Emit(oc::Stloc_S, locals[local_pValueArrayType_index]);
			il->Emit(oc::Ldloc_S, locals[local_pValueArrayType_index]);
			//	>stack:1<

			auto param_list_index = locals.Count;
			locals.Add(param_list_index, il->DeclareLocal(info._type));

			auto loop_size_index = locals.Count;
			locals.Add(loop_size_index, il->DeclareLocal(int::typeid));

			auto loop_i_index = locals.Count;
			locals.Add(loop_i_index, il->DeclareLocal(int::typeid));

			il->EmitCall(oc::Call, get_ValueArrayType_size, nullptr);
			il->Emit(oc::Stloc_S, locals[loop_size_index]);
			//	>stack:0<

			il->Emit(oc::Ldloc_S, locals[loop_size_index]);
			il->Emit(oc::Newobj, info._type->GetConstructor(gcnew array<System::Type^>(1) { int::typeid }));
			il->Emit(oc::Stloc_S, locals[param_list_index]);
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
			il->Emit(oc::Ldloc_S, locals[param_list_index]);

			il->Emit(oc::Ldloc_S, locals[local_pValueArrayType_index]);
			il->EmitCall(oc::Call, get_pArrayType_form_ValueType, nullptr);
			il->Emit(oc::Ldloc_S, locals[loop_i_index]);
			il->EmitCall(oc::Call, get_pValueType_from_ValueArrayType_by_index, nullptr);
			parseParameter(il, info.genericArgs[0], locals);
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

			il->Emit(oc::Ldloc_S, locals[param_list_index]);
		}
		break;
		case ValidType::Dictionary:
			throw gcnew System::NotSupportedException("NotSupported Type [Dictinary]");
			break;
		case ValidType::Void:
			throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			break;
		}
	}

	inline void ExportFunctionRegister::parseReturnVal(ILGenerator^ il, FunctionInfo::TypeInfo% info, Dictionary<int, LocalBuilder^>% locals)
	{
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

		il->Emit(oc::Pop);
	}

	::RemoteCall::ValueType ExportFunctionRegister::ExportedFunc::_Invoke(std::vector<::RemoteCall::ValueType> vec)
	{
		try
		{
			auto a = this->dynamicMethod(&vec);
			auto p =  (::RemoteCall::ValueType*)a;
			Console::WriteLine(p->value.index());
			Console::WriteLine("address a:" + ((intptr_t)a).ToString());
			return *p;
		}
		CATCH
			return ::RemoteCall::pack(nullptr);
	}
}




#undef oc