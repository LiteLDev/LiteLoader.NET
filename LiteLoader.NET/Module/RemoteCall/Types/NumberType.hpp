#pragma once
#include <LiteLoader.NET\Main\DotNETGlobal.hpp>

namespace RemoteCall
{
	struct NumberType;
}

namespace LiteLoader::RemoteCall 
{
	public value class NumberType/* : IValue*/
	{
		__int64 i;
		double f;

		//ctor
	public:
		NumberType(double v);
		NumberType(float v);
		NumberType(__int64 v);
		NumberType(int v);
		NumberType(short v);
		NumberType(char v);
		NumberType(unsigned __int64 v);
		NumberType(unsigned int v);
		NumberType(unsigned short v);
		NumberType(unsigned char v);
		NumberType(__int64 i, double f);

	internal:
		NumberType(::RemoteCall::NumberType const& v);

		//opeator
	public:
		static operator NumberType(double v);
		static operator NumberType(float v);
		static operator NumberType(__int64 v);
		static operator NumberType(int v);
		static operator NumberType(short v);
		static operator NumberType(char v);
		static operator NumberType(unsigned __int64 v);
		static operator NumberType(unsigned int v);
		static operator NumberType(unsigned short v);
		static operator NumberType(unsigned char v);
		static operator double(NumberType v);
		static operator float(NumberType v);
		static operator __int64(NumberType v);
		static operator int(NumberType v);
		static operator short(NumberType v);
		static operator char(NumberType v);
		static operator unsigned __int64(NumberType v);
		static operator unsigned int(NumberType v);
		static operator unsigned short(NumberType v);
		static operator unsigned char(NumberType v);
		//method
	public:

		double AsDouble();
		float AsFloat();
		__int64 AsInt64();
		int AsInt();
		short AsShort();
		char AsSByte();
		unsigned __int64 AsUInt64();
		unsigned int AsUInt();
		unsigned short AsUShort();
		unsigned char AsByte();

		generic<typename T>
		T Get();

	internal:
		::RemoteCall::NumberType _toNative();
	public:
		virtual String^ ToString() override;
	};
}