#include <src/Header/MC/ReadOnlyBinaryStream.hpp>
#include <src/Header/MC/Vec3.hpp>

namespace MC
{
    inline void ReadOnlyBinaryStream::Read(void* buffer, unsigned __int64 size) { NativePtr->read(buffer, size); }

    inline void ReadOnlyBinaryStream::Read(array<System::Byte>^ buffer)
    {
        pin_ptr<System::Byte> p = &buffer[0];
        NativePtr->read(p, buffer->Length);
    }

    inline ReadOnlyBinaryStream::ReadOnlyBinaryStream(String^ str)
    {
        NativePtr = new ::ReadOnlyBinaryStream(marshalString(str));
        ownsNativeInstance = true;
    }

    inline ReadOnlyBinaryStream::ReadOnlyBinaryStream(String^ str, bool b)
    {
        NativePtr = new ::ReadOnlyBinaryStream(marshalString(str), b);
        ownsNativeInstance = true;
    }

    inline bool ReadOnlyBinaryStream::CanReadBool() { return NativePtr->canReadBool(); }

    inline bool ReadOnlyBinaryStream::GetBool() { return NativePtr->getBool(); }

    inline System::Byte ReadOnlyBinaryStream::GetByte() { return NativePtr->getByte(); }

    inline double ReadOnlyBinaryStream::GetDouble() { return NativePtr->getDouble(); }

    inline float ReadOnlyBinaryStream::GetFloat() { return NativePtr->getFloat(); }

    inline StreamReadResult ReadOnlyBinaryStream::GetReadCompleteResult()
    {
        return static_cast<StreamReadResult>(NativePtr->getReadCompleteResult());
    }

    inline int ReadOnlyBinaryStream::GetSignedBigEndianInt() { return NativePtr->getSignedBigEndianInt(); }

    inline int ReadOnlyBinaryStream::GetSignedInt() { return NativePtr->getSignedInt(); }

    inline __int64 ReadOnlyBinaryStream::GetSignedInt64() { return NativePtr->getSignedInt64(); }

    inline short ReadOnlyBinaryStream::GetSignedShort() { return NativePtr->getSignedShort(); }

    inline String^ ReadOnlyBinaryStream::GetString() { return marshalString(NativePtr->getString()); }

    inline bool ReadOnlyBinaryStream::GetString([Out] String^% str)
    {
        str = nullptr;
        std::string __str;
        auto ret = NativePtr->getString(__str);
        if (!ret)
            return false;
        str = marshalString(__str);
        return true;
    }

    inline unsigned int ReadOnlyBinaryStream::GetUnsignedInt() { return NativePtr->getUnsignedInt(); }

    inline unsigned __int64 ReadOnlyBinaryStream::GetUnsignedInt64() { return NativePtr->getUnsignedInt64(); }

    inline unsigned short ReadOnlyBinaryStream::GetUnsignedShort() { return NativePtr->getUnsignedShort(); }

    inline unsigned int ReadOnlyBinaryStream::GetUnsignedVarInt() { return NativePtr->getUnsignedVarInt(); }

    inline unsigned __int64 ReadOnlyBinaryStream::GetUnsignedVarInt64() { return NativePtr->getUnsignedVarInt64(); }

    inline int ReadOnlyBinaryStream::GetVarInt() { return NativePtr->getVarInt(); }

    inline __int64 ReadOnlyBinaryStream::GetVarInt64() { return NativePtr->getVarInt64(); }

    Mce::UUID ReadOnlyBinaryStream::GetUUID()
    {
        mce::UUID uuid;
        NativePtr->readType(uuid);
        return uuid;
    }

    /*Vec3 ReadOnlyBinaryStream::GetVec3()
    {
        ::Vec3 vec3;
        NativePtr->readType(vec3);
        return vec3;
    }*/
}
