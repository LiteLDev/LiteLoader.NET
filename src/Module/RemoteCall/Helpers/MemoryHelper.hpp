#pragma once
#include <RemoteCallAPI.h>

#include <src/Main/DotNETGlobal.hpp>

#include "TypeHelper.hpp"
#include "TypeCastHelper.hpp"

namespace LiteLoader::RemoteCall::Helper
{
    using byte = unsigned char;
    using array_type = ::RemoteCall::ValueType::ArrayType;
    using array_type_native_iterator = ::RemoteCall::ValueType::ArrayType::iterator;

    using System::Runtime::InteropServices::SafeHandle;
    using System::Security::SuppressUnmanagedCodeSecurityAttribute;

    public ref class MemoryHelper
    {
    public:
        ref class RemoreCallHandle : SafeHandle
        {
        public:
            System::Nullable<InstanceType> instanceType;

            property bool IsInvalid
            {
                virtual bool get() override;
            }

            RemoreCallHandle(void* ptr, bool ownsNativeInstance, InstanceType type);
            RemoreCallHandle();

        protected:
            bool ReleaseHandle() override;
        };

        value class Allocator
        {
        public:
            void* valueTypeInstancePtr;

            void Alloc();
            void Free();
            void* GetPtr();

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
            void SetValue(TypeCastHelper::ArrayTypeWeakRef% v);
            void SetValue(TypeCastHelper::ObjectTypeWeakRef% v);
            void SetValueByMove(TypeCastHelper::ArrayTypeWeakRef% v);
            void SetValueByMove(TypeCastHelper::ObjectTypeWeakRef% v);
            TypeCastHelper::ArrayTypeWeakRef SetValueAsArrayType();
            TypeCastHelper::ObjectTypeWeakRef SetValueAsObjectType();
        };

        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, bool v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, String^ v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, MC::Player^ v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, MC::Actor^ v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, MC::BlockActor^ v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, MC::Container^ v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, MC::Vec3 v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, MC::BlockPos v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, ItemType^ v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, BlockType^ v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, NbtType^ v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, WorldPosType^ v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, BlockPosType^ v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, double v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, float v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, __int64 v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, int v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, short v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, char v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, unsigned __int64 v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, unsigned int v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, unsigned short v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, unsigned char v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, TypeCastHelper::ArrayTypeWeakRef% v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, TypeCastHelper::ObjectTypeWeakRef% v);
        static void ArrayType_EmplaceBack(TypeCastHelper::ArrayTypeWeakRef% typeRef, Allocator% v);

        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, bool v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, String^ v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, MC::Player^ v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, MC::Actor^ v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, MC::BlockActor^ v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, MC::Container^ v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, MC::Vec3 v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, MC::BlockPos v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, ItemType^ v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, BlockType^ v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, NbtType^ v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, WorldPosType^ v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, BlockPosType^ v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, double v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, float v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, __int64 v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, int v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, short v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, char v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, unsigned __int64 v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, unsigned int v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, unsigned short v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, unsigned char v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, TypeCastHelper::ArrayTypeWeakRef% v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, TypeCastHelper::ObjectTypeWeakRef% v);
        static void ObjectType_EmplaceBack(TypeCastHelper::ObjectTypeWeakRef% typeRef, String^ key, Allocator% v);
    };
}

#define MEMORYHELPER_METHOD_INFO(funcname) ::LiteLoader::RemoteCall::Helper::MemoryHelper::typeid->GetMethod(#funcname)
