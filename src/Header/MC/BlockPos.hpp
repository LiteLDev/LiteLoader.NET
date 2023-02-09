#pragma once
#include "Types.hpp"

#include <mc/BlockPos.hpp>
#include <mc/ChunkBlockPos.hpp>
#include "Vec3.hpp"

namespace MC
{
    value class BoundingBox;
}

namespace MC
{
    [StructLayout(LayoutKind::Sequential, Size = sizeof(::BlockPos))]
    public value class BlockPos {
    internal:
        operator ::BlockPos() { return { X,Y,Z }; }
        static operator BlockPos(::BlockPos const& obj) { return BlockPos(obj.x, obj.y, obj.z); }
        BlockPos(::BlockPos&& pos) :X(pos.x), Y(pos.y), Z(pos.z) {}
        BlockPos(::BlockPos const& pos) :X(pos.x), Y(pos.y), Z(pos.z) {}

    public:
        int X, Y, Z;
    public:
        BlockPos(int mx, int my, int mz) :X(mx), Y(my), Z(mz) {}

        BlockPos(Vec3 vec) {
            pin_ptr<BlockPos> p = this;
            (*(::BlockPos*)p) = ::BlockPos(vec);
        }
        BlockPos(double mx, double my, double mz) :X((int)mx), Y((int)my), Z((int)mz) {}

        BlockPos(float mx, float my, float mz) :X((int)mx), Y((int)my), Z((int)mz) {}


    public:
        BlockPos Neighbor(unsigned char val) {
            pin_ptr<BlockPos> p = this;
            return ((::BlockPos*)p)->neighbor(val);
        }

        int RandomSeed() {
            pin_ptr<BlockPos> p = this;
            return ((::BlockPos*)p)->randomSeed();
        }

        BlockPos Relative(unsigned char a1, int a2) {
            pin_ptr<BlockPos> p = this;
            return ((::BlockPos*)p)->relative(a1, a2);
        }

    public:
        static initonly BlockPos MAX = ::BlockPos::MAX;
        static initonly BlockPos MIN = ::BlockPos::MIN;
        static initonly BlockPos ONE = ::BlockPos::ONE;
        static initonly BlockPos ZERO = ::BlockPos::ZERO;
    public:
        void BindType() {
            pin_ptr<BlockPos> p = this;
            ((::BlockPos*)p)->bindType();
        }

        property array<BlockPos>^ Neighbors {
            array<BlockPos>^ get() {
                auto ret = gcnew array<BlockPos>(6);
                ret[0] = BlockPos{ X, Y - 1, Z };
                ret[1] = BlockPos{ X, Y + 1, Z };
                ret[2] = BlockPos{ X, Y, Z - 1 };
                ret[3] = BlockPos{ X, Y, Z + 1 };
                ret[4] = BlockPos{ X - 1, Y, Z };
                ret[5] = BlockPos{ X + 1, Y, Z };
                return ret;
            }
        };

        String^ ToString() override {
            return X.ToString() + "," + Y.ToString() + "," + Z.ToString();
        }

        BlockPos Add(int dx) {
            return BlockPos{ X + dx ,Y ,Z };
        }

        BlockPos Add(int dx, int dy) {
            return BlockPos{ X + dx, Y + dy, Z };
        }

        BlockPos Add(int dx, int dy, int dz) {
            return BlockPos{ X + dx, Y + dy, Z + dz };
        }

    public:
        property int% default[int]{
            int% get(int index) {
                pin_ptr<BlockPos> p = this;
                return (*(::BlockPos*)p)[index];
            }
        };

        static bool operator==(BlockPos obj, BlockPos b) {
            return obj.X == b.X && obj.Y == b.Y && obj.Z == b.Z;
        }

        static bool operator!=(BlockPos obj, BlockPos b) {
            return obj.X != b.X || obj.Y != b.Y || obj.Z != b.Z;
        }

        static BlockPos operator+(BlockPos obj, BlockPos b)
        {
            return BlockPos{ obj.X + b.X, obj.Y + b.Y, obj.Z + b.Z };
        }

        static BlockPos operator*(BlockPos obj, BlockPos b)
        {
            return BlockPos{ obj.X * b.X, obj.Y * b.Y, obj.Z * b.Z };
        }

        static BlockPos operator/(BlockPos obj, BlockPos b)
        {
            return BlockPos{ obj.X / b.X, obj.Y / b.Y, obj.Z / b.Z };
        }

        static BlockPos operator-(BlockPos obj, BlockPos b)
        {
            return BlockPos{ obj.X - b.X, obj.Y - b.Y, obj.Z - b.Z };
        }

        static BlockPos operator*(BlockPos obj, int b)
        {
            return BlockPos{ obj.X * b, obj.Y * b, obj.Z * b };
        }

        static BlockPos operator/(BlockPos obj, int b)
        {
            return BlockPos{ obj.X / b, obj.Y / b, obj.Z / b };
        }

        static BlockPos operator+(BlockPos obj, int b)
        {
            return BlockPos{ obj.X + b, obj.Y + b, obj.Z + b };
        }

        static BlockPos operator-(BlockPos obj, int b)
        {
            return BlockPos{ obj.X - b, obj.Y - b, obj.Z - b };
        }

    public:
        bool ContainedWithin(BlockPos const% a, BlockPos const% b) {
            return X >= a.X && Y >= a.Y && Z >= a.Z && X <= b.X && Y <= b.Y && Z <= b.Z;
        }

        property double Length {
            double get() {
                return System::Math::Sqrt(X * X + Y * Y + Z * Z);
            }
        }

        double DistanceTo(BlockPos a) {
            return (*this - a).Length;
        }
    /*
    public:
        inline static BlockPos Max(BlockPos% a, BlockPos% b)
        {
            pin_ptr<BlockPos> pa = &a;
            pin_ptr<BlockPos> pb = &b;
            return ::BlockPos::MAX(*(::BlockPos*)pa, *(::BlockPos*)pb);
        }

        inline static BlockPos Min(BlockPos% a, BlockPos% b)
        {
            pin_ptr<BlockPos> pa = &a;
            pin_ptr<BlockPos> pb = &b;
            return ::BlockPos::MIN(*(::BlockPos*)pa, *(::BlockPos*)pb);
        }
    */
    public:
        inline Vec3 ToVec3();
        inline Vec3 BottomCenter();
        inline Vec3 Center();
        inline bool ContainedWithin(BoundingBox% obj);

    public:
        property size_t HashVal {
            size_t get() {
                pin_ptr<BlockPos> p = this;
                std::hash<::BlockPos> hash;
                return hash(*(::BlockPos*)p);
            }
        }

        int GetHashCode() override {
            return (int)HashVal;
        }
    };
}