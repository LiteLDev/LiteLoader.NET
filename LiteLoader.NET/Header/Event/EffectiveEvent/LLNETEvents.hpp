#pragma once
#include "include.hpp"
#include <EventAPI.h>

#include "../../MC/Vec3.hpp"
#include "../../MC/BlockInstance.hpp"
#include "../../MC/Player.hpp"
#include "../../MC/BlockPos.hpp"
#include "../../MC/AABB.hpp"
#include "../../MC/ItemStack.hpp"
#include "../../MC/Container.hpp"

#define _PIN_OBJECT(eventName) pin_ptr<eventName> _this = this
#define _THIS(eventName) ((::Event::eventName*)_this)

#define _Property(type, nativeName, name, eventName)						\
    property type name														\
    {																		\
        inline type get()													\
        {																	\
			_PIN_OBJECT(eventName);											\
            return _THIS(eventName)->nativeName;							\
        }																	\
        inline void set(type arg)											\
        {																	\
			_PIN_OBJECT(eventName);											\
            _THIS(eventName)->nativeName = arg;								\
        }																	\
    }

#define _Property_Instance(Namespace, type, nativeName, name, eventName)	\
    property Namespace::type ^ name											\
	{																		\
        inline Namespace::type ^ get()										\
		{																	\
			_PIN_OBJECT(eventName);											\
            return gcnew Namespace::type(_THIS(eventName)->nativeName);		\
        }																	\
		inline void	set(Namespace::type ^ arg)								\
        {																	\
			_PIN_OBJECT(eventName);											\
            _THIS(eventName)->nativeName = arg;								\
        }																	\
    }

#define _Property_ValueType(Namespace, type, nativeName, name, eventName)	\
    property Namespace::type name											\
	{																		\
        inline Namespace::type get()										\
		{																	\
			_PIN_OBJECT(eventName);											\
            return Namespace::type(_THIS(eventName)->nativeName);			\
        }																	\
		inline void	set(Namespace::type arg)								\
        {																	\
			_PIN_OBJECT(eventName);											\
            _THIS(eventName)->nativeName = arg;								\
        }																	\
    }

#define _Property_Ptr(Namespace, type, nativeName, name, eventName)			\
    property Namespace::type ^ name											\
	{																		\
        inline Namespace::type ^ get()										\
		{																	\
			_PIN_OBJECT(eventName);											\
            return gcnew Namespace::type(_THIS(eventName)->nativeName);		\
        }																	\
		inline void	set(Namespace::type ^ arg)								\
        {																	\
			_PIN_OBJECT(eventName);											\
            _THIS(eventName)->nativeName = arg->NativePtr;					\
        }																	\
    }

#define _Property_Enum(type, nativeEnum, nativeName, name, eventName)		\
    property type name														\
    {																		\
        inline type get()													\
        {																	\
			_PIN_OBJECT(eventName);											\
            return ((type)(_THIS(eventName)->nativeName));					\
        }																	\
        inline void set(type arg)											\
        {																	\
			_PIN_OBJECT(eventName);											\
            _THIS(eventName)->nativeName = ((nativeEnum)(arg));				\
        }																	\
    }

#define _Property_String(nativeName, name, eventName)						\
    property String^ name													\
	{																		\
        inline String^ get()												\
		{																	\
			_PIN_OBJECT(eventName);											\
            return marshalString(_THIS(eventName)->nativeName);				\
        }																	\
		inline void	set(String^ arg)										\
        {																	\
			_PIN_OBJECT(eventName);											\
            _THIS(eventName)->nativeName = marshalString(arg);				\
        }																	\
    }

#define IEventAPIs(eventId)													\
virtual property bool IsCancelled											\
{																			\
	bool get()																\
	{																		\
		return NativeEventIsCancelledManager::get(this->GetHashCode());		\
	}																		\
	void set(bool value)													\
	{																		\
		NativeEventIsCancelledManager::set(this->GetHashCode(), value);		\
	}																		\
}																			\
static constexpr size_t EventId = eventId;


#define EventClass(className) [StructLayout(LayoutKind::Sequential, Size = sizeof(::Event::className))] public value class className : IEvent, INativeEvent, ICancellable


namespace LLNET::Event::Effective::NativeEvents
{

	EventClass(PlayerPreJoinEvent)
	{
#define EVENTNAME PlayerPreJoinEvent 

	public:
		IEventAPIs(1);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_String(mIP, IP, EVENTNAME);
		_Property_String(mXUID, XUID, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerJoinEvent)
	{
#define EVENTNAME PlayerJoinEvent 

	public:
		IEventAPIs(2);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerLeftEvent)
	{
#define EVENTNAME PlayerLeftEvent 

	public:
		IEventAPIs(3);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_String(mXUID, XUID, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerRespawnEvent)
	{
#define EVENTNAME PlayerRespawnEvent 

	public:
		IEventAPIs(4);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerUseItemEvent)
	{
#define EVENTNAME PlayerUseItemEvent 

	public:
		IEventAPIs(5);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerUseItemOnEvent)
	{
#define EVENTNAME PlayerUseItemOnEvent 

	public:
		IEventAPIs(6);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property(char, mFace, Face, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerChatEvent)
	{
#define EVENTNAME PlayerChatEvent 

	public:
		IEventAPIs(7);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_String(mMessage, Message, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerChangeDimEvent)
	{
#define EVENTNAME PlayerChangeDimEvent 

	public:
		IEventAPIs(8);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(int, mToDimensionId, ToDimensionId, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerJumpEvent)
	{
#define EVENTNAME PlayerJumpEvent 

	public:
		IEventAPIs(9);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerSneakEvent)
	{
#define EVENTNAME PlayerSneakEvent 

	public:
		IEventAPIs(10);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(bool, mIsSneaking, IsSneaking, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerAttackEvent)
	{
#define EVENTNAME PlayerAttackEvent 

	public:
		IEventAPIs(11);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, Actor, mTarget, Target, EVENTNAME);
		_Property(int, mAttackDamage, AttackDamage, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerAttackBlockEvent)
	{
#define EVENTNAME PlayerAttackBlockEvent 

	public:
		IEventAPIs(12);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerDieEvent)
	{
#define EVENTNAME PlayerDieEvent 

	public:
		IEventAPIs(13);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, ActorDamageSource, mDamageSource, DamageSource, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerPickupItemEvent)
	{
#define EVENTNAME PlayerPickupItemEvent 

	public:
		IEventAPIs(14);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, Actor, mItemEntity, ItemEntity, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerDropItemEvent)
	{
#define EVENTNAME PlayerDropItemEvent 

	public:
		IEventAPIs(15);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerEatEvent)
	{
#define EVENTNAME PlayerEatEvent 

	public:
		IEventAPIs(16);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mFoodItem, FoodItem, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerConsumeTotemEvent)
	{
#define EVENTNAME PlayerConsumeTotemEvent 

	public:
		IEventAPIs(17);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerCmdEvent)
	{
#define EVENTNAME PlayerCmdEvent 

	public:
		IEventAPIs(18);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_String(mCommand, Command, EVENTNAME);
		_Property_Ptr(MC, MCRESULT, mResult, Result, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerEffectChangedEvent)
	{
#define EVENTNAME PlayerEffectChangedEvent 

	public:
		IEventAPIs(19);
	public:
		enum class EventType
		{
			Add,
			Remove,
			Update
		};
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Enum(EventType, ::Event::PlayerEffectChangedEvent::EventType, mEventType, Event_Type, EVENTNAME);
		_Property_Ptr(MC, MobEffectInstance, mEffect, Effect, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerStartDestroyBlockEvent)
	{
#define EVENTNAME PlayerStartDestroyBlockEvent 

	public:
		IEventAPIs(20);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerDestroyBlockEvent)
	{
#define EVENTNAME PlayerDestroyBlockEvent 

	public:
		IEventAPIs(21);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerPlaceBlockEvent)
	{
#define EVENTNAME PlayerPlaceBlockEvent 

	public:
		IEventAPIs(22);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerOpenContainerEvent)
	{
#define EVENTNAME PlayerOpenContainerEvent 

	public:
		IEventAPIs(23);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Container, mContainer, Container, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerCloseContainerEvent)
	{
#define EVENTNAME PlayerCloseContainerEvent 

	public:
		IEventAPIs(24);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Container, mContainer, Container, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerInventoryChangeEvent)
	{
#define EVENTNAME PlayerInventoryChangeEvent 

	public:
		IEventAPIs(25);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(int, mSlot, Slot, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mPreviousItemStack, PreviousItemStack, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mNewItemStack, NewItemStack, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerMoveEvent)
	{
#define EVENTNAME PlayerMoveEvent 

	public:
		IEventAPIs(26);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_ValueType(MC, Vec3, mPos, Pos, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerSprintEvent)
	{
#define EVENTNAME PlayerSprintEvent 

	public:
		IEventAPIs(27);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(bool, mIsSprinting, IsSprinting, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerSetArmorEvent)
	{
#define EVENTNAME PlayerSetArmorEvent 

	public:
		IEventAPIs(28);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(int, mSlot, Slot, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mArmorItem, ArmorItem, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerUseRespawnAnchorEvent)
	{
#define EVENTNAME PlayerUseRespawnAnchorEvent 

	public:
		IEventAPIs(29);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerOpenContainerScreenEvent)
	{
#define EVENTNAME PlayerOpenContainerScreenEvent 

	public:
		IEventAPIs(30);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerUseFrameBlockEvent)
	{
#define EVENTNAME PlayerUseFrameBlockEvent 

	public:
		IEventAPIs(31);
	public:
		enum class TypeEnum
		{
			Use,
			Attack
		};
		_Property_Enum(TypeEnum, ::Event::PlayerUseFrameBlockEvent::Type, mType, Type, EVENTNAME);
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerScoreChangedEvent)
	{
#define EVENTNAME PlayerScoreChangedEvent 

	public:
		IEventAPIs(32);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(int, mScore, Score, EVENTNAME);
		_Property_Ptr(MC, Objective, mObjective, Objective, EVENTNAME);
		_Property_Ptr(MC, ScoreboardId, mScoreboardId, ScoreboardId, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerExperienceAddEvent)
	{
#define EVENTNAME PlayerExperienceAddEvent 

	public:
		IEventAPIs(33);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(int, mExp, Exp, EVENTNAME);

#undef EVENTNAME 
	};
	///////////////////////////// Block Events /////////////////////////////

	EventClass(BlockInteractedEvent)
	{
#define EVENTNAME BlockInteractedEvent 

	public:
		IEventAPIs(34);
	public:
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(BlockChangedEvent)
	{
#define EVENTNAME BlockChangedEvent 

	public:
		IEventAPIs(35);
	public:
		_Property_Instance(MC, BlockInstance, mPreviousBlockInstance, PreviousBlockInstance, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mNewBlockInstance, NewBlockInstance, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(BlockExplodedEvent)
	{
#define EVENTNAME BlockExplodedEvent 

	public:
		IEventAPIs(36);
	public:
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Actor, mExplodeSource, ExplodeSource, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(FireSpreadEvent)
	{
#define EVENTNAME FireSpreadEvent 

	public:
		IEventAPIs(37);
	public:
		_Property_ValueType(MC, BlockPos, mTarget, Target, EVENTNAME);
		_Property(int, mDimensionId, DimensionId, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(ContainerChangeEvent)
	{
#define EVENTNAME ContainerChangeEvent 

	public:
		IEventAPIs(38);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, Actor, mActor, Actor, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Container, mContainer, Cotainer, EVENTNAME);
		_Property(int, mSlot, Slot, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mPreviousItemStack, PreviousItemStack, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mNewItemStack, NewItemStack, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(ProjectileHitBlockEvent)
	{
#define EVENTNAME ProjectileHitBlockEvent 

	public:
		IEventAPIs(39);
	public:
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Actor, mSource, Source, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(RedStoneUpdateEvent)
	{
#define EVENTNAME RedStoneUpdateEvent 

	public:
		IEventAPIs(40);
	public:
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property(int, mRedStonePower, RedStonePower, EVENTNAME);
		_Property(bool, mIsActivated, IsActivated, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(HopperSearchItemEvent)
	{
#define EVENTNAME HopperSearchItemEvent 

	public:
		IEventAPIs(41);
	public:
		_Property(int, isMinecart, isMinecart, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mHopperBlock, HopperBlock, EVENTNAME);
		_Property_ValueType(MC, Vec3, mMinecartPos, MinecartPos, EVENTNAME);
		_Property(int, mDimensionId, DimensionId, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(HopperPushOutEvent)
	{
#define EVENTNAME HopperPushOutEvent 

	public:
		IEventAPIs(42);
	public:
		_Property_Instance(MC, Vec3, mPos, Pos, EVENTNAME);
		_Property(int, mDimensionId, DimensionId, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PistonTryPushEvent)
	{
#define EVENTNAME PistonTryPushEvent 

	public:
		IEventAPIs(43);
	public:
		_Property_Instance(MC, BlockInstance, mPistonBlockInstance, PistonBlockInstance, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mTargetBlockInstance, TargetBlockInstance, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PistonPushEvent)
	{
#define EVENTNAME PistonPushEvent 

	public:
		IEventAPIs(44);
	public:
		_Property_Instance(MC, BlockInstance, mPistonBlockInstance, PistonBlockInstance, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mTargetBlockInstance, TargetBlockInstance, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(FarmLandDecayEvent)
	{
#define EVENTNAME FarmLandDecayEvent 

	public:
		IEventAPIs(45);
	public:
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Actor, mActor, Actor, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(LiquidSpreadEvent)
	{
#define EVENTNAME LiquidSpreadEvent 

	public:
		IEventAPIs(46);
	public:
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_ValueType(MC, BlockPos, mTarget, Target, EVENTNAME);
		_Property(int, mDimensionId, DimensionId, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(CmdBlockExecuteEvent)
	{
#define EVENTNAME CmdBlockExecuteEvent 

	public:
		IEventAPIs(47);
	public:
		_Property_String(mCommand, Command, EVENTNAME);
		_Property(bool, mIsMinecart, IsMinecart, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Actor, mMinecart, Minecart, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(BlockExplodeEvent)
	{
#define EVENTNAME BlockExplodeEvent 

	public:
		IEventAPIs(48);
	public:
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property(float, mRadius, Radius, EVENTNAME);
		_Property(float, mMaxResistance, MaxResistance, EVENTNAME);
		_Property(bool, mBreaking, Breaking, EVENTNAME);
		_Property(bool, mFire, Fire, EVENTNAME);

#undef EVENTNAME 
	};
	///////////////////////////// Entity Events /////////////////////////////

	EventClass(EntityTransformEvent)
	{
#define EVENTNAME EntityTransformEvent 

	public:
		IEventAPIs(49);
	public:
		property MC::ActorUniqueID BeforeEntityUniqueId
		{
			MC::ActorUniqueID get()
			{
				_PIN_OBJECT(EVENTNAME);
				return *_THIS(EVENTNAME)->mBeforeEntityUniqueId;
			}
			void set(MC::ActorUniqueID value)
			{
				_PIN_OBJECT(EVENTNAME);
				*_THIS(EVENTNAME)->mBeforeEntityUniqueId = value;
			}
		}
		_Property_Ptr(MC, Actor, mAfterEntity, AfterEntity, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(EntityExplodeEvent)
	{
#define EVENTNAME EntityExplodeEvent 

	public:
		IEventAPIs(50);
	public:
		_Property_Ptr(MC, Actor, mActor, Actor, EVENTNAME);
		_Property_ValueType(MC, Vec3, mPos, Pos, EVENTNAME);
		_Property_Ptr(MC, BlockSource, mDimension, Dimension, EVENTNAME);
		_Property(float, mRadius, Radius, EVENTNAME);
		_Property(float, mMaxResistance, MaxResistance, EVENTNAME);
		_Property(bool, mBreaking, Breaking, EVENTNAME);
		_Property(bool, mFire, Fire, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(MobHurtEvent)
	{
#define EVENTNAME MobHurtEvent 

	public:
		IEventAPIs(51);
	public:
		_Property_Ptr(MC, Mob, mMob, Mob, EVENTNAME);
		_Property_Ptr(MC, ActorDamageSource, mDamageSource, DamageSource, EVENTNAME);
		_Property(float, mDamage, Damage, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(MobDieEvent)
	{
#define EVENTNAME MobDieEvent 

	public:
		IEventAPIs(52);
	public:
		_Property_Ptr(MC, Mob, mMob, Mob, EVENTNAME);
		_Property_Ptr(MC, ActorDamageSource, mDamageSource, DamageSource, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(ProjectileHitEntityEvent)
	{
#define EVENTNAME ProjectileHitEntityEvent 

	public:
		IEventAPIs(53);
	public:
		_Property_Ptr(MC, Actor, mTarget, Target, EVENTNAME);
		_Property_Ptr(MC, Actor, mSource, Source, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(WitherBossDestroyEvent)
	{
#define EVENTNAME WitherBossDestroyEvent 

	public:
		IEventAPIs(54);
	public:
		_Property_Ptr(MC, WitherBoss, mWitherBoss, WitherBoss, EVENTNAME);
		_Property_Instance(MC, AABB, mDestroyRange, DestroyRange, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(EntityRideEvent)
	{
#define EVENTNAME EntityRideEvent 

	public:
		IEventAPIs(55);
	public:
		_Property_Ptr(MC, Actor, mRider, Rider, EVENTNAME);
		_Property_Ptr(MC, Actor, mVehicle, Vehicle, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(EntityStepOnPressurePlateEvent)
	{
#define EVENTNAME EntityStepOnPressurePlateEvent 

	public:
		IEventAPIs(56);
	public:
		_Property_Ptr(MC, Actor, mActor, Actor, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(NpcCmdEvent)
	{
#define EVENTNAME NpcCmdEvent 

	public:
		IEventAPIs(57);
	public:
		_Property_Ptr(MC, Actor, mNpc, Npc, EVENTNAME);
		_Property_String(mCommand, Command, EVENTNAME);
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(ProjectileSpawnEvent)
	{
#define EVENTNAME ProjectileSpawnEvent 

	public:
		IEventAPIs(58);
	public:
		_Property_Ptr(MC, Actor, mShooter, Shooter, EVENTNAME);
		_Property_Ptr(MC, ActorDefinitionIdentifier, mIdentifier, Identifier, EVENTNAME);
		_Property_String(mType, Type, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(ProjectileCreatedEvent)
	{
#define EVENTNAME ProjectileCreatedEvent 

	public:
		IEventAPIs(59);
	public:
		_Property_Ptr(MC, Actor, mShooter, Shooter, EVENTNAME);
		_Property_Ptr(MC, Actor, mProjectile, Projectile, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(ArmorStandChangeEvent)
	{
#define EVENTNAME ArmorStandChangeEvent 

	public:
		IEventAPIs(60);
	public:
		_Property_Ptr(MC, ArmorStand, mArmorStand, ArmorStand, EVENTNAME);
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(int, mSlot, Slot, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(ItemUseOnActorEvent)
	{
#define EVENTNAME ItemUseOnActorEvent 

	public:
		IEventAPIs(61);
	public:
		_Property_Instance(MC, ActorRuntimeID, mTarget, Target, EVENTNAME);
		_Property(int, mInteractiveMode, InteractiveMode, EVENTNAME);

#undef EVENTNAME 
	};
	///////////////////////////// Other Events /////////////////////////////

	EventClass(PostInitEvent)
	{
#define EVENTNAME PostInitEvent 

	public:
		IEventAPIs(62);
	public:

#undef EVENTNAME 
	};

	EventClass(ServerStartedEvent)
	{
#define EVENTNAME ServerStartedEvent 

	public:
		IEventAPIs(63);
	public:

#undef EVENTNAME 
	};

	EventClass(ServerStoppedEvent)
	{
#define EVENTNAME ServerStoppedEvent 

	public:
		IEventAPIs(64);
	public:

#undef EVENTNAME 
	};

	EventClass(ConsoleCmdEvent)
	{
#define EVENTNAME ConsoleCmdEvent 

	public:
		IEventAPIs(65);
	public:
		_Property_String(mCommand, Command, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(RegCmdEvent)
	{
#define EVENTNAME RegCmdEvent 

	public:
		IEventAPIs(66);
	public:
		_Property_Ptr(MC, CommandRegistry, mCommandRegistry, CommandRegistry, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(ConsoleOutputEvent)
	{
#define EVENTNAME ConsoleOutputEvent 

	public:
		IEventAPIs(67);
	public:
		_Property_String(mOutput, Output, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(PlayerBedEnterEvent)
	{
#define EVENTNAME PlayerBedEnterEvent 

	public:
		IEventAPIs(68);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(ScriptPluginManagerEvent)
	{
#define EVENTNAME ScriptPluginManagerEvent 

	public:
		IEventAPIs(69);
	public:
		enum class OperationEnum
		{
			Load,
			Unload,
			Reload
		};
		_Property_Enum(OperationEnum, ::Event::ScriptPluginManagerEvent::Operation, operation, Operation, EVENTNAME);
		_Property_String(target, Target, EVENTNAME);
		_Property_String(otherInfo, OtherInfo, EVENTNAME);
		_Property_String(pluginExtention, PluginExtention, EVENTNAME);
		_Property(bool, success, Success, EVENTNAME);

#undef EVENTNAME 
	};

	EventClass(MobSpawnEvent)
	{
#define EVENTNAME MobSpawnEvent 

	public:
		IEventAPIs(70);
	public:
		_Property_String(mTypeName, TypeName, EVENTNAME);
		_Property_ValueType(MC, Vec3, mPos, Pos, EVENTNAME);
		_Property(int, mDimensionId, DimensionId, EVENTNAME);

#undef EVENTNAME 
	};
}
