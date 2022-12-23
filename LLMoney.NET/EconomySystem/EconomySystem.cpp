#include "EconomySystem.hpp"

using namespace LiteLoader;

money_t LLMoney::EconomySystem::GetMoney(_xuid_t player)
{
	if (dynamicSymbolsMap.LLMoneyGet)
		return dynamicSymbolsMap.LLMoneyGet(marshalString(player));
	else
	{
		economicLogger->warn->WriteLine("API money.getMoney have not been loaded!");
		return 0;
	}
}

bool LLMoney::EconomySystem::SetMoney(_xuid_t player, money_t money)
{
	if (dynamicSymbolsMap.LLMoneySet)
		return dynamicSymbolsMap.LLMoneySet(marshalString(player), money);
	else
	{
		economicLogger->warn->WriteLine("API money.setMoney have not been loaded!");
		return false;
	}
}

bool LLMoney::EconomySystem::AddMoney(_xuid_t player, money_t money)
{
	if (dynamicSymbolsMap.LLMoneyAdd)
		return dynamicSymbolsMap.LLMoneyAdd(marshalString(player), money);
	else
	{
		economicLogger->warn->WriteLine("API money.addMoney have not been loaded!");
		return false;
	}
}

bool LLMoney::EconomySystem::ReduceMoney(_xuid_t player, money_t money)
{
	if (dynamicSymbolsMap.LLMoneyReduce)
		return dynamicSymbolsMap.LLMoneyReduce(marshalString(player), money);
	else
	{
		economicLogger->warn->WriteLine("API money.reduceMoney have not been loaded!");
		return false;
	}
}

bool LLMoney::EconomySystem::TransMoney(_xuid_t player1, _xuid_t player2, money_t money, String^ notes)
{
	if (dynamicSymbolsMap.LLMoneyTrans)
		return dynamicSymbolsMap.LLMoneyTrans(marshalString(player1), marshalString(player2), money, marshalString(notes));
	else
	{
		economicLogger->warn->WriteLine("API money.transMoney have not been loaded!");
		return false;
	}
}

String^ LLMoney::EconomySystem::GetMoneyHist(_xuid_t player, int time)
{
	if (dynamicSymbolsMap.LLMoneyGetHist)
		return marshalString(dynamicSymbolsMap.LLMoneyGetHist(marshalString(player), time));
	else
	{
		economicLogger->warn->WriteLine("API money.getTransHist have not been loaded!");
		return "";
	}
}

bool LLMoney::EconomySystem::ClearMoneyHist(int time)
{
	if (dynamicSymbolsMap.LLMoneyClearHist)
	{
		dynamicSymbolsMap.LLMoneyClearHist(time);
		return true;
	}
	else
	{
		economicLogger->warn->WriteLine("API money.clearHist have not been loaded!");
		return false;
	}
}

bool LLMoney::EconomySystem::_moneyBeforeEventCallback(LLMoneyEvent type, xuid_t from, xuid_t to, money_t value)
{
	auto ev = gcnew EconomySystemBeforeEvent(
		LLMoneyEventType(type),
		marshalString(from),
		marshalString(to),
		value);

	EventManager::CallEvent(ev);

	delete ev;
	return true;
}

bool LLMoney::EconomySystem::_moneyEventCallback(LLMoneyEvent type, xuid_t from, xuid_t to, money_t value)
{
	auto ev = gcnew EconomySystemEvent(
		LLMoneyEventType(type),
		marshalString(from),
		marshalString(to),
		value);

	EventManager::CallEvent(ev);

	delete ev;
	return true;
}
