#pragma once
#include "EventManager.hpp"
#include <EventAPI.h>

#include "../../MC/Vec3.hpp"
#include "../../MC/BlockInstance.hpp"
#include "../../MC/Player.hpp"
#include "../../MC/ServerPlayer.hpp"
#include "../../MC/BlockPos.hpp"
#include "../../MC/AABB.hpp"
#include "../../MC/ItemStack.hpp"
#include "../../MC/Container.hpp"
#include "../../MC/ActorDamageSource.hpp"
#include "../../MC/MCRESULT.hpp"
#include "../../MC/MobEffectInstance.hpp"
#include "../../MC/Objective.hpp"
#include "../../MC/ScoreboardId.hpp"
#include "../../MC/BlockSource.hpp"
#include "../../MC/WitherBoss.hpp"
#include "../../MC/ActorDefinitionIdentifier.hpp"
#include "../../MC/ArmorStand.hpp"
#include "../../Command/CommandRegistry.hpp"
#include "../../Command/Command.hpp"

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

#define IEventAPIs(eventId,eventName)										\
virtual property bool IsCancelled											\
{																			\
	bool get()																\
	{																		\
		return NativeEventIsCancelledManager::get();						\
	}																		\
	void set(bool value)													\
	{																		\
		NativeEventIsCancelledManager::set(value);							\
	}																		\
}																			\
static const size_t EventId = eventId;


#define EventClass(className) [StructLayout(LayoutKind::Sequential, Size = sizeof(::Event:: className))] public value class className : IEvent, INativeEvent, ICancellable

#define CallEventAPI(...) static void CallEvent(__VA_ARGS__)

#define NativeCallback(eventName)																						\
internal:																												\
	delegate bool _delNativeCallback(::Event::eventName&);																\
	static bool _nativeCallback(::Event::eventName& ev)																	\
	{																													\
		NativeEventIsCancelledManager::set(false);																		\
		auto% _ev = *(eventName*)&ev;																					\
		EventManager::_callNativeEvent(_ev, EventId);															\
		return !_ev.IsCancelled;																						\
	}																													\
	static void _init()																									\
	{																													\
		auto delfunc = gcnew _delNativeCallback(&_nativeCallback);														\
		GCHandle::Alloc(delfunc);																						\
		::Event::EventManager<::Event::eventName>::addEventListenerRef(													\
			LLNET_INFO_LOADER_NAME,																							\
			static_cast<bool(*)(::Event::eventName&)>((void*)Marshal::GetFunctionPointerForDelegate(delfunc)));			\
	}

namespace LLNET::Event::Effective::NativeEvents
{
        ///////////////////////////// Player Events /////////////////////////////

#define EVENTNAME PlayerPreJoinEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(1, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_String(mIP, IP, EVENTNAME);
        _Property_String(mXUID, XUID, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerJoinEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(2, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerLeftEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(3, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_String(mXUID, XUID, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerRespawnEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(4, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerUseItemEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(5, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerUseItemOnEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(6, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
        _Property(char, mFace, Face, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerChatEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(7, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_String(mMessage, Message, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerChangeDimEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(8, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property(int, mToDimensionId, ToDimensionId, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerJumpEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

        /*delegate bool _delNativeCallback(::Event::PlayerJumpEvent&);
        static bool _nativeCallback(::Event::PlayerJumpEvent & ev)
        {
            auto% _ev = *(PlayerJumpEvent*)&ev;
            EventManager::_callNativeEvent(_ev, EventId);
            return !_ev.IsCancelled;
        }
        static PlayerJumpEvent()
        {
            auto delfunc = gcnew _delNativeCallback(&_nativeCallback);
            GCHandle::Alloc(delfunc);
            ::Event::EventManager<::Event::PlayerJumpEvent>::addEventListenerRef(
                LLNET_INFO_LOADER_NAME,
                static_cast<bool(*)(::Event::PlayerJumpEvent&)>((void*)Marshal::GetFunctionPointerForDelegate(delfunc)));
        }*/

    public:
        IEventAPIs(9, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerSneakEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(10, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property(bool, mIsSneaking, IsSneaking, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerAttackEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(11, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Ptr(MC, Actor, mTarget, Target, EVENTNAME);
        _Property(int, mAttackDamage, AttackDamage, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerAttackBlockEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(12, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerDieEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(13, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Ptr(MC, ActorDamageSource, mDamageSource, DamageSource, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerPickupItemEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(14, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Ptr(MC, Actor, mItemEntity, ItemEntity, EVENTNAME);
        _Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerDropItemEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(15, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerEatEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(16, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Ptr(MC, ItemStack, mFoodItem, FoodItem, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerConsumeTotemEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(17, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerCmdEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(18, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_String(mCommand, Command, EVENTNAME);
        _Property_Ptr(MC, MCRESULT, mResult, Result, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerEffectChangedEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(19, EVENTNAME);

        enum class EventType
        {
            Add,
            Remove,
            Update
        };

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Enum(EventType, ::Event::PlayerEffectChangedEvent::EventType, mEventType, Event_Type, EVENTNAME);
        _Property_Ptr(MC, MobEffectInstance, mEffect, Effect, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerStartDestroyBlockEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(20, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerDestroyBlockEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(21, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerPlaceBlockEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(22, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerOpenContainerEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(23, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
        _Property_Ptr(MC, Container, mContainer, Container, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerCloseContainerEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(24, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
        _Property_Ptr(MC, Container, mContainer, Container, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerInventoryChangeEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(25, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property(int, mSlot, Slot, EVENTNAME);
        _Property_Ptr(MC, ItemStack, mPreviousItemStack, PreviousItemStack, EVENTNAME);
        _Property_Ptr(MC, ItemStack, mNewItemStack, NewItemStack, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerMoveEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(26, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_ValueType(MC, Vec3, mPos, Pos, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerSprintEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(27, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property(bool, mIsSprinting, IsSprinting, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerSetArmorEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(28, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property(int, mSlot, Slot, EVENTNAME);
        _Property_Ptr(MC, ItemStack, mArmorItem, ArmorItem, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerUseRespawnAnchorEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(29, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerOpenContainerScreenEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(30, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerUseFrameBlockEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(31, EVENTNAME);

        enum class TypeEnum
        {
            Use,
            Attack
        };

        _Property_Enum(TypeEnum, ::Event::PlayerUseFrameBlockEvent::Type, mType, Type, EVENTNAME);
        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerScoreChangedEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(32, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property(int, mScore, Score, EVENTNAME);
        _Property_Ptr(MC, Objective, mObjective, Objective, EVENTNAME);
        _Property_Ptr(MC, ScoreboardId, mScoreboardId, ScoreboardId, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerExperienceAddEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(33, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property(int, mExp, Exp, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerInteractEntityEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(61, EVENTNAME);

        enum class InteractiveModeType
		{
			RightClick,
			LeftClick
		};

        _Property_Instance(MC, ActorRuntimeID, mTargetId, TargetId, EVENTNAME);
        _Property_Enum(InteractiveModeType, ::Event::PlayerInteractEntityEvent::InteractiveMode, mInteractiveMode, InteractiveMode, EVENTNAME);
    };
#undef EVENTNAME

    ///////////////////////////// Block Events /////////////////////////////

#define EVENTNAME BlockInteractedEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(34, EVENTNAME);

        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME BlockChangedEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(35, EVENTNAME);

        _Property_Instance(MC, BlockInstance, mPreviousBlockInstance, PreviousBlockInstance, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mNewBlockInstance, NewBlockInstance, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME BlockExplodedEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(36, EVENTNAME);

        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
        _Property_Ptr(MC, Actor, mExplodeSource, ExplodeSource, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME FireSpreadEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(37, EVENTNAME);

        _Property_ValueType(MC, BlockPos, mTarget, Target, EVENTNAME);
        _Property(int, mDimensionId, DimensionId, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME ContainerChangeEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(38, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Ptr(MC, Actor, mActor, Actor, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
        _Property_Ptr(MC, Container, mContainer, Cotainer, EVENTNAME);
        _Property(int, mSlot, Slot, EVENTNAME);
        _Property_Ptr(MC, ItemStack, mPreviousItemStack, PreviousItemStack, EVENTNAME);
        _Property_Ptr(MC, ItemStack, mNewItemStack, NewItemStack, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME ProjectileHitBlockEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(39, EVENTNAME);

        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
        _Property_Ptr(MC, Actor, mSource, Source, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME RedStoneUpdateEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(40, EVENTNAME);

        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
        _Property(int, mRedStonePower, RedStonePower, EVENTNAME);
        _Property(bool, mIsActivated, IsActivated, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME HopperSearchItemEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(41, EVENTNAME);

        _Property(int, isMinecart, isMinecart, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mHopperBlock, HopperBlock, EVENTNAME);
        _Property_ValueType(MC, Vec3, mMinecartPos, MinecartPos, EVENTNAME);
        _Property(int, mDimensionId, DimensionId, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME HopperPushOutEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(42, EVENTNAME);

        _Property_Instance(MC, Vec3, mPos, Pos, EVENTNAME);
        _Property(int, mDimensionId, DimensionId, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PistonTryPushEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(43, EVENTNAME);

        _Property_Instance(MC, BlockInstance, mPistonBlockInstance, PistonBlockInstance, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mTargetBlockInstance, TargetBlockInstance, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PistonPushEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(44, EVENTNAME);

        _Property_Instance(MC, BlockInstance, mPistonBlockInstance, PistonBlockInstance, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mTargetBlockInstance, TargetBlockInstance, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME FarmLandDecayEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(45, EVENTNAME);

        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
        _Property_Ptr(MC, Actor, mActor, Actor, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME LiquidSpreadEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(46, EVENTNAME);

        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
        _Property_ValueType(MC, BlockPos, mTarget, Target, EVENTNAME);
        _Property(int, mDimensionId, DimensionId, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME CmdBlockExecuteEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(47, EVENTNAME);

        _Property_String(mCommand, Command, EVENTNAME);
        _Property(bool, mIsMinecart, IsMinecart, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
        _Property_Ptr(MC, Actor, mMinecart, Minecart, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME BlockExplodeEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(48, EVENTNAME);

        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
        _Property(float, mRadius, Radius, EVENTNAME);
        _Property(float, mMaxResistance, MaxResistance, EVENTNAME);
        _Property(bool, mBreaking, Breaking, EVENTNAME);
        _Property(bool, mFire, Fire, EVENTNAME);
    };
#undef EVENTNAME

    ///////////////////////////// Entity Events /////////////////////////////

#define EVENTNAME EntityTransformEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(49, EVENTNAME);

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
    };
#undef EVENTNAME

#define EVENTNAME EntityExplodeEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(50, EVENTNAME);

        _Property_Ptr(MC, Actor, mActor, Actor, EVENTNAME);
        _Property_ValueType(MC, Vec3, mPos, Pos, EVENTNAME);
        _Property_Ptr(MC, BlockSource, mDimension, Dimension, EVENTNAME);
        _Property(float, mRadius, Radius, EVENTNAME);
        _Property(float, mMaxResistance, MaxResistance, EVENTNAME);
        _Property(bool, mBreaking, Breaking, EVENTNAME);
        _Property(bool, mFire, Fire, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME MobHurtEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(51, EVENTNAME);

        _Property_Ptr(MC, Mob, mMob, Mob, EVENTNAME);
        _Property_Ptr(MC, ActorDamageSource, mDamageSource, DamageSource, EVENTNAME);
        _Property(float, mDamage, Damage, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME MobDieEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(52, EVENTNAME);

        _Property_Ptr(MC, Mob, mMob, Mob, EVENTNAME);
        _Property_Ptr(MC, ActorDamageSource, mDamageSource, DamageSource, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME ProjectileHitEntityEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(53, EVENTNAME);

        _Property_Ptr(MC, Actor, mTarget, Target, EVENTNAME);
        _Property_Ptr(MC, Actor, mSource, Source, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME WitherBossDestroyEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(54, EVENTNAME);

        _Property_Ptr(MC, WitherBoss, mWitherBoss, WitherBoss, EVENTNAME);
        _Property_Instance(MC, AABB, mDestroyRange, DestroyRange, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME EntityRideEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(55, EVENTNAME);

        _Property_Ptr(MC, Actor, mRider, Rider, EVENTNAME);
        _Property_Ptr(MC, Actor, mVehicle, Vehicle, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME EntityStepOnPressurePlateEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(56, EVENTNAME);

        _Property_Ptr(MC, Actor, mActor, Actor, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME NpcCmdEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(57, EVENTNAME);

        _Property_Ptr(MC, Actor, mNpc, Npc, EVENTNAME);
        _Property_String(mCommand, Command, EVENTNAME);
        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME ProjectileSpawnEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(58, EVENTNAME);

        _Property_Ptr(MC, Actor, mShooter, Shooter, EVENTNAME);
        _Property_Ptr(MC, ActorDefinitionIdentifier, mIdentifier, Identifier, EVENTNAME);
        _Property_String(mType, Type, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME ProjectileCreatedEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(59, EVENTNAME);

        _Property_Ptr(MC, Actor, mShooter, Shooter, EVENTNAME);
        _Property_Ptr(MC, Actor, mProjectile, Projectile, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME ArmorStandChangeEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(60, EVENTNAME);

        _Property_Ptr(MC, ArmorStand, mArmorStand, ArmorStand, EVENTNAME);
        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property(int, mSlot, Slot, EVENTNAME);
    };
#undef EVENTNAME

    ///////////////////////////// Other Events /////////////////////////////

#define EVENTNAME PostInitEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(62, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME ServerStartedEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(63, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME ServerStoppedEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(64, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME ConsoleCmdEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(65, EVENTNAME);

        _Property_String(mCommand, Command, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME RegCmdEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(66, EVENTNAME);

        _Property_Ptr(MC, CommandRegistry, mCommandRegistry, CommandRegistry, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME ConsoleOutputEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(67, EVENTNAME);

        _Property_String(mOutput, Output, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME PlayerBedEnterEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(68, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Ptr(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME ScriptPluginManagerEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(69, EVENTNAME);

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
    };
#undef EVENTNAME

#define EVENTNAME MobSpawnEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(70, EVENTNAME);

        _Property_String(mTypeName, TypeName, EVENTNAME);
        _Property_ValueType(MC, Vec3, mPos, Pos, EVENTNAME);
        _Property(int, mDimensionId, DimensionId, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME BlockPlacedByPlayerEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(71, EVENTNAME);

        _Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
        _Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
    };
#undef EVENTNAME

#define EVENTNAME FormResponsePacketEvent
    EventClass(EVENTNAME)
    {
        NativeCallback(EVENTNAME);

    public:
        IEventAPIs(72, EVENTNAME);

        _Property_Ptr(MC, ServerPlayer, mServerPlayer, ServerPlayer, EVENTNAME);
        _Property(unsigned, mFormId, FormId, EVENTNAME);
        _Property_String(mJsonData, JsonData, EVENTNAME);
    };
#undef EVENTNAME
}
