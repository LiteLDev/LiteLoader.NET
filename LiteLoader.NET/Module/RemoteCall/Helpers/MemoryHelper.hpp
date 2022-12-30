#pragma once
#include <RemoteCallAPI.h>

#include <LiteLoader.NET/Main/DotNETGlobal.hpp>

#include "TypeHelper.hpp"
#include "TypeCastHelper.hpp"

namespace LiteLoader::RemoteCall::Helper
{
    using byte = unsigned char;
    using array_type = ::RemoteCall::ValueType::ArrayType;
    using array_type_native_iterator = ::RemoteCall::ValueType::ArrayType::iterator;

    using System::Runtime::InteropServices::SafeHandle;
    using System::Security::SuppressUnmanagedCodeSecurityAttribute;
    generic<typename T>
    using Nullable = System::Nullable<T>;

    public ref class MemoryHelper
    {
    public:
        ref class RemoreCallHandle : SafeHandle
        {
        public:
            Nullable<InstanceType> instanceType;

            RemoreCallHandle(void* ptr, bool ownsNativeInstance, InstanceType type);
            RemoreCallHandle();

        protected:
            bool ReleaseHandle() override;
        };

        value class Allocator
        {
        public:
            byte* valueTypeInstancePtr;

            void Alloc();
            void Free();

            void SetValue();
            void SetValue(bool v);
            void SetValue(String^ v);
            void SetValue(MC::Player^ v);
            void SetValue(MC::Actor^ v);
            void SetValue(MC::BlockActor^ v);
            void SetValue(MC::Container^ v);
            void SetValue(MC::Vec3 v);
            void SetValue(MC::BlockPos v);
            void SetValue(ItemType^ v);
            void SetValue(BlockType^ v);
            void SetValue(NbtType^ v);
            void SetValue(WorldPosType^ v);
            void SetValue(BlockPosType^ v);
            void SetValue(double v);
            void SetValue(float v);
            void SetValue(__int64 v);
            void SetValue(int v);
            void SetValue(short v);
            void SetValue(char v);
            void SetValue(unsigned __int64 v);
            void SetValue(unsigned int v);
            void SetValue(unsigned short v);
            void SetValue(unsigned char v);
            TypeCastHelper::ArrayTypeWeakRef SetValueAsArrayType(size_t size);
            TypeCastHelper::ObjectTypeWeakRef SetValueAsObjectType(size_t size);

            static void SetValue(void* pValueType);
            static void SetValue(void* pValueType, bool v);
            static void SetValue(void* pValueType, String^ v);
            static void SetValue(void* pValueType, MC::Player^ v);
            static void SetValue(void* pValueType, MC::Actor^ v);
            static void SetValue(void* pValueType, MC::BlockActor^ v);
            static void SetValue(void* pValueType, MC::Container^ v);
            static void SetValue(void* pValueType, MC::Vec3 v);
            static void SetValue(void* pValueType, MC::BlockPos v);
            static void SetValue(void* pValueType, ItemType^ v);
            static void SetValue(void* pValueType, BlockType^ v);
            static void SetValue(void* pValueType, NbtType^ v);
            static void SetValue(void* pValueType, WorldPosType^ v);
            static void SetValue(void* pValueType, BlockPosType^ v);
            static void SetValue(void* pValueType, double v);
            static void SetValue(void* pValueType, float v);
            static void SetValue(void* pValueType, __int64 v);
            static void SetValue(void* pValueType, int v);
            static void SetValue(void* pValueType, short v);
            static void SetValue(void* pValueType, char v);
            static void SetValue(void* pValueType, unsigned __int64 v);
            static void SetValue(void* pValueType, unsigned int v);
            static void SetValue(void* pValueType, unsigned short v);
            static void SetValue(void* pValueType, unsigned char v);
        };
    };
}

#define MEMORYHELPER_METHOD_INFO(funcname) ::LiteLoader::RemoteCall::Helper::MemoryHelper::typeid->GetMethod(#funcname)
