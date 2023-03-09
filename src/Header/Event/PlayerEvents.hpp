#pragma once
#include "Event.hpp"

namespace LiteLoader::Event
{

    ///////////////////////////// Player Events /////////////////////////////

    Class PlayerPreJoinEvent
        : public EventTemplate<PlayerPreJoinEvent, ::Event::PlayerPreJoinEvent>
    {
        EventAPIs(PlayerPreJoinEvent, 1);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_String(mIP, IP);
        Property_String(mXUID, XUID);
    };

    Class PlayerJoinEvent
        : public EventTemplate<PlayerJoinEvent, ::Event::PlayerJoinEvent>
    {
        EventAPIs(PlayerJoinEvent, 2);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
    };

    Class PlayerLeftEvent
        : public EventTemplate<PlayerLeftEvent, ::Event::PlayerLeftEvent>
    {
        EventAPIs(PlayerLeftEvent, 3);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_String(mXUID, XUID);
    };

    Class PlayerRespawnEvent
        : public EventTemplate<PlayerRespawnEvent, ::Event::PlayerRespawnEvent>
    {
        EventAPIs(PlayerRespawnEvent, 4);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
    };

    Class PlayerUseItemEvent
        : public EventTemplate<PlayerUseItemEvent, ::Event::PlayerUseItemEvent>
    {
        EventAPIs(PlayerUseItemEvent, 5);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Ptr(MC, ItemStack, mItemStack, ItemStack);
    };

    Class PlayerUseItemOnEvent
        : public EventTemplate<PlayerUseItemOnEvent, ::Event::PlayerUseItemOnEvent>
    {
        EventAPIs(PlayerUseItemOnEvent, 6);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Ptr(MC, ItemStack, mItemStack, ItemStack);
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
        Property(char, mFace, Face);
        Property_ValueType(MC, Vec3, mClickPos, ClickPos);
    };

    Class PlayerChatEvent
        : public EventTemplate<PlayerChatEvent, ::Event::PlayerChatEvent>
    {
        EventAPIs(PlayerChatEvent, 7);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_String(mMessage, Message);
    };

    Class PlayerChangeDimEvent
        : public EventTemplate<PlayerChangeDimEvent, ::Event::PlayerChangeDimEvent>
    {
        EventAPIs(PlayerChangeDimEvent, 8);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property(int, mToDimensionId, ToDimensionId);
    };

    Class PlayerJumpEvent
        : public EventTemplate<PlayerJumpEvent, ::Event::PlayerJumpEvent>
    {
        EventAPIs(PlayerJumpEvent, 9);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
    };

    Class PlayerSneakEvent
        : public EventTemplate<PlayerSneakEvent, ::Event::PlayerSneakEvent>
    {
        EventAPIs(PlayerSneakEvent, 10);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property(bool, mIsSneaking, IsSneaking);
    };

    Class PlayerAttackEvent
        : public EventTemplate<PlayerAttackEvent, ::Event::PlayerAttackEvent>
    {
        EventAPIs(PlayerAttackEvent, 11);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Ptr(MC, Actor, mTarget, Target);
        Property(float, mAttackDamage, AttackDamage);
    };

    Class PlayerAttackBlockEvent
        : public EventTemplate<PlayerAttackBlockEvent, ::Event::PlayerAttackBlockEvent>
    {
        EventAPIs(PlayerAttackBlockEvent, 12);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Ptr(MC, ItemStack, mItemStack, ItemStack);
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
    };

    Class PlayerDieEvent
        : public EventTemplate<PlayerDieEvent, ::Event::PlayerDieEvent>
    {
        EventAPIs(PlayerDieEvent, 13);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Ptr(MC, ActorDamageSource, mDamageSource, DamageSource);
    };

    Class PlayerPickupItemEvent
        : public EventTemplate<PlayerPickupItemEvent, ::Event::PlayerPickupItemEvent>
    {
        EventAPIs(PlayerPickupItemEvent, 14);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Ptr(MC, Actor, mItemEntity, ItemEntity);
        Property_Ptr(MC, ItemStack, mItemStack, ItemStack);
    };

    Class PlayerDropItemEvent
        : public EventTemplate<PlayerDropItemEvent, ::Event::PlayerDropItemEvent>
    {
        EventAPIs(PlayerDropItemEvent, 15);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Ptr(MC, ItemStack, mItemStack, ItemStack);
    };

    Class PlayerEatEvent
        : public EventTemplate<PlayerEatEvent, ::Event::PlayerEatEvent>
    {
        EventAPIs(PlayerEatEvent, 16);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Ptr(MC, ItemStack, mFoodItem, FoodItem);
    };

    Class PlayerConsumeTotemEvent
        : public EventTemplate<PlayerConsumeTotemEvent, ::Event::PlayerConsumeTotemEvent>
    {
        EventAPIs(PlayerConsumeTotemEvent, 17);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
    };

    Class PlayerCmdEvent
        : public EventTemplate<PlayerCmdEvent, ::Event::PlayerCmdEvent>
    {
        EventAPIs(PlayerCmdEvent, 18);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_String(mCommand, Command);
        Property_Ptr(MC, MCRESULT, mResult, Result);
    };

    Class PlayerEffectChangedEvent
        : public EventTemplate<PlayerEffectChangedEvent, ::Event::PlayerEffectChangedEvent>
    {
        EventAPIs(PlayerEffectChangedEvent, 19);

    public:
        enum class EventType
        {
            Add,
            Remove,
            Update
        };

        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Enum(EventType, ::Event::PlayerEffectChangedEvent::EventType, mEventType, Event_Type);
        Property_Ptr(MC, MobEffectInstance, mEffect, Effect);
    };

    Class PlayerStartDestroyBlockEvent
        : public EventTemplate<PlayerStartDestroyBlockEvent, ::Event::PlayerStartDestroyBlockEvent>
    {
        EventAPIs(PlayerStartDestroyBlockEvent, 20);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
    };

    Class PlayerDestroyBlockEvent
        : public EventTemplate<PlayerDestroyBlockEvent, ::Event::PlayerDestroyBlockEvent>
    {
        EventAPIs(PlayerDestroyBlockEvent, 21);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
    };

    Class PlayerPlaceBlockEvent
        : public EventTemplate<PlayerPlaceBlockEvent, ::Event::PlayerPlaceBlockEvent>
    {
        EventAPIs(PlayerPlaceBlockEvent, 22);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
    };

    Class BlockPlacedByPlayerEvent
        : public EventTemplate<BlockPlacedByPlayerEvent, ::Event::BlockPlacedByPlayerEvent>
    {
        EventAPIs(BlockPlacedByPlayerEvent, 23);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
    };

    Class PlayerOpenContainerEvent
        : public EventTemplate<PlayerOpenContainerEvent, ::Event::PlayerOpenContainerEvent>
    {
        EventAPIs(PlayerOpenContainerEvent, 24);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
        Property_Ptr(MC, Container, mContainer, Container);
    };

    Class PlayerCloseContainerEvent
        : public EventTemplate<PlayerCloseContainerEvent, ::Event::PlayerCloseContainerEvent>
    {
        EventAPIs(PlayerCloseContainerEvent, 25);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
        Property_Ptr(MC, Container, mContainer, Container);
    };

    Class PlayerInventoryChangeEvent
        : public EventTemplate<PlayerInventoryChangeEvent, ::Event::PlayerInventoryChangeEvent>
    {
        EventAPIs(PlayerInventoryChangeEvent, 26);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property(int, mSlot, Slot);
        Property_Ptr(MC, ItemStack, mPreviousItemStack, PreviousItemStack);
        Property_Ptr(MC, ItemStack, mNewItemStack, NewItemStack);
    };

    Class PlayerSprintEvent
        : public EventTemplate<PlayerSprintEvent, ::Event::PlayerSprintEvent>
    {
        EventAPIs(PlayerSprintEvent, 28);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property(bool, mIsSprinting, IsSprinting);
    };

    Class PlayerSetArmorEvent
        : public EventTemplate<PlayerSetArmorEvent, ::Event::PlayerSetArmorEvent>
    {
        EventAPIs(PlayerSetArmorEvent, 29);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property(int, mSlot, Slot);
        Property_Ptr(MC, ItemStack, mArmorItem, ArmorItem);
    };

    Class PlayerUseRespawnAnchorEvent
        : public EventTemplate<PlayerUseRespawnAnchorEvent, ::Event::PlayerUseRespawnAnchorEvent>
    {
        EventAPIs(PlayerUseRespawnAnchorEvent, 30);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
    };

    Class PlayerOpenContainerScreenEvent
        : public EventTemplate<PlayerOpenContainerScreenEvent, ::Event::PlayerOpenContainerScreenEvent>
    {
        EventAPIs(PlayerOpenContainerScreenEvent, 31);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
    };

    Class PlayerUseFrameBlockEvent
        : public EventTemplate<PlayerUseFrameBlockEvent, ::Event::PlayerUseFrameBlockEvent>
    {
        EventAPIs(PlayerUseFrameBlockEvent, 32);

    public:
        enum class TypeEnum
        {
            Use,
            Attack
        };

        Property_Enum(TypeEnum, ::Event::PlayerUseFrameBlockEvent::Type, mType, Type);
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
    };

    Class PlayerScoreChangedEvent
        : public EventTemplate<PlayerScoreChangedEvent, ::Event::PlayerScoreChangedEvent>
    {
        EventAPIs(PlayerScoreChangedEvent, 33);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property(int, mScore, Score);
        Property_Ptr(MC, Objective, mObjective, Objective);
        Property_Ptr(MC, ScoreboardId, mScoreboardId, ScoreboardId);
    };

    Class PlayerExperienceAddEvent
        : public EventTemplate<PlayerExperienceAddEvent, ::Event::PlayerExperienceAddEvent>
    {
        EventAPIs(PlayerExperienceAddEvent, 34);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property(int, mExp, Exp);
    };

    Class PlayerInteractEntityEvent
        : public EventTemplate<PlayerInteractEntityEvent, ::Event::PlayerInteractEntityEvent>
    {
        EventAPIs(PlayerInteractEntityEvent, 35);

    public:
        enum class InteractiveModeType
        {
            RightClick,
            LeftClick
        };

        Property_Ptr(MC, ServerPlayer, mPlayer, Player);
        Property_Instance(MC, ActorRuntimeID, mTargetId, TargetId);
        Property_Enum(InteractiveModeType, ::Event::PlayerInteractEntityEvent::InteractiveMode, mInteractiveMode,
                      InteractiveMode);
    };
}