#pragma once
#include <EventAPI.h>
#include "EventManager.hpp"
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <LiteLoader.NET/Tools/PropertryHelper.hpp>

#define EventAPIs(EventName, Id)																							\
public:                                                                                                                     \
    ref class EventListener							                                                                        \
    {                                                                                                                       \
    internal:                                                                                                               \
        __EventListener<::Event::EventName>^ _listener;                                                                     \
        EventListener(__EventListener<::Event::EventName>^ listener):_listener(listener){}                                  \
    public:                                                                                                                 \
		void Remove() { _listener->Remove(); }																				\
    };                                                                                                                      \
    using EventTemplate = EventTemplate<EventName, ::Event::EventName>;                                                     \
                                                                                                                            \
    static EventListener ^ Subscribe(EventHandler ^ callback) {                                                             \
		return gcnew EventListener(EventTemplate::subscribe(Assembly::GetCallingAssembly(), callback));						\
    };                                                                                                                      \
    static EventListener ^ Subscribe_Ref(EventHandler ^ callback) {                                                         \
        return gcnew EventListener(EventTemplate::subscribe_ref(Assembly::GetCallingAssembly(), callback));                 \
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
	    auto _ev = cast_event(ev);																							\
	    EventManager::_callNativeEvent(_ev, Id);																            \
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
#include <LiteLoader.NET/Main/PluginOwnData.hpp>

#define Class __ref_class

namespace LLNET::Event
{
	using namespace MC;

	template <typename NATIVEEVENT>
	public ref class __EventListener :INativeEventListener
	{
	private:
		int listenerId;
		bool deleted = false;

	public:
		__EventListener(int id)
			: listenerId(id)
		{
		}

		virtual void Remove()
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

		__forceinline static REFEVENT^ cast_event(NATIVEEVENT& ev)
		{
			auto ret = gcnew REFEVENT{};
			ret->ownsNativeInstance = true;
			ret->_this = new NATIVEEVENT(std::move(ev));
			return ret;
		};

		__forceinline static REFEVENT^ cast_event_ref(const NATIVEEVENT& ev)
		{
			auto ret = gcnew REFEVENT{};
			ret->ownsNativeInstance = false;
			ret->_this = const_cast<NATIVEEVENT*>(&ev);
			return ret;
		};

		__forceinline NATIVEEVENT& cast_event()
		{
			return *_this;
		};

	private:
		ref class EventCallBack
		{
		private:
			bool NATIVECALLBACK call(NATIVEEVENT ev)
			{
				auto _ev = EventTemplate::cast_event(ev);
				bool ret;
				try
				{
					ret = delfunc(_ev);
				}
				CATCH
					return ret;
			}

			bool NATIVECALLBACK call_ref(const NATIVEEVENT& ev)
			{
				auto _ev = EventTemplate::cast_event_ref(ev);
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
					DelegateCallbackFunc_ref^ ftr = gcnew DelegateCallbackFunc_ref(this, &EventCallBack::call_ref);
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
					DelegateCallbackFunc^ ftr = gcnew DelegateCallbackFunc(this, &EventCallBack::call);
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
		static __EventListener<NATIVEEVENT>^ subscribe(Assembly^ plugin, EventHandler^ callback)
		{
			auto callbackInstance = gcnew EventCallBack(plugin->GetName()->FullName, callback, false);
			GC::KeepAlive(callbackInstance);

			auto module = (IntPtr)GET_MODULE(plugin);

			using NativeEventList = List<INativeEventListener^>;

			NativeEventList^ list = nullptr;

			if (!PluginOwnData::SubscribedNativeEvent->ContainsKey(module))
			{
				list = gcnew NativeEventList;
				PluginOwnData::SubscribedNativeEvent->Add(module, list);
			}
			else
			{
				list = PluginOwnData::SubscribedNativeEvent[module];
			}

			list->Add(callbackInstance->Listener);

			return callbackInstance->Listener;
		};

		static __EventListener<NATIVEEVENT>^ subscribe_ref(Assembly^ plugin, EventHandler^ callback)
		{
			auto callbackInstance = gcnew EventCallBack(plugin->GetName()->FullName, callback, true);
			GC::KeepAlive(callbackInstance);

			auto module = (IntPtr)GET_MODULE(plugin);

			using NativeEventList = List<INativeEventListener^>;

			NativeEventList^ list = nullptr;

			if (!PluginOwnData::SubscribedNativeEvent->ContainsKey(module))
			{
				list = gcnew NativeEventList;
				PluginOwnData::SubscribedNativeEvent->Add(module, list);
			}
			else
			{
				list = PluginOwnData::SubscribedNativeEvent[module];
			}

			list->Add(callbackInstance->Listener);

			return callbackInstance->Listener;
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
} // namespace LLNET::Event
