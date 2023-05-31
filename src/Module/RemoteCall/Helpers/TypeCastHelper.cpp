#include <mutex>

#include "TypeCastHelper.hpp"

#include <src/Module/RemoteCall/Types/NumberType.hpp>
#include <src/Module/RemoteCall/Types/WorldPosType.hpp>
#include <src/Module/RemoteCall/Types/BlockPosType.hpp>
#include <src/Module/RemoteCall/Types/ItemType.hpp>
#include <src/Module/RemoteCall/Types/BlockType.hpp>
#include <src/Module/RemoteCall/Types/NbtType.hpp>

#include <src/Header/MC/Player.hpp>
#include <src/Header/MC/Actor.hpp>
#include <src/Header/MC/BlockActor.hpp>
#include <src/Header/MC/Container.hpp>
#include <src/Header/MC/Vec3.hpp>
#include <src/Header/MC/BlockPos.hpp>

//#define REMOTECALL_DEBUG
//#define REMOTECALL_DEBUG_INFO Console::WriteLine

namespace LiteLoader::RemoteCall::Helper
{
    using number_type = ::RemoteCall::NumberType;
    using array_type = ::RemoteCall::ValueType::ArrayType;
    using object_type = ::RemoteCall::ValueType::ObjectType;
    using value_type = ::RemoteCall::ValueType;
    using world_pos_type = ::RemoteCall::WorldPosType;
    using block_pos_type = ::RemoteCall::BlockPosType;
    using item_type = ::RemoteCall::ItemType;
    using block_type = ::RemoteCall::BlockType;
    using nbt_type = ::RemoteCall::NbtType;
    using value = ::RemoteCall::Value;

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline double TypeCastHelper::Native2double(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG
        return std::get<number_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)).get<double>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline float TypeCastHelper::Native2float(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return std::get<number_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)).get<float>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline int64_t TypeCastHelper::Native2int64_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return std::get<number_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)).get<int64_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline int32_t TypeCastHelper::Native2int32_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return std::get<number_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)).get<int32_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline int16_t TypeCastHelper::Native2int16_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return std::get<number_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)).get<int16_t>();
}

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline int8_t TypeCastHelper::Native2int8_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return std::get<number_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)).get<int8_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline uint64_t TypeCastHelper::Native2uint64_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return std::get<number_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)).get<uint64_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline uint32_t TypeCastHelper::Native2uint32_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return std::get<number_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)).get<uint32_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline uint16_t TypeCastHelper::Native2uint16_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return std::get<number_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)).get<uint16_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline uint8_t TypeCastHelper::Native2uint8_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return std::get<number_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)).get<uint8_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline bool TypeCastHelper::Native2bool(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return std::get<bool>(std::get<value>(reinterpret_cast<value_type*>(val)->value));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline String^ TypeCastHelper::Native2string(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return marshalString(std::get<std::string>(std::get<value>(reinterpret_cast<value_type*>(val)->value)));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline LiteLoader::RemoteCall::NumberType TypeCastHelper::Native2NumberType(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return NumberType(std::get<number_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline MC::Player^ TypeCastHelper::Native2Player(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew MC::Player(std::get<::Player*>(std::get<value>(reinterpret_cast<value_type*>(val)->value)));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline MC::Actor^ TypeCastHelper::Native2Actor(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew MC::Actor(std::get<::Actor*>(std::get<value>(reinterpret_cast<value_type*>(val)->value)));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline MC::BlockActor^ TypeCastHelper::Native2BlockActor(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew MC::BlockActor(std::get<::BlockActor*>(std::get<value>(reinterpret_cast<value_type*>(val)->value)));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline MC::Container^ TypeCastHelper::Native2Container(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew MC::Container(std::get<::Container*>(std::get<value>(reinterpret_cast<value_type*>(val)->value)));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline MC::Vec3 TypeCastHelper::Native2Vec3(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return MC::Vec3(std::get<world_pos_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)).pos);
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline MC::BlockPos TypeCastHelper::Native2BlockPos(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return MC::BlockPos(std::get<block_pos_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)).pos);
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline LiteLoader::RemoteCall::WorldPosType^ TypeCastHelper::Native2WorldPosType(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew WorldPosType(std::get<world_pos_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline LiteLoader::RemoteCall::BlockPosType^ TypeCastHelper::Native2BlockPosType(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew BlockPosType(std::get<block_pos_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline LiteLoader::RemoteCall::ItemType^ TypeCastHelper::Native2ItemType(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew ItemType(std::get<item_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline LiteLoader::RemoteCall::BlockType^ TypeCastHelper::Native2BlockType(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew BlockType(std::get<block_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline LiteLoader::RemoteCall::NbtType^ TypeCastHelper::Native2NbtType(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew NbtType(std::get<nbt_type>(std::get<value>(reinterpret_cast<value_type*>(val)->value)));
    }

    void* TypeCastHelper::Native2ArrayTypePtr(void* val)
    {
        return &std::get<array_type>(reinterpret_cast<value_type*>(val)->value);
    }

    void* TypeCastHelper::Native2ObjectTypePtr(void* val)
    {
        return &std::get<object_type>(reinterpret_cast<value_type*>(val)->value);
    }

    inline TypeCastHelper::ArrayTypeWeakRef::iterator::iterator(void* instance)
        :instance(instance)
    {
    }

    inline bool TypeCastHelper::ArrayTypeWeakRef::iterator::MoveNext()
    {
        pin_ptr<__iterator> pinpIter = &iter;
        array_type_native_iterator* pIter = reinterpret_cast<array_type_native_iterator*>(pinpIter);
        auto pNative = reinterpret_cast<array_type*>(instance);

        if (isIterSet)
        {
            ++(*pIter);
            return *pIter != pNative->end();
        }
        else
        {
            auto _iter = pNative->begin();
            if (_iter == pNative->end())
                return false;

            memcpy(pIter, &_iter, sizeof(array_type_native_iterator));
            isIterSet = true;
            return true;
        }
    }

    inline void TypeCastHelper::ArrayTypeWeakRef::iterator::Reset()
    {
        isIterSet = false;
    }

    inline void* TypeCastHelper::ArrayTypeWeakRef::iterator::GetCurrentPtr()
    {
        pin_ptr<__iterator> pinpIter = &iter;
        array_type_native_iterator* pIter = reinterpret_cast<array_type_native_iterator*>(pinpIter);
        return &*pIter;
    }

    inline nint_t TypeCastHelper::ArrayTypeWeakRef::iterator::Current::get()
    {
        return nint_t(GetCurrentPtr());
    }

    inline Object^ TypeCastHelper::ArrayTypeWeakRef::iterator::CurrentNonGgeneric::get()
    {
        return Current;
    }

    inline TypeCastHelper::ArrayTypeWeakRef::ArrayTypeWeakRef(void* ptr)
        :ptr(ptr)
    {
    }

    inline size_t TypeCastHelper::ArrayTypeWeakRef::Size()
    {
        return reinterpret_cast<array_type*>(ptr)->size();
    }

    inline void TypeCastHelper::ArrayTypeWeakRef::Reset(void* ptr)
    {
        this->ptr = ptr;
    }

    void* TypeCastHelper::ArrayTypeWeakRef::GetArrayTypePtrByIndex(int index)
    {
        return &(*reinterpret_cast<array_type*>(ptr))[index];
    }

    inline nint_t TypeCastHelper::ArrayTypeWeakRef::default::get(int index)
    {
        return nint_t(GetArrayTypePtrByIndex(index));
    }

    inline TypeCastHelper::ArrayTypeWeakRef::iterator TypeCastHelper::ArrayTypeWeakRef::GetIterator()
    {
        return iterator(ptr);
    }

    inline IEnumerator<nint_t>^ TypeCastHelper::ArrayTypeWeakRef::GetEnumerator()
    {
        return GetIterator();
    }

    inline IEnumeratorNonGgeneric^ TypeCastHelper::ArrayTypeWeakRef::GetEnumeratorNonGgeneric()
    {
        return GetEnumerator();
    }

    inline TypeCastHelper::ObjectTypeWeakRef::iterator::iterator(void* instance)
        :instance(instance)
    {
    }

    inline bool TypeCastHelper::ObjectTypeWeakRef::iterator::MoveNext()
    {
        pin_ptr<__iterator> pinpIter = &iter;
        object_type_native_iterator* pIter = reinterpret_cast<object_type_native_iterator*>(pinpIter);
        auto pNative = reinterpret_cast<object_type*>(instance);

        if (isIterSet)
        {
            ++(*pIter);
            return *pIter != pNative->end() ? true : false;
        }
        else
        {
            auto _iter = pNative->begin();
            if (_iter == pNative->end())
                return false;

            memcpy(pIter, &_iter, sizeof(object_type_native_iterator));
            isIterSet = true;
            return true;
        }
    }

    inline void TypeCastHelper::ObjectTypeWeakRef::iterator::Reset()
    {
        isIterSet = false;
    }

    inline void* TypeCastHelper::ObjectTypeWeakRef::iterator::GetCurrentPtr()
    {
        pin_ptr<__iterator> pinpIter = &iter;
        object_type_native_iterator* pIter = reinterpret_cast<object_type_native_iterator*>(pinpIter);
        return &*pIter;
    }

    String^ TypeCastHelper::ObjectTypeWeakRef::iterator::GetKey()
    {
        pin_ptr<__iterator> pinpIter = &iter;
        object_type_native_iterator* pIter = reinterpret_cast<object_type_native_iterator*>(pinpIter);
        return marshalString((**pIter).first);
    }

    void* TypeCastHelper::ObjectTypeWeakRef::iterator::GetValue()
    {
        pin_ptr<__iterator> pinpIter = &iter;
        object_type_native_iterator* pIter = reinterpret_cast<object_type_native_iterator*>(pinpIter);
        return &(**pIter).second;
    }

    inline nint_t TypeCastHelper::ObjectTypeWeakRef::iterator::Current::get()
    {
        return nint_t(GetCurrentPtr());
    }

    inline Object^ TypeCastHelper::ObjectTypeWeakRef::iterator::CurrentNonGgeneric::get()
    {
        return Current;
    }

    inline TypeCastHelper::ObjectTypeWeakRef::ObjectTypeWeakRef(void* ptr)
        :ptr(ptr)
    {
    }

    inline size_t TypeCastHelper::ObjectTypeWeakRef::Size()
    {
        return reinterpret_cast<object_type*>(ptr)->size();
    }

    inline void TypeCastHelper::ObjectTypeWeakRef::Reset(void* ptr)
    {
        this->ptr = ptr;
    }

    inline nint_t TypeCastHelper::ObjectTypeWeakRef::default::get(String^ key)
    {
        return static_cast<nint_t>(&(reinterpret_cast<object_type*>(ptr)->operator[](marshalString(key))));
    }

    inline TypeCastHelper::ObjectTypeWeakRef::iterator TypeCastHelper::ObjectTypeWeakRef::GetIterator()
    {
        return iterator(ptr);
    }

    inline IEnumerator<nint_t>^ TypeCastHelper::ObjectTypeWeakRef::GetEnumerator()
    {
        return GetIterator();
    }

    inline IEnumeratorNonGgeneric^ TypeCastHelper::ObjectTypeWeakRef::GetEnumeratorNonGgeneric()
    {
        return GetEnumerator();
    }
}