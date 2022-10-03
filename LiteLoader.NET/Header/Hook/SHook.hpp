#pragma once

#include <HookAPI.h>

#include <LiteLoader.NET/Header/Hook/HookSymbolAttribute.hpp>
#include "IHookBase.hpp"

namespace LLNET::Hook
{
	generic<typename TDelegate> where TDelegate : System::Delegate
		public ref class SHookBase abstract : IHookBase
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

	public ref class Shook __static
	{
	internal:
		static List<System::Delegate^> HookedFunctions;

	public:
		generic<typename T, typename TDelegate>
		where TDelegate : System::Delegate
		where T : SHookBase<TDelegate>, gcnew()
			static void RegisterHook();

		generic<typename TDelegate> where TDelegate : System::Delegate
			static TDelegate HookFunction(String^ signature, TDelegate newFunc);
	};



	generic<typename T, typename TDelegate>
	where TDelegate : System::Delegate
	where T : SHookBase<TDelegate>, gcnew()
		inline void Shook::RegisterHook()
	{
		auto hookType = T::typeid;
		auto hookAttributes = hookType->GetCustomAttributes(HookSymbolAttribute::typeid, false);

		if (hookAttributes == nullptr || hookAttributes->Length == 0)
			throw gcnew System::NullReferenceException;

		auto sig = static_cast<HookSymbolAttribute^>(hookAttributes[0])->Sym;
		auto instance = gcnew T();

		instance->_original = HookFunction(sig, instance->Hook);
	}

	generic<typename TDelegate>
	inline TDelegate Shook::HookFunction(String^ signature, TDelegate newFunc)
	{
		NULL_ARG_CHEEK(newFunc);
		NULL_ARG_CHEEK(signature);

		GC::KeepAlive(newFunc);
		GCHandle::Alloc(newFunc);

		auto pHook = (void*)Marshal::GetFunctionPointerForDelegate(newFunc);

		HookedFunctions.Add(newFunc);

		void* pOriginal = nullptr;

		::THookRegister((void*)ll::hook::findSig(marshalString(signature).c_str()), pHook, (void**)&pOriginal);

		if (pOriginal == nullptr)
			throw gcnew LLNET::Core::HookFailedException;

		return (TDelegate)Marshal::GetDelegateForFunctionPointer<TDelegate>(IntPtr(pOriginal));
	}
}