#include "RemoteCallRegisterBase.hpp"
namespace LLNET::RemoteCall::Internal {
	inline Pair<bool, RemoteCallRegisterBase::ValidType> RemoteCallRegisterBase::_tryGetValidType(System::Type^ t)
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

	inline RemoteCallRegisterBase::FunctionInfo::TypeInfo RemoteCallRegisterBase::_generateTypeInfo(System::Type^ t)
	{

		auto type = _tryGetValidType(t);
		if (!type.Key)
			throw gcnew LLNET::Core::InvalidRemoteCallTypeException;

		auto ret = FunctionInfo::TypeInfo();
		ret._type = t;
		ret.type = type.Value;

		switch (type.Value)
		{
		case ValidType::List:
		{
			ret.genericArgs = gcnew array<FunctionInfo::TypeInfo>(1);

			ret.genericArgs[0] = _generateTypeInfo(t->GenericTypeArguments[0]);
		}
		break;

		case ValidType::Dictionary:
		{
			ret.genericArgs = gcnew array<FunctionInfo::TypeInfo>(2);

			ret.genericArgs[0] = _generateTypeInfo(t->GenericTypeArguments[0]);
			ret.genericArgs[1] = _generateTypeInfo(t->GenericTypeArguments[1]);
		}
		break;

		default:
			break;
		case ValidType::Invalid:
			throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
		}

		return ret;
	}

	void RemoteCallRegisterBase::IL_ManagedObjectToValueType(ILGenerator^ il, FunctionInfo::TypeInfo% info, Dictionary<int, LocalBuilder^>% locals)
	{
		switch (info.type)
		{
		case ValidType::Invalid:
			throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			break;
		case ValidType::Double:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_double), nullptr));
			break;
		case ValidType::Float:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_float), nullptr));
			break;
		case ValidType::Int64:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_int64), nullptr));
			break;
		case ValidType::Int32:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_int32), nullptr));
			break;
		case ValidType::Int16:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_int16), nullptr));
			break;
		case ValidType::Int8:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_int8), nullptr));
			break;
		case ValidType::UInt64:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_uint64), nullptr));
			break;
		case ValidType::UInt32:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_uint32), nullptr));
			break;
		case ValidType::UInt16:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_uint16), nullptr));
			break;
		case ValidType::UInt8:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_uint8), nullptr));
			break;
		case ValidType::Bool:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_bool), nullptr));
			break;
		case ValidType::String:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_string), nullptr));
			break;
		case ValidType::NumberType:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_NumberType), nullptr));
			break;
		case ValidType::Player:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_Player), nullptr));
			break;
		case ValidType::Actor:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_Actor), nullptr));
			break;
		case ValidType::BlockActor:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_BlockActor), nullptr));
			break;
		case ValidType::Container:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_Container), nullptr));
			break;
		case ValidType::Vec3:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_Vec3), nullptr));
			break;
		case ValidType::BlockPos:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_BlockPos), nullptr));
			break;
		case ValidType::WorldPosType:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_WorldPosType), nullptr));
			break;
		case ValidType::BlockPosType:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_BlockPosType), nullptr));
			break;
		case ValidType::ItemType:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_ItemType), nullptr));
			break;
		case ValidType::BlockType:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_BlockType), nullptr));
			break;
		case ValidType::NbtType:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_NbtType), nullptr));
			break;
		case ValidType::List:
		{

			//add local ::RemoteCall::ValueType::ArrayType
			auto local_pArrayType_index = locals.Count;
			locals.Add(local_pArrayType_index, il->DeclareLocal(VOID_POINTER_TYPE, true));

			//add local ::RemoteCall::ValueType
			auto local_pValueType_index = locals.Count;
			locals.Add(local_pValueType_index, il->DeclareLocal(VOID_POINTER_TYPE, true));

			auto local_arg_list_index = locals.Count;
			locals.Add(local_arg_list_index, il->DeclareLocal(info._type, true));

			auto loop_size_index = locals.Count;
			locals.Add(loop_size_index, il->DeclareLocal(int::typeid));

			auto loop_i_index = locals.Count;
			locals.Add(loop_i_index, il->DeclareLocal(int::typeid));

			//	>stack:1<
			//	£­object

			_INFO(il->Emit(oc::Stloc_S,locals[local_arg_list_index]));

			//create ::RemoteCall::ValueType::ArrayType
			_INFO(il->EmitCall(oc::Call, _HelperMethod(_create_ArrayType), nullptr));
			_INFO(il->Emit(oc::Stloc_S, locals[local_pArrayType_index]));
			//	>stack:0<

			//	(int i = 0)
			_INFO(il->Emit(oc::Ldc_I4_0));
			_INFO(il->Emit(oc::Stloc_S, locals[loop_i_index]));

			_INFO(il->Emit(oc::Ldloc_S,locals[local_arg_list_index]));
			_INFO(il->EmitCall(oc::Call, info._type->GetProperty("Count")->GetMethod, nullptr));
			_INFO(il->Emit(oc::Stloc_S, locals[loop_size_index]));

			auto loop_start_label = il->DefineLabel();
			auto loop_body_label = il->DefineLabel();
			//jump to loop
			il->Emit(oc::Br_S, loop_start_label);
			il->MarkLabel(loop_body_label);
			//loop body	{   ///////////////////////////////////////////////////////////////////////

			_INFO(il->Emit(oc::Ldloc_S, locals[local_arg_list_index]));
			_INFO(il->Emit(oc::Ldloc_S, locals[loop_i_index]));
			_INFO(il->EmitCall(oc::Call, info._type->GetProperty("Item")->GetMethod, nullptr));

			_INFO(IL_ManagedObjectToValueType(il, info.genericArgs[0], locals));
			//	>stack:1<
			//	1£­argN ::RemoteCall::ValueType pointer

			//emplace back to ArrayType
			_INFO(il->Emit(oc::Ldloc_S, locals[local_pArrayType_index]));
			_INFO(il->EmitCall(oc::Call, _HelperMethod(_emplace_ValueType_back_to_ArrayType_and_delete), nullptr));
			//	>stack:0<
			//emplace back end

			//loop body	}   ///////////////////////////////////////////////////////////////////////
			//	(i++)
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

			_INFO(il->Emit(oc::Ldloc_S, locals[local_pArrayType_index]));
			_INFO(il->EmitCall(oc::Call, _HelperMethod(_create_ValueType_by_ArrayType_and_delete), nullptr));
			//	>stack:1<
			//	1£­returned pointer
		}
		break;
		case ValidType::Dictionary:
			throw gcnew System::NotSupportedException("NotSupported Type [Dictinary]");
			break;
		case ValidType::Void:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_create_ValueType_by_null), nullptr));
			break;
		}
	}

	void RemoteCallRegisterBase::IL_ValueTypeToManagedObject(ILGenerator^ il, FunctionInfo::TypeInfo% info, Dictionary<int, LocalBuilder^>% locals)
	{
		switch (info.type)
		{
		case ValidType::Invalid:
			throw gcnew LLNET::Core::InvalidRemoteCallTypeException;
			break;
		case ValidType::Double:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_double_from_ValueType), nullptr));
			break;
		case ValidType::Float:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_float_from_ValueType), nullptr));
			break;
		case ValidType::Int64:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_int64_from_ValueType), nullptr));
			break;
		case ValidType::Int32:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_int32_from_ValueType), nullptr));
			break;
		case ValidType::Int16:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_int16_from_ValueType), nullptr));
			break;
		case ValidType::Int8:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_int8_from_ValueType), nullptr));
			break;
		case ValidType::UInt64:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_uint64_from_ValueType), nullptr));
			break;
		case ValidType::UInt32:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_uint32_from_ValueType), nullptr));
			break;
		case ValidType::UInt16:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_uint16_from_ValueType), nullptr));
			break;
		case ValidType::UInt8:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_uint8_from_ValueType), nullptr));
			break;
		case ValidType::Bool:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_bool_from_ValueType), nullptr));
			break;
		case ValidType::String:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_string_from_ValueType), nullptr));
			break;
		case ValidType::NumberType:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_NumberType_from_ValueType), nullptr));
			break;
		case ValidType::Player:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_Player_from_ValueType), nullptr));
			break;
		case ValidType::Actor:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_Actor_from_ValueType), nullptr));
			break;
		case ValidType::BlockActor:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_BlockActor_from_ValueType), nullptr));
			break;
		case ValidType::Container:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_Container_from_ValueType), nullptr));
			break;
		case ValidType::Vec3:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_Vec3_from_ValueType), nullptr));
			break;
		case ValidType::BlockPos:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_BlockPos_from_ValueType), nullptr));
			break;
		case ValidType::WorldPosType:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_WorldPosType_from_ValueType), nullptr));
			break;
		case ValidType::BlockPosType:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_BlockPosType_from_ValueType), nullptr));
			break;
		case ValidType::ItemType:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_ItemType_from_ValueType), nullptr));
			break;
		case ValidType::BlockType:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_BlockType_from_ValueType), nullptr));
			break;
		case ValidType::NbtType:
			_INFO(il->EmitCall(OpCodes::Call, _HelperMethod(_get_NbtType_from_ValueType), nullptr));
			break;
		case ValidType::List:
		{
			auto AddMethod = info._type->GetMethod("Add");

			auto ret_list_index = locals.Count;
			locals.Add(ret_list_index, il->DeclareLocal(info._type));

			auto loop_size_index = locals.Count;
			locals.Add(loop_size_index, il->DeclareLocal(int::typeid));

			auto loop_i_index = locals.Count;
			locals.Add(loop_i_index, il->DeclareLocal(int::typeid));

			auto local_pArrayType_form_ValueType_index = locals.Count;
			locals.Add(local_pArrayType_form_ValueType_index, il->DeclareLocal(VOID_POINTER_TYPE));

			//	>stack:1<
			//	1£­::RemoteCall::ValueType pointer
			_INFO(il->EmitCall(oc::Call, _HelperMethod(_get_ArrayType_from_ValueType), nullptr));
			_INFO(il->Emit(oc::Stloc_S, locals[local_pArrayType_form_ValueType_index]));

			_INFO(il->Emit(oc::Ldloc_S, locals[local_pArrayType_form_ValueType_index]));
			_INFO(il->EmitCall(oc::Call, _HelperMethod(_get_ArrayType_size), nullptr));
			//	>stack:1<
			//	1£­size int
			_INFO(il->Emit(oc::Stloc_S, locals[loop_size_index]));


			_INFO(il->Emit(oc::Ldloc_S, locals[loop_size_index]));
			//new list
			_INFO(il->Emit(oc::Newobj, info._type->GetConstructor(gcnew array<System::Type^>(1) { int::typeid })));
			//store list instance
			_INFO(il->Emit(oc::Stloc_S, locals[ret_list_index]));
			//	>stack:0<

			//	(int i = 0)
			_INFO(il->Emit(oc::Ldc_I4_0));
			_INFO(il->Emit(oc::Stloc_S, locals[loop_i_index]));

			auto loop_start_label = il->DefineLabel();
			auto loop_body_label = il->DefineLabel();

			//loop(for)
			il->Emit(oc::Br_S, loop_start_label);
			il->MarkLabel(loop_body_label);
			//loop body	{	//////////////////////////////////////////////////////

			_INFO(il->Emit(oc::Ldloc_S, locals[ret_list_index]));
			//	>stack:1<
			//	1£­list instance
			_INFO(il->Emit(oc::Ldloc_S, locals[local_pArrayType_form_ValueType_index]));
			_INFO(il->Emit(oc::Ldloc_S, locals[loop_i_index]));
			//	>stack:3<
			//	1£­list instance
			//	2£­::RemoteCall::ArrayType pointer
			//	3£­i

			_INFO(il->EmitCall(oc::Call, _HelperMethod(_get_ValueType_from_ArrayType_by_index), nullptr));
			//	>stack:2<
			//	1£­list instance
			//	2£­returned ::RemoteCall::ValueType pointer

			_INFO(IL_ValueTypeToManagedObject(il, info.genericArgs[0], locals));
			//	>stack:2<
			//	1£­list instance
			//	2£­returned object

			_INFO(il->EmitCall(oc::Call, AddMethod, nullptr));
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
}