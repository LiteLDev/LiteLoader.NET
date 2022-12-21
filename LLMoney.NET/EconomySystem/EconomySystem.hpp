#pragma once

#include <LLMoney.NET/Tools/Using.hpp>
#include <LLMoney.NET/Tools/StringHelper.hpp>
#include <string>
#include <Windows.h>


#pragma unmanaged

typedef long long money_t;
typedef std::string xuid_t;

enum LLMoneyEvent
{
	Set, Add, Reduce, Trans
};
typedef bool (*LLMoneyCallback)(LLMoneyEvent type, xuid_t from, xuid_t to, money_t value);

typedef money_t(*LLMoneyGet_T)(xuid_t);
typedef std::string(*LLMoneyGetHist_T)(xuid_t, int);
typedef bool (*LLMoneyTrans_T)(xuid_t, xuid_t, money_t, std::string const&);
typedef bool (*LLMoneySet_T)(xuid_t, money_t);
typedef bool (*LLMoneyAdd_T)(xuid_t, money_t);
typedef bool (*LLMoneyReduce_T)(xuid_t, money_t);
typedef void (*LLMoneyClearHist_T)(int);

typedef void (*LLMoneyListenBeforeEvent_T)(LLMoneyCallback callback);
typedef void (*LLMoneyListenAfterEvent_T)(LLMoneyCallback callback);

struct dynamicSymbolsMap_type
{
	LLMoneyGet_T LLMoneyGet = nullptr;
	LLMoneySet_T LLMoneySet = nullptr;
	LLMoneyAdd_T LLMoneyAdd = nullptr;
	LLMoneyReduce_T LLMoneyReduce = nullptr;
	LLMoneyTrans_T LLMoneyTrans = nullptr;
	LLMoneyGetHist_T LLMoneyGetHist = nullptr;
	LLMoneyClearHist_T LLMoneyClearHist = nullptr;

	LLMoneyListenBeforeEvent_T LLMoneyListenBeforeEvent = nullptr;
	LLMoneyListenAfterEvent_T LLMoneyListenAfterEvent = nullptr;
} dynamicSymbolsMap;

#pragma managed

namespace LLMoney
{
	using LiteLoader::Logger::Logger;
	using namespace LiteLoader::Event;

	public ref class LLMoneyException :LiteLoader::NET::LiteLoaderDotNETException
	{
	public:
		LLMoneyException(String^ message)
			:LiteLoaderDotNETException(message)
		{
		}
	};

	public enum class LLMoneyEventType
	{
		Set, Add, Reduce, Trans
	};

	public ref class EconomySystemEventBase
		:EventBase
	{
	public:
		EconomySystemEventBase(LLMoneyEventType evType, String^ from, String^ to, money_t val)
			:eventType(evType), from(from), to(to), value(val)
		{
		}
		LLMoneyEventType eventType;
		String^ from;
		String^ to;
		money_t value;
	};

	public ref class EconomySystemBeforeEvent
		:EconomySystemEventBase
	{
	public:
		EconomySystemBeforeEvent(LLMoneyEventType evType, String^ from, String^ to, money_t val)
			:EconomySystemEventBase(evType, from, to, val)
		{
		}
	};

	public ref class EconomySystemEvent
		:EconomySystemEventBase
	{
	public:
		EconomySystemEvent(LLMoneyEventType evType, String^ from, String^ to, money_t val)
			:EconomySystemEventBase(evType, from, to, val)
		{
		}

	};



	public ref class EconomySystem sealed
	{
		typedef long long money_t;
		typedef String^ _xuid_t;
	public:
		static EconomySystem()
		{
			auto llmoney = LiteLoader::LLAPI::GetPlugin("LLMoney");
			if (llmoney->Handler == IntPtr::Zero)
			{
				economicLogger->warn->WriteLine("LLMoney not found!");
			}

			HMODULE h = (HMODULE)(void*)llmoney->Handler;

			dynamicSymbolsMap.LLMoneyGet = (LLMoneyGet_T)GetProcAddress(h, "LLMoneyGet");
			if (!dynamicSymbolsMap.LLMoneyGet)
				economicLogger->warn->WriteLine("Fail to load API money.getMoney!");

			dynamicSymbolsMap.LLMoneySet = (LLMoneySet_T)GetProcAddress(h, "LLMoneySet");
			if (!dynamicSymbolsMap.LLMoneySet)
				economicLogger->warn->WriteLine("Fail to load API money.setMoney!");

			dynamicSymbolsMap.LLMoneyAdd = (LLMoneyAdd_T)GetProcAddress(h, "LLMoneyAdd");
			if (!dynamicSymbolsMap.LLMoneyAdd)
				economicLogger->warn->WriteLine("Fail to load API money.addMoney!");

			dynamicSymbolsMap.LLMoneyReduce = (LLMoneyReduce_T)GetProcAddress(h, "LLMoneyReduce");
			if (!dynamicSymbolsMap.LLMoneyReduce)
				economicLogger->warn->WriteLine("Fail to load API money.reduceMoney!");

			dynamicSymbolsMap.LLMoneyTrans = (LLMoneyTrans_T)GetProcAddress(h, "LLMoneyTrans");
			if (!dynamicSymbolsMap.LLMoneyTrans)
				economicLogger->warn->WriteLine("Fail to load API money.transMoney!");

			dynamicSymbolsMap.LLMoneyGetHist = (LLMoneyGetHist_T)GetProcAddress(h, "LLMoneyGetHist");
			if (!dynamicSymbolsMap.LLMoneyGetHist)
				economicLogger->warn->WriteLine("Fail to load API money.getTransHist!");

			dynamicSymbolsMap.LLMoneyClearHist = (LLMoneyClearHist_T)GetProcAddress(h, "LLMoneyClearHist");
			if (!dynamicSymbolsMap.LLMoneyClearHist)
				economicLogger->warn->WriteLine("Fail to load API money.clearHist!");

			dynamicSymbolsMap.LLMoneyListenBeforeEvent = (LLMoneyListenBeforeEvent_T)GetProcAddress(h, "LLMoneyListenBeforeEvent");
			dynamicSymbolsMap.LLMoneyListenAfterEvent = (LLMoneyListenAfterEvent_T)GetProcAddress(h, "LLMoneyListenAfterEvent");

			if (!dynamicSymbolsMap.LLMoneyListenBeforeEvent || !dynamicSymbolsMap.LLMoneyListenAfterEvent)
			{
				economicLogger->warn->WriteLine("Fail to load API to listen money event!");
			}
			else
			{
				auto beforeEvCallback = gcnew delLLMoneyCallback(&_moneyBeforeEventCallback);
				auto evCallback = gcnew delLLMoneyCallback(&_moneyEventCallback);
				GCHandle::Alloc(beforeEvCallback);
				GCHandle::Alloc(evCallback);

				dynamicSymbolsMap.LLMoneyListenBeforeEvent(static_cast<LLMoneyCallback>(
					(void*)Marshal::GetFunctionPointerForDelegate(beforeEvCallback)));
				dynamicSymbolsMap.LLMoneyListenAfterEvent(static_cast<LLMoneyCallback>(
					(void*)Marshal::GetFunctionPointerForDelegate(evCallback)));
			}
		}

		static money_t GetMoney(_xuid_t player);
		static bool SetMoney(_xuid_t player, money_t money);
		static bool AddMoney(_xuid_t player, money_t money);
		static bool ReduceMoney(_xuid_t player, money_t money);
		static bool TransMoney(_xuid_t player1, _xuid_t player2, money_t money, String^ notes);
		static String^ GetMoneyHist(_xuid_t player, int time);
		static bool ClearMoneyHist(int time);
	internal:
		static bool _moneyBeforeEventCallback(LLMoneyEvent type, xuid_t from, xuid_t to, money_t value);
		static bool _moneyEventCallback(LLMoneyEvent type, xuid_t from, xuid_t to, money_t value);

		delegate bool delLLMoneyCallback(LLMoneyEvent type, xuid_t from, xuid_t to, money_t value);

		static Logger^ economicLogger = gcnew Logger("LLMoney.NET");
	};
}