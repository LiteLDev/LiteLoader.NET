#pragma once

#include <HookAPI.h>

#include <LiteLoader.NET/Header/Hook/HookSymbolAttribute.hpp>

namespace LLNET::Hook
{
	generic<typename TDelegate> where TDelegate : System::Delegate
		public ref class AHookBase abstract
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

	public ref class Ahook sealed
	{
	internal:
		static List<System::Delegate^> HookedFunctions;

	public:
		generic<typename T, typename TDelegate>
		where TDelegate : System::Delegate
		where T : AHookBase<TDelegate>, gcnew()
			static void RegisterHook();

		generic<typename TDelegate> where TDelegate : System::Delegate
			static TDelegate HookFunction(void* address, TDelegate newFunc);

		generic<typename TDelegate> where TDelegate : System::Delegate
			static TDelegate HookFunction(intptr_t address, TDelegate newFunc);
	};



	generic<typename T, typename TDelegate>
	where TDelegate : System::Delegate
	where T : AHookBase<TDelegate>, gcnew()
		inline void Ahook::RegisterHook()
	{
		auto hookType = T::typeid;
		auto hookAttributes = hookType->GetCustomAttributes(HookSymbolAttribute::typeid, false);

		if (hookAttributes == nullptr || hookAttributes->Length == 0)
			throw gcnew System::NullReferenceException;

		auto add = static_cast<HookSymbolAttribute^>(hookAttributes[0])->Add;
		auto instance = gcnew T();

		instance->_original = HookFunction(add, instance->Hook);
	}



	generic<typename TDelegate>
	inline TDelegate Ahook::HookFunction(void* address, TDelegate newFunc)
	{
		NULL_ARG_CHEEK(newFunc);

		if (address == nullptr)
			throw gcnew System::ArgumentNullException("address", "Cannot be null");

		GC::KeepAlive(newFunc);
		GCHandle::Alloc(newFunc);

		auto pHook = (void*)Marshal::GetFunctionPointerForDelegate(newFunc);

		HookedFunctions.Add(newFunc);

		void* pOriginal = nullptr;

		::THookRegister(address, pHook, (void**)&pOriginal);

		if (pOriginal == nullptr)
			throw gcnew LLNET::Core::HookFailedException;

		return (TDelegate)Marshal::GetDelegateForFunctionPointer<TDelegate>(IntPtr(pOriginal));
	}

	generic<typename TDelegate>
	inline TDelegate Ahook::HookFunction(intptr_t address, TDelegate newFunc)
	{
		return HookFunction((void*)address, newFunc);
	}
}