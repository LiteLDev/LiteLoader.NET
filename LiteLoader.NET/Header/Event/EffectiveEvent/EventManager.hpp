#pragma once
#include "include.hpp"

constexpr int LOWEST = 0;
constexpr int LOW = 1;
constexpr int NORMAL = 2;
constexpr int HIGH = 3;
constexpr int HIGHEST = 4;
constexpr int MONITOR = 5;



constexpr int IS_NORMAL = 0;
constexpr int IS_INSTANCE = 64;
constexpr int IS_REF = 128;
constexpr int IS_IGNORECANCELLED = 256;
constexpr int IS_INSTANCE_AND_REF = IS_INSTANCE | IS_REF;
constexpr int IS_INSTANCE_AND_IGNORECANCELLED = IS_INSTANCE | IS_IGNORECANCELLED;
constexpr int IS_REF_AND_IGNORECANCELLED = IS_REF | IS_IGNORECANCELLED;
constexpr int IS_INSTANCE_AND_REF_AND_IGNORECANCELLED = IS_INSTANCE | IS_REF | IS_IGNORECANCELLED;



namespace LLNET::Event::Effective
{

	ref class NativeEventIsCancelledManager sealed
	{
	internal:
		/*static Dictionary<int, bool> IsCancelledData;*/
		static bool current = false;

		inline static void set(bool isCancelled);
		inline static bool get();
		/*inline static void add(bool isCancelled);*/
		/*inline static void remove(int hashcode);*/
	};

	public enum class EventCode
	{
		SUCCESS = 0,
		UNREGISTERED,
		CATCHED_EXCEPTIONS
		//UNKNOWN
	};

	public ref class EventManager sealed
	{
	internal:

		using __IgnoreCancelled = bool;
		using __IsRef = bool;
		using __IsInstance = bool;
		using __CallBackFunctionPointer = IntPtr;
		using __ListenerType = System::Type;
		using __HMODULE = IntPtr;
		using __CallbackFunctionInfo = System::ValueTuple<__CallBackFunctionPointer, __IgnoreCancelled, __IsRef, __IsInstance, __ListenerType^, __HMODULE>;
		using __PermissionWithCallbackFunctions = array<List<__CallbackFunctionInfo>^>;
		using __EventId = size_t;
		using __EventManagerData = Dictionary<__EventId, __PermissionWithCallbackFunctions^>;

		using __EventIds = Dictionary<System::Type^, __EventId>;

		static __EventManagerData eventManagerData;
		static __EventIds eventIds;
		static System::Random rand;
		static Queue<Exception^>^ lastExceptions = gcnew Queue<Exception^>;
		static List<__EventId> initializedNativeEvents;

	public:
		//public API
		generic<typename TEvent> where TEvent : IEvent
			static void RegisterEvent();

		generic<typename TListener> where TListener : IEventListener
			static void RegisterListener(__HMODULE handle);

		generic<typename TListener> where TListener : IEventListener
			static void RegisterListener();

		generic<typename TEvent> where TEvent : IEvent
			static EventCode CallEvent(TEvent ev);

		generic<typename TEvent> where TEvent : IEvent
			static EventCode CallEvent(TEvent ev, __EventId eventId);

		generic<typename TEvent> where TEvent : IEvent
			static __EventId GetEventId();

		static array<Exception^>^ GetLastCallingExceptions();

	private:
		static void _registerEvent(System::Type^ eventType);

		generic<typename TEvent> where TEvent : IEvent
			static EventCode _callEvent(TEvent ev, List<__CallbackFunctionInfo>^* pfuncs);

	internal:
		generic<typename TEvent> where TEvent : IEvent
			static EventCode _callNativeEvent(TEvent% ev, List<__CallbackFunctionInfo>^* pfuncs);

		generic<typename TEvent> where TEvent : IEvent
			static EventCode CallNativeEventInternal(TEvent% ev, __EventId eventId);

		static void _initEvents();

		generic<typename TEvent> where TEvent : IEvent, INativeEvent
			static void _registerEventInternal(__EventId id);
	};
}




//#include "LLNETEvents.hpp"

namespace LLNET::Event::Effective
{
	generic<typename TEvent> where TEvent : IEvent
		inline void EventManager::RegisterEvent()
	{
		_registerEvent(TEvent::typeid);
	}



	void EventManager::_registerEvent(System::Type^ eventType)
	{
		__EventId eventId = 0;

	RE_GENERATE_EVENTID:
		do
		{
			eventId = __EventId(rand.Next()) ^ __EventId(rand.Next() & 7);
		} while (eventIds.ContainsValue(eventId));

		if (0 < eventId && eventId <= 128)
		{
			goto RE_GENERATE_EVENTID;
		}

		eventIds.Add(eventType, eventId);
		eventManagerData.Add(eventId, gcnew __PermissionWithCallbackFunctions(6) { nullptr });
	}



	generic<typename TEvent> where TEvent : IEvent, INativeEvent
		inline void EventManager::_registerEventInternal(__EventId id)
	{
		eventIds.Add(TEvent::typeid, id);
		eventManagerData.Add(id, gcnew __PermissionWithCallbackFunctions(6) { nullptr });
	}



	generic<typename TListener> where TListener : IEventListener
		inline void EventManager::RegisterListener()
	{
		RegisterListener<TListener>(IntPtr(GlobalClass::__GetCurrentModule(Assembly::GetCallingAssembly())));
	}



	generic<typename TListener> where TListener : IEventListener
		inline void EventManager::RegisterListener(__HMODULE handle)
	{
		auto listenerType = TListener::typeid;
		auto Methods = listenerType->GetMethods(
			BindingFlags::Public |
			BindingFlags::NonPublic |
			BindingFlags::Static |
			BindingFlags::Instance);

		auto listenerMethodDatas = gcnew List<System::ValueTuple<MethodInfo^, EventPriority, bool, bool, bool>>;

		for each (auto method in Methods)
		{
			auto evHandlerAttrArr = method->GetCustomAttributes(EventHandlerAttribute::typeid, false);
			if (evHandlerAttrArr->Length == 0)
				continue;
			else
			{
				if (!method->IsStatic)
				{
					auto defaultCtor = listenerType->GetConstructor(System::Array::Empty<System::Type^>());
					if (defaultCtor == nullptr)
						throw gcnew RegisterEventListenerException("Handler must be static or it's class must have default constructor!  at Handler:<" + listenerType->Name + "." + method->Name + ">");
				}

				auto evHandlerAttr = static_cast<EventHandlerAttribute^>(evHandlerAttrArr[0]);
				listenerMethodDatas->Add(System::ValueTuple<MethodInfo^, EventPriority, bool, bool, bool>
				{
					method,
					evHandlerAttr->Priority,
					evHandlerAttr->IgnoreCancelled,
					!method->IsStatic,
					false
				});
			}
		}

		for each (auto methodData in listenerMethodDatas)
		{
			auto method = methodData.Item1;

			auto methodRetType = method->ReturnType;

			if (methodRetType != void::typeid)
				throw gcnew RegisterEventListenerException("Handler.ReturnType must be System.Void!  at Handler:<" + listenerType->Name + "." + method->Name + ">");


			auto methodParam = method->GetParameters();

			if (methodParam->Length != 1)
				goto PARAM_CHECK_STEP1_FAILED;

			__IsRef isref = false;
			auto paramType = methodParam[0]->ParameterType;
			auto elementParamType = paramType;

			if (paramType->IsByRef)
			{
				isref = true;
				elementParamType = paramType->GetElementType();
			}

			auto paramInterfaces = elementParamType->GetInterfaces();
			for each (auto Interface in paramInterfaces)
			{
				if (Interface == IEvent::typeid)
					goto PARAM_CHECK_STEP1_SUCCEED;
			}


		PARAM_CHECK_STEP1_FAILED:
			throw gcnew RegisterEventListenerException("Handler can only have one parameter which the type is based on IEvent!  at Handler:<" + listenerType->Name + "." + method->Name + ">");

		PARAM_CHECK_STEP1_SUCCEED:

			if (!eventIds.ContainsKey(elementParamType))
				_registerEvent(elementParamType);

			auto eventId = eventIds[elementParamType];
			bool isNativeEventListener = 0 < eventId && eventId <= 128;

			if (isref)
			{
				methodData.Item5 = true;
			}
			else
			{
			    if (isNativeEventListener)
			    {
					throw gcnew RegisterEventListenerException("Parameter of the native event handler must be passed by reference (use 'in' or 'ref' keyword in C#)!  at Handler:<" + listenerType->Name + "." + method->Name + ">");
			    }
			}

			auto eventPriority = (int)methodData.Item2;

			auto callbackFuncArr = eventManagerData[eventId];

			if (callbackFuncArr[eventPriority] == nullptr)
				callbackFuncArr[eventPriority] = gcnew List<__CallbackFunctionInfo>;

			callbackFuncArr[eventPriority]->Add(__CallbackFunctionInfo(method->MethodHandle.GetFunctionPointer(), methodData.Item3, isref, methodData.Item4, methodData.Item4 ? listenerType : nullptr, handle));

			if (isNativeEventListener)
			{
				if (!initializedNativeEvents.Contains(eventId))
					elementParamType
					->GetMethod("_init", BindingFlags::Static | BindingFlags::NonPublic)
					->Invoke(nullptr, System::Array::Empty<System::Type^>());
				initializedNativeEvents.Add(eventId);
			}
		}
	}



	generic<typename TEvent> where TEvent : IEvent
		inline EventCode EventManager::CallEvent(TEvent ev)
	{
		return CallEvent(ev, 0);
	}


	generic<typename TEvent> where TEvent : IEvent
		inline EventCode EventManager::CallEvent(TEvent ev, __EventId eventId)
	{
		if (eventId != 0)
			goto SKIP_CHECK;

		auto eventType = ev->GetType();
		if (!eventIds.ContainsKey(eventType))
			return EventCode::UNREGISTERED;

		eventId = eventIds[eventType];

	SKIP_CHECK:

		if (lastExceptions->Count > 0)
			lastExceptions->Clear();

		auto functions = eventManagerData[eventId];
		pin_ptr<List<__CallbackFunctionInfo>^> pfunctions = &functions[0];

		if (eventId > 128)
			return _callEvent(ev, pfunctions);
		else
			return _callNativeEvent(ev, pfunctions);
	}



	generic<typename TEvent> where TEvent : IEvent
		inline EventCode EventManager::_callEvent(TEvent ev, List<__CallbackFunctionInfo>^* pfuncs)
	{
		bool catchedException = false;

		for (int i = 0; i < 6; i++)
		{
			auto funcs = pfuncs[i];
			if (funcs == nullptr)
				continue;

			for each (auto func in funcs)
			{
				int callingmode = (func.Item2 ? IS_IGNORECANCELLED : 0) | (func.Item3 ? IS_REF : 0) | (func.Item4 ? IS_INSTANCE : 0);

				try
				{
					switch (callingmode)
					{
					case IS_NORMAL:

						((void(*)(TEvent))(void*)func.Item1)(ev);
						break;

					case IS_INSTANCE:

						((void(*)(Object^, TEvent))(void*)func.Item1)(System::Activator::CreateInstance(func.Item5), ev);
						break;

					case IS_REF:

						((void(*)(TEvent%))(void*)func.Item1)(ev);
						break;

					case IS_IGNORECANCELLED:

						if (!ev->IsCancelled)
							((void(*)(TEvent))(void*)func.Item1)(ev);
						break;

					case IS_INSTANCE_AND_REF:

						((void(*)(Object^, TEvent%))(void*)func.Item1)(System::Activator::CreateInstance(func.Item5), ev);
						break;

					case IS_INSTANCE_AND_IGNORECANCELLED:

						if (!ev->IsCancelled)
							((void(*)(Object^, TEvent))(void*)func.Item1)(System::Activator::CreateInstance(func.Item5), ev);
						break;

					case IS_REF_AND_IGNORECANCELLED:

						if (!ev->IsCancelled)
							((void(*)(TEvent%))(void*)func.Item1)(ev);
						break;

					case IS_INSTANCE_AND_REF_AND_IGNORECANCELLED:

						if (!ev->IsCancelled)
							((void(*)(Object^, TEvent%))(void*)func.Item1)(System::Activator::CreateInstance(func.Item5), ev);
						break;
					}
				}
				catch (Exception^ ex)
				{
					lastExceptions->Enqueue(ex);
					catchedException = true;
				}
			}
		}

		if (catchedException)
			return EventCode::CATCHED_EXCEPTIONS;
		else
			return EventCode::SUCCESS;
	}



	generic<typename TEvent> where TEvent : IEvent
		inline EventCode EventManager::CallNativeEventInternal(TEvent% ev, __EventId eventId)
	{
		if (lastExceptions->Count > 0)
			lastExceptions->Clear();

		auto functions = eventManagerData[eventId];
		pin_ptr<List<__CallbackFunctionInfo>^> pfunctions = &functions[0];

		return _callNativeEvent(ev, pfunctions);
	}



	generic<typename TEvent> where TEvent : IEvent
		inline EventCode EventManager::_callNativeEvent(TEvent% ev, List<__CallbackFunctionInfo>^* pfuncs)
	{
		for (int i = 0; i < 6; i++)
		{
			auto funcs = pfuncs[i];
			if (funcs == nullptr)
				continue;
			for each (auto func in funcs)
			{
				int callingmode = IS_REF | (func.Item2 ? IS_IGNORECANCELLED : 0) | (func.Item4 ? IS_INSTANCE : 0);

				try
				{
					switch (callingmode)
					{
					case IS_REF:

						((void(*)(TEvent%))(void*)func.Item1)(ev);
						break;

					case IS_INSTANCE_AND_REF:

						((void(*)(Object^, TEvent%))(void*)func.Item1)(System::Activator::CreateInstance(func.Item5), ev);
						break;

					case IS_REF_AND_IGNORECANCELLED:

						if (!ev->IsCancelled)
							((void(*)(TEvent%))(void*)func.Item1)(ev);
						break;

					case IS_INSTANCE_AND_REF_AND_IGNORECANCELLED:
						if (!ev->IsCancelled)
							((void(*)(Object^, TEvent%))(void*)func.Item1)(System::Activator::CreateInstance(func.Item5), ev);
						break;
					}
				}
				catch (Exception^ ex)
				{
					lastExceptions->Enqueue(ex);
				}
			}
		}
		return EventCode::SUCCESS;
	}



	generic<typename TEvent> where TEvent : IEvent
		inline EventManager::__EventId EventManager::GetEventId()
	{
		return eventIds[TEvent::typeid];
	}



	inline void NativeEventIsCancelledManager::set(bool isCancelled)
	{
		current = isCancelled;
	}

	inline bool NativeEventIsCancelledManager::get()
	{
		return current;
	}

	//inline void NativeEventIsCancelledManager::add( bool isCancelled)
	//{
	//	IsCancelledData.Add(hashcode, isCancelled);
	//}

	//inline void NativeEventIsCancelledManager::remove(int hashcode)
	//{
	//	IsCancelledData.Remove(hashcode);
	//}

	inline void EventBase::Call()
	{
		EventManager::CallEvent(this);
	}

	inline array<Exception^>^ EventManager::GetLastCallingExceptions()
	{
		return lastExceptions->ToArray();
	}
}
