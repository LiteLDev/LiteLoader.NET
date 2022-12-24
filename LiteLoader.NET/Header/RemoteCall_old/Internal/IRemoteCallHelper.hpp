#pragma once
#include <LiteLoader.NET/Header/RemoteCall/ValueType.hpp>

namespace LiteLoader::RemoteCall::Internal
{
	public interface class IRemoteCallHelper {
	public:
		inline static void* _create_ValueType_by_double(double val);
		inline static void* _create_ValueType_by_float(float val);
		inline static void* _create_ValueType_by_int64(int64_t val);
		inline static void* _create_ValueType_by_int32(int32_t val);
		inline static void* _create_ValueType_by_int16(int16_t val);
		inline static void* _create_ValueType_by_int8(int8_t val);
		inline static void* _create_ValueType_by_uint64(uint64_t val);
		inline static void* _create_ValueType_by_uint32(uint32_t val);
		inline static void* _create_ValueType_by_uint16(uint16_t val);
		inline static void* _create_ValueType_by_uint8(uint8_t val);
		inline static void* _create_ValueType_by_bool(bool val);
		inline static void* _create_ValueType_by_string(String^ val);
		inline static void* _create_ValueType_by_NumberType(NumberType val);
		inline static void* _create_ValueType_by_Player(MC::Player^ val);
		inline static void* _create_ValueType_by_Actor(MC::Actor^ val);
		inline static void* _create_ValueType_by_BlockActor(MC::BlockActor^ val);
		inline static void* _create_ValueType_by_Container(MC::Container^ val);
		inline static void* _create_ValueType_by_Vec3(MC::Vec3 val);
		inline static void* _create_ValueType_by_BlockPos(MC::BlockPos val);
		inline static void* _create_ValueType_by_WorldPosType(WorldPosType^ val);
		inline static void* _create_ValueType_by_BlockPosType(BlockPosType^ val);
		inline static void* _create_ValueType_by_ItemType(ItemType^ val);
		inline static void* _create_ValueType_by_BlockType(BlockType^ val);
		inline static void* _create_ValueType_by_NbtType(NbtType^ val);

		inline static double _get_double_from_ValueType(void* val);
		inline static float _get_float_from_ValueType(void* val);
		inline static int64_t _get_int64_from_ValueType(void* val);
		inline static int32_t _get_int32_from_ValueType(void* val);
		inline static int16_t _get_int16_from_ValueType(void* val);
		inline static int8_t _get_int8_from_ValueType(void* val);
		inline static uint64_t _get_uint64_from_ValueType(void* val);
		inline static uint32_t _get_uint32_from_ValueType(void* val);
		inline static uint16_t _get_uint16_from_ValueType(void* val);
		inline static uint8_t _get_uint8_from_ValueType(void* val);
		inline static bool _get_bool_from_ValueType(void* val);
		inline static String^ _get_string_from_ValueType(void* val);
		inline static NumberType _get_NumberType_from_ValueType(void* val);
		inline static MC::Player^ _get_Player_from_ValueType(void* val);
		inline static MC::Actor^ _get_Actor_from_ValueType(void* val);
		inline static MC::BlockActor^ _get_BlockActor_from_ValueType(void* val);
		inline static MC::Container^ _get_Container_from_ValueType(void* val);
		inline static MC::Vec3 _get_Vec3_from_ValueType(void* val);
		inline static MC::BlockPos _get_BlockPos_from_ValueType(void* val);
		inline static WorldPosType^ _get_WorldPosType_from_ValueType(void* val);
		inline static BlockPosType^ _get_BlockPosType_from_ValueType(void* val);
		inline static ItemType^ _get_ItemType_from_ValueType(void* val);
		inline static BlockType^ _get_BlockType_from_ValueType(void* val);
		inline static NbtType^ _get_NbtType_from_ValueType(void* val);

		inline static void* _create_ArrayType();
		inline static void _delete_ArrayType(void* arr);
		inline static void* _create_ValueType();
		inline static void _delete_ValueType(void* val);
		inline static void* _create_ObjectType();
		inline static void _delete_ObjectType(void* obj);

		inline static void _delete_ObjectType_iterator(void* iter);

		inline static void* _create_ValueType_by_null();
		inline static void _emplace_ValueType_back_to_ArrayType(void* val, void* arr);
		inline static void* _create_ValueType_by_ArrayType(void* arr);
		inline static void* _get_ValueType_from_ArrayType_by_index(void* arr, int index);

		inline static void* _get_ArrayType_from_ValueType(void* val);
		inline static int _get_ArrayType_size(void* arr);

		inline static void* _create_std_string_from_String(String^ str);
		inline static String^ _get_String_from_std_string(void* str);
		inline static void _delete_std_string(void* str);

		inline static void* _get_ObjectType_begin_iterator(void* obj);
		inline static bool _is_iterator_not_equals_ObjectType_end(void* iter, void* obj);
		inline static void _iterator_move_next(void* iter);
		inline static void* get_iterator_current_key(void* iter);
		inline static void* get_iterator_current_value_by_stdmove(void* iter);

		inline static void* _get_ObjectType_from_ValueType(void* val);
		inline static int _get_ObjectType_size(void* obj);

		inline static void* _create_ValueType_by_ObjectType(void* obj);
		inline static void _emplace_string_and_ValueType_to_ObjectType(void* val, String^ str, void* obj);

		/*inline static void _set_ValueType(void* val_a, void* val_b);*/
	};
}

#define _HelperMethod(name)\
LiteLoader::RemoteCall::Internal::IRemoteCallHelper::typeid->GetMethod(#name)

#define VOID_POINTER_TYPE void::typeid->MakePointerType()


#ifdef REMOTECALL_DEBUG

#define _INFO(info)\
il->EmitWriteLine(#info);info

#else

#define _INFO(info)\
info

#endif

#define __INLINE [MethodImpl(MethodImplOptions::AggressiveInlining)] inline



using System::Reflection::MethodInfo;
using System::Reflection::FieldInfo;
