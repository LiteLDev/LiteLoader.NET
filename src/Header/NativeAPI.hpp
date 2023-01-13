#pragma once
//#define private public
//#define protected public
#include <src/Main/DotNETGlobal.hpp>
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
                throw gcnew System::OutOfMemoryException("std::bad_alloc::what():" + marshalString(ex.what()));
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

        //static void* TestVector(...array<int>^ ints)
        //{
        //    auto ret = new std::vector<int>;
        //    /*auto iter = ret->begin();

        //    constexpr auto size = sizeof(std::vector<int>);
        //    constexpr auto size = sizeof(ret->_Mypair);
        //    constexpr auto size = sizeof(ret->_Mypair._Myval2);
        //    constexpr auto size = sizeof(ret->_Mypair._Myval2._Myend);
        //    constexpr auto size = sizeof(ret->_Mypair._Myval2._Myfirst);
        //    constexpr auto size = sizeof(ret->_Mypair._Myval2._Mylast);

        //    constexpr auto size = sizeof(iter._Ptr);

        //    constexpr auto offset = offsetof(std::vector<int>, _Mypair);
        //    constexpr auto offset = offsetof(decltype(ret->_Mypair), _Myval2);
        //    constexpr auto offset = offsetof(decltype(ret->_Mypair._Myval2), _Myfirst);
        //    constexpr auto offset = offsetof(decltype(ret->_Mypair._Myval2), _Mylast);
        //    constexpr auto offset = offsetof(decltype(ret->_Mypair._Myval2), _Myend);

        //    constexpr auto offset = offsetof(decltype(iter), _Ptr);*/

        //    for each (auto var in ints)
        //    {
        //        ret->emplace_back(var);
        //    }
        //    return ret;
        //}
    };
}