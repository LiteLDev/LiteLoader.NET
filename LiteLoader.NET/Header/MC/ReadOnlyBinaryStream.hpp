#pragma once

#include <MC/ReadOnlyBinaryStream.hpp>
#include <MC/RakNet.hpp>
#include "Types.hpp"
#include "../Core/STLHelper/string.hpp"

#pragma make_public(::ReadOnlyBinaryStream)

namespace MC
{
	using __string = LLNET::Core::Std::string;

	public enum class StreamReadResult {};

	public ref class ReadOnlyBinaryStream
		:ClassTemplate<ReadOnlyBinaryStream, ::ReadOnlyBinaryStream>
	{
	public:
		__ctor(ReadOnlyBinaryStream, ::ReadOnlyBinaryStream);
	public:
		property size_t ReadPointer {size_t get() { return NativePtr->readPointer; } void set(size_t value) { NativePtr->readPointer = value; } };
		property bool Unk {bool get() { return NativePtr->unk; } void set(bool value) { NativePtr->unk = value; } };
		property String^ OwnBuf {String^ get() { return marshalString(NativePtr->ownBuf); } void set(String^ value) { NativePtr->ownBuf = marshalString(value); } };
		property __string^ Buf {__string^ get() { return gcnew __string(NativePtr->pBuf); } void set(__string^ value) { *NativePtr->pBuf = *value->NativePtr; } };
	public:
		property String^ Data {String^ get() { return marshalString(NativePtr->getData()); } };
		property size_t Length {size_t get() { return NativePtr->getLength(); } };
		//property size_t ReadPointer { size_t get() { return NativePtr->getReadPointer(); } };
		property size_t UnreadLength { size_t get() { return NativePtr->getUnreadLength(); } };
	public:
		String^ GetData();
		__string^ GetData_Native();
		void Read(void* buffer, unsigned __int64 size);
		void Read(array<System::Byte>^ buffer);
	public:
		ReadOnlyBinaryStream(String^ str);
		ReadOnlyBinaryStream(String^ str, bool b);
	public:
		bool CanReadBool();
		bool GetBool();
		unsigned char GetByte();
		double GetDouble();
		float GetFloat();
		StreamReadResult GetReadCompleteResult();
		int GetSignedBigEndianInt();
		int GetSignedInt();
		__int64 GetSignedInt64();
		short getSignedShort();
		String^ GetString();
		bool GetString([Out] String^% str);
		unsigned char GetUnsignedChar();
		unsigned int GetUnsignedInt();
		unsigned __int64 GetUnsignedInt64();
		unsigned short GetUnsignedShort();
		unsigned int GetUnsignedVarInt();
		unsigned __int64 GetUnsignedVarInt64();
		int GetVarInt();
		__int64 GetVarInt64();
	};

}
