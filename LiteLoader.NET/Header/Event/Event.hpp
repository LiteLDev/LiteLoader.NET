#pragma once
#include <EventAPI.h>
#include "EventManager.hpp"
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <LiteLoader.NET/Tools/PropertryHelper.hpp>

#define EventAPIs(EventName, Id)																							\
public:                                                                                                                     \
    ref class EventListener{                                                                                                \
    internal:                                                                                                               \
        __EventListener<::Event::EventName>^ _listener;                                                                     \
        EventListener(__EventListener<::Event::EventName>^ listener):_listener(listener){}                                  \
    public:                                                                                                                 \
		void Remove() { _listener->Remove(); }                                                                              \
    };                                                                                                                      \
    using EventTemplate = EventTemplate<EventName, ::Event::EventName>;                                                     \
                                                                                                                            \
    static EventListener ^ Subscribe(EventHandler ^ callback) {                                                             \
        auto assembly = System::Reflection::Assembly::GetCallingAssembly();                                                 \
        auto pluginname = assembly->GetName()->FullName;                                                                    \
        return gcnew EventListener(EventTemplate::subscribe(pluginname, callback));                                         \
    };                                                                                                                      \
    static EventListener ^ Subscribe_Ref(EventHandler ^ callback) {                                                         \
        auto assembly = System::Reflection::Assembly::GetCallingAssembly();                                                 \
        auto pluginname = assembly->GetName()->FullName;                                                                    \
        return gcnew EventListener(EventTemplate::subscribe_ref(pluginname, callback));                                     \
    };                                                                                                                      \
    static void Unsubscribe(EventListener ^ listener)                                                                       \
    {                                                                                                                       \
        EventTemplate::unsubscribe(listener->_listener);                                                                    \
    }                                                                                                                       \
    static bool HasListener()                                                                                               \
    {                                                                                                                       \
        return EventTemplate::hasListener();                                                                                \
    }                                                                                                                       \
                                                                                                                            \
internal:																													\
    static const size_t EventId = Id;																						\
	delegate bool _delNativeCallback(::Event::EventName&);																	\
    static bool _nativeCallback(::Event::EventName& ev)																		\
    {																														\
	    auto _ev = Translate(ev);																							\
	    EventManager::_callNativeEvent(_ev, Id);																			\
	    return !_ev->IsCancelled;																							\
    }																														\
    static void _init()																										\
    {																														\
	    auto delfunc = gcnew _delNativeCallback(&_nativeCallback);															\
	    GCHandle::Alloc(delfunc);																							\
	    ::Event::EventManager<::Event::EventName>::addEventListenerRef(														\
		    LLNET_INFO_LOADER_NAME,																							\
		    static_cast<bool(*)(::Event::EventName&)>((void*)Marshal::GetFunctionPointerForDelegate(delfunc)));				\
    }																														\
	                                                                                                                        \
private:                                                                                                                    \
    static Dictionary<EventHandler ^, EventListener ^> ^ eventData = gcnew Dictionary<EventHandler ^, EventListener ^>;     \
    static EventHandler ^ pE;                                                                                               \
                                                                                                                            \
public:                                                                                                                     \
    static event EventHandler ^ Event {                                                                                     \
        void add(EventHandler ^ p)                                                                                          \
        {                                                                                                                   \
            pE = static_cast<EventHandler ^>(System::Delegate::Combine(pE, p));                                             \
            eventData->Add(p, Subscribe(p));                                                                                \
        }                                                                                                                   \
        void remove(EventHandler ^ p)                                                                                       \
        {                                                                                                                   \
            pE = static_cast<EventHandler ^>(System::Delegate::Remove(pE, p));                                              \
            for each(auto pair in eventData)                                                                                \
            {                                                                                                               \
                if (pair.Key->Equals(p))                                                                                    \
                {                                                                                                           \
                    Unsubscribe(pair.Value);                                                                                \
                    eventData->Remove(p);                                                                                   \
                }                                                                                                           \
            }                                                                                                               \
        }                                                                                                                   \
    };                                                                                                                      \
                                                                                                                            \
private:

#include <LiteLoader.NET/Header/MC/AABB.hpp>
#include <LiteLoader.NET/Header/MC/Types.hpp>
#include <LiteLoader.NET/Header/MC/BlockInstance.hpp>
#include <LiteLoader.NET/Header/MC/BlockSource.hpp>
#include <LiteLoader.NET/Header/MC/Container.hpp>
#include <LiteLoader.NET/Header/MC/ItemStack.hpp>
#include <LiteLoader.NET/Header/MC/Player.hpp>
#include <LiteLoader.NET/Header/MC/ServerPlayer.hpp>
#include <LiteLoader.NET/Header/MC/ActorDamageSource.hpp>
#include <LiteLoader.NET/Header/MC/MCRESULT.hpp>
#include <LiteLoader.NET/Header/MC/MobEffectInstance.hpp>
#include <LiteLoader.NET/Header/MC/Objective.hpp>
#include <LiteLoader.NET/Header/MC/WitherBoss.hpp>
#include <LiteLoader.NET/Header/MC/ActorDefinitionIdentifier.hpp>
#include <LiteLoader.NET/Header/MC/ArmorStand.hpp>
#include <LiteLoader.NET/Header/MC/Vec3.hpp>
#include <LiteLoader.NET/Header/MC/BlockPos.hpp>
#include <LiteLoader.NET/Header/MC/ScoreboardId.hpp>
#include <LiteLoader.NET/Header/Command/CommandRegistry.hpp>
#include <LiteLoader.NET/Header/Command/CommandParameterData.hpp>

#include <LiteLoader.NET/Header/Logger/Logger.hpp>

namespace LLNET::Event
{
    using namespace MC;

    template <typename NATIVEEVENT>
    public ref class __EventListener
    {
    private:
        int listenerId;
        bool deleted = false;

    public:
        __EventListener(int id)
            : listenerId(id)
        {
        }

        void Remove()
        {
            if (!deleted)
            {
                deleted = true;
                ::Event::EventManager<NATIVEEVENT>::removeEventListener(listenerId);
            }
        }
    };

    template <typename REFEVENT, typename NATIVEEVENT>
    public ref class EventTemplate : IEvent, ICancellable
    {
        bool isCancelled;
    protected:
        NATIVEEVENT* _this;
        bool ownsNativeInstance;

    public:
        delegate bool EventHandler(REFEVENT^ ev);
        virtual property bool IsCancelled
        {
            bool get() { return isCancelled; };
            void set(bool value) { isCancelled = value; };
        }

    protected:
        EventTemplate()
            : _this(nullptr)
              , ownsNativeInstance(false)
        {
        };

        !EventTemplate()
        {
            if (ownsNativeInstance)
                delete _this;
        };

        ~EventTemplate()
        {
            this->!EventTemplate();
        };

        static REFEVENT^ Translate(NATIVEEVENT& ev)
        {
            auto ret = gcnew REFEVENT{};
            ret->ownsNativeInstance = true;
            ret->_this = new NATIVEEVENT(std::move(ev));
            return ret;
        };

        static REFEVENT^ Translate_ref(const NATIVEEVENT& ev)
        {
            auto ret = gcnew REFEVENT{};
            ret->ownsNativeInstance = false;
            ret->_this = const_cast<NATIVEEVENT*>(&ev);
            return ret;
        };

        NATIVEEVENT& Translate()
        {
            return *_this;
        };

    private:
        ref class EventCallBack
        {
        private:
            bool NATIVECALLBACK Fn(NATIVEEVENT ev)
            {
                auto _ev = EventTemplate::Translate(ev);
                bool ret;
                try
                {
                    ret = delfunc(_ev);
                }
                CATCH
                return ret;
            }

            bool NATIVECALLBACK Fn_ref(const NATIVEEVENT& ev)
            {
                auto _ev = EventTemplate::Translate_ref(ev);
                bool ret;
                try
                {
                    ret = delfunc(_ev);
                }
                CATCH
                return ret;
            }

        private:
            delegate bool DelegateCallbackFunc(NATIVEEVENT ev);
            using NativeCallbackFunc = bool(*)(NATIVEEVENT ev);
            delegate bool DelegateCallbackFunc_ref(const NATIVEEVENT& ev);
            using NativeCallbackFunc_ref = bool(*)(const NATIVEEVENT& ev);

        public:
            EventCallBack(String^ pluginName, EventHandler^ callback, bool isRef)
                : delfunc(callback)
            {
                switch (isRef)
                {
                case true:
                    {
                        DelegateCallbackFunc_ref^ ftr = gcnew DelegateCallbackFunc_ref(this, &EventCallBack::Fn_ref);
                        gch = GCHandle::Alloc(ftr);
                        IntPtr^ _ptr = Marshal::GetFunctionPointerForDelegate(ftr);
                        auto pfunc = static_cast<NativeCallbackFunc_ref>(_ptr->ToPointer());
                        Listener = gcnew __EventListener<NATIVEEVENT>(
                            ::Event::EventManager<NATIVEEVENT>::addEventListenerRef(
                                pluginName ? marshalString(pluginName) : "",
                                pfunc));
                    }
                    break;
                case false:
                    {
                        DelegateCallbackFunc^ ftr = gcnew DelegateCallbackFunc(this, &EventCallBack::Fn);
                        gch = GCHandle::Alloc(ftr);
                        IntPtr^ _ptr = Marshal::GetFunctionPointerForDelegate(ftr);
                        auto pfunc = static_cast<NativeCallbackFunc>(_ptr->ToPointer());
                        Listener = gcnew __EventListener<NATIVEEVENT>(
                            ::Event::EventManager<NATIVEEVENT>::addEventListener(
                                pluginName ? marshalString(pluginName) : "",
                                pfunc));
                    }
                    break;
                }
            }

            ~EventCallBack()
            {
                if (gch.IsAllocated)
                {
                    gch.Free();
                }
            }

        private:
            EventHandler^ delfunc;
            GCHandle gch;

        public:
            __EventListener<NATIVEEVENT>^ Listener;
        };

    protected:
        static __EventListener<NATIVEEVENT>^ subscribe(String^ pluginName, EventHandler^ callback)
        {
            auto c = gcnew EventCallBack(pluginName, callback, false);
            GC::KeepAlive(c);
            return c->Listener;
        };

        static __EventListener<NATIVEEVENT>^ subscribe_ref(String^ pluginName, EventHandler^ callback)
        {
            auto c = gcnew EventCallBack(pluginName, callback, true);
            GC::KeepAlive(c);
            return c->Listener;
        };

        static void unsubscribe(__EventListener<NATIVEEVENT>^ listener)
        {
            listener->Remove();
        }

        static bool hasListener()
        {
            return ::Event::EventManager<NATIVEEVENT>::hasListener();
        }
    };

#define Class \
public        \
    ref class

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
        Property(int, mAttackDamage, AttackDamage);
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

    Class PlayerMoveEvent
        : public EventTemplate<PlayerMoveEvent, ::Event::PlayerMoveEvent>
    {
        EventAPIs(PlayerMoveEvent, 27);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_ValueType(MC, Vec3, mPos, Pos);
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

    ///////////////////////////// Entity Events /////////////////////////////

    Class EntityTransformEvent
        : public EventTemplate<EntityTransformEvent, ::Event::EntityTransformEvent>
    {
        EventAPIs(EntityTransformEvent, 51);

    public:
        property MC::ActorUniqueID BeforeEntityUniqueId
        {
            MC::ActorUniqueID get()
            {
                return *_this->mBeforeEntityUniqueId;
            }

            void set(MC::ActorUniqueID value)
            {
                *_this->mBeforeEntityUniqueId = value;
            }
        }

        Property_Ptr(MC, Actor, mAfterEntity, AfterEntity);
    };

    Class EntityExplodeEvent
        : public EventTemplate<EntityExplodeEvent, ::Event::EntityExplodeEvent>
    {
        EventAPIs(EntityExplodeEvent, 52);

    public:
        Property_Ptr(MC, Actor, mActor, Actor);
        Property_ValueType(MC, Vec3, mPos, Pos);
        Property_Ptr(MC, BlockSource, mDimension, Dimension);
        Property(float, mRadius, Radius);
        Property(float, mMaxResistance, MaxResistance);
        Property(bool, mBreaking, Breaking);
        Property(bool, mFire, Fire);
    };

    Class MobHurtEvent
        : public EventTemplate<MobHurtEvent, ::Event::MobHurtEvent>
    {
        EventAPIs(MobHurtEvent, 53);

    public:
        Property_Ptr(MC, Mob, mMob, Mob);
        Property_Ptr(MC, ActorDamageSource, mDamageSource, DamageSource);
        Property(float, mDamage, Damage);
    };

    Class MobDieEvent
        : public EventTemplate<MobDieEvent, ::Event::MobDieEvent>
    {
        EventAPIs(MobDieEvent, 54);

    public:
        Property_Ptr(MC, Mob, mMob, Mob);
        Property_Ptr(MC, ActorDamageSource, mDamageSource, DamageSource);
    };

    Class ProjectileHitEntityEvent
        : public EventTemplate<ProjectileHitEntityEvent, ::Event::ProjectileHitEntityEvent>
    {
        EventAPIs(ProjectileHitEntityEvent, 55);

    public:
        Property_Ptr(MC, Actor, mTarget, Target);
        Property_Ptr(MC, Actor, mSource, Source);
    };

    Class WitherBossDestroyEvent
        : public EventTemplate<WitherBossDestroyEvent, ::Event::WitherBossDestroyEvent>
    {
        EventAPIs(WitherBossDestroyEvent, 56);

    public:
        Property_Ptr(MC, WitherBoss, mWitherBoss, WitherBoss);
        Property_Instance(MC, AABB, mDestroyRange, DestroyRange);
    };

    Class EntityRideEvent
        : public EventTemplate<EntityRideEvent, ::Event::EntityRideEvent>
    {
        EventAPIs(EntityRideEvent, 57);

    public:
        Property_Ptr(MC, Actor, mRider, Rider);
        Property_Ptr(MC, Actor, mVehicle, Vehicle);
    };

    Class EntityStepOnPressurePlateEvent
        : public EventTemplate<EntityStepOnPressurePlateEvent, ::Event::EntityStepOnPressurePlateEvent>
    {
        EventAPIs(EntityStepOnPressurePlateEvent, 58);

    public:
        Property_Ptr(MC, Actor, mActor, Actor);
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
    };

    Class NpcCmdEvent
        : public EventTemplate<NpcCmdEvent, ::Event::NpcCmdEvent>
    {
        EventAPIs(NpcCmdEvent, 59);

    public:
        Property_Ptr(MC, Actor, mNpc, Npc);
        Property_String(mCommand, Command);
        Property_Ptr(MC, Player, mPlayer, Player);
    };

    Class ProjectileSpawnEvent
        : public EventTemplate<ProjectileSpawnEvent, ::Event::ProjectileSpawnEvent>
    {
        EventAPIs(ProjectileSpawnEvent, 60);

    public:
        Property_Ptr(MC, Actor, mShooter, Shooter);
        Property_Ptr(MC, ActorDefinitionIdentifier, mIdentifier, Identifier);
        Property_String(mType, Type);
    };

    Class ProjectileCreatedEvent
        : public EventTemplate<ProjectileCreatedEvent, ::Event::ProjectileCreatedEvent>
    {
        EventAPIs(ProjectileCreatedEvent, 61);

    public:
        Property_Ptr(MC, Actor, mShooter, Shooter);
        Property_Ptr(MC, Actor, mProjectile, Projectile);
    };

    Class ArmorStandChangeEvent
        : public EventTemplate<ArmorStandChangeEvent, ::Event::ArmorStandChangeEvent>
    {
        EventAPIs(ArmorStandChangeEvent, 62);

    public:
        Property_Ptr(MC, ArmorStand, mArmorStand, ArmorStand);
        Property_Ptr(MC, Player, mPlayer, Player);
        Property(int, mSlot, Slot);
    };

    ///////////////////////////// Other Events /////////////////////////////

    Class PostInitEvent
        : public EventTemplate<PostInitEvent, ::Event::PostInitEvent>
    {
        EventAPIs(PostInitEvent, 63)
    };

    Class ServerStartedEvent
        : public EventTemplate<ServerStartedEvent, ::Event::ServerStartedEvent>
    {
        EventAPIs(ServerStartedEvent, 64)
    };

    Class ServerStoppedEvent
        : public EventTemplate<ServerStoppedEvent, ::Event::ServerStoppedEvent>
    {
        EventAPIs(ServerStoppedEvent, 65)
    };

    Class ConsoleCmdEvent
        : public EventTemplate<ConsoleCmdEvent, ::Event::ConsoleCmdEvent>
    {
        EventAPIs(ConsoleCmdEvent, 66);

    public:
        Property_String(mCommand, Command);
    };

    Class RegCmdEvent
        : public EventTemplate<RegCmdEvent, ::Event::RegCmdEvent>
    {
        EventAPIs(RegCmdEvent, 67);

    public:
        Property_Ptr(MC, CommandRegistry, mCommandRegistry, CommandRegistry);
    };

    Class ConsoleOutputEvent
        : public EventTemplate<ConsoleOutputEvent, ::Event::ConsoleOutputEvent>
    {
        EventAPIs(ConsoleOutputEvent, 68);

    public:
        Property_String(mOutput, Output);
    };

    Class PlayerBedEnterEvent
        : public EventTemplate<PlayerBedEnterEvent, ::Event::PlayerBedEnterEvent>
    {
        EventAPIs(PlayerBedEnterEvent, 69);

    public:
        Property_Ptr(MC, Player, mPlayer, Player);
        Property_Ptr(MC, BlockInstance, mBlockInstance, BlockInstance);
    };

    Class ScriptPluginManagerEvent
        : public EventTemplate<ScriptPluginManagerEvent, ::Event::ScriptPluginManagerEvent>
    {
        EventAPIs(ScriptPluginManagerEvent, 70);

    public:
        enum class OperationEnum
        {
            Load,
            Unload,
            Reload
        };

        Property_Enum(OperationEnum, ::Event::ScriptPluginManagerEvent::Operation, operation, Operation);
        Property_String(target, Target);
        Property_String(otherInfo, OtherInfo);
        // Property_String(pluginExtention, PluginExtention);
        Property(bool, success, Success);
    };

    Class MobSpawnEvent
        : public EventTemplate<MobSpawnEvent, ::Event::MobSpawnEvent>
    {
        EventAPIs(MobSpawnEvent, 71);

    public:
        Property_String(mTypeName, TypeName);
        Property_ValueType(MC, Vec3, mPos, Pos);
        Property(int, mDimensionId, DimensionId);
    };

    Class FormResponsePacketEvent
        : public EventTemplate<FormResponsePacketEvent, ::Event::FormResponsePacketEvent>
    {
        EventAPIs(FormResponsePacketEvent, 72);

    public:
        Property_Ptr(MC, ServerPlayer, mServerPlayer, Player);
        Property(unsigned, mFormId, FormId);
        Property_String(mJsonData, JsonData);
    };
} // namespace LLNET::Event
