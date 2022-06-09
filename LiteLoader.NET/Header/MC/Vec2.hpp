#pragma once
#include "Types.hpp"
#include "Vec2.hpp"
namespace MC
{
	[StructLayout(LayoutKind::Sequential)]
	public value class Vec2
	{
	internal:
		operator ::Vec2() { return ::Vec2{ x,y }; }
		operator ::Vec2 const& () {
			pin_ptr<Vec2>p = this;
			return *(::Vec2*)p;
		}
		static operator Vec2(::Vec2 const& obj) { return Vec2(obj.x, obj.y); }
	public:
		float x, y;

		property float X {
			float get() { return x; }
			void set(float x) { this->x = x; }
		}
		property float Y {
			float get() { return y; }
			void set(float y) { this->y = y; }
		}
	public:
		Vec2(float a, float b)
			:x(a), y(b) {}

		String^ ToString() override {
			return x.ToString() + "," + y.ToString();
		}

		inline static Vec2 operator*(Vec2 const% obj, float num) {
			return Vec2{ obj.x * num,obj.y * num };
		}

		inline static Vec2 operator+(Vec2 const% a, Vec2 const% b)
		{
			return Vec2{ a.x + b.x, a.y + b.y };
		}

		inline static Vec2 operator-(Vec2 const% a, Vec2 const% b)
		{
			return Vec2{ a.x - b.x, a.y - b.y };
		}

	public:
		static property Vec2 const LOWEST {Vec2 const get() { return ::Vec2::LOWEST; }}
		static property Vec2 const MAX {Vec2 const get() { return ::Vec2::MAX; }}
		static property Vec2 const MIN {Vec2 const get() { return ::Vec2::MIN; }}
		static property Vec2 const NEG_UNIT_X {Vec2 const get() { return ::Vec2::NEG_UNIT_X; }}
		static property Vec2 const LOWESNEG_UNIT_YT {Vec2 const get() { return ::Vec2::NEG_UNIT_Y; }}
		static property Vec2 const ONE {Vec2 const get() { return ::Vec2::ONE; }}
		static property Vec2 const UNIT_X {Vec2 const get() { return ::Vec2::UNIT_X; }}
		static property Vec2 const UNIT_Y {Vec2 const get() { return ::Vec2::UNIT_Y; }}
		static property Vec2 const ZERO {Vec2 const get() { return ::Vec2::ZERO; }}
	};
} // namespace MC
