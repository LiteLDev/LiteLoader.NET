#pragma once
#include <RemoteCallAPI.h>

#include <src/Main/DotNETGlobal.hpp>

//#define REMOTECALL_DEBUG

namespace MC
{
    ref class Player;
    ref class Actor;
    ref class BlockActor;
    ref class Container;
    value class Vec3;
    value class BlockPos;
}

namespace LiteLoader::RemoteCall
{
    value class NumberType;
    ref class WorldPosType;
    ref class BlockPosType;
    ref class ItemType;
    ref class BlockType;
    ref class NbtType;
}

namespace LiteLoader::RemoteCall::Helper
{
    using array_type = ::RemoteCall::ValueType::ArrayType;
    using array_type_native_iterator = ::RemoteCall::ValueType::ArrayType::iterator;
    using object_type = ::RemoteCall::ValueType::ObjectType;
    using object_type_native_iterator = ::RemoteCall::ValueType::ObjectType::iterator;

    public ref class TypeCastHelper __static
    {
    public:

        value struct ArrayTypeWeakRef :IEnumerable<IntPtr>
        {
            value struct iterator :IEnumerator<IntPtr>
            {
                [StructLayout(LayoutKind::Sequential, Size = sizeof(array_type_native_iterator))]
                value struct __iterator {};

                __iterator iter;
                bool isIterSet;
                void* instance;

                iterator(void* instance);
                virtual bool MoveNext();
                virtual void Reset();
                void* GetCurrentPtr();
                property IntPtr Current
                {
                    virtual IntPtr get();
                }

            private:
                property Object^ CurrentNonGgeneric
                {
                    virtual Object^ get() sealed = IEnumeratorNonGgeneric::Current::get;
                };
            };

            void* ptr;

            ArrayTypeWeakRef(void* ptr);
            size_t Size();
            void Reset(void* ptr);
            void* GetArrayTypePtrByIndex(int index);

            property IntPtr default[int]
            {
                IntPtr get(int index);
            }
            virtual IEnumerator<IntPtr>^ GetEnumerator();
            iterator GetIterator();

        private:
            virtual IEnumeratorNonGgeneric^ GetEnumeratorNonGgeneric() sealed = IEnumerableNonGgeneric::GetEnumerator;
        };

        value struct ObjectTypeWeakRef :IEnumerable<IntPtr>
        {
            value struct iterator :IEnumerator<IntPtr>
            {
                [StructLayout(LayoutKind::Sequential, Size = sizeof(object_type_native_iterator))]
                value struct __iterator {};

                __iterator iter;
                bool isIterSet;
                void* instance;

                iterator(void* instance);
                virtual bool MoveNext();
                virtual void Reset();
                void* GetCurrentPtr();
                property IntPtr Current
                {
                    virtual IntPtr get();
                }
                String^ GetKey();
                void* GetValue();

            private:
                property Object^ CurrentNonGgeneric
                {
                    virtual Object^ get() sealed = IEnumeratorNonGgeneric::Current::get;
                };
            };

            void* ptr;

            ObjectTypeWeakRef(void* ptr);
            size_t Size();
            void Reset(void* ptr);

            property IntPtr default[String^]
            {
                IntPtr get(String ^ key);
            }

            virtual IEnumerator<IntPtr>^ GetEnumerator();
            iterator GetIterator();

        private:
            virtual IEnumeratorNonGgeneric^ GetEnumeratorNonGgeneric() sealed = IEnumerableNonGgeneric::GetEnumerator;
        };

        static double Native2double(void* val);
        static float Native2float(void* val);
        static int64_t Native2int64_t(void* val);
        static int32_t Native2int32_t(void* val);
        static int16_t Native2int16_t(void* val);
        static int8_t Native2int8_t(void* val);
        static uint64_t Native2uint64_t(void* val);
        static uint32_t Native2uint32_t(void* val);
        static uint16_t Native2uint16_t(void* val);
        static uint8_t Native2uint8_t(void* val);
        static bool Native2bool(void* val);
        static String^ Native2string(void* val);
        static NumberType Native2NumberType(void* val);
        static MC::Player^ Native2Player(void* val);
        static MC::Actor^ Native2Actor(void* val);
        static MC::BlockActor^ Native2BlockActor(void* val);
        static MC::Container^ Native2Container(void* val);
        static MC::Vec3 Native2Vec3(void* val);
        static MC::BlockPos Native2BlockPos(void* val);
        static WorldPosType^ Native2WorldPosType(void* val);
        static BlockPosType^ Native2BlockPosType(void* val);
        static ItemType^ Native2ItemType(void* val);
        static BlockType^ Native2BlockType(void* val);
        static NbtType^ Native2NbtType(void* val);

        static void* Native2ArrayTypePtr(void* val);
        static void* Native2ObjectTypePtr(void* val);
    };
}

#define TYPECASTHELPER_METHOD_INFO(funcname) ::LiteLoader::RemoteCall::Helper::TypeCastHelper::typeid->GetMethod(#funcname)
