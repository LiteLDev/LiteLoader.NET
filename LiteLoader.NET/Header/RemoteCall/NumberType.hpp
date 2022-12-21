#pragma once
#include "include.hpp"
#include "Interfaces.hpp"

namespace LiteLoader::RemoteCall {
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
		NumberType(__int64 i, double f)
			: i(i), f(f) {};
	internal:
		NumberType(::RemoteCall::NumberType const& v)
			:i(v.i), f(v.f) {};
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

		double AsDouble() {
			return static_cast<double>(f);
		}
		float AsFloat() {
			return static_cast<float>(f);
		}
		__int64 AsInt64() {
			return static_cast<__int64>(i);
		}
		int AsInt() {
			return static_cast<int>(i);
		}
		short AsShort() {
			return static_cast<short>(i);
		}
		char AsSByte() {
			return static_cast<char>(i);
		}
		unsigned __int64 AsUInt64() {
			return static_cast<unsigned __int64>(i);
		}
		unsigned int AsUInt() {
			return static_cast<unsigned int>(i);
		}
		unsigned short AsUShort() {
			return static_cast<unsigned short>(i);
		}
		unsigned char AsByte() {
			return static_cast<unsigned char>(i);
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
	public:
		virtual String^ ToString() override {
			return L'<' + f.ToString() + L',' + i.ToString() + L'>';
		}
	};
}