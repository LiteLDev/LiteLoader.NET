#pragma once
#include "Types.hpp"
#include <MC/AABB.hpp>
#include <MC/HitResult.hpp>

namespace MC {
	value class Vec3;
	ref class HitResult;
}

namespace MC {
	public ref class AABB
		:ClassTemplate<AABB, ::AABB>
	{
	public:
		__ctor_all(AABB, ::AABB);
	public:
		property Vec3 PointA {Vec3 get(); }
		property Vec3 PointB {Vec3 get(); }
	public:
		AABB(Vec3 v1, Vec3 v2);
		AABB(Vec3 vec, float f);
		AABB(float f1, float f2, float f3, float f4, float f5, float f6);
		Vec3 AxisInside(AABB^ aabb, Vec3 vec);
		HitResult^ Clip(Vec3 v1, Vec3 v2);
		Vec3 ClipCollide(AABB^ aabb, Vec3 vec, bool b, float% f);
		AABB^ CloneAndExpandAlongDirection(Vec3 vec);
		AABB^ CloneAndFloor(float f1, float f2);
		AABB^ CloneAndFloorMinAndCeilingMax();
		AABB^ CloneAndGrow(Vec3 vec);
		AABB^ CloneAndShrink(Vec3 vec);
		//	//AABB^ CloneAndTransformByMatrix(class Matrix&);
		bool Contains(AABB^ aabb);
		bool Contains(Vec3 vec);
		float DistanceTo(AABB^ aabb);
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
		bool Intersects(AABB^ aabb);
		bool Intersects(Vec3 v1, Vec3 v2);
		bool IntersectsInner(AABB^ aabb);
		AABB^ Set(float f1, float f2, float f3, float f4, float f5, float f6);
		AABB^ Set(AABB^ aabb);
		AABB^ Set(Vec3 v1, Vec3 v2);
		AABB^ Shrink(Vec3 vec);
		AABB^ TranslateCenterTo(Vec3 vec);
	public:
		static bool operator!=(AABB^ a, AABB^ b);
		static bool operator==(AABB^ a, AABB^ b);
	public:
		static property AABB^ BLOCK_SHAPE {AABB^ get(); };
		static property AABB^ BOX_AT_ORIGIN_WITH_NO_VOLUME {AABB^ get(); };
	};
}