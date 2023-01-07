#include "NumberType.hpp"
#include <RemoteCallAPI.h>

namespace LiteLoader::RemoteCall
{
    inline NumberType::NumberType(double v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)) {}

    inline NumberType::NumberType(float v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)) {}

    inline NumberType::NumberType(__int64 v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)) {}

    inline NumberType::NumberType(int v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)) {}

    inline NumberType::NumberType(short v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)) {}

    inline NumberType::NumberType(char v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)) {}

    inline NumberType::NumberType(unsigned __int64 v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)) {}

    inline NumberType::NumberType(unsigned int v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)) {}

    inline NumberType::NumberType(unsigned short v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)) {}

    inline NumberType::NumberType(unsigned char v)
        : i(static_cast<__int64>(v))
        , f(static_cast<double>(v)) {}

    inline NumberType::NumberType(__int64 i, double f)
        : i(i), f(f) {}

    inline NumberType::NumberType(::RemoteCall::NumberType const& v)
        : i(v.i), f(v.f) {}

    inline NumberType::operator NumberType(double v) {
        return NumberType(v);
    }

    inline NumberType::operator NumberType(float v) {
        return NumberType(v);
    }

    inline NumberType::operator NumberType(__int64 v) {
        return NumberType(v);
    }

    inline NumberType::operator NumberType(int v) {
        return NumberType(v);
    }

    inline NumberType::operator NumberType(short v) {
        return NumberType(v);
    }

    inline NumberType::operator NumberType(char v) {
        return NumberType(v);
    }

    inline NumberType::operator NumberType(unsigned __int64 v) {
        return NumberType(v);
    }

    inline NumberType::operator NumberType(unsigned int v) {
        return NumberType(v);
    }

    inline NumberType::operator NumberType(unsigned short v) {
        return NumberType(v);
    }

    inline NumberType::operator NumberType(unsigned char v) {
        return NumberType(v);
    }

    inline NumberType::operator double(NumberType v) {
        return static_cast<double>(v.f);
    }

    inline NumberType::operator float(NumberType v) {
        return static_cast<float>(v.f);
    }

    inline NumberType::operator __int64(NumberType v) {
        return static_cast<__int64>(v.i);
    }

    inline NumberType::operator int(NumberType v) {
        return static_cast<int>(v.i);
    }

    inline NumberType::operator short(NumberType v) {
        return static_cast<short>(v.i);
    }

    inline NumberType::operator char(NumberType v) {
        return static_cast<char>(v.i);
    }

    inline NumberType::operator unsigned __int64(NumberType v) {
        return static_cast<unsigned __int64>(v.i);
    }

    inline NumberType::operator unsigned int(NumberType v) {
        return static_cast<unsigned int>(v.i);
    }

    inline NumberType::operator unsigned short(NumberType v) {
        return static_cast<unsigned short>(v.i);
    }

    inline NumberType::operator unsigned char(NumberType v) {
        return static_cast<unsigned char>(v.i);
    }

    inline double NumberType::AsDouble() {
        return static_cast<double>(f);
    }

    inline float NumberType::AsFloat() {
        return static_cast<float>(f);
    }

    inline __int64 NumberType::AsInt64() {
        return static_cast<__int64>(i);
    }

    inline int NumberType::AsInt() {
        return static_cast<int>(i);
    }

    inline short NumberType::AsShort() {
        return static_cast<short>(i);
    }

    inline char NumberType::AsSByte() {
        return static_cast<char>(i);
    }

    inline unsigned __int64 NumberType::AsUInt64() {
        return static_cast<unsigned __int64>(i);
    }

    inline unsigned int NumberType::AsUInt() {
        return static_cast<unsigned int>(i);
    }

    inline unsigned short NumberType::AsUShort() {
        return static_cast<unsigned short>(i);
    }

    inline unsigned char NumberType::AsByte() {
        return static_cast<unsigned char>(i);
    }

    inline ::RemoteCall::NumberType NumberType::_toNative()
    {
        return ::RemoteCall::NumberType{ i, f };
    }

    inline String^ NumberType::ToString() {
        return L'<' + f.ToString() + L',' + i.ToString() + L'>';
    }

    generic<typename T>
    T NumberType::Get()
    {
        if (T::typeid == double::typeid || T::typeid == float::typeid)
        {
            return T(f);
        }
        return T(i);
    }
}