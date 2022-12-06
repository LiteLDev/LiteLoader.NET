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

    virtual bool Equals(MC::Tag ^ tag) override;

    virtual unsigned long long hash();

    void Append(MC::CompoundTag ^ tag);

    void Clear();

    bool Contains(::String^ key);

    bool Contains(::String^ key, MC::Tag::Type type);

    void DeepCopy(MC::CompoundTag ^ tag);

    MC::Tag ^ Get(::String^ key);

    bool GetBoolean(::String^ key);

    unsigned char GetByte(::String^ key);

    MC::CompoundTag ^ GetCompound(::String^ key);

    float GetFloat(::String^ key);

    int GetInt(::String^ key);

    long long GetInt64(::String^ key);

    short GetShort(::String^ key);

    ::String^ GetString(::String^ key);

    MC::Tag ^ Put(::String^ key, MC::Tag ^ value);

    void PutBoolean(::String^ key, bool value);

    unsigned char PutByte(::String^ key, unsigned char value);

    MC::CompoundTag ^ PutCompound(::String^ key, MC::CompoundTag ^ value);

    float PutFloat(::String^ key, float value);

    int PutInt(::String^ key, int value);

    long long PutInt64(::String^ key, long long value);

    short PutShort(::String^ key, short value);

    ::String^ PutString(::String^ key, ::String^ value);

    bool Remove(::String^ key);

    void Rename(::String^ keyName, ::String^ newKeyName);

#endif // INCLUDE_MCAPI
};
} // namespace MC
