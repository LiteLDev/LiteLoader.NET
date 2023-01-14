#pragma once

#include <mc/ReadOnlyBinaryStream.hpp>
#include <mc/RakNet.hpp>
#include "Types.hpp"
#include <src/Module/Core/Std/string.hpp>

namespace MC
{
    using __string = LiteLoader::NET::Std::string;

    public enum class StreamReadResult
    {
    };

    public ref class ReadOnlyBinaryStream
        : ClassTemplate<ReadOnlyBinaryStream, ::ReadOnlyBinaryStream>
    {
    public:
        __ctor(ReadOnlyBinaryStream, ::ReadOnlyBinaryStream);
        __ctor_default(ReadOnlyBinaryStream, ::ReadOnlyBinaryStream);

        property unsigned __int64 ReadPointer
        {
            unsigned __int64 get() { return NativePtr->readPointer; }
            void set(unsigned __int64 value) { NativePtr->readPointer = value; }
        }
        property bool Unk
        {
            bool get()
            {
                return NativePtr->unk;
            }
            void set(bool value)
            {
                NativePtr->unk = value;
            }
        }
        property String^ OwnBuf
        {
            String^ get() { return marshalString(NativePtr->ownBuf); }

            void set(String^ value)
            {
                NativePtr->ownBuf = marshalString(value);
            }
        }
        property __string^ Buf
        {
            __string^ get() { return gcnew __string(NativePtr->pBuf); }

            void set(__string^ value)
            {
                *NativePtr->pBuf = *value->NativePtr;
            }
        }

        property String^ Data { String^ get() { return marshalString(NativePtr->getData()); } };
        property unsigned __int64 Length { unsigned __int64 get() { return NativePtr->getLength(); } };
        property unsigned __int64 UnreadLength { unsigned __int64 get() { return NativePtr->getUnreadLength(); } };
        
        void Read(void* buffer, unsigned __int64 size);
        void Read(array<System::Byte>^ buffer);

        ReadOnlyBinaryStream(String^ str);
        ReadOnlyBinaryStream(String^ str, bool b);

        bool CanReadBool();
        bool GetBool();
        System::Byte GetByte();
        double GetDouble();
        float GetFloat();
        StreamReadResult GetReadCompleteResult();
        int GetSignedBigEndianInt();
        int GetSignedInt();
        __int64 GetSignedInt64();
        short GetSignedShort();
        int GetVarInt();
        __int64 GetVarInt64();
        String^ GetString();
        bool GetString([Out] String^% str);
        unsigned int GetUnsignedInt();
        unsigned __int64 GetUnsignedInt64();
        unsigned short GetUnsignedShort();
        unsigned int GetUnsignedVarInt();
        unsigned __int64 GetUnsignedVarInt64();
        Mce::UUID GetUUID();
        //Vec3 GetVec3();
    };
}
