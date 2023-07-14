#include <src/Header/MC/ReadOnlyBinaryStream.hpp>
#include <src/Header/MC/Vec3.hpp>
#include <mc/Bedrock.hpp>

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

    inline bool ReadOnlyBinaryStream::GetBool()
    {
        auto result = NativePtr->getBool();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

    inline System::Byte ReadOnlyBinaryStream::GetByte()
    {
        auto result = NativePtr->getByte();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

    inline double ReadOnlyBinaryStream::GetDouble()
    {
        auto result = NativePtr->getDouble();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

    inline float ReadOnlyBinaryStream::GetFloat()
    {
        auto result = NativePtr->getFloat();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

    inline int ReadOnlyBinaryStream::GetSignedBigEndianInt()
    {
        auto result = NativePtr->getSignedBigEndianInt();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

    inline int ReadOnlyBinaryStream::GetSignedInt()
    {
        auto result = NativePtr->getSignedInt();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

    inline __int64 ReadOnlyBinaryStream::GetSignedInt64()
    {
        auto result = NativePtr->getSignedInt64();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

    inline short ReadOnlyBinaryStream::GetSignedShort()
    {
        auto result = NativePtr->getSignedShort();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

    inline bool ReadOnlyBinaryStream::GetString([Out] String^% str)
    {
        str = nullptr;
        std::string __str;
        auto ret = NativePtr->getString(__str);
        if (!ret.has_value())
            return false;
        str = marshalString(__str);
        return true;
    }

    inline unsigned int ReadOnlyBinaryStream::GetUnsignedInt()
    {
        auto result = NativePtr->getUnsignedInt();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

    inline unsigned __int64 ReadOnlyBinaryStream::GetUnsignedInt64()
    {
        auto result = NativePtr->getUnsignedInt64();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

    inline unsigned short ReadOnlyBinaryStream::GetUnsignedShort()
    {
        auto result = NativePtr->getUnsignedShort();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

    inline unsigned int ReadOnlyBinaryStream::GetUnsignedVarInt()
    {
        auto result = NativePtr->getUnsignedVarInt();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

    inline unsigned __int64 ReadOnlyBinaryStream::GetUnsignedVarInt64()
    {
        auto result = NativePtr->getUnsignedVarInt64();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

    inline int ReadOnlyBinaryStream::GetVarInt()
    {
        auto result = NativePtr->getVarInt();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

    inline __int64 ReadOnlyBinaryStream::GetVarInt64()
    {
        auto result = NativePtr->getVarInt64();
        return result.has_value() ? result.value() : throw gcnew System::NullReferenceException();
    }

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
