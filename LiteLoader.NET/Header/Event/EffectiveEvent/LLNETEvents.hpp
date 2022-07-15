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
#include "../../MC/ActorDamageSource.hpp"
#include "../../MC/MCRESULT.hpp"
#include "../../MC/MobEffectInstance.hpp"
#include "../../MC/Objective.hpp"
#include "../../MC/ScoreboardId.hpp"
#include "../../MC/BlockSource.hpp"
#include "../../MC/WitherBoss.hpp"
#include "../../MC/ActorDefinitionIdentifier.hpp"
#include "../../MC/ArmStand.hpp"
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
static const size_t EventId = eventId;


#define EventClass(className) [StructLayout(LayoutKind::Sequential, Size = sizeof(::Event::className))] public value class className : IEvent, INativeEvent, ICancellable

#define CallEventAPI(...) static void CallEvent(__VA_ARGS__)

#define NativeCallback(eventName)										\
delegate bool _delNativeCallback(::Event::eventName&);					\
static bool _nativeCallback(::Event::eventName& ev)						\
{																		\
	auto% _ev = *(eventName*)&ev;										\
	EventManager::CallNativeEventInternal(_ev, EventId);				\
	return !_ev.IsCancelled;											\
}																		\
static eventName()														\
{																		\
	auto delfunc = gcnew _delNativeCallback(&_nativeCallback);			\
	GCHandle::Alloc(delfunc);											\
	::Event::eventName::subscribe_ref(									\
		static_cast<bool(*)(::Event::eventName&)>(						\
			(void*)Marshal::GetFunctionPointerForDelegate(delfunc)));	\
}


namespace LLNET::Event::Effective::NativeEvents
{

	EventClass(PlayerPreJoinEvent)
	{
#define EVENTNAME PlayerPreJoinEvent 

	private:
		NativeCallback(PlayerPreJoinEvent);

	public:
		IEventAPIs(1);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_String(mIP, IP, EVENTNAME);
		_Property_String(mXUID, XUID, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, String ^ mIP, String ^ mXUID);

#undef EVENTNAME 
	};

	EventClass(PlayerJoinEvent)
	{
#define EVENTNAME PlayerJoinEvent 

	private:
		NativeCallback(PlayerJoinEvent);

	public:
		IEventAPIs(2);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer);

#undef EVENTNAME 
	};

	EventClass(PlayerLeftEvent)
	{
#define EVENTNAME PlayerLeftEvent 

	private:
		NativeCallback(PlayerLeftEvent);

	public:
		IEventAPIs(3);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_String(mXUID, XUID, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, String ^ mXUID);

#undef EVENTNAME 
	};

	EventClass(PlayerRespawnEvent)
	{
#define EVENTNAME PlayerRespawnEvent 

	private:
		NativeCallback(PlayerRespawnEvent);

	public:
		IEventAPIs(4);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer);

#undef EVENTNAME 
	};

	EventClass(PlayerUseItemEvent)
	{
#define EVENTNAME PlayerUseItemEvent 

	private:
		NativeCallback(PlayerUseItemEvent);

	public:
		IEventAPIs(5);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::ItemStack ^ mItenStack);

#undef EVENTNAME 
	};

	EventClass(PlayerUseItemOnEvent)
	{
#define EVENTNAME PlayerUseItemOnEvent 

	private:
		NativeCallback(PlayerUseItemOnEvent);

	public:
		IEventAPIs(6);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property(char, mFace, Face, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::ItemStack ^ mItenStack, MC::BlockInstance ^ mBlockInstance, char mFace);

#undef EVENTNAME 
	};

	EventClass(PlayerChatEvent)
	{
#define EVENTNAME PlayerChatEvent 

	private:
		NativeCallback(PlayerChatEvent);

	public:
		IEventAPIs(7);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_String(mMessage, Message, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, String ^ mMessage);

#undef EVENTNAME 
	};

	EventClass(PlayerChangeDimEvent)
	{
#define EVENTNAME PlayerChangeDimEvent 

	private:
		NativeCallback(PlayerChangeDimEvent);

	public:
		IEventAPIs(8);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(int, mToDimensionId, ToDimensionId, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, int mToDimensionId);

#undef EVENTNAME 
	};

	EventClass(PlayerJumpEvent)
	{
#define EVENTNAME PlayerJumpEvent 

	private:
		NativeCallback(PlayerJumpEvent);

	public:
		IEventAPIs(9);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer);

#undef EVENTNAME 
	};

	EventClass(PlayerSneakEvent)
	{
#define EVENTNAME PlayerSneakEvent 

	private:
		NativeCallback(PlayerSneakEvent);

	public:
		IEventAPIs(10);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(bool, mIsSneaking, IsSneaking, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, bool mIsSneaking);

#undef EVENTNAME 
	};

	EventClass(PlayerAttackEvent)
	{
#define EVENTNAME PlayerAttackEvent 

	private:
		NativeCallback(PlayerAttackEvent);

	public:
		IEventAPIs(11);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, Actor, mTarget, Target, EVENTNAME);
		_Property(int, mAttackDamage, AttackDamage, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::Actor ^ mTarget, int mAttackDamage);

#undef EVENTNAME 
	};

	EventClass(PlayerAttackBlockEvent)
	{
#define EVENTNAME PlayerAttackBlockEvent 

	private:
		NativeCallback(PlayerAttackBlockEvent);

	public:
		IEventAPIs(12);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::ItemStack ^ mItemStack, MC::BlockInstance ^ mBlockInstance);

#undef EVENTNAME 
	};

	EventClass(PlayerDieEvent)
	{
#define EVENTNAME PlayerDieEvent 

	private:
		NativeCallback(PlayerDieEvent);

	public:
		IEventAPIs(13);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, ActorDamageSource, mDamageSource, DamageSource, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::ActorDamageSource ^ mDamageSource);

#undef EVENTNAME 
	};

	EventClass(PlayerPickupItemEvent)
	{
#define EVENTNAME PlayerPickupItemEvent 

	private:
		NativeCallback(PlayerPickupItemEvent);

	public:
		IEventAPIs(14);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, Actor, mItemEntity, ItemEntity, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::Actor ^ mItemEntity, MC::ItemStack ^ mItemStack);

#undef EVENTNAME 
	};

	EventClass(PlayerDropItemEvent)
	{
#define EVENTNAME PlayerDropItemEvent 

	private:
		NativeCallback(PlayerDropItemEvent);

	public:
		IEventAPIs(15);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mItemStack, ItemStack, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::ItemStack ^ mItemStack);

#undef EVENTNAME
	};

	EventClass(PlayerEatEvent)
	{
#define EVENTNAME PlayerEatEvent 

	private:
		NativeCallback(PlayerEatEvent);

	public:
		IEventAPIs(16);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mFoodItem, FoodItem, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::ItemStack ^ mFoodItem);

#undef EVENTNAME
	};

	EventClass(PlayerConsumeTotemEvent)
	{
#define EVENTNAME PlayerConsumeTotemEvent 

	private:
		NativeCallback(PlayerConsumeTotemEvent);

	public:
		IEventAPIs(17);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer);

#undef EVENTNAME
	};

	EventClass(PlayerCmdEvent)
	{
#define EVENTNAME PlayerCmdEvent 

	private:
		NativeCallback(PlayerCmdEvent);

	public:
		IEventAPIs(18);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_String(mCommand, Command, EVENTNAME);
		_Property_Ptr(MC, MCRESULT, mResult, Result, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::Command ^ mCommand, MC::MCRESULT ^ mResult);

#undef EVENTNAME
	};

	EventClass(PlayerEffectChangedEvent)
	{
#define EVENTNAME PlayerEffectChangedEvent 

	private:
		NativeCallback(PlayerEffectChangedEvent);

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
	public:
		//CallEventAPI(MC::Player ^ mPlayer, EventType mEventType, MC::MobEffectInstance ^ mEffect);

#undef EVENTNAME
	};

	EventClass(PlayerStartDestroyBlockEvent)
	{
#define EVENTNAME PlayerStartDestroyBlockEvent 

	private:
		NativeCallback(PlayerStartDestroyBlockEvent);

	public:
		IEventAPIs(20);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::BlockInstance ^ mBlockInstance);

#undef EVENTNAME
	};

	EventClass(PlayerDestroyBlockEvent)
	{
#define EVENTNAME PlayerDestroyBlockEvent 

	private:
		NativeCallback(PlayerDestroyBlockEvent);

	public:
		IEventAPIs(21);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::BlockInstance ^ mBlockInstance);

#undef EVENTNAME
	};

	EventClass(PlayerPlaceBlockEvent)
	{
#define EVENTNAME PlayerPlaceBlockEvent 

	private:
		NativeCallback(PlayerPlaceBlockEvent);

	public:
		IEventAPIs(22);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::BlockInstance ^ mBlockInstance);

#undef EVENTNAME
	};

	EventClass(PlayerOpenContainerEvent)
	{
#define EVENTNAME PlayerOpenContainerEvent 

	private:
		NativeCallback(PlayerOpenContainerEvent);

	public:
		IEventAPIs(23);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Container, mContainer, Container, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::BlockInstance ^ mBlockInstance, MC::Container ^ mContainer);

#undef EVENTNAME
	};

	EventClass(PlayerCloseContainerEvent)
	{
#define EVENTNAME PlayerCloseContainerEvent 

	private:
		NativeCallback(PlayerCloseContainerEvent);

	public:
		IEventAPIs(24);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Container, mContainer, Container, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::BlockInstance ^ mBlockInstance, MC::Container ^ mContainer);

#undef EVENTNAME
	};

	EventClass(PlayerInventoryChangeEvent)
	{
#define EVENTNAME PlayerInventoryChangeEvent 

	private:
		NativeCallback(PlayerInventoryChangeEvent);

	public:
		IEventAPIs(25);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(int, mSlot, Slot, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mPreviousItemStack, PreviousItemStack, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mNewItemStack, NewItemStack, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, int mSlot, MC::ItemStack ^ mPreviousItemStack, MC::ItemStack ^ mNewItemStack);

#undef EVENTNAME
	};

	EventClass(PlayerMoveEvent)
	{
#define EVENTNAME PlayerMoveEvent 

	private:
		NativeCallback(PlayerMoveEvent);

	public:
		IEventAPIs(26);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_ValueType(MC, Vec3, mPos, Pos, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::Vec3 mPos);

#undef EVENTNAME
	};

	EventClass(PlayerSprintEvent)
	{
#define EVENTNAME PlayerSprintEvent 

	private:
		NativeCallback(PlayerSprintEvent);

	public:
		IEventAPIs(27);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(bool, mIsSprinting, IsSprinting, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, bool mIsSprinting);

#undef EVENTNAME
	};

	EventClass(PlayerSetArmorEvent)
	{
#define EVENTNAME PlayerSetArmorEvent 

	private:
		NativeCallback(PlayerSetArmorEvent);

	public:
		IEventAPIs(28);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(int, mSlot, Slot, EVENTNAME);
		_Property_Ptr(MC, ItemStack, mArmorItem, ArmorItem, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, int mSlot, MC::ItemStack ^ mArmorItem);

#undef EVENTNAME
	};

	EventClass(PlayerUseRespawnAnchorEvent)
	{
#define EVENTNAME PlayerUseRespawnAnchorEvent 

	private:
		NativeCallback(PlayerUseRespawnAnchorEvent);

	public:
		IEventAPIs(29);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::BlockInstance ^ mBlockInstance);

#undef EVENTNAME
	};

	EventClass(PlayerOpenContainerScreenEvent)
	{
#define EVENTNAME PlayerOpenContainerScreenEvent 

	private:
		NativeCallback(PlayerOpenContainerScreenEvent);

	public:
		IEventAPIs(30);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer);

#undef EVENTNAME
	};

	EventClass(PlayerUseFrameBlockEvent)
	{
#define EVENTNAME PlayerUseFrameBlockEvent 

	private:
		NativeCallback(PlayerUseFrameBlockEvent);

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
	public:
		//CallEventAPI(TypeEnum mType, MC::Player ^ mPlayer, MC::BlockInstance ^ mBlockInstance);

#undef EVENTNAME
	};

	EventClass(PlayerScoreChangedEvent)
	{
#define EVENTNAME PlayerScoreChangedEvent 

	private:
		NativeCallback(PlayerScoreChangedEvent);

	public:
		IEventAPIs(32);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(int, mScore, Score, EVENTNAME);
		_Property_Ptr(MC, Objective, mObjective, Objective, EVENTNAME);
		_Property_Ptr(MC, ScoreboardId, mScoreboardId, ScoreboardId, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, int mScore, MC::Objective ^ Objective, MC::ScoreboardId ^ mBlockInstance);

#undef EVENTNAME
	};

	EventClass(PlayerExperienceAddEvent)
	{
#define EVENTNAME PlayerExperienceAddEvent 

	private:
		NativeCallback(PlayerExperienceAddEvent);

	public:
		IEventAPIs(33);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(int, mExp, Exp, EVENTNAME);
	public:
		//CallEventAPI(MC::Player ^ mPlayer, int mExp);

#undef EVENTNAME
	};
	///////////////////////////// Block Events /////////////////////////////

	EventClass(BlockInteractedEvent)
	{
#define EVENTNAME BlockInteractedEvent 

	private:
		NativeCallback(BlockInteractedEvent);

	public:
		IEventAPIs(34);
	public:
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
	public:
		//CallEventAPI(MC::BlockInstance ^ mBlockInstance, MC::Player ^ mPlayer);

#undef EVENTNAME
	};

	EventClass(BlockChangedEvent)
	{
#define EVENTNAME BlockChangedEvent 

	private:
		NativeCallback(BlockChangedEvent);

	public:
		IEventAPIs(35);
	public:
		_Property_Instance(MC, BlockInstance, mPreviousBlockInstance, PreviousBlockInstance, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mNewBlockInstance, NewBlockInstance, EVENTNAME);
	public:
		//CallEventAPI(MC::BlockInstance ^ mPreviousBlockInstance, MC::BlockInstance ^ mNewBlockInstance);

#undef EVENTNAME
	};

	EventClass(BlockExplodedEvent)
	{
#define EVENTNAME BlockExplodedEvent 

	private:
		NativeCallback(BlockExplodedEvent);

	public:
		IEventAPIs(36);
	public:
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Actor, mExplodeSource, ExplodeSource, EVENTNAME);
	public:
		//CallEventAPI(MC::BlockInstance ^ mBlockInstance, MC::Actor ^ mExplodeSource);

#undef EVENTNAME
	};

	EventClass(FireSpreadEvent)
	{
#define EVENTNAME FireSpreadEvent 

	private:
		NativeCallback(FireSpreadEvent);

	public:
		IEventAPIs(37);
	public:
		_Property_ValueType(MC, BlockPos, mTarget, Target, EVENTNAME);
		_Property(int, mDimensionId, DimensionId, EVENTNAME);
	public:
		//CallEventAPI(MC::BlockPos mBlockInstance, int mDimensionId);

#undef EVENTNAME
	};

	EventClass(ContainerChangeEvent)
	{
#define EVENTNAME ContainerChangeEvent 

	private:
		NativeCallback(ContainerChangeEvent);

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
	public:
		//CallEventAPI(MC::Player ^ mPlayer, MC::Actor ^ mActor, MC::BlockInstance ^ mBlockInstance, MC::Container ^ mContainer, int mSlot, MC::ItemStack ^ mPreviousItemStack, MC::Player ^ mNewItemStack);

#undef EVENTNAME
	};

	EventClass(ProjectileHitBlockEvent)
	{
#define EVENTNAME ProjectileHitBlockEvent 

	private:
		NativeCallback(ProjectileHitBlockEvent);

	public:
		IEventAPIs(39);
	public:
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Actor, mSource, Source, EVENTNAME);
	public:
		//CallEventAPI(MC::BlockInstance ^ mBlockInstance, MC::Actor ^ mSource);

#undef EVENTNAME
	};

	EventClass(RedStoneUpdateEvent)
	{
#define EVENTNAME RedStoneUpdateEvent 

	private:
		NativeCallback(RedStoneUpdateEvent);

	public:
		IEventAPIs(40);
	public:
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property(int, mRedStonePower, RedStonePower, EVENTNAME);
		_Property(bool, mIsActivated, IsActivated, EVENTNAME);
	public:
		//CallEventAPI(MC::BlockInstance ^ mBlockInstance, int mRedStonePower, bool mIsActivated);

#undef EVENTNAME
	};

	EventClass(HopperSearchItemEvent)
	{
#define EVENTNAME HopperSearchItemEvent 

	private:
		NativeCallback(HopperSearchItemEvent);

	public:
		IEventAPIs(41);
	public:
		_Property(int, isMinecart, isMinecart, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mHopperBlock, HopperBlock, EVENTNAME);
		_Property_ValueType(MC, Vec3, mMinecartPos, MinecartPos, EVENTNAME);
		_Property(int, mDimensionId, DimensionId, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(HopperPushOutEvent)
	{
#define EVENTNAME HopperPushOutEvent 

	private:
		NativeCallback(HopperPushOutEvent);

	public:
		IEventAPIs(42);
	public:
		_Property_Instance(MC, Vec3, mPos, Pos, EVENTNAME);
		_Property(int, mDimensionId, DimensionId, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(PistonTryPushEvent)
	{
#define EVENTNAME PistonTryPushEvent 

	private:
		NativeCallback(PistonTryPushEvent);

	public:
		IEventAPIs(43);
	public:
		_Property_Instance(MC, BlockInstance, mPistonBlockInstance, PistonBlockInstance, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mTargetBlockInstance, TargetBlockInstance, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(PistonPushEvent)
	{
#define EVENTNAME PistonPushEvent 

	private:
		NativeCallback(PistonPushEvent);

	public:
		IEventAPIs(44);
	public:
		_Property_Instance(MC, BlockInstance, mPistonBlockInstance, PistonBlockInstance, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mTargetBlockInstance, TargetBlockInstance, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(FarmLandDecayEvent)
	{
#define EVENTNAME FarmLandDecayEvent 

	private:
		NativeCallback(FarmLandDecayEvent);

	public:
		IEventAPIs(45);
	public:
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Actor, mActor, Actor, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(LiquidSpreadEvent)
	{
#define EVENTNAME LiquidSpreadEvent 

	private:
		NativeCallback(LiquidSpreadEvent);

	public:
		IEventAPIs(46);
	public:
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_ValueType(MC, BlockPos, mTarget, Target, EVENTNAME);
		_Property(int, mDimensionId, DimensionId, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(CmdBlockExecuteEvent)
	{
#define EVENTNAME CmdBlockExecuteEvent 

	private:
		NativeCallback(CmdBlockExecuteEvent);

	public:
		IEventAPIs(47);
	public:
		_Property_String(mCommand, Command, EVENTNAME);
		_Property(bool, mIsMinecart, IsMinecart, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property_Ptr(MC, Actor, mMinecart, Minecart, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(BlockExplodeEvent)
	{
#define EVENTNAME BlockExplodeEvent 

	private:
		NativeCallback(BlockExplodeEvent);

	public:
		IEventAPIs(48);
	public:
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);
		_Property(float, mRadius, Radius, EVENTNAME);
		_Property(float, mMaxResistance, MaxResistance, EVENTNAME);
		_Property(bool, mBreaking, Breaking, EVENTNAME);
		_Property(bool, mFire, Fire, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};
	///////////////////////////// Entity Events /////////////////////////////

	EventClass(EntityTransformEvent)
	{
#define EVENTNAME EntityTransformEvent 

	private:
		NativeCallback(EntityTransformEvent);

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

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(EntityExplodeEvent)
	{
#define EVENTNAME EntityExplodeEvent 

	private:
		NativeCallback(EntityExplodeEvent);

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

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(MobHurtEvent)
	{
#define EVENTNAME MobHurtEvent 

	private:
		NativeCallback(MobHurtEvent);

	public:
		IEventAPIs(51);
	public:
		_Property_Ptr(MC, Mob, mMob, Mob, EVENTNAME);
		_Property_Ptr(MC, ActorDamageSource, mDamageSource, DamageSource, EVENTNAME);
		_Property(float, mDamage, Damage, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(MobDieEvent)
	{
#define EVENTNAME MobDieEvent 

	private:
		NativeCallback(MobDieEvent);

	public:
		IEventAPIs(52);
	public:
		_Property_Ptr(MC, Mob, mMob, Mob, EVENTNAME);
		_Property_Ptr(MC, ActorDamageSource, mDamageSource, DamageSource, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(ProjectileHitEntityEvent)
	{
#define EVENTNAME ProjectileHitEntityEvent 

	private:
		NativeCallback(ProjectileHitEntityEvent);

	public:
		IEventAPIs(53);
	public:
		_Property_Ptr(MC, Actor, mTarget, Target, EVENTNAME);
		_Property_Ptr(MC, Actor, mSource, Source, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(WitherBossDestroyEvent)
	{
#define EVENTNAME WitherBossDestroyEvent 

	private:
		NativeCallback(WitherBossDestroyEvent);

	public:
		IEventAPIs(54);
	public:
		_Property_Ptr(MC, WitherBoss, mWitherBoss, WitherBoss, EVENTNAME);
		_Property_Instance(MC, AABB, mDestroyRange, DestroyRange, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(EntityRideEvent)
	{
#define EVENTNAME EntityRideEvent 

	private:
		NativeCallback(EntityRideEvent);

	public:
		IEventAPIs(55);
	public:
		_Property_Ptr(MC, Actor, mRider, Rider, EVENTNAME);
		_Property_Ptr(MC, Actor, mVehicle, Vehicle, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(EntityStepOnPressurePlateEvent)
	{
#define EVENTNAME EntityStepOnPressurePlateEvent 

	private:
		NativeCallback(EntityStepOnPressurePlateEvent);

	public:
		IEventAPIs(56);
	public:
		_Property_Ptr(MC, Actor, mActor, Actor, EVENTNAME);
		_Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(NpcCmdEvent)
	{
#define EVENTNAME NpcCmdEvent 

	private:
		NativeCallback(NpcCmdEvent);

	public:
		IEventAPIs(57);
	public:
		_Property_Ptr(MC, Actor, mNpc, Npc, EVENTNAME);
		_Property_String(mCommand, Command, EVENTNAME);
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(ProjectileSpawnEvent)
	{
#define EVENTNAME ProjectileSpawnEvent 

	private:
		NativeCallback(ProjectileSpawnEvent);

	public:
		IEventAPIs(58);
	public:
		_Property_Ptr(MC, Actor, mShooter, Shooter, EVENTNAME);
		_Property_Ptr(MC, ActorDefinitionIdentifier, mIdentifier, Identifier, EVENTNAME);
		_Property_String(mType, Type, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(ProjectileCreatedEvent)
	{
#define EVENTNAME ProjectileCreatedEvent 

	private:
		NativeCallback(ProjectileCreatedEvent);

	public:
		IEventAPIs(59);
	public:
		_Property_Ptr(MC, Actor, mShooter, Shooter, EVENTNAME);
		_Property_Ptr(MC, Actor, mProjectile, Projectile, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(ArmorStandChangeEvent)
	{
#define EVENTNAME ArmorStandChangeEvent 

	private:
		NativeCallback(ArmorStandChangeEvent);

	public:
		IEventAPIs(60);
	public:
		_Property_Ptr(MC, ArmorStand, mArmorStand, ArmorStand, EVENTNAME);
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property(int, mSlot, Slot, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(ItemUseOnActorEvent)
	{
#define EVENTNAME ItemUseOnActorEvent 

	private:
		NativeCallback(ItemUseOnActorEvent);

	public:
		IEventAPIs(61);
	public:
		_Property_Instance(MC, ActorRuntimeID, mTarget, Target, EVENTNAME);
		_Property(int, mInteractiveMode, InteractiveMode, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};
	///////////////////////////// Other Events /////////////////////////////

	EventClass(PostInitEvent)
	{
#define EVENTNAME PostInitEvent 

	private:
		NativeCallback(PostInitEvent);

	public:
		IEventAPIs(62);
	public:

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(ServerStartedEvent)
	{
#define EVENTNAME ServerStartedEvent 

	private:
		NativeCallback(ServerStartedEvent);

	public:
		IEventAPIs(63);
	public:

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(ServerStoppedEvent)
	{
#define EVENTNAME ServerStoppedEvent 

	private:
		NativeCallback(ServerStoppedEvent);

	public:
		IEventAPIs(64);
	public:

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(ConsoleCmdEvent)
	{
#define EVENTNAME ConsoleCmdEvent 

	private:
		NativeCallback(ConsoleCmdEvent);

	public:
		IEventAPIs(65);
	public:
		_Property_String(mCommand, Command, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(RegCmdEvent)
	{
#define EVENTNAME RegCmdEvent 

	private:
		NativeCallback(RegCmdEvent);

	public:
		IEventAPIs(66);
	public:
		_Property_Ptr(MC, CommandRegistry, mCommandRegistry, CommandRegistry, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(ConsoleOutputEvent)
	{
#define EVENTNAME ConsoleOutputEvent 

	private:
		NativeCallback(ConsoleOutputEvent);

	public:
		IEventAPIs(67);
	public:
		_Property_String(mOutput, Output, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(PlayerBedEnterEvent)
	{
#define EVENTNAME PlayerBedEnterEvent 

	private:
		NativeCallback(PlayerBedEnterEvent);

	public:
		IEventAPIs(68);
	public:
		_Property_Ptr(MC, Player, mPlayer, Player, EVENTNAME);
		_Property_Ptr(MC, BlockInstance, mBlockInstance, BlockInstance, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(ScriptPluginManagerEvent)
	{
#define EVENTNAME ScriptPluginManagerEvent 

	private:
		NativeCallback(ScriptPluginManagerEvent);

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

	public:
		//CallEventAPI();
#undef EVENTNAME
	};

	EventClass(MobSpawnEvent)
	{
#define EVENTNAME MobSpawnEvent 

	private:
		NativeCallback(MobSpawnEvent);

	public:
		IEventAPIs(70);
	public:
		_Property_String(mTypeName, TypeName, EVENTNAME);
		_Property_ValueType(MC, Vec3, mPos, Pos, EVENTNAME);
		_Property(int, mDimensionId, DimensionId, EVENTNAME);

	public:
		//CallEventAPI();
#undef EVENTNAME
	};
}
