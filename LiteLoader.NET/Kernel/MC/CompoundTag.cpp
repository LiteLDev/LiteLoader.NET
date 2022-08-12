#include <LiteLoader.NET/Header/MC/CompoundTag.hpp>

#include <LiteLoader.NET/Header/MC/ItemStack.hpp>
#include <LiteLoader.NET/Header/MC/Actor.hpp>
#include <LiteLoader.NET/Header/MC/Block.hpp>
#include <LiteLoader.NET/Header/MC/BlockActor.hpp>
#include <LiteLoader.NET/Header/MC/Player.hpp>
#include <LiteLoader.NET/Header/MC/CompoundTagVariant.hpp>
#include <LiteLoader.NET/Header/MC/ByteArrayTag.hpp>
#include <LiteLoader.NET/Header/MC/ByteTag.hpp>
#include <LiteLoader.NET/Header/MC/CompoundTag.hpp>
#include <LiteLoader.NET/Header/MC/DoubleTag.hpp>
#include <LiteLoader.NET/Header/MC/ShortTag.hpp>
#include <LiteLoader.NET/Header/MC/EndTag.hpp>
#include <LiteLoader.NET/Header/MC/FloatTag.hpp>
#include <LiteLoader.NET/Header/MC/Int64Tag.hpp>
#include <LiteLoader.NET/Header/MC/IntArrayTag.hpp>
#include <LiteLoader.NET/Header/MC/IntTag.hpp>
#include <LiteLoader.NET/Header/MC/ListTag.hpp>
#include <LiteLoader.NET/Header/MC/ShortTag.hpp>
#include <LiteLoader.NET/Header/MC/StringTag.hpp>
#include <LiteLoader.NET/Header/MC/Tag.hpp>

namespace MC
{

inline CompoundTag ^ CompoundTag::Create()
{
    return gcnew CompoundTag(::CompoundTag::create().release(), true);
}

inline Dictionary<String^, CompoundTagVariant ^> ^ CompoundTag::Value()
{
    Dictionary<String^, CompoundTagVariant ^> ^ ret;
    auto& stdmap = NativePtr->value();
    ret = gcnew Dictionary<String^, CompoundTagVariant ^>(int(stdmap.size()));
    for (auto iter = stdmap.begin(); iter != stdmap.end(); ++iter)
        ret->Add(
            marshalString((*iter).first),
            gcnew CompoundTagVariant(&iter->second));
    return ret;
}

// put value
inline void CompoundTag::PutEnd(String^ key)
{
    NativePtr->putEnd(marshalString(key));
}

inline double ^ CompoundTag::PutDouble(String^ key, double val)
{
    return NativePtr->putDouble(marshalString(key), val);
}

inline void CompoundTag::PutByteArray(String^ key, array<char> ^ data /*, size_t size*/)
{
    pin_ptr<char> p_ptr = &data[0];
    NativePtr->putByteArray(marshalString(key), (char*)p_ptr, data->Length);
}

inline void CompoundTag::PutIntArray(String^ key, array<int> ^ data /*, size_t size*/)
{
    pin_ptr<int> p_ptr = &data[0];
    NativePtr->putIntArray(marshalString(key), (int*)p_ptr, data->Length);
}

inline TagMemoryChunk ^ CompoundTag::PutIntArray(String^ key, TagMemoryChunk ^ val)
{
    return gcnew TagMemoryChunk(
        NativePtr->putIntArray(marshalString(key), val));
}

// get value
inline double CompoundTag::GetDouble(String^ key)
{
    return NativePtr->getDouble(marshalString(key));
}

inline TagMemoryChunk const ^ CompoundTag::GetIntArray(String^ key)
{
    return gcnew TagMemoryChunk(::TagMemoryChunk(NativePtr->getIntArray(marshalString(key))));
}

// get tag
inline ByteTag const ^ CompoundTag::GetByteTag(String^ key)
{
    return gcnew ByteTag((::ByteTag*)NativePtr->getByteTag(marshalString(key)));
}
inline ShortTag const ^ CompoundTag::GetShortTag(String^ key)
{
    return gcnew ShortTag((::ShortTag*)NativePtr->getShortTag(marshalString(key)));
}
inline FloatTag const ^ CompoundTag::GetFloatTag(String^ key)
{
    return gcnew FloatTag((::FloatTag*)NativePtr->getFloatTag(marshalString(key)));
}
inline DoubleTag const ^ CompoundTag::GetDoubleTag(String^ key)
{
    return gcnew DoubleTag((::DoubleTag*)NativePtr->getDoubleTag(marshalString(key)));
}
inline ByteArrayTag const ^ CompoundTag::GetByteArrayTag(String^ key)
{
    return gcnew ByteArrayTag((::ByteArrayTag*)NativePtr->getByteArrayTag(marshalString(key)));
}
inline StringTag const ^ CompoundTag::GetStringTag(String^ key)
{
    return gcnew StringTag((::StringTag*)NativePtr->getStringTag(marshalString(key)));
}
inline IntArrayTag const ^ CompoundTag::GetIntArrayTag(String^ key)
{
    return gcnew IntArrayTag((::IntArrayTag*)NativePtr->getIntArrayTag(marshalString(key)));
}
inline ListTag const ^ CompoundTag::GetListTag(String^ key)
{
    return gcnew ListTag((::ListTag*)NativePtr->getListTag(marshalString(key)));
}
inline CompoundTag ^ CompoundTag::GetCompoundTag(String^ key)
{
    return gcnew CompoundTag((::CompoundTag*)NativePtr->getCompoundTag(marshalString(key)));
}
inline Tag ^ CompoundTag::operator[](String^ key)
{
    return gcnew Tag((*NativePtr)[marshalString(key)]);
}

// io
inline void CompoundTag::SetItemStack(ItemStack ^ item)
{
    NativePtr->setItemStack(item->NativePtr);
}

inline void CompoundTag::SetBlock(Block ^ block)
{
    NativePtr->setBlock(block);
}

inline bool CompoundTag::SetActor(Actor ^ actor)
{
    return NativePtr->setActor(actor);
}

inline bool CompoundTag::SetBlockActor(BlockActor ^ ble)
{
    return NativePtr->setBlockActor(ble);
}

inline bool CompoundTag::SetPlayer(Player ^ player)
{
    return NativePtr->setPlayer(player->NativePtr);
}

inline CompoundTag ^ CompoundTag::FromItemStack(ItemStack ^ item)
{
    return gcnew CompoundTag(::CompoundTag::fromItemStack(item->NativePtr).release(), true);
}

inline CompoundTag ^ CompoundTag::FromBlock(Block ^ block)
{
    return gcnew CompoundTag(::CompoundTag::fromBlock(block).release(), true);
}

inline CompoundTag ^ CompoundTag::FromActor(Actor ^ actor)
{
    return gcnew CompoundTag(::CompoundTag::fromActor(actor).release(), true);
}

inline CompoundTag ^ CompoundTag::FromBlockActor(BlockActor ^ blockActor)
{
    return gcnew CompoundTag(::CompoundTag::fromBlockActor(blockActor).release(), true);
}

inline CompoundTag ^ CompoundTag::FromPlayer(Player ^ player)
{
    return gcnew CompoundTag(::CompoundTag::fromPlayer(player->NativePtr).release(), true);
}

inline String^ CompoundTag::ToSNBT()
{
    return marshalString(NativePtr->toSNBT());
}
inline String^ CompoundTag::ToBinaryNBT(bool isLittleEndian)
{
    return marshalString(NativePtr->toBinaryNBT(isLittleEndian));
}
inline String^ CompoundTag::ToBinaryNBT()
{
    return marshalString(NativePtr->toBinaryNBT());
}
inline CompoundTag ^ CompoundTag::FromSNBT(String^ snbt)
{
    return gcnew CompoundTag(::CompoundTag::fromSNBT(marshalString(snbt)).release(), true);
}
inline CompoundTag ^ CompoundTag::FromBinaryNBT(void* data, size_t len, bool isLittleEndian)
{
    return gcnew CompoundTag(::CompoundTag::fromBinaryNBT(data, len, isLittleEndian).release(), true);
}
inline CompoundTag ^ CompoundTag::FromBinaryNBT(void* data, size_t len)
{
    return gcnew CompoundTag(::CompoundTag::fromBinaryNBT(data, len).release(), true);
}
inline CompoundTag ^ CompoundTag::FromBinaryNBT(void* data, size_t len, size_t& endOffset, bool isLittleEndian)
{
    return gcnew CompoundTag(::CompoundTag::fromBinaryNBT(data, len, endOffset, isLittleEndian).release(), true);
}
inline CompoundTag ^ CompoundTag::FromBinaryNBT(void* data, size_t len, size_t& endOffset)
{
    return gcnew CompoundTag(::CompoundTag::fromBinaryNBT(data, len, endOffset).release(), true);
}

} // namespace MC


#ifdef INCLUDE_MCAPI

#include <memory>

void MC::CompoundTag::DeleteChildren()
{
    ((class ::CompoundTag*)NativePtr)->deleteChildren();
}

::String^ MC::CompoundTag::ToString()
{
    auto __ret = ((class ::CompoundTag*)NativePtr)->toString();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

MC::Tag::Type MC::CompoundTag::GetId()
{
    auto __ret = ((class ::CompoundTag*)NativePtr)->getId();
    return (MC::Tag::Type)__ret;
}

bool MC::CompoundTag::Equals(MC::Tag ^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Tag*)_0->NativePtr;
    auto __ret = ((class ::CompoundTag*)NativePtr)->equals(__arg0);
    return __ret;
}

unsigned long long MC::CompoundTag::hash()
{
    auto __ret = ((class ::CompoundTag*)NativePtr)->hash();
    return __ret;
}

void MC::CompoundTag::Append(MC::CompoundTag ^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::CompoundTag*)_0->NativePtr;
    ((class ::CompoundTag*)NativePtr)->append(__arg0);
}

void MC::CompoundTag::Clear()
{
    ((class ::CompoundTag*)NativePtr)->clear();
}

bool MC::CompoundTag::Contains(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __ret = ((class ::CompoundTag*)NativePtr)->contains(__arg0);
    return __ret;
}

bool MC::CompoundTag::Contains(::String^ _0, MC::Tag::Type _1)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __arg1 = (enum ::Tag::Type)_1;
    auto __ret = ((class ::CompoundTag*)NativePtr)->contains(__arg0, __arg1);
    return __ret;
}

void MC::CompoundTag::DeepCopy(MC::CompoundTag ^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::CompoundTag*)_0->NativePtr;
    ((class ::CompoundTag*)NativePtr)->deepCopy(__arg0);
}

MC::Tag ^ MC::CompoundTag::Get(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __ret = ((class ::CompoundTag*)NativePtr)->get(__arg0);
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Tag((class ::Tag*)__ret);
}

bool MC::CompoundTag::GetBoolean(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __ret = ((class ::CompoundTag*)NativePtr)->getBoolean(__arg0);
    return __ret;
}

unsigned char MC::CompoundTag::GetByte(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __ret = ((class ::CompoundTag*)NativePtr)->getByte(__arg0);
    return __ret;
}

MC::CompoundTag ^ MC::CompoundTag::GetCompound(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __ret = ((class ::CompoundTag*)NativePtr)->getCompound(__arg0);
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::CompoundTag((class ::CompoundTag*)__ret);
}

float MC::CompoundTag::GetFloat(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __ret = ((class ::CompoundTag*)NativePtr)->getFloat(__arg0);
    return __ret;
}

int MC::CompoundTag::GetInt(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __ret = ((class ::CompoundTag*)NativePtr)->getInt(__arg0);
    return __ret;
}

long long MC::CompoundTag::GetInt64(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __ret = ((class ::CompoundTag*)NativePtr)->getInt64(__arg0);
    return __ret;
}

short MC::CompoundTag::GetShort(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __ret = ((class ::CompoundTag*)NativePtr)->getShort(__arg0);
    return __ret;
}

::String^ MC::CompoundTag::GetString(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto& __ret = ((class ::CompoundTag*)NativePtr)->getString(__arg0);
    return (::String^)(clix::marshalString<clix::E_UTF8>(__ret));
}

MC::Tag ^ MC::CompoundTag::Put(::String^ _0, MC::Tag ^ _1)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    if (ReferenceEquals(_1, nullptr))
        throw gcnew ::System::ArgumentNullException("_1", "Cannot be null because it is a C++ reference (&).");
    auto& __arg1 = *(class ::Tag*)_1->NativePtr;
    auto& __ret = ((class ::CompoundTag*)NativePtr)->put(__arg0, std::move(__arg1));
    return (MC::Tag ^)((&__ret == nullptr) ? nullptr : gcnew ::MC::Tag((class ::Tag*)&__ret));
}

void MC::CompoundTag::PutBoolean(::String^ _0, bool _1)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    ((class ::CompoundTag*)NativePtr)->putBoolean(__arg0, _1);
}

unsigned char MC::CompoundTag::PutByte(::String^ _0, unsigned char _1)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto& __ret = ((class ::CompoundTag*)NativePtr)->putByte(__arg0, _1);
    return (unsigned char)(__ret);
}

MC::CompoundTag ^ MC::CompoundTag::PutCompound(::String^ _0, MC::CompoundTag ^ _1)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    if (ReferenceEquals(_1, nullptr))
        throw gcnew ::System::ArgumentNullException("_1", "Cannot be null because it is passed by value.");
    auto __ret = ((class ::CompoundTag*)NativePtr)->putCompound(__arg0, std::unique_ptr<::CompoundTag>((::CompoundTag*)_1->Release()));
    return __ret == nullptr ? nullptr : gcnew ::MC::CompoundTag(__ret);
}

float MC::CompoundTag::PutFloat(::String^ _0, float _1)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto& __ret = ((class ::CompoundTag*)NativePtr)->putFloat(__arg0, _1);
    return (float)(__ret);
}

int MC::CompoundTag::PutInt(::String^ _0, int _1)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto& __ret = ((class ::CompoundTag*)NativePtr)->putInt(__arg0, _1);
    return (int)(__ret);
}

long long MC::CompoundTag::PutInt64(::String^ _0, long long _1)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto& __ret = ((class ::CompoundTag*)NativePtr)->putInt64(__arg0, _1);
    return (long long)(__ret);
}

short MC::CompoundTag::PutShort(::String^ _0, short _1)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto& __ret = ((class ::CompoundTag*)NativePtr)->putShort(__arg0, _1);
    return (short)(__ret);
}

::String^ MC::CompoundTag::PutString(::String^ _0, ::String^ _1)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __arg1 = clix::marshalString<clix::E_UTF8>(_1);
    auto& __ret = ((class ::CompoundTag*)NativePtr)->putString(__arg0, __arg1);
    return (::String^)(clix::marshalString<clix::E_UTF8>(__ret));
}

bool MC::CompoundTag::Remove(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __ret = ((class ::CompoundTag*)NativePtr)->remove(__arg0);
    return __ret;
}

void MC::CompoundTag::Rename(::String^ _0, ::String^ _1)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __arg1 = clix::marshalString<clix::E_UTF8>(_1);
    ((class ::CompoundTag*)NativePtr)->rename(__arg0, __arg1);
}

bool MC::CompoundTag::IsEmpty::get()
{
    auto __ret = ((class ::CompoundTag*)NativePtr)->isEmpty();
    return __ret;
}
#endif // INCLUDE_MCAPI
