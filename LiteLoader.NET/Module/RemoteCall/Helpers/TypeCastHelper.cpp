#include "TypeCastHelper.hpp"

#include <LiteLoader.NET/Module/RemoteCall/Types/NumberType.hpp>
#include <LiteLoader.NET/Module/RemoteCall/Types/WorldPosType.hpp>
#include <LiteLoader.NET/Module/RemoteCall/Types/BlockPosType.hpp>
#include <LiteLoader.NET/Module/RemoteCall/Types/ItemType.hpp>
#include <LiteLoader.NET/Module/RemoteCall/Types/BlockType.hpp>
#include <LiteLoader.NET/Module/RemoteCall/Types/NbtType.hpp>

#include <LiteLoader.NET/Header/MC/Player.hpp>
#include <LiteLoader.NET/Header/MC/Actor.hpp>
#include <LiteLoader.NET/Header/MC/BlockActor.hpp>
#include <LiteLoader.NET/Header/MC/Container.hpp>
#include <LiteLoader.NET/Header/MC/Vec3.hpp>
#include <LiteLoader.NET/Header/MC/BlockPos.hpp>

namespace LiteLoader::RemoteCall::Helper
{
#define __VALUE std::get<::RemoteCall::Value>(((::RemoteCall::ValueType*)val)->value)
#define __NUMBERTYPE std::get<::RemoteCall::NumberType>(__VALUE)

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline double TypeCastHelper::_Native2double(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return __NUMBERTYPE.get<double>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline float TypeCastHelper::_Native2float(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return __NUMBERTYPE.get<float>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline int64_t TypeCastHelper::_Native2int64_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return __NUMBERTYPE.get<int64_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline int32_t TypeCastHelper::_Native2int32_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return __NUMBERTYPE.get<int32_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline int16_t TypeCastHelper::_Native2int16_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return __NUMBERTYPE.get<int16_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline int8_t TypeCastHelper::_Native2int8_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return __NUMBERTYPE.get<int8_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline uint64_t TypeCastHelper::_Native2uint64_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return __NUMBERTYPE.get<uint64_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline uint32_t TypeCastHelper::_Native2uint32_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return __NUMBERTYPE.get<uint32_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline uint16_t TypeCastHelper::_Native2uint16_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return __NUMBERTYPE.get<uint16_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline uint8_t TypeCastHelper::_Native2uint8_t(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return __NUMBERTYPE.get<uint8_t>();
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline bool TypeCastHelper::_Native2bool(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return std::get<bool>(__VALUE);
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline String^ TypeCastHelper::_Native2string(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return marshalString(std::get<std::string>(__VALUE));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline LiteLoader::RemoteCall::NumberType TypeCastHelper::_Native2NumberType(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return NumberType(__NUMBERTYPE);
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline MC::Player^ TypeCastHelper::_Native2Player(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew MC::Player(std::get<::Player*>(__VALUE));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline MC::Actor^ TypeCastHelper::_Native2Actor(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew MC::Actor(std::get<::Actor*>(__VALUE));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline MC::BlockActor^ TypeCastHelper::_Native2BlockActor(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew MC::BlockActor(std::get<::BlockActor*>(__VALUE));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline MC::Container^ TypeCastHelper::_Native2Container(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew MC::Container(std::get<::Container*>(__VALUE));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline MC::Vec3 TypeCastHelper::_Native2Vec3(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return MC::Vec3(std::get<::RemoteCall::WorldPosType>(__VALUE).pos);
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline MC::BlockPos TypeCastHelper::_Native2BlockPos(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return MC::BlockPos(std::get<::RemoteCall::BlockPosType>(__VALUE).pos);
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline LiteLoader::RemoteCall::WorldPosType^ TypeCastHelper::_Native2WorldPosType(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew WorldPosType(std::get<::RemoteCall::WorldPosType>(__VALUE));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline LiteLoader::RemoteCall::BlockPosType^ TypeCastHelper::_Native2BlockPosType(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew BlockPosType(std::get<::RemoteCall::BlockPosType>(__VALUE));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline LiteLoader::RemoteCall::ItemType^ TypeCastHelper::_Native2ItemType(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew ItemType(std::get<::RemoteCall::ItemType>(__VALUE));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline LiteLoader::RemoteCall::BlockType^ TypeCastHelper::_Native2BlockType(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew BlockType(std::get<::RemoteCall::BlockType>(__VALUE));
    }

    [MethodImpl(MethodImplOptions::AggressiveInlining)]
    inline LiteLoader::RemoteCall::NbtType^ TypeCastHelper::_Native2NbtType(void* val)
    {
#ifdef REMOTECALL_DEBUG
        REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

        return gcnew NbtType(std::get<::RemoteCall::NbtType>(__VALUE));
    }

    inline TypeCastHelper::ArrayTypeWeakRef::iterator::iterator(void* instance)
        :instance(instance)
    {
    }

    inline bool TypeCastHelper::ArrayTypeWeakRef::iterator::MoveNext()
    {
        array_type_native_iterator* pIter = reinterpret_cast<array_type_native_iterator*>(pin_ptr<__iterator>(&iter));
        auto pNative = reinterpret_cast<array_type*>(instance);

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
        array_type_native_iterator* pIter = reinterpret_cast<array_type_native_iterator*>(pin_ptr<__iterator>(&iter));
        return &*pIter;
    }

    inline IntPtr TypeCastHelper::ArrayTypeWeakRef::iterator::Current::get()
    {
        return IntPtr(GetCurrentPtr());
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

    inline IntPtr TypeCastHelper::ArrayTypeWeakRef::default::get(size_t index)
    {
        return static_cast<IntPtr>(&(reinterpret_cast<array_type*>(ptr)->operator[](index)));
    }

    inline TypeCastHelper::ArrayTypeWeakRef::iterator TypeCastHelper::ArrayTypeWeakRef::GetIterator()
    {
        return iterator(ptr);
    }

    inline IEnumerator<IntPtr>^ TypeCastHelper::ArrayTypeWeakRef::GetEnumerator()
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
        object_type_native_iterator* pIter = reinterpret_cast<object_type_native_iterator*>(pin_ptr<__iterator>(&iter));
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
        object_type_native_iterator* pIter = reinterpret_cast<object_type_native_iterator*>(pin_ptr<__iterator>(&iter));
        return &*pIter;
    }

    inline IntPtr TypeCastHelper::ObjectTypeWeakRef::iterator::Current::get()
    {
        return IntPtr(GetCurrentPtr());
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

    inline IntPtr TypeCastHelper::ObjectTypeWeakRef::default::get(String^ key)
    {
        return static_cast<IntPtr>(&(reinterpret_cast<object_type*>(ptr)->operator[](marshalString(key))));
    }

    inline TypeCastHelper::ObjectTypeWeakRef::iterator TypeCastHelper::ObjectTypeWeakRef::GetIterator()
    {
        return iterator(ptr);
    }
    
    inline IEnumerator<IntPtr>^ TypeCastHelper::ObjectTypeWeakRef::GetEnumerator()
    {
        return GetIterator();
    }

    inline IEnumeratorNonGgeneric^ TypeCastHelper::ObjectTypeWeakRef::GetEnumeratorNonGgeneric()
    {
        return GetEnumerator();
    }
}