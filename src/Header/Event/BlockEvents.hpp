#pragma once
#include "Event.hpp"

namespace LiteLoader::Event
{

    ///////////////////////////// Block Events /////////////////////////////

    Class BlockInteractedEvent
        : public EventTemplate<BlockInteractedEvent, ::Event::BlockInteractedEvent>
    {
        EventAPIs(BlockInteractedEvent, 36);

    public:
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
        Property_Ptr(MC, Player, mPlayer, Player);
    };

    Class BlockChangedEvent
        : public EventTemplate<BlockChangedEvent, ::Event::BlockChangedEvent>
    {
        EventAPIs(BlockChangedEvent, 37);

    public:
        Property_Instance(MC, BlockInstance, mPreviousBlockInstance, PreviousBlockInstance);
        Property_Instance(MC, BlockInstance, mNewBlockInstance, NewBlockInstance);
    };

    Class BlockExplodedEvent
        : public EventTemplate<BlockExplodedEvent, ::Event::BlockExplodedEvent>
    {
        EventAPIs(BlockExplodedEvent, 38);

    public:
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
        Property_Ptr(MC, Actor, mExplodeSource, ExplodeSource);
    };

    Class FireSpreadEvent
        : public EventTemplate<FireSpreadEvent, ::Event::FireSpreadEvent>
    {
        EventAPIs(FireSpreadEvent, 39);

    public:
        Property_ValueType(MC, BlockPos, mTarget, Target);
        Property(int, mDimensionId, DimensionId);
    };

    Class ContainerChangeEvent
        : public EventTemplate<ContainerChangeEvent, ::Event::ContainerChangeEvent>
    {
        EventAPIs(ContainerChangeEvent, 40);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Ptr(MC, Actor, mActor, Actor);
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
        Property_Ptr(MC, Container, mContainer, Cotainer);
        Property(int, mSlot, Slot);
        Property_Ptr(MC, ItemStack, mPreviousItemStack, PreviousItemStack);
        Property_Ptr(MC, ItemStack, mNewItemStack, NewItemStack);
    };

    Class ProjectileHitBlockEvent
        : public EventTemplate<ProjectileHitBlockEvent, ::Event::ProjectileHitBlockEvent>
    {
        EventAPIs(ProjectileHitBlockEvent, 41);

    public:
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
        Property_Ptr(MC, Actor, mSource, Source);
    };

    Class RedStoneUpdateEvent
        : public EventTemplate<RedStoneUpdateEvent, ::Event::RedStoneUpdateEvent>
    {
        EventAPIs(RedStoneUpdateEvent, 42);

    public:
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
        Property(int, mRedStonePower, RedStonePower);
        Property(bool, mIsActivated, IsActivated);
    };

    Class HopperSearchItemEvent
        : public EventTemplate<HopperSearchItemEvent, ::Event::HopperSearchItemEvent>
    {
        EventAPIs(HopperSearchItemEvent, 43);

    public:
        Property(int, isMinecart, isMinecart);
        Property_Instance(MC, BlockInstance, mHopperBlock, HopperBlock);
        Property_ValueType(MC, Vec3, mMinecartPos, MinecartPos);
        Property(int, mDimensionId, DimensionId);
    };

    Class HopperPushOutEvent
        : public EventTemplate<HopperPushOutEvent, ::Event::HopperPushOutEvent>
    {
        EventAPIs(HopperPushOutEvent, 44);

    public:
        Property_Instance(MC, Vec3, mPos, Pos);
        Property(int, mDimensionId, DimensionId);
    };

    Class PistonTryPushEvent
        : public EventTemplate<PistonTryPushEvent, ::Event::PistonTryPushEvent>
    {
        EventAPIs(PistonTryPushEvent, 45);

    public:
        Property_Instance(MC, BlockInstance, mPistonBlockInstance, PistonBlockInstance);
        Property_Instance(MC, BlockInstance, mTargetBlockInstance, TargetBlockInstance);
    };

    Class PistonPushEvent
        : public EventTemplate<PistonPushEvent, ::Event::PistonPushEvent>
    {
        EventAPIs(PistonPushEvent, 46);

    public:
        Property_Instance(MC, BlockInstance, mPistonBlockInstance, PistonBlockInstance);
        Property_Instance(MC, BlockInstance, mTargetBlockInstance, TargetBlockInstance);
    };

    Class FarmLandDecayEvent
        : public EventTemplate<FarmLandDecayEvent, ::Event::FarmLandDecayEvent>
    {
        EventAPIs(FarmLandDecayEvent, 47);

    public:
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
        Property_Ptr(MC, Actor, mActor, Actor);
    };

    Class LiquidSpreadEvent
        : public EventTemplate<LiquidSpreadEvent, ::Event::LiquidSpreadEvent>
    {
        EventAPIs(LiquidSpreadEvent, 48);

    public:
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
        Property_ValueType(MC, BlockPos, mTarget, Target);
        Property(int, mDimensionId, DimensionId);
    };

    Class CmdBlockExecuteEvent
        : public EventTemplate<CmdBlockExecuteEvent, ::Event::CmdBlockExecuteEvent>
    {
        EventAPIs(CmdBlockExecuteEvent, 49);

    public:
        Property_String(mCommand, Command);
        Property(bool, mIsMinecart, IsMinecart);
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
        Property_Ptr(MC, Actor, mMinecart, Minecart);
    };

    Class BlockExplodeEvent
        : public EventTemplate<BlockExplodeEvent, ::Event::BlockExplodeEvent>
    {
        EventAPIs(BlockExplodeEvent, 50);

    public:
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
        Property(float, mRadius, Radius);
        Property(float, mMaxResistance, MaxResistance);
        Property(bool, mBreaking, Breaking);
        Property(bool, mFire, Fire);
    };
}