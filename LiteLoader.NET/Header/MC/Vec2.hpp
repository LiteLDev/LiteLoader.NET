#pragma once
#include <mc/Vec2.hpp>
#include "Types.hpp"
namespace MC
{
	[StructLayout(LayoutKind::Sequential, Size = sizeof(::Vec2))]
	public value class Vec2
	{
	internal:
		operator ::Vec2() { return ::Vec2{ x,y }; }
		static operator Vec2(::Vec2 const& obj) { return Vec2(obj.x, obj.y); }
		Vec2(::Vec2&& vec) :x(vec.x), y(vec.y) {}
		Vec2(::Vec2 const& vec) :x(vec.x), y(vec.y) {}
	public:
		float x, y;

		property float X {
			inline float get() { return x; }
			inline void set(float x) { this->x = x; }
		}
		property float Y {
			inline float get() { return y; }
			inline  void set(float y) { this->y = y; }
		}
	public:
		Vec2(float a, float b)
			:x(a), y(b) {}

		inline String^ ToString() override {
			return x.ToString() + "," + y.ToString();
		}

		inline static Vec2 operator*(Vec2 const obj, float num) {
			return Vec2{ obj.x * num,obj.y * num };
		}

		inline static Vec2 operator+(Vec2 const a, Vec2 const b)
		{
			return Vec2{ a.x + b.x, a.y + b.y };
		}

		inline static Vec2 operator-(Vec2 const a, Vec2 const b)
		{
			return Vec2{ a.x - b.x, a.y - b.y };
		}

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
