#include "MemoryHelper.hpp"

namespace LiteLoader::RemoteCall::Helper
{
    using array_type = ::RemoteCall::ValueType::ArrayType;
    using object_type = ::RemoteCall::ValueType::ObjectType;
    using value_type = ::RemoteCall::ValueType;
    using world_pos_type = ::RemoteCall::WorldPosType;
    using block_pos_type = ::RemoteCall::BlockPosType;
    using item_type = ::RemoteCall::ItemType;
    using block_type = ::RemoteCall::BlockType;
    using nbt_type = ::RemoteCall::NbtType;

    MemoryHelper::RemoreCallHandle::RemoreCallHandle(void* ptr, bool ownsNativeInstance, InstanceType type)
        :SafeHandle(IntPtr(ptr), ownsNativeInstance), instanceType(type)
    {
    }

    MemoryHelper::RemoreCallHandle::RemoreCallHandle()
        :SafeHandle(IntPtr::Zero, false)
    {
    }

    inline bool MemoryHelper::RemoreCallHandle::ReleaseHandle()
    {
        if (!instanceType.HasValue)
            return false;

        switch (static_cast<InstanceType>(instanceType))
        {
        case InstanceType::Value:
        {
            delete reinterpret_cast<::RemoteCall::Value*>(handle.ToPointer());
        }
        return true;
        case InstanceType::ArrayType:
        {
            delete reinterpret_cast<::RemoteCall::ValueType::ArrayType*> (handle.ToPointer());
        }
        return true;
        case InstanceType::ObjectType:
        {
            delete reinterpret_cast<::RemoteCall::ValueType::ObjectType*>(handle.ToPointer());
        }
        return true;
        default:
            return false;
        }
    }
    void MemoryHelper::Allocator::Alloc()
    {
        valueTypeInstancePtr = new byte[sizeof(value_type)];
    }
    void MemoryHelper::Allocator::Free()
    {
        reinterpret_cast<value_type*>(valueTypeInstancePtr)->~ValueType();
        delete[] valueTypeInstancePtr;
    }
    void* MemoryHelper::Allocator::GetPtr()
    {
        return valueTypeInstancePtr;
    }
    void MemoryHelper::Allocator::SetValue()
    {
        new (valueTypeInstancePtr)value_type(nullptr);
    }
    void MemoryHelper::Allocator::SetValue(bool v)
    {
        new (valueTypeInstancePtr)value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(double v)
    {
        new (valueTypeInstancePtr)value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(float v)
    {
        new (valueTypeInstancePtr)value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(__int64 v)
    {
        new (valueTypeInstancePtr)value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(int v)
    {
        new (valueTypeInstancePtr)value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(short v)
    {
        new (valueTypeInstancePtr)value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(char v)
    {
        new (valueTypeInstancePtr)value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(unsigned __int64 v)
    {
        new (valueTypeInstancePtr)value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(unsigned int v)
    {
        new (valueTypeInstancePtr)value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(unsigned short v)
    {
        new (valueTypeInstancePtr)value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(unsigned char v)
    {
        new (valueTypeInstancePtr)value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(String^ v)
    {
        new (valueTypeInstancePtr)value_type(marshalString(v));
    }
    void MemoryHelper::Allocator::SetValue(MC::Player^ v)
    {
        new (valueTypeInstancePtr)value_type(v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(MC::Actor^ v)
    {
        new (valueTypeInstancePtr)value_type(v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(MC::BlockActor^ v)
    {
        new (valueTypeInstancePtr)value_type(v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(MC::Container^ v)
    {
        new (valueTypeInstancePtr)value_type(v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(MC::Vec3 v)
    {
        new (valueTypeInstancePtr)value_type(world_pos_type(*reinterpret_cast<::Vec3*>(&v)));
    }
    void MemoryHelper::Allocator::SetValue(MC::BlockPos v)
    {
        new (valueTypeInstancePtr)value_type(block_pos_type(*reinterpret_cast<::BlockPos*>(&v)));
    }
    void MemoryHelper::Allocator::SetValue(ItemType^ v)
    {
        new (valueTypeInstancePtr)value_type(*v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(BlockType^ v)
    {
        new (valueTypeInstancePtr)value_type(*v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(NbtType^ v)
    {
        new (valueTypeInstancePtr)value_type(*v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(WorldPosType^ v)
    {
        new (valueTypeInstancePtr)value_type(*v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(BlockPosType^ v)
    {
        new (valueTypeInstancePtr)value_type(*v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(TypeCastHelper::ArrayTypeWeakRef% v)
    {
        new (valueTypeInstancePtr)value_type(*reinterpret_cast<array_type*>(v.ptr));
    }
    void MemoryHelper::Allocator::SetValue(TypeCastHelper::ObjectTypeWeakRef% v)
    {
        new (valueTypeInstancePtr)value_type(*reinterpret_cast<array_type*>(v.ptr));
    }
    void MemoryHelper::Allocator::SetValueByMove(TypeCastHelper::ArrayTypeWeakRef% v)
    {
        new (valueTypeInstancePtr)value_type(std::move(*reinterpret_cast<array_type*>(v.ptr)));
    }
    void MemoryHelper::Allocator::SetValueByMove(TypeCastHelper::ObjectTypeWeakRef% v)
    {
        new (valueTypeInstancePtr)value_type(std::move(*reinterpret_cast<array_type*>(v.ptr)));
    }

    void MemoryHelper::Allocator::SetValueAsArrayType()
    {
        new (valueTypeInstancePtr)value_type(array_type());
    }
    void MemoryHelper::Allocator::SetValueAsObjectType()
    {
        new (valueTypeInstancePtr)value_type(object_type());
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(nullptr));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, bool v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, String^ v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(marshalString(v)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, MC::Player^ v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v->NativePtr));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, MC::Actor^ v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v->NativePtr));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, MC::BlockActor^ v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v->NativePtr));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, MC::Container^ v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v->NativePtr));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, MC::Vec3 v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(world_pos_type(*reinterpret_cast<::Vec3*>(&v))));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, MC::BlockPos v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(world_pos_type(*reinterpret_cast<::Vec3*>(&v))));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, ItemType^ v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v->NativePtr));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, BlockType^ v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v->NativePtr));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, NbtType^ v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v->NativePtr));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, WorldPosType^ v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v->NativePtr));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, BlockPosType^ v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v->NativePtr));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, double v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, float v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, __int64 v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, int v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, short v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, char v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, unsigned __int64 v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, unsigned int v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, unsigned short v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, unsigned char v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(v));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, TypeCastHelper::ArrayTypeWeakRef% v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(std::move(*reinterpret_cast<array_type*>(v.ptr))));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, TypeCastHelper::ObjectTypeWeakRef% v)
    {
        reinterpret_cast<array_type*>(typeRef.ptr)->emplace_back(value_type(std::move(*reinterpret_cast<object_type*>(v.ptr))));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(nullptr)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, bool v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, String^ v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(marshalString(v))));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, MC::Player^ v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v->NativePtr)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, MC::Actor^ v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v->NativePtr)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, MC::BlockActor^ v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v->NativePtr)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, MC::Container^ v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v->NativePtr)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, MC::Vec3 v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(world_pos_type(*reinterpret_cast<::Vec3*>(&v)))));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, MC::BlockPos v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(world_pos_type(*reinterpret_cast<::Vec3*>(&v)))));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, ItemType^ v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v->NativePtr)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, BlockType^ v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v->NativePtr)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, NbtType^ v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v->NativePtr)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, WorldPosType^ v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v->NativePtr)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, BlockPosType^ v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v->NativePtr)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, double v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, float v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, __int64 v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, int v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, short v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, char v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, unsigned __int64 v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, unsigned int v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, unsigned short v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, unsigned char v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(v)));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, TypeCastHelper::ArrayTypeWeakRef% v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(std::move(*reinterpret_cast<array_type*>(v.ptr)))));
    }
    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    void MemoryHelper::ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, TypeCastHelper::ObjectTypeWeakRef% v)
    {
        reinterpret_cast<object_type*>(typeRef.ptr)->emplace(std::make_pair(marshalString(key), value_type(std::move(*reinterpret_cast<object_type*>(v.ptr)))));
    }
}