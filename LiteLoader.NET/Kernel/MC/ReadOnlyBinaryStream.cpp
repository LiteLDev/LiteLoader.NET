#include "../../Header/MC/ReadOnlyBinaryStream.hpp"

namespace MC::NetWork
{
	inline String^ ReadOnlyBinaryStream::GetData() { return marshalString(NativePtr->getData()); }

	inline __string^ ReadOnlyBinaryStream::GetData_Native() { return gcnew __string(const_cast<std::string*>(&NativePtr->getData())); }

	inline void ReadOnlyBinaryStream::Read(void* buffer, unsigned __int64 size) { NativePtr->read(buffer, size); }

	inline void ReadOnlyBinaryStream::Read(array<System::Byte>^ buffer)
	{
		pin_ptr<System::Byte> p = &buffer[0];
		NativePtr->read(p, buffer->Length);
	}

	inline ReadOnlyBinaryStream::ReadOnlyBinaryStream(String^ str)
	{
		nativePtr = new ::ReadOnlyBinaryStream(marshalString(str));
		ownsNativeInstance = true;
	}

	inline ReadOnlyBinaryStream::ReadOnlyBinaryStream(String^ str, bool b)
	{
		nativePtr = new ::ReadOnlyBinaryStream(marshalString(str), b);
		ownsNativeInstance = true;
	}

	inline bool ReadOnlyBinaryStream::CanReadBool() { return NativePtr->canReadBool(); }

	inline bool ReadOnlyBinaryStream::GetBool() { return NativePtr->getBool(); }

	inline unsigned char ReadOnlyBinaryStream::GetByte() { return NativePtr->getByte(); }

	inline double ReadOnlyBinaryStream::GetDouble() { return NativePtr->getDouble(); }

	inline float ReadOnlyBinaryStream::GetFloat() { return NativePtr->getFloat(); }

	inline StreamReadResult ReadOnlyBinaryStream::GetReadCompleteResult() { return StreamReadResult(NativePtr->getReadCompleteResult()); }

	inline int ReadOnlyBinaryStream::GetSignedBigEndianInt() { return NativePtr->getSignedBigEndianInt(); }

	inline int ReadOnlyBinaryStream::GetSignedInt() { return NativePtr->getSignedInt(); }

	inline __int64 ReadOnlyBinaryStream::GetSignedInt64() { return NativePtr->getSignedInt64(); }

	inline short ReadOnlyBinaryStream::getSignedShort() { return NativePtr->getSignedShort(); }

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

	inline unsigned char ReadOnlyBinaryStream::GetUnsignedChar() { return NativePtr->getUnsignedChar(); }

	inline unsigned int ReadOnlyBinaryStream::GetUnsignedInt() { return NativePtr->getUnsignedInt(); }

	inline unsigned __int64 ReadOnlyBinaryStream::GetUnsignedInt64() { return NativePtr->getUnsignedInt64(); }

	inline unsigned short ReadOnlyBinaryStream::GetUnsignedShort() { return NativePtr->getUnsignedShort(); }

	inline unsigned int ReadOnlyBinaryStream::GetUnsignedVarInt() { return NativePtr->getUnsignedVarInt(); }

	inline unsigned __int64 ReadOnlyBinaryStream::GetUnsignedVarInt64() { return NativePtr->getUnsignedVarInt64(); }

	inline int ReadOnlyBinaryStream::GetVarInt() { return NativePtr->getVarInt(); }

	inline __int64 ReadOnlyBinaryStream::GetVarInt64() { return NativePtr->getVarInt64(); }

}