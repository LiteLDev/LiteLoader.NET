#pragma once
#include "Types.hpp"

#include <MC/BlockPos.hpp>
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
		operator ::BlockPos() { return { x,y,z }; }
		static operator BlockPos(::BlockPos const& obj) { return BlockPos(obj.x, obj.y, obj.z); }
		BlockPos(::BlockPos&& pos) :x(pos.x), y(pos.y), z(pos.z) {}
		BlockPos(::BlockPos const& pos) :x(pos.x), y(pos.y), z(pos.z) {}
	public:
		int x, y, z;

		property int X {int get() { return x; }}
		property int Y {int get() { return y; }}
		property int Z {int get() { return z; }}
	public:
		BlockPos(int mx, int my, int mz) :x(mx), y(my), z(mz) {}

		BlockPos(Vec3 vec) {
			pin_ptr<BlockPos> p = this;
			(*(::BlockPos*)p) = ::BlockPos(vec);
		}
		BlockPos(double mx, double my, double mz) :x((int)mx), y((int)my), z((int)mz) {}

		BlockPos(float mx, float my, float mz) :x((int)mx), y((int)my), z((int)mz) {}


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
				ret[0] = BlockPos{ x, y - 1, z };
				ret[1] = BlockPos{ x, y + 1, z };
				ret[2] = BlockPos{ x, y, z - 1 };
				ret[3] = BlockPos{ x, y, z + 1 };
				ret[4] = BlockPos{ x - 1, y, z };
				ret[5] = BlockPos{ x + 1, y, z };
				return ret;
			}
		};

		String^ ToString() override {
			return x.ToString() + "," + y.ToString() + "," + z.ToString();
		}

		BlockPos Add(int dx) {
			return BlockPos{ x + dx ,y ,z };
		}

		BlockPos Add(int dx, int dy) {
			return BlockPos{ x + dx, y + dy, z };
		}

		BlockPos Add(int dx, int dy, int dz) {
			return BlockPos{ x + dx, y + dy, z + dz };
		}

	public:
		property int% default[int]{
			int% get(int index) {
				pin_ptr<BlockPos> p = this;
				return (*(::BlockPos*)p)[index];
			}
		};

		static bool operator==(BlockPos obj, BlockPos b) {
			return obj.x == b.x && obj.y == b.y && obj.z == b.z;
		}

		static bool operator!=(BlockPos obj, BlockPos b) {
			return obj.x != b.x || obj.y != b.y || obj.z != b.z;
		}

		static BlockPos operator+(BlockPos obj, BlockPos b)
		{
			return BlockPos{ obj.x + b.x, obj.y + b.y, obj.z + b.z };
		}

		static BlockPos operator*(BlockPos obj, BlockPos b)
		{
			return BlockPos{ obj.x * b.x, obj.y * b.y, obj.z * b.z };
		}

		static BlockPos operator/(BlockPos obj, BlockPos b)
		{
			return BlockPos{ obj.x / b.x, obj.y / b.y, obj.z / b.z };
		}

		static BlockPos operator-(BlockPos obj, BlockPos b)
		{
			return BlockPos{ obj.x - b.x, obj.y - b.y, obj.z - b.z };
		}

		static BlockPos operator*(BlockPos obj, int b)
		{
			return BlockPos{ obj.x * b, obj.y * b, obj.z * b };
		}

		static BlockPos operator/(BlockPos obj, int b)
		{
			return BlockPos{ obj.x / b, obj.y / b, obj.z / b };
		}

		static BlockPos operator+(BlockPos obj, int b)
		{
			return BlockPos{ obj.x + b, obj.y + b, obj.z + b };
		}

		static BlockPos operator-(BlockPos obj, int b)
		{
			return BlockPos{ obj.x - b, obj.y - b, obj.z - b };
		}

	public:
		bool ContainedWithin(BlockPos const% a, BlockPos const% b) {
			return x >= a.x && y >= a.y && z >= a.z && x <= b.x && y <= b.y && z <= b.z;
		}

		property double Length {
			double get() {
				return System::Math::Sqrt(x * x + y * y + z * z);
			}
		}

		double DistanceTo(BlockPos a) {
			return (*this - a).Length;
		}

	public:
		inline static BlockPos Max(BlockPos% a, BlockPos% b)
		{
			pin_ptr<BlockPos> pa = &a;
			pin_ptr<BlockPos> pb = &b;
			return ::BlockPos::max(*(::BlockPos*)pa, *(::BlockPos*)pb);
		}

		inline static BlockPos Min(BlockPos% a, BlockPos% b)
		{
			pin_ptr<BlockPos> pa = &a;
			pin_ptr<BlockPos> pb = &b;
			return ::BlockPos::min(*(::BlockPos*)pa, *(::BlockPos*)pb);
		}

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