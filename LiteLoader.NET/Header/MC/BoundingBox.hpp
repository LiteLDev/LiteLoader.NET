#pragma once
#include <MC/BoundingBox.hpp>
#include "Types.hpp"
#include "BlockPos.hpp"


namespace MC {
	[StructLayout(LayoutKind::Sequential, Size = sizeof(::BoundingBox))]
	public value class BoundingBox {
	internal:
		operator ::BoundingBox() { return { min.operator ::BlockPos(),max.operator ::BlockPos() }; }
		static operator BoundingBox(::BoundingBox const& obj) { return BoundingBox(obj.min, obj.max); }
		BoundingBox(::BoundingBox&& obj) :min(obj.min), max(obj.max) {}
		BoundingBox(::BoundingBox const& obj) :min(obj.min), max(obj.max) {}
	public:
		BlockPos min;
		BlockPos max;

		property BlockPos Min {
			BlockPos get() {
				return min;
			}
		}

		property BlockPos Max {
			BlockPos get() {
				return max;
			}
		}

	public:
		BoundingBox(BlockPos min, BlockPos max) :min(min), max(max) {}

	public:
		property BlockPos Center {
			BlockPos get() {
				return BlockPos{ (min.x + max.x) / 2, (min.y + max.y) / 2, (min.z + max.z) / 2 };
			}
		}

		inline AABB ToAABB();

	public:
		property BlockPos% default[int]{
			BlockPos % get(int index) {
				pin_ptr<BoundingBox> p = this;
				return *(BlockPos*)(&((*(::BoundingBox*)p)[index]));
			}
		};

		delegate void ForEachBlockInBoxHandler(BlockPos% pos);

		void ForEachBlockInBox(ForEachBlockInBoxHandler^ todo);

		/// <summary>
		/// More Faster
		/// </summary>
		/// <param name="pfunc">£­Function Pointer</param>
		void ForEachBlockInBox_pFunc(void(*pfunc)(const BlockPos%)) {
			pin_ptr<BoundingBox> p = this;
			((::BoundingBox*)p)->forEachBlockInBox((void(*)(const ::BlockPos&))(pfunc));
		}

		property bool IsValid {
			bool get() {
				pin_ptr<BoundingBox> p = this;
				return ((::BoundingBox*)p)->isValid();
			}
		}

		property size_t HashVal {
			size_t get() {
				pin_ptr<BoundingBox>p = this;
				std::hash<::BoundingBox> hash;
				return hash(*(::BoundingBox*)p);
			}
		}

		int GetHashCode() override {
			return (int)HashVal;
		}
	public:
		static BoundingBox MergeBoundingBox(BoundingBox% a, BoundingBox% b) {
			pin_ptr<BoundingBox> pa = &a;
			pin_ptr<BoundingBox> pb = &b;
			return ::BoundingBox::mergeBoundingBox(*(::BoundingBox*)pa, *(::BoundingBox*)pb);
		}
		static BoundingBox OrientBox(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10) {
			return ::BoundingBox::orientBox(i1, i2, i3, i4, i5, i6, i7, i8, i9, i10);
		}
	};
}
