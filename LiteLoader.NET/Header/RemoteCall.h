#pragma once
#include "../Extra/mutex.h"


#define REMOTECALL_FIXED

#ifdef REMOTECALL_FIXED

#include <RemoteCallAPI.h>
#include "../Main/.NETGlobal.hpp"
#include "../Tools/NativeCallbackConverter.hpp"
#include "../Main/ClassTemplate.h"

#include "../Header/MC/CompoundTag.hpp"
#include "../Header/MC/ItemStack.hpp"
#include "../Header/MC/BlockInstance.hpp"
#include "../Header/MC/Player.hpp"
#include "../Header/MC/Actor.hpp"
#include "../Header/MC/BlockActor.hpp"
#include "../Header/MC/Container.hpp"
#include "../Header/MC/Vec3.hpp"
#include "../Header/MC/BlockPos.hpp"

namespace LLNET::RemoteCall
{
public
ref class RemoteCallAPI abstract
{
public:
    delegate String ^ CallbackFn(List<String ^> ^);
    static bool ExportFunc(String ^ nameSpace, String ^ funcName, CallbackFn ^ fn);
    static bool ExportFunc(String ^ nameSpace, String ^ funcName, CallbackFn ^ fn, IntPtr handler);

    static CallbackFn ^ ImportFunc(String ^ nameSpace, String ^ funcName);

    static bool HasFunc(String ^ nameSpace, String ^ funcName);
    static bool RemoveFunc(String ^ nameSpace, String ^ funcName);
    static bool RemoveNameSpace(String ^ nameSpace);
    static bool RemoveFuncs(List<Pair<String ^, String ^>> ^ funcs);

public:
    using ValueType = ::RemoteCall::ValueType;
    //防止gc回收
    static Dictionary<uint64_t, NativeCallbackHandler ^> ^ CallbackData = gcnew Dictionary<uint64_t, NativeCallbackHandler ^>;
};
} // namespace LLNET::RemoteCall


namespace LLNET::RemoteCall
{


interface class IRemoteCallType
{
};

public
ref class NbtType : ClassTemplate<NbtType, ::RemoteCall::NbtType>, IRemoteCallType
{
public:
    NbtType(MC::CompoundTag ^ tag)
        : ClassTemplate(new ::RemoteCall::NbtType(tag->NativePtr), true)
    {
    }

    MC::CompoundTag ^ Get() {
        return gcnew MC::CompoundTag(NativePtr->get<CompoundTag*>());
    }
};

public
ref class ItemType : ClassTemplate<ItemType, ::RemoteCall::ItemType>, IRemoteCallType
{
public:
    ItemType(MC::ItemStack ^ item)
        : ClassTemplate(new ::RemoteCall::ItemType(item->NativePtr), true)
    {
    }

    MC::ItemStack ^ Get() {
        return gcnew MC::ItemStack(NativePtr->get<::ItemStack*>());
    }
};

public
ref class BlockType : ClassTemplate<BlockType, ::RemoteCall::BlockType>, IRemoteCallType
{
    BlockType(MC::BlockInstance ^ block)
        : ClassTemplate(new ::RemoteCall::BlockType(*block->NativePtr), true)
    {
    }
};


[StructLayout(LayoutKind::Sequential)] public  value class NumberType : IRemoteCallType {
    __int64 i;
    double f;

public:
    NumberType(double v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)){};
    NumberType(float v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)){};
    NumberType(__int64 v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)){};
    NumberType(int v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)){};
    NumberType(short v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)){};
    NumberType(char v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)){};
    NumberType(unsigned __int64 v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)){};
    NumberType(unsigned int v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)){};
    NumberType(unsigned short v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)){};
    NumberType(unsigned char v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)){};

    //generic<typename T> where T : System::ValueType
    //                                  T
    //                              Get()
    //{
    //    if (T::typeid == float ::typeid || T::typeid == double ::typeid)
    //        return  safe_cast<T>(f);
    //    return safe_cast<T>(i);
    //}

internal:
    operator ::RemoteCall::NumberType()
    {
        return ::RemoteCall::NumberType{i, f};
    }
};

public
ref class Value : ClassTemplate<Value, ::RemoteCall::Value>
{
    using T = ::RemoteCall::Value;

public:
    Value()
        : ClassTemplate(new T(), true)
    {
    }
    Value(nullptr_t null)
        : ClassTemplate(new T(null), true)
    {
    }
    Value(NumberType num)
        : ClassTemplate(new T(num.operator ::RemoteCall::NumberType()), true)
    {
    }
    Value(MC::Player ^ player)
        : ClassTemplate(new T(player->NativePtr), true)
    {
    }
    Value(MC::Actor ^ actor)
        : ClassTemplate(new T(actor->NativePtr), true)
    {
    }
    Value(MC::BlockActor ^ bloackActor)
        : ClassTemplate(new T(bloackActor->NativePtr), true)
    {
    }
    Value(MC::Container ^ container)
        : ClassTemplate(new T(container->NativePtr), true)
    {
    }
    Value(MC::Vec3 ^ vec3)
        : ClassTemplate(new T(*vec3->NativePtr), true)
    {
    }
    Value(MC::BlockPos ^ blockPos)
        : ClassTemplate(new T(*blockPos->NativePtr), true)
    {
    }
    Value(ItemType ^ itemType)
        : ClassTemplate(new T(*itemType->NativePtr), true)
    {
    }
    Value(BlockType^ blockType)
        : ClassTemplate(new T(*blockType->NativePtr))
    {
    }
    Value(NbtType^ nbtType)
        : ClassTemplate(new T(*nbtType->NativePtr), true)
    {
    }
};

public
ref class ValueType : ClassTemplate<ValueType, ::RemoteCall::ValueType>
{
};


} // namespace LLNET::RemoteCall

#endif // REMOTECALL_FIXED
