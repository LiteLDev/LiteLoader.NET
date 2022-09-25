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

	public ref class Ahook abstract
	{
	internal:
		static List<System::Delegate^> HookedFunctions;

	public:
		generic<typename T, typename TDelegate>
		where TDelegate : System::Delegate
		where T : AHookBase<TDelegate>, gcnew()
			static void RegisterHook();
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
		if (add == 0)
			throw gcnew System::NullReferenceException;

		auto instance = gcnew T();
		auto hookFunc = instance->Hook;

		if (hookFunc == nullptr)
			throw gcnew System::NullReferenceException;

		GC::KeepAlive(instance->Hook);
		GCHandle::Alloc(instance->Hook);

		auto pHook = (void*)Marshal::GetFunctionPointerForDelegate(hookFunc);

		HookedFunctions.Add(hookFunc);

		void* pOriginal = nullptr;

		::THookRegister(add, pHook, (void**)&pOriginal);
		if (pOriginal == nullptr)
			throw gcnew LLNET::Core::HookFailedException;

		instance->_original = (TDelegate)Marshal::GetDelegateForFunctionPointer<TDelegate>(IntPtr(pOriginal));
	}
}