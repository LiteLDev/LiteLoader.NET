#pragma once
#include <MC/Vec3.hpp>
#include "Types.hpp"
#include "Vec2.hpp"

namespace MC {
	ref class BlockPos;
}

namespace MC {
	[StructLayout(LayoutKind::Sequential, Size = sizeof(::Vec3))]
	public value class Vec3 {
	internal:
		operator ::Vec3() { return { x,y,z }; }
		static operator Vec3(::Vec3 const& obj) { return Vec3(obj.x, obj.y, obj.z); }
		Vec3(::Vec3&& vec) :x(vec.x), y(vec.y), z(vec.z) {}
		Vec3(::Vec3 const& vec) :x(vec.x), y(vec.y), z(vec.z) {}
	public:
		float x, y, z;

		property float X {
			float get() { return x; }
			void set(float x) { this->x = x; }
		}

		property float Y {
			float get() { return y; }
			void set(float y) { this->y = y; }
		}

		property float Z {
			float get() { return z; }
			void set(float z) { this->z = z; }
		}
	public:
		inline Vec3(float x, float y, float z)
			:x(x), y(y), z(z) {}

		inline Vec3(double x, double y, double z)
			: x((float)x), y((float)y), z((float)z) {}

		inline Vec3(int x, int y, int z)
			: x((float)x), y((float)y), z((float)z) {}

		inline Vec3(BlockPos^ pos);

		Vec3 Abs() {
			pin_ptr<Vec3> p = this;
			return ((::Vec3*)p)->abs();
		}

		Vec3 Ceil() {
			pin_ptr<Vec3> p = this;
			return ((::Vec3*)p)->ceil();
		}

		float DistanceToLineSquared(Vec3% a, Vec3% b) {
			pin_ptr<Vec3> p = this;
			pin_ptr<Vec3> pa = &a;
			pin_ptr<Vec3> pb = &b;

			return ((::Vec3*)p)->distanceToLineSquared(*(::Vec3*)pa, *(::Vec3*)pb);
		}

		float DistanceToSqr(Vec3% obj) {
			pin_ptr<Vec3> p = this;
			pin_ptr<Vec3> pobj = &obj;

			return ((::Vec3*)p)->distanceToSqr(*(::Vec3*)pobj);
		}

		Vec3 Floor(float num) {
			pin_ptr<Vec3> p = this;

			return ((::Vec3*)p)->floor(num);
		}

		property bool IsNan {
			bool get() {
				pin_ptr<Vec3> p = this;

				return ((::Vec3*)p)->isNan();
			}
		}

		//bool IsNear(Vec3% obj, float num) {
		//	pin_ptr<Vec3> p = this;
		//	pin_ptr<Vec3> pobj = &obj;

		//	return ((::Vec3*)p)->isNear(*(::Vec3*)pobj, num);
		//}

		float MaxComponent() {
			pin_ptr<Vec3> p = this;

			return ((::Vec3*)p)->maxComponent();
		}

		Vec3 Normalized() {
			pin_ptr<Vec3> p = this;

			return ((::Vec3*)p)->normalized();
		}

		Vec3 XZ() {
			pin_ptr<Vec3> p = this;

			return ((::Vec3*)p)->xz();
		}

		static property Vec3 const HALF { inline Vec3 const get() { return ::Vec3::HALF; }}
		static property Vec3 const MAX {inline Vec3 const get() { return ::Vec3::MAX; }}
		static property Vec3 const MIN {inline Vec3 const get() { return ::Vec3::MIN; }}
		static property Vec3 const NEG_UNIT_X {inline Vec3 const get() { return ::Vec3::NEG_UNIT_X; }}
		static property Vec3 const LOWESNEG_UNIT_YT {inline Vec3 const get() { return ::Vec3::NEG_UNIT_Y; }}
		static property Vec3 const ONE {inline Vec3 const get() { return ::Vec3::ONE; }}
		static property Vec3 const UNIT_X {inline Vec3 const get() { return ::Vec3::UNIT_X; }}
		static property Vec3 const UNIT_Y {inline Vec3 const get() { return ::Vec3::UNIT_Y; }}
		static property Vec3 const ZERO {inline Vec3 const get() { return ::Vec3::ZERO; }}

		Vec3 Clamp(Vec3% a, Vec3% b, Vec3% c) {
			pin_ptr<Vec3> p = this;
			pin_ptr<Vec3> pa = &a;
			pin_ptr<Vec3> pb = &b;
			pin_ptr<Vec3> pc = &c;

			return ((::Vec3*)p)->clamp(*(::Vec3*)pa, *(::Vec3*)pb, *(::Vec3*)pc);
		}

		Vec3 DirectionFromRotation(Vec2% obj) {
			pin_ptr<Vec3> p = this;
			pin_ptr<Vec2> pobj = &obj;

			return ((::Vec3*)p)->directionFromRotation(*(::Vec2*)pobj);
		}

		Vec2 RotationFromDirection(Vec3% obj) {
			pin_ptr<Vec3> p = this;
			pin_ptr<Vec3> pobj = &obj;

			return ((::Vec3*)p)->rotationFromDirection(*(::Vec3*)pobj);
		}

		BlockPos^ ToBlockPos();

		property float Length {
			inline float get() {
				pin_ptr<Vec3> p = this;

				return ((::Vec3*)p)->length();
			}
		}

		float DistanceTo(Vec3% obj) {
			pin_ptr<Vec3> p = this;
			pin_ptr<Vec3> pobj = &obj;

			return ((::Vec3*)p)->distanceTo(*(::Vec3*)pobj);
		}

		inline Vec3 Add(float dx, float dy, float dz) {
			return Vec3{ x + dx, y + dy, z + dz };
		}

		inline Vec3 Normalize() {
			float l = Length;
			return Vec3{ x / l, y / l, z / l };
		}

		static bool operator==(Vec3% a, Vec3% b) {
			return a.x == b.x && a.y == b.y && a.z == b.z;
		}

		static bool operator!=(Vec3% a, Vec3% b) {
			return a.x != b.x || a.y != b.y || a.z != b.z;
		}

		static Vec3 operator*(Vec3% obj, float b) {
			return Vec3{ obj.x * b, obj.y * b, obj.z * b };
		}

		static Vec3 operator/(Vec3% obj, float b) {
			return Vec3{ obj.x / b, obj.y / b, obj.z / b };
		}

		static Vec3 operator+(Vec3% obj, float b) {
			return Vec3{ obj.x + b, obj.y + b, obj.z + b };
		}

		static Vec3 operator-(Vec3% obj, float b) {
			return Vec3{ obj.x - b, obj.y - b, obj.z - b };
		}

		static float Dot(Vec3% a, Vec3% b) {
			return { a.x * b.x + a.y * b.y + a.z * b.z };
		}

		inline Vec3 Cross(Vec3% a, Vec3% b) {
			return Vec3{ a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
		}
	};
}