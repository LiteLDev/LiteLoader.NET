#pragma once
#include <mc/Vec3.hpp>
#include "Types.hpp"
#include "Vec2.hpp"

namespace MC {
    value class BlockPos;
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

        inline Vec3(BlockPos pos);

        inline Vec3(System::Numerics::Vector3);

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

            return (float)((float)((float)(*((float*)pobj + 1) - *((float*)p + 1)) *
                (float)(*((float*)pobj + 1) - *((float*)p + 1))) +
                (float)((float)(*(float*)pobj - *(float*)p) * (float)(*(float*)pobj - *(float*)p))) +
                (float)((float)(*((float*)pobj + 2) - *((float*)p + 2)) *
                    (float)(*((float*)pobj + 2) - *((float*)p + 2)));
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
        //    pin_ptr<Vec3> p = this;
        //    pin_ptr<Vec3> pobj = &obj;

        //    return ((::Vec3*)p)->isNear(*(::Vec3*)pobj, num);
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

        initonly static Vec3 HALF = ::Vec3::HALF;
        initonly static Vec3 MAX = ::Vec3::MAX;
        initonly static Vec3 MIN = ::Vec3::MIN;
        initonly static Vec3 NEG_UNIT_X = ::Vec3::NEG_UNIT_X;
        initonly static Vec3 LOWESNEG_UNIT_YT = ::Vec3::NEG_UNIT_Y;
        initonly static Vec3 ONE = ::Vec3::ONE;
        initonly static Vec3 UNIT_X = ::Vec3::UNIT_X;
        initonly static Vec3 UNIT_Y = ::Vec3::UNIT_Y;
        initonly static Vec3 ZERO = ::Vec3::ZERO;

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

        BlockPos ToBlockPos();

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

        String^ ToString() override {
            return x.ToString() + "," + y.ToString() + "," + z.ToString();
        }

        inline Vec3 Add(float dx, float dy, float dz) {
            return Vec3{ x + dx, y + dy, z + dz };
        }

        inline Vec3 Normalize() {
            float l = Length;
            return Vec3{ x / l, y / l, z / l };
        }

        property float% default[int]
        {
            float% get(int index)
            {
                pin_ptr<Vec3>p = this;
                return (*(::Vec3*)p)[index];
            }
        };

        static bool operator==(Vec3 a, Vec3 b) {
            return a.x == b.x && a.y == b.y && a.z == b.z;
        }

        static bool operator!=(Vec3 a, Vec3 b) {
            return a.x != b.x || a.y != b.y || a.z != b.z;
        }

        static Vec3 operator*(Vec3 obj, float b) {
            return Vec3{ obj.x * b, obj.y * b, obj.z * b };
        }

        static Vec3 operator/(Vec3 obj, float b) {
            return Vec3{ obj.x / b, obj.y / b, obj.z / b };
        }

        static Vec3 operator+(Vec3 obj, float b) {
            return Vec3{ obj.x + b, obj.y + b, obj.z + b };
        }

        static Vec3 operator-(Vec3 obj, float b) {
            return Vec3{ obj.x - b, obj.y - b, obj.z - b };
        }

        static Vec3 operator*(Vec3 obj, Vec3 b) {
            return Vec3{ obj.x * b.x, obj.y * b.y, obj.z * b.z };
        }

        static Vec3 operator/(Vec3 obj, Vec3 b) {
            return Vec3{ obj.x / b.x, obj.y / b.y, obj.z / b.z };
        }

        static Vec3 operator+(Vec3 obj, Vec3 b) {
            return Vec3{ obj.x + b.x, obj.y + b.y, obj.z + b.z };
        }

        static Vec3 operator-(Vec3 obj, Vec3 b) {
            return Vec3{ obj.x - b.x, obj.y - b.y, obj.z - b.z };
        }

        static explicit operator System::Numerics::Vector3(Vec3 obj) {
            return System::Numerics::Vector3{ obj.X, obj.Y, obj.Z };
        }

        static float Dot(Vec3 a, Vec3 b) {
            return { a.x * b.x + a.y * b.y + a.z * b.z };
        }

        inline Vec3 Cross(Vec3 a, Vec3 b) {
            return Vec3{ a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
        }
        /*
        inline static Vec3 Max(Vec3 a, Vec3 b) {
            pin_ptr<Vec3> pa = &a;
            pin_ptr<Vec3> pb = &b;
            return ::Vec3::MAX(*(::Vec3*)pa, *(::Vec3*)pb);
        }

        inline static Vec3 Min(Vec3 a, Vec3 b) {
            pin_ptr<Vec3> pa = &a;
            pin_ptr<Vec3> pb = &b;
            return ::Vec3::MIN(*(::Vec3*)pa, *(::Vec3*)pb);
        }
        */
        property size_t HashVal {
            size_t get() {
                pin_ptr<Vec3> p = this;
                std::hash<::Vec3> hash;
                return hash(*(::Vec3*)p);
            }
        }

        int GetHashCode() override {
            return (int)HashVal;
        }
    };
}