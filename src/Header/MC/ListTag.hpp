#pragma once
#include "Tag.hpp"
#include "TagMemoryChunk.hpp"

#include <mc/ListTag.hpp>

namespace MC
{
ref class Tag;
ref struct TagMemoryChunk;
}

namespace MC
{

public
ref class ListTag : public Tag
{
public:
    __ctor_base(ListTag, ::ListTag, Tag);
    __ctor_default_base(ListTag, ::ListTag, Tag);

    inline static ListTag ^ Create();
    array<Tag ^> ^ Value();
    property Tag ^ default[int] {
        Tag ^ get(int index) {
            return gcnew Tag(((::Tag*)((*NativePtr)[index])));
        }
    };
    inline Tag::Type const GetElementType();
    inline size_t getSize();
    array<Tag ^> ^ Get();
    inline unsigned char GetByte(int i);
    inline short GetShort(int i);
    inline int64_t GetInt64(int i);
    inline TagMemoryChunk ^ GetByteArray(int i);
    inline void AddEnd();
    inline void AddByte(unsigned char v);
    inline void AddShort(short v);
    inline void AddInt(int v);
    inline void AddInt64(__int64 v);
    inline void AddFloat(float v);
    inline void AddDouble(double v);
    inline void AddString(String^ v);
    inline void AddByteArray(TagMemoryChunk ^ byteArr);
    inline void AddByteArray(array<char> ^ data /*, size_t size*/);
    inline void AddIntArray(TagMemoryChunk ^ intArr);
    inline void AddIntArray(array<int> ^ data /*, size_t size*/);

#ifdef INCLUDE_MCAPI

    property int Size
    {
        int get();
    }

    virtual void DeleteChildren() override;

    virtual ::String^ ToString() override;

    virtual MC::Tag::Type GetId();

    virtual bool Equals(MC::Tag ^ _0) override;

    virtual unsigned long long hash();

    void Erase(unsigned long long _0);

    MC::Tag ^ Get(int _0);

    double GetDouble(int _0);

    float GetFloat(int _0);

    int GetInt(int _0);

    ::String^ GetString(int _0);

    void PopBack();

#endif INCLUDE_MCAPI
};

} // namespace MC
