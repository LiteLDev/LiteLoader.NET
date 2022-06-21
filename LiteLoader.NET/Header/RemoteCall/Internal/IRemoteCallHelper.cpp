#include "IRemoteCallHelper.hpp"

using __ValueType = ::RemoteCall::ValueType;
using __ArrayType = ::RemoteCall::ValueType::ArrayType;
using __ObjectType = ::RemoteCall::ValueType::ObjectType;

using __NumberType = ::RemoteCall::NumberType;
using __WorldPosType = ::RemoteCall::WorldPosType;
using __BlockPosType = ::RemoteCall::BlockPosType;
using __ItemType = ::RemoteCall::ItemType;
using __BlockType = ::RemoteCall::BlockType;
using __NbtType = ::RemoteCall::NbtType;


namespace LLNET::RemoteCall::Internal
{

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_double(double val) {
		return new __ValueType(::RemoteCall::pack(val));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_float(float val) {
		return new __ValueType(::RemoteCall::pack(val));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_int64(int64_t val) {
		return new __ValueType(::RemoteCall::pack(val));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_int32(int32_t val) {
		return new __ValueType(::RemoteCall::pack(val));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_int16(int16_t val) {
		return new __ValueType(::RemoteCall::pack(val));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_int8(int8_t val) {
		return new __ValueType(::RemoteCall::pack(val));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_uint64(uint64_t val) {
		return new __ValueType(::RemoteCall::pack(val));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_uint32(uint32_t val) {
		return new __ValueType(::RemoteCall::pack(val));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_uint16(uint16_t val) {
		return new __ValueType(::RemoteCall::pack(val));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_uint8(uint8_t val) {
		return new __ValueType(::RemoteCall::pack(val));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_bool(bool val) {
		return new __ValueType(::RemoteCall::pack(val));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_string(String^ val) {
		if (val == nullptr)
			return new __ValueType(::RemoteCall::pack(std::string("")));
		return new __ValueType(::RemoteCall::pack(marshalString(val)));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_NumberType(NumberType val) {
		return new __ValueType(::RemoteCall::pack(val._toNative()));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_Player(MC::Player^ val) {
		return new __ValueType(::RemoteCall::pack(val->NativePtr));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_Actor(MC::Actor^ val) {
		return new __ValueType(::RemoteCall::pack(val->NativePtr));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_BlockActor(MC::BlockActor^ val) {
		return new __ValueType(::RemoteCall::pack(val->NativePtr));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_Container(MC::Container^ val) {
		return new __ValueType(::RemoteCall::pack(val->NativePtr));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_Vec3(MC::Vec3 val) {
		return new __ValueType(::RemoteCall::pack(std::make_pair(::Vec3(val), 0)));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_BlockPos(MC::BlockPos val) {
		return new __ValueType(::RemoteCall::pack(std::make_pair(::BlockPos(val), 0)));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_WorldPosType(WorldPosType^ val) {
		return new __ValueType(::RemoteCall::pack(*val->NativePtr));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_BlockPosType(BlockPosType^ val) {
		return new __ValueType(::RemoteCall::pack(*val->NativePtr));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_ItemType(ItemType^ val) {
		return new __ValueType(::RemoteCall::pack(*val->NativePtr));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_BlockType(BlockType^ val) {
		return new __ValueType(::RemoteCall::pack(*val->NativePtr));
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_NbtType(NbtType^ val) {
		return new __ValueType(::RemoteCall::pack(*val->NativePtr));
	}

#define __VALUE std::get<::RemoteCall::Value>(((::RemoteCall::ValueType*)val)->value)
#define __NUMBERTYPE std::get<::RemoteCall::NumberType>(__VALUE)

	__INLINE double IRemoteCallHelper::_get_double_from_ValueType(void* val) {
		return __NUMBERTYPE.get<double>();
	}

	__INLINE float IRemoteCallHelper::_get_float_from_ValueType(void* val) {
		return __NUMBERTYPE.get<float>();
	}

	__INLINE int64_t IRemoteCallHelper::_get_int64_from_ValueType(void* val) {
		return __NUMBERTYPE.get<int64_t>();
	}

	__INLINE int32_t IRemoteCallHelper::_get_int32_from_ValueType(void* val) {
		return __NUMBERTYPE.get<int32_t>();
	}

	__INLINE int16_t IRemoteCallHelper::_get_int16_from_ValueType(void* val) {
		return __NUMBERTYPE.get<int16_t>();
	}

	__INLINE int8_t IRemoteCallHelper::_get_int8_from_ValueType(void* val) {
		return __NUMBERTYPE.get<int8_t>();
	}

	__INLINE uint64_t IRemoteCallHelper::_get_uint64_from_ValueType(void* val) {
		return __NUMBERTYPE.get<uint64_t>();
	}

	__INLINE uint32_t IRemoteCallHelper::_get_uint32_from_ValueType(void* val) {
		return __NUMBERTYPE.get<uint32_t>();
	}

	__INLINE uint16_t IRemoteCallHelper::_get_uint16_from_ValueType(void* val) {
		return __NUMBERTYPE.get<uint16_t>();
	}

	__INLINE uint8_t IRemoteCallHelper::_get_uint8_from_ValueType(void* val) {
		return __NUMBERTYPE.get<uint8_t>();
	}

	__INLINE bool IRemoteCallHelper::_get_bool_from_ValueType(void* val) {
		return std::get<bool>(__VALUE);
	}

	__INLINE String^ IRemoteCallHelper::_get_string_from_ValueType(void* val) {
		return marshalString(std::get<std::string>(__VALUE));
	}

	__INLINE NumberType IRemoteCallHelper::_get_NumberType_from_ValueType(void* val) {
		return NumberType(__NUMBERTYPE);
	}

	__INLINE MC::Player^ IRemoteCallHelper::_get_Player_from_ValueType(void* val) {
		return gcnew MC::Player(std::get<::Player*>(__VALUE));
	}

	__INLINE MC::Actor^ IRemoteCallHelper::_get_Actor_from_ValueType(void* val) {
		return gcnew MC::Actor(std::get<::Actor*>(__VALUE));
	}

	__INLINE MC::BlockActor^ IRemoteCallHelper::_get_BlockActor_from_ValueType(void* val) {
		return gcnew MC::BlockActor(std::get<::BlockActor*>(__VALUE));
	}

	__INLINE MC::Container^ IRemoteCallHelper::_get_Container_from_ValueType(void* val) {
		return gcnew MC::Container(std::get<::Container*>(__VALUE));
	}

	__INLINE MC::Vec3 IRemoteCallHelper::_get_Vec3_from_ValueType(void* val) {
		return MC::Vec3(std::get<::RemoteCall::WorldPosType>(__VALUE).pos);
	}

	__INLINE MC::BlockPos IRemoteCallHelper::_get_BlockPos_from_ValueType(void* val) {
		return MC::BlockPos(std::get<::RemoteCall::BlockPosType>(__VALUE).pos);
	}

	__INLINE WorldPosType^ IRemoteCallHelper::_get_WorldPosType_from_ValueType(void* val) {
		return gcnew WorldPosType(std::get<::RemoteCall::WorldPosType>(__VALUE));
	}

	__INLINE BlockPosType^ IRemoteCallHelper::_get_BlockPosType_from_ValueType(void* val) {
		return gcnew BlockPosType(std::get<::RemoteCall::BlockPosType>(__VALUE));
	}

	__INLINE ItemType^ IRemoteCallHelper::_get_ItemType_from_ValueType(void* val) {
		return gcnew ItemType(std::get<::RemoteCall::ItemType>(__VALUE));
	}

	__INLINE BlockType^ IRemoteCallHelper::_get_BlockType_from_ValueType(void* val) {
		return gcnew BlockType(std::get<::RemoteCall::BlockType>(__VALUE));
	}

	__INLINE NbtType^ IRemoteCallHelper::_get_NbtType_from_ValueType(void* val) {
		return gcnew NbtType(std::get<::RemoteCall::NbtType>(__VALUE));
	}

	__INLINE void* IRemoteCallHelper::_create_ArrayType() {
		return new __ArrayType;
	}

	__INLINE void IRemoteCallHelper::_delete_ArrayType(void* arr) {
		delete (__ArrayType*)arr;
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType() {
		return new __ValueType;
	}

	__INLINE void IRemoteCallHelper::_delete_ValueType(void* val) {
		delete (__ValueType*)val;
	}

	__INLINE void* IRemoteCallHelper::_create_ObjectType() {
		return new __ObjectType;
	}

	__INLINE void IRemoteCallHelper::_delete_ObjectType(void* obj) {
		delete (__ObjectType*)obj;
	}

	__INLINE void IRemoteCallHelper::_delete_ObjectType_iterator(void* iter) {
		delete (__ObjectType::iterator*)iter;
	}




	__INLINE void* IRemoteCallHelper::_create_ValueType_by_null() {
		return new __ValueType(nullptr);
	}

	__INLINE void IRemoteCallHelper::_emplace_ValueType_back_to_ArrayType_and_delete(void* val, void* arr) {
		((__ArrayType*)arr)->emplace_back(std::move(*(__ValueType*)val));
		delete (__ValueType*)val;
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_ArrayType_and_delete(void* arr) {
		auto ret = new __ValueType(std::move(*(__ArrayType*)arr));
		delete (__ArrayType*)arr;
		return ret;
	}

	__INLINE void* IRemoteCallHelper::_get_ValueType_from_ArrayType_by_index(void* arr, int index) {
		return new __ValueType(std::move((*(__ArrayType*)arr)[index]));
	}

	__INLINE void* IRemoteCallHelper::_get_ArrayType_from_ValueType(void* val) {
		return &std::get<__ArrayType>(((__ValueType*)val)->value);
	}

	__INLINE int IRemoteCallHelper::_get_ArrayType_size(void* arr) {
		return (int)((__ArrayType*)arr)->size();
	}

	__INLINE void* IRemoteCallHelper::_create_std_string_from_String(String^ str) {
		return new std::string(marshalString(str));
	}

	__INLINE String^ IRemoteCallHelper::_get_String_from_std_string(void* str) {
		return marshalString(*(std::string*)str);
	}

	__INLINE void IRemoteCallHelper::_delete_std_string(void* str) {
		delete (std::string*)str;
	}

	__INLINE void* IRemoteCallHelper::_get_ObjectType_begin_iterator(void* obj) {
		return new __ObjectType::iterator(((__ObjectType*)obj)->begin());
	}

	__INLINE bool IRemoteCallHelper::_is_iterator_not_equals_ObjectType_end(void* iter, void* obj) {
		return *(__ObjectType::iterator*)iter != ((__ObjectType*)obj)->end();
	}

	__INLINE void IRemoteCallHelper::_iterator_move_next(void* iter) {
		((__ObjectType::iterator*)iter)->operator++();
	}

	__INLINE void* IRemoteCallHelper::get_iterator_current_key(void* iter) {
		return (void*)&(*(__ObjectType::iterator*)iter)->first;
	}

	__INLINE void* IRemoteCallHelper::get_iterator_current_value_by_stdmove(void* iter) {
		return new __ValueType(std::move((*(__ObjectType::iterator*)iter)->second));
	}

	__INLINE void* IRemoteCallHelper::_get_ObjectType_from_ValueType(void* val) {
		return &std::get<__ObjectType>(((__ValueType*)val)->value);
	}

	__INLINE int IRemoteCallHelper::_get_ObjectType_size(void* obj) {
		return (int)((__ObjectType*)obj)->size();
	}

	__INLINE void* IRemoteCallHelper::_create_ValueType_by_ObjectType_and_delete(void* obj) {
		auto ret = new __ValueType(std::move(*(__ObjectType*)obj));
		delete (__ObjectType*)obj;
		return ret;
	}

	__INLINE void IRemoteCallHelper::_emplace_string_and_ValueType_to_ObjectType_and_delete(void* val, String^ str, void* obj) {
		((__ObjectType*)obj)->emplace(marshalString(str), std::move(*(__ValueType*)val));
		delete (__ValueType*)val;
	}

}