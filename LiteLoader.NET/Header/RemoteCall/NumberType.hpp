#pragma once
#include "include.hpp"
#include "Interfaces.hpp"

namespace LLNET::RemoteCall {
	public
	value class NumberType : IValue
	{
		__int64 i;
		double f;

		//ctor
	public:
		NumberType(double v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(float v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(__int64 v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(int v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(short v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(char v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(unsigned __int64 v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(unsigned int v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(unsigned short v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
		NumberType(unsigned char v)
			: i(static_cast<__int64>(v))
			, f(static_cast<double>(v)) {};
	internal:
		NumberType(__int64 i, double f)
			: i(i), f(f) {};
		//opeator
	public:
		static operator NumberType(double v) {
			return NumberType(v);
		}
		static operator NumberType(float v) {
			return NumberType(v);
		}
		static operator NumberType(__int64 v) {
			return NumberType(v);
		}
		static operator NumberType(int v) {
			return NumberType(v);
		}
		static operator NumberType(short v) {
			return NumberType(v);
		}
		static operator NumberType(char v) {
			return NumberType(v);
		}
		static operator NumberType(unsigned __int64 v) {
			return NumberType(v);
		}
		static operator NumberType(unsigned int v) {
			return NumberType(v);
		}
		static operator NumberType(unsigned short v) {
			return NumberType(v);
		}
		static operator NumberType(unsigned char v) {
			return NumberType(v);
		}
		static operator double(NumberType v) {
			return static_cast<double>(v.f);
		}
		static operator float(NumberType v) {
			return static_cast<float>(v.f);
		}
		static operator __int64(NumberType v) {
			return static_cast<__int64>(v.i);
		}
		static operator int(NumberType v) {
			return static_cast<int>(v.i);
		}
		static operator short(NumberType v) {
			return static_cast<short>(v.i);
		}
		static operator char(NumberType v) {
			return static_cast<char>(v.i);
		}
		static operator unsigned __int64(NumberType v) {
			return static_cast<unsigned __int64>(v.i);
		}
		static operator unsigned int(NumberType v) {
			return static_cast<unsigned int>(v.i);
		}
		static operator unsigned short(NumberType v) {
			return static_cast<unsigned short>(v.i);
		}
		static operator unsigned char(NumberType v) {
			return static_cast<unsigned char>(v.i);
		}
		//method
	public:

		double AsDouble(NumberType v) {
			return static_cast<double>(v.f);
		}
		float AsFloat(NumberType v) {
			return static_cast<float>(v.f);
		}
		__int64 AsInt64(NumberType v) {
			return static_cast<__int64>(v.i);
		}
		int AsInt(NumberType v) {
			return static_cast<int>(v.i);
		}
		short AsShort(NumberType v) {
			return static_cast<short>(v.i);
		}
		char AsSByte(NumberType v) {
			return static_cast<char>(v.i);
		}
		unsigned __int64 AsUInt64(NumberType v) {
			return static_cast<unsigned __int64>(v.i);
		}
		unsigned int AsUInt(NumberType v) {
			return static_cast<unsigned int>(v.i);
		}
		unsigned short AsUShort(NumberType v) {
			return static_cast<unsigned short>(v.i);
		}
		unsigned char AsByte(NumberType v) {
			return static_cast<unsigned char>(v.i);
		}

		generic<typename T>
		T Get()
		{
			if (T::typeid == double ::typeid || T::typeid == float ::typeid)
				return T(f);
			return T(i);
		}

	internal:
		::RemoteCall::NumberType _toNative()
		{
			return ::RemoteCall::NumberType{ i, f };
		}
	};
}