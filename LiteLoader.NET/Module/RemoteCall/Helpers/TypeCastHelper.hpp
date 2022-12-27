#pragma once
#include <RemoteCallAPI.h>

#include <LiteLoader.NET/Main/DotNETGlobal.hpp>

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
                property Object^ CurrentNonGgeneric
                {
                    virtual Object^ get() = IEnumeratorNonGgeneric::Current::get;
                };
            };

            void* ptr;

            ArrayTypeWeakRef(void* ptr);
            size_t Size();
            void Reset(void* ptr);

            property IntPtr default[size_t]
            {
                IntPtr get(size_t index);
            }

            virtual IEnumeratorNonGgeneric^ GetEnumeratorNonGgeneric() new sealed = IEnumerableNonGgeneric::GetEnumerator;
            virtual IEnumerator<IntPtr>^ GetEnumerator();
            iterator GetIterator();
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
                property Object^ CurrentNonGgeneric
                {
                    virtual Object^ get() = IEnumeratorNonGgeneric::Current::get;
                };
            };

            void* ptr;

            ObjectTypeWeakRef(void* ptr);
            size_t Size();
            void Reset(void* ptr);

            property IntPtr default[String^]
            {
                IntPtr get(String^ key);
            }

            virtual IEnumeratorNonGgeneric^ GetEnumeratorNonGgeneric() = IEnumerableNonGgeneric::GetEnumerator;
            virtual IEnumerator<IntPtr>^ GetEnumerator();
            iterator GetIterator();
        };

        static double _Native2double(void* val);
        static float _Native2float(void* val);
        static int64_t _Native2int64_t(void* val);
        static int32_t _Native2int32_t(void* val);
        static int16_t _Native2int16_t(void* val);
        static int8_t _Native2int8_t(void* val);
        static uint64_t _Native2uint64_t(void* val);
        static uint32_t _Native2uint32_t(void* val);
        static uint16_t _Native2uint16_t(void* val);
        static uint8_t _Native2uint8_t(void* val);
        static bool _Native2bool(void* val);
        static String^ _Native2string(void* val);
        static NumberType _Native2NumberType(void* val);
        static MC::Player^ _Native2Player(void* val);
        static MC::Actor^ _Native2Actor(void* val);
        static MC::BlockActor^ _Native2BlockActor(void* val);
        static MC::Container^ _Native2Container(void* val);
        static MC::Vec3 _Native2Vec3(void* val);
        static MC::BlockPos _Native2BlockPos(void* val);
        static WorldPosType^ _Native2WorldPosType(void* val);
        static BlockPosType^ _Native2BlockPosType(void* val);
        static ItemType^ _Native2ItemType(void* val);
        static BlockType^ _Native2BlockType(void* val);
        static NbtType^ _Native2NbtType(void* val);


    };
}

#define TYPECASTHELPER_METHOD_INFO(funcname) ::LiteLoader::RemoteCall::Helper::TypeCastHelper::typeid->GetMethod(#funcname)
