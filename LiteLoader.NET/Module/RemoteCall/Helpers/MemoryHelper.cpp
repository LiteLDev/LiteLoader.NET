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
            return true;

        switch (static_cast<InstanceType>(instanceType))
        {
        case InstanceType::Value:
        {
            delete reinterpret_cast<::RemoteCall::Value*>(handle.ToPointer());
        }
        break;
        case InstanceType::ArrayType:
        {
            delete reinterpret_cast<::RemoteCall::ValueType::ArrayType*> (handle.ToPointer());
        }
        break;
        case InstanceType::ObjectType:
        {
            delete reinterpret_cast<::RemoteCall::ValueType::ObjectType*>(handle.ToPointer());
        }
        break;
        default:
            break;
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

    TypeCastHelper::ArrayTypeWeakRef MemoryHelper::Allocator::SetValueAsArrayType(size_t size)
    {
        
    }
    TypeCastHelper::ObjectTypeWeakRef MemoryHelper::Allocator::SetValueAsObjectType(size_t size)
    {

    }

    void MemoryHelper::Allocator::SetValue(void* pValueType)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(nullptr);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, bool v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, String^ v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(marshalString(v));
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, MC::Player^ v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, MC::Actor^ v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, MC::BlockActor^ v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, MC::Container^ v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, MC::Vec3 v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(world_pos_type(*reinterpret_cast<::Vec3*>(&v)));
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, MC::BlockPos v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(world_pos_type(*reinterpret_cast<::Vec3*>(&v)));
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, ItemType^ v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, BlockType^ v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, NbtType^ v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, WorldPosType^ v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, BlockPosType^ v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v->NativePtr);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, double v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, float v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, __int64 v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, int v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, short v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, char v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, unsigned __int64 v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, unsigned int v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, unsigned short v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v);
    }
    void MemoryHelper::Allocator::SetValue(void* pValueType, unsigned char v)
    {
        *reinterpret_cast<value_type*>(pValueType) = value_type(v);
    }
}