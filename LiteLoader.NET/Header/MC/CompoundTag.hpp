#pragma once

#include "CompoundTagVariant.hpp"
#include "ByteArrayTag.hpp"
#include "ByteTag.hpp"
#include "DoubleTag.hpp"
#include "EndTag.hpp"
#include "ShortTag.hpp"
#include "FloatTag.hpp"
#include "StringTag.hpp"
#include "IntArrayTag.hpp"
#include "ListTag.hpp"

#include <mc/CompoundTag.hpp>

using System::Collections::Generic::Dictionary;

namespace MC
{
ref class Actor;
ref class Player;
ref class ItemStack;
ref class Block;
ref class BlockActor;
ref class ItemStack;
ref class CompoundTagVariant;
} // namespace MC

namespace MC
{
public
ref class CompoundTag : public Tag
{
public:
    __ctor_base(CompoundTag, ::CompoundTag, Tag);

    inline static CompoundTag ^ Create();
    inline Dictionary<String^, CompoundTagVariant ^> ^ Value();
    // put value
    inline void PutEnd(String^ key);
    inline double ^ PutDouble(String^ key, double val);
    inline void PutByteArray(String^ key, array<char> ^ data /*, size_t size*/);
    inline void PutIntArray(String^ key, array<int> ^ data /*, size_t size*/);
    inline TagMemoryChunk ^ PutIntArray(String^ key, TagMemoryChunk ^ val);
    // get value
    inline double GetDouble(String^ key);
    inline TagMemoryChunk const ^ GetIntArray(String^ key);
    // get tag
    inline ByteTag const ^ GetByteTag(String^ key);
    inline ShortTag const ^ GetShortTag(String^ key);
    inline FloatTag const ^ GetFloatTag(String^ key);
    inline DoubleTag const ^ GetDoubleTag(String^ key);
    inline ByteArrayTag const ^ GetByteArrayTag(String^ key);
    inline StringTag const ^ GetStringTag(String^ key);
    inline IntArrayTag const ^ GetIntArrayTag(String^ key);
    inline ListTag const ^ GetListTag(String^ key);
    inline CompoundTag ^ GetCompoundTag(String^ key);
    inline Tag ^ operator[](String^ key);
    // io
    inline void SetItemStack(ItemStack ^ item);
    inline void SetBlock(Block ^ blk);
    inline bool SetActor(Actor ^ actor);
    inline bool SetBlockActor(BlockActor ^ ble);
    inline bool SetPlayer(Player ^ player);
    inline static CompoundTag ^ FromItemStack(ItemStack ^ item);
    inline static CompoundTag ^ FromBlock(Block ^ blk);
    inline static CompoundTag ^ FromActor(Actor ^ actor);
    inline static CompoundTag ^ FromBlockActor(BlockActor ^ ble);
    inline static CompoundTag ^ FromPlayer(Player ^ player);
    inline String^ ToSNBT();
    inline String^ ToBinaryNBT(bool isLittleEndian);
    inline String^ ToBinaryNBT();
    inline static CompoundTag ^ FromSNBT(String^ snbt);
    inline static CompoundTag ^ FromBinaryNBT(void* data, size_t len, bool isLittleEndian);
    inline static CompoundTag ^ FromBinaryNBT(void* data, size_t len);
    inline static CompoundTag ^ FromBinaryNBT(void* data, size_t len, size_t& endOffset, bool isLittleEndian);
    inline static CompoundTag ^ FromBinaryNBT(void* data, size_t len, size_t& endOffset);


#ifdef INCLUDE_MCAPI

    property bool IsEmpty
    {
        bool get();
    }

    virtual void DeleteChildren() override;

    virtual ::String^ ToString() override;

    virtual MC::Tag::Type GetId();

    virtual bool Equals(MC::Tag ^ _0) override;

    virtual unsigned long long hash();

    void Append(MC::CompoundTag ^ _0);

    void Clear();

    bool Contains(::String^ _0);

    bool Contains(::String^ _0, MC::Tag::Type _1);

    void DeepCopy(MC::CompoundTag ^ _0);

    MC::Tag ^ Get(::String^ _0);

    bool GetBoolean(::String^ _0);

    unsigned char GetByte(::String^ _0);

    MC::CompoundTag ^ GetCompound(::String^ _0);

    float GetFloat(::String^ _0);

    int GetInt(::String^ _0);

    long long GetInt64(::String^ _0);

    short GetShort(::String^ _0);

    ::String^ GetString(::String^ _0);

    MC::Tag ^ Put(::String^ _0, MC::Tag ^ _1);

    void PutBoolean(::String^ _0, bool _1);

    unsigned char PutByte(::String^ _0, unsigned char _1);

    MC::CompoundTag ^ PutCompound(::String^ _0, MC::CompoundTag ^ _1);

    float PutFloat(::String^ _0, float _1);

    int PutInt(::String^ _0, int _1);

    long long PutInt64(::String^ _0, long long _1);

    short PutShort(::String^ _0, short _1);

    ::String^ PutString(::String^ _0, ::String^ _1);

    bool Remove(::String^ _0);

    void Rename(::String^ _0, ::String^ _1);

#endif // INCLUDE_MCAPI
};
} // namespace MC
