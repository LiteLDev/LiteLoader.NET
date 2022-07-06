#pragma once

#include "ReadOnlyBinaryStream.hpp"
#include <MC/BinaryStream.hpp>

#pragma make_public(::BinaryStream)

namespace MC::NetWork
{
	ref class BinaryStream : MC::ReadOnlyBinaryStream
	{
	public:
		__ctor_base(BinaryStream, ::BinaryStream, MC::ReadOnlyBinaryStream)
	public:
		property String^ WriteBuf {String^ get() { return marshalString(NativePtr->writeBuf); } void set(String^ value) { NativePtr->writeBuf = marshalString(value); }};
		property __string^ WBuf { __string^ get() { return gcnew __string(NativePtr->pwBuf); } void set(__string^ value) { *NativePtr->pwBuf = *value->NativePtr; }};
	public:
		BinaryStream(String^ str, bool b);
		BinaryStream();
		String^ GetAndReleaseData();
		__string^ GetAndReleaseData_Native();
		void Reset();
		void WriteBool(bool val);
		void WriteByte(unsigned char val);
		void WriteDouble(double val);
		void WriteFloat(float val);
		void WriteSignedBigEndianInt(int val);
		void WriteSignedInt(int val);
		void WriteSignedInt64(__int64 val);
		void WriteSignedShort(short val);
		void WriteString(String^ val);
		void WriteUnsignedChar(unsigned char val);
		void WriteUnsignedInt(unsigned int val);
		void WriteUnsignedInt64(unsigned __int64 val);
		void WriteUnsignedShort(unsigned short val);
		void WriteUnsignedVarInt(unsigned int val);
		void WriteUnsignedVarInt64(unsigned __int64 val);
		void WriteVarInt(int val);
		void WriteVarInt64(__int64 val);
	public:
		void Write(void const* p, unsigned __int64 size);
		void Write(array<System::Byte>^ arr);
	};
}