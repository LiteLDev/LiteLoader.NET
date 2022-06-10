#pragma once
#include <MC/HitResult.hpp>
#include "Types.hpp"

namespace MC {
	public enum class HitResultType :int {
		TILE = 0,
		ENTITY,
		ENTITY_OUT_OF_RANGE,
		NO_HIT,
	};
	value class Vec3;
	ref class BlockPos;
	ref class Actor;
}

namespace MC {
	public ref class HitResult
		:ClassTemplate<HitResult, ::HitResult>
	{
	public:
		__ctor_all(HitResult, ::HitResult);
	public:
		property FaceID Facing { FaceID get(); }
		property Vec3 Pos { Vec3 get(); }
		property bool IsHitLiquid { bool get(); }
		property bool IsEntity { bool get(); }
		property bool IsTile { bool get(); }
		property MC::BlockPos^ BlockPos { MC::BlockPos^ get(); }
		property MC::BlockPos^ LiquidPos { MC::BlockPos^ get(); }
		property FaceID LiquidFacing { FaceID get(); }
		//property MC::HitResultType HitResultType { MC::HitResultType get(); }
	public:
		HitResult(HitResult% obj);
		HitResult(Vec3 v1, Vec3 v2, Vec3 v3);
		HitResult(Vec3 v1, Vec3 v2, Actor^ ac, Vec3 v3);
		HitResult(Vec3 v1, Vec3 v2, Actor^ ac);
		HitResult(Vec3 v1, Vec3 v2, MC::BlockPos^ pos, unsigned char b, Vec3 v3);
		HitResult();
	public:
		//void __AutoClassInit2(unsigned __int64 a1);
		float DistanceTo(Actor^ ac);
		Actor^ GetEntity();
		property bool IsHit { bool get(); };
	public:
		HitResult^ operator=(HitResult^ obj);
	};
}