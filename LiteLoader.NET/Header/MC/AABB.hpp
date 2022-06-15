#pragma once
#include "Types.hpp"
#include <MC/AABB.hpp>
#include <MC/HitResult.hpp>

#include "Vec3.hpp"

namespace MC {
	value class Vec3;
	ref class HitResult;
}

namespace MC {
	[StructLayout(LayoutKind::Sequential, Size = sizeof(::AABB))]
	public value class AABB {
	internal:
		operator ::AABB() { return { pointA.operator ::Vec3(),pointB.operator ::Vec3() }; }
		static operator AABB(::AABB const& obj) { return AABB(obj.pointA, obj.pointB); }
		AABB(::AABB&& obj) :pointA(obj.pointA), pointB(obj.pointB) {}
		AABB(::AABB const& obj) :pointA(obj.pointA), pointB(obj.pointB) {}
	public:
		Vec3 pointA;
		Vec3 pointB;

		property Vec3 PointA {
			Vec3 get() {
				return pointA;
			}
		}
		property Vec3 PointB {
			Vec3 get() {
				return pointB;
			}
		}
	public:
		AABB(Vec3 a, Vec3 b) :pointA(a), pointB(b) {}
		AABB(Vec3 vec, float val) {
			pin_ptr<AABB> p = this;
			(*(::AABB*)p) = ::AABB(vec, val);
		}
		AABB(float f1, float f2, float f3, float f4, float f5, float f6) {
			pin_ptr<AABB> p = this;
			(*(::AABB*)p) = ::AABB(f1, f2, f3, f4, f5, f6);
		}
	public:
		Vec3 AxisInside(AABB aabb, Vec3 vec);
		HitResult^ Clip(Vec3 v1, Vec3 v2);
		Vec3 ClipCollide(AABB aabb, Vec3 vec, bool b, float% f);
		AABB CloneAndExpandAlongDirection(Vec3 vec);
		AABB CloneAndFloor(float f1, float f2);
		AABB CloneAndFloorMinAndCeilingMax();
		AABB CloneAndGrow(Vec3 vec);
		AABB CloneAndShrink(Vec3 vec);
		//	//AABB CloneAndTransformByMatrix(class Matrix&);
		bool Contains(AABB aabb);
		bool Contains(Vec3 vec);
		float DistanceTo(AABB aabb);
		float DistanceTo(Vec3 vec);
	public:
		property Vec3 Bounds {Vec3 get(); };
		property Vec3 Center {Vec3 get(); };
		property float Size {float get(); };
		property float Volume {float get(); };
		//property bool HasZeroVolume {bool get(); };
		property bool IsValid {bool get(); };
	public:
		bool IntersectSegment(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4);
		bool Intersects(AABB aabb);
		bool Intersects(Vec3 v1, Vec3 v2);
		bool IntersectsInner(AABB aabb);
		AABB Set(float f1, float f2, float f3, float f4, float f5, float f6);
		AABB Set(AABB aabb);
		AABB Set(Vec3 v1, Vec3 v2);
		AABB Shrink(Vec3 vec);
		AABB TranslateCenterTo(Vec3 vec);
	public:
		static bool operator!=(AABB a, AABB b);
		static bool operator==(AABB a, AABB b);
	public:
		static initonly AABB BLOCK_SHAPE = ::AABB::BLOCK_SHAPE;
		static initonly AABB BOX_AT_ORIGIN_WITH_NO_VOLUME = ::AABB::BOX_AT_ORIGIN_WITH_NO_VOLUME;
	};
}