#pragma once

#include <HookAPI.h>

#include <LiteLoader.NET/Header/Hook/HookSymbolAttribute.hpp>
#include "HookHelper.hpp"
#include <LiteLoader.NET/Main/PluginOwnData.hpp>

namespace LiteLoader::Hook
{
	generic<typename TDelegate> where TDelegate : System::Delegate
		public ref class THookBase abstract
	{
	internal:
		TDelegate _original;

	public:
		property TDelegate Hook
		{
		public:
			virtual TDelegate get() abstract;
		};

	public:
		property TDelegate Original
		{
			TDelegate get()
			{
				return _original;
			};
		};
	};

	using namespace System::Reflection;

	public ref class Thook __static
	{
	internal:
		static List<System::Delegate^> HookedFunctions;

	public:
		generic<typename T, typename TDelegate>
		where TDelegate : System::Delegate
		where T : THookBase<TDelegate>, gcnew()
			static void RegisterHook();

		generic<typename TDelegate>
		where TDelegate: System::Delegate
		static TDelegate HookFunction(String^ symbol, TDelegate newFunc);
	};



	generic<typename T, typename TDelegate>
	where TDelegate : System::Delegate
	where T : THookBase<TDelegate>, gcnew()
		inline void Thook::RegisterHook()
	{
		auto hookType = T::typeid;
		auto hookAttributes = hookType->GetCustomAttributes(HookSymbolAttribute::typeid, false);

		if (hookAttributes == nullptr || hookAttributes->Length == 0)
			throw gcnew System::NullReferenceException;

		auto sym = static_cast<HookSymbolAttribute^>(hookAttributes[0])->Sym;

		auto instance = gcnew T();

		instance->_original = HookHelper::_hookFunction(IntPtr(CALLING_MODULE), sym, instance->Hook);
	}

	generic<typename TDelegate>
	inline TDelegate Thook::HookFunction(String^ symbol, TDelegate newFunc)
	{
		return HookHelper::_hookFunction(IntPtr(CALLING_MODULE), symbol, newFunc);
	}
}