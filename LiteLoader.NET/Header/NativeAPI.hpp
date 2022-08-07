#pragma once
#include <LiteLoader.NET/Main/.NETGlobal.hpp>
#include <Windows.h>

#pragma unmanaged

typedef DWORD EXCEPTION_CODE;

extern __declspec(noinline) EXCEPTION_CODE _try_catch(void(*pfunc)());

#pragma managed


namespace LLNET::Hook
{

	public ref class NativeAPI abstract
	{
	public:
		static bool TryCatch(System::Action^ act, [Out] System::Exception^% exc)
		{
			exc = nullptr;
			auto pfunc = reinterpret_cast<void(*)()>((void*)act->Method->MethodHandle.GetFunctionPointer());

			auto code = _try_catch(pfunc);

			if (!code)
			{
				return true;
			}
			else
			{
				exc = gcnew System::Exception("0x" + System::Convert::ToString((int)code, 16));
				return false;
			}
		}
	};
}