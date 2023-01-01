#pragma once
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <Windows.h>

#pragma unmanaged

typedef DWORD EXCEPTION_CODE;

extern __declspec(noinline) EXCEPTION_CODE _try_catch(void(*pfunc)());

#pragma managed


namespace LiteLoader::Hook
{

    public ref class NativeAPI __static
    {
    public:
        static bool TryCatch(System::Action^ act, [Out] System::Exception^% exc)
        {
            exc = nullptr;
            auto pfunc = reinterpret_cast<void(*)()>(act->Method->MethodHandle.GetFunctionPointer().ToPointer());

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

        static void* operator_new(size_t size)
        {
            try
            {
                return ::operator new(size);
            }
            catch (const std::bad_alloc& ex)
            {
                throw gcnew System::OutOfMemoryException;
            }
        }

        static void operator_delete(void** ptr)
        {
            if (ptr == nullptr)
                return;

            ::operator delete(*ptr);
            *ptr = nullptr;
        }

        static void operator_delete(void* p)
        {
            ::operator delete(p);
        }
    };
}