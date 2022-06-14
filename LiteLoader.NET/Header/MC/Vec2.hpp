#pragma once
#include <MC/Vec2.hpp>
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
		static property Vec2 const LOWEST { inline Vec2 const get() { return ::Vec2::LOWEST; }}
		static property Vec2 const MAX {inline Vec2 const get() { return ::Vec2::MAX; }}
		static property Vec2 const MIN {inline Vec2 const get() { return ::Vec2::MIN; }}
		static property Vec2 const NEG_UNIT_X {inline Vec2 const get() { return ::Vec2::NEG_UNIT_X; }}
		static property Vec2 const LOWESNEG_UNIT_YT {inline Vec2 const get() { return ::Vec2::NEG_UNIT_Y; }}
		static property Vec2 const ONE {inline Vec2 const get() { return ::Vec2::ONE; }}
		static property Vec2 const UNIT_X {inline Vec2 const get() { return ::Vec2::UNIT_X; }}
		static property Vec2 const UNIT_Y {inline Vec2 const get() { return ::Vec2::UNIT_Y; }}
		static property Vec2 const ZERO {inline Vec2 const get() { return ::Vec2::ZERO; }}
	};
} // namespace MC
