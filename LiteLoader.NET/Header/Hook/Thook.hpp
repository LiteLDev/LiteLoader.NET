#pragma once

#include <HookAPI.h>

#include <LiteLoader.NET/Header/Hook/HookSymbolAttribute.hpp>

namespace LLNET::Hook
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

	public ref class Thook abstract
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

		instance->_original = HookFunction(sym, instance->Hook);
	}

	generic<typename TDelegate>
	inline TDelegate Thook::HookFunction(String^ symbol, TDelegate newFunc)
	{
		NULL_ARG_CHEEK(newFunc);
		NULL_ARG_CHEEK(symbol);

		GC::KeepAlive(newFunc);
		GCHandle::Alloc(newFunc);

		auto pHook = (void*)Marshal::GetFunctionPointerForDelegate(newFunc);

		HookedFunctions.Add(newFunc);

		void* pOriginal = nullptr;

		::THookRegister(marshalString(symbol).c_str(), pHook, (void**)&pOriginal);

		if (pOriginal == nullptr)
			throw gcnew LLNET::Core::HookFailedException;

		return (TDelegate)Marshal::GetDelegateForFunctionPointer<TDelegate>(IntPtr(pOriginal));
	}
}