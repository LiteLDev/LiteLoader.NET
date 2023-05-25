#pragma once
#include <mc/vec2.hpp>
#include "Types.hpp"

namespace MC
{
    [StructLayout(LayoutKind::Sequential, Size = sizeof(::Vec2))]
    public value class Vec2
    {
    internal:
        operator ::Vec2() { return ::Vec2{ X,Y }; }
        static operator Vec2(::Vec2 const& obj) { return Vec2(obj.x, obj.y); }
        Vec2(::Vec2&& vec) :X(vec.x), Y(vec.y) {}
        Vec2(::Vec2 const& vec) :X(vec.x), Y(vec.y) {}

    public:
        float X, Y;
    public:
        Vec2(float a, float b)
            :X(a), Y(b) {}

        inline Vec2(System::Numerics::Vector2);

        inline String^ ToString() override {
            return X.ToString() + "," + Y.ToString();
        }

        inline static Vec2 operator*(Vec2 const obj, float num) {
            return Vec2{ obj.X * num,obj.Y * num };
        }

        inline static Vec2 operator+(Vec2 const a, Vec2 const b)
        {
            return Vec2{ a.X + b.X, a.Y + b.Y };
        }

        inline static Vec2 operator-(Vec2 const a, Vec2 const b)
        {
            return Vec2{ a.X - b.X, a.Y - b.Y };
        }

        static operator System::Numerics::Vector2(Vec2);

    public:
        static initonly Vec2 LOWEST = ::Vec2::LOWEST;
        static initonly Vec2 MAX = ::Vec2::MAX;
        static initonly Vec2 MIN = ::Vec2::MIN;
        static initonly Vec2 NEG_UNIT_X = ::Vec2::NEG_UNIT_X;
        static initonly Vec2 LOWESNEG_UNIT_YT = ::Vec2::NEG_UNIT_Y;
        static initonly Vec2 ONE = ::Vec2::ONE;
        static initonly Vec2 UNIT_X = ::Vec2::UNIT_X;
        static initonly Vec2 UNIT_Y = ::Vec2::UNIT_Y;
        static initonly Vec2 ZERO = ::Vec2::ZERO;
    };
} // namespace MC
