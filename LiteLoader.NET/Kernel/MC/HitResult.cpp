#include <LiteLoader.NET/Header/MC/HitResult.hpp>
#include <LiteLoader.NET/Header/MC/Vec3.hpp>
#include <LiteLoader.NET/Header/MC/BlockPos.hpp>
#include <LiteLoader.NET/Header/MC/Actor.hpp>

namespace MC {
    FaceID HitResult::Facing::get() {
        return FaceID(NativePtr->getFacing());
    }

    FaceID HitResult::LiquidFacing::get() {
        return FaceID(NativePtr->getLiquidFacing());
    }

    Vec3 HitResult::Pos::get() {
        return NativePtr->getPos();
    }

    bool HitResult::IsHitLiquid::get() {
        return NativePtr->isHitLiquid();
    }

    bool HitResult::IsEntity::get() {
        return NativePtr->isHitLiquid();
    }

    bool HitResult::IsTile::get() {
        return NativePtr->isHitLiquid();
    }

    bool HitResult::IsHit::get() {
        return NativePtr->isHitLiquid();
    }

    MC::BlockPos HitResult::BlockPos::get() {
        return MC::BlockPos(NativePtr->getBlockPos());
    }

    MC::BlockPos HitResult::LiquidPos::get() {
        return MC::BlockPos(NativePtr->getLiquidPos());
    }

    //MC::HitResultType HitResult::HitResultType::get() {
    //    return MC::HitResultType(NativePtr->getHitResultType());
    //}


    HitResult::HitResult(HitResult% obj)
        :ClassTemplate(*obj.NativePtr)
    {
    }

    HitResult::HitResult(Vec3 v1, Vec3 v2, Vec3 v3)
        :ClassTemplate(::HitResult(v1, v2, v3))
    {
    }

    HitResult::HitResult(Vec3 v1, Vec3 v2, Actor^ ac, Vec3 v3)
        :ClassTemplate(::HitResult(v1, v2, *ac->NativePtr, v3))
    {
    }

    HitResult::HitResult(Vec3 v1, Vec3 v2, Actor^ ac)
        :ClassTemplate(::HitResult(v1, v2, *ac->NativePtr))
    {
    }

    HitResult::HitResult(Vec3 v1, Vec3 v2, MC::BlockPos pos, unsigned char b, Vec3 v3)
        :ClassTemplate(::HitResult(v1, v2, pos, b, v3))
    {
    }

    HitResult::HitResult()
        :ClassTemplate(::HitResult())
    {
    }

    //void HitResult::__AutoClassInit2(unsigned __int64 a1)
    //{
    //    return NativePtr->__autoclassinit2(a1);
    //}

    float HitResult::DistanceTo(Actor^ ac)
    {
        return NativePtr->distanceTo(*ac->NativePtr);
    }

    Actor^ HitResult::GetEntity()
    {
        return gcnew Actor(NativePtr->getEntity());
    }

    HitResult^ HitResult::operator=(HitResult^ obj)
    {
        *NativePtr = *obj->NativePtr;
        return this;
    }

}