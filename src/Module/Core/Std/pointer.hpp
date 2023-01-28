#pragma once
#include <src/Main/DotNETGlobal.hpp>
#include <src/Module/Core/ICppClass.hpp>
#include "ICppStdClass.hpp"

namespace LiteLoader::NET
{
    using LiteLoader::NET::Std::Internal::ICppStdClass;

    generic<typename T> where T:IConstructableCppClass, gcnew()

        public value class pointer : IConstructableCppClass
    {
    private:
        static bool isValueType = ICppStdClass<T>::isValueType;
        static size_t type_size = ICppStdClass<T>::type_size;

    private:
        nint_t pInstance;

    public:
        static operator pointer(T val)
        {
            auto ret = pointer();
            ret.pInstance = val->Intptr;
            return ret;
        }
        static operator T(pointer ptr)
        {
            return ptr.Dereference();
        }

    public:

        literal size_t NativeClassSize = sizeof(intptr_t);

        //IConstructableCppClass
        property nint_t Intptr
        {
            virtual nint_t get()
            {
                return pInstance;
            }
            virtual void set(nint_t value)
            {
                pInstance = value;
            }
        }
        property bool OwnsNativeInstance
        {
        public:
            virtual bool get()
            {
                return true;
            }
            virtual void set(bool value)
            {
                return;
            }
        }

        virtual void Destruct()
        {
        }
        virtual void SetNativePointer(nint_t ptr, bool ownsInstance)
        {
            pInstance = ptr;
        }

        virtual size_t GetClassSize()
        {
            return NativeClassSize;
        }

    public:

        /// <summary>
        /// C++ operator delete
        /// </summary>
        void Delete()
        {
            auto _Ptr = pInstance.ToPointer();

            if (isValueType)
            {
                if (ICppStdClass<T>::isICppClass)
                {
                    auto ret = T();
                    ICppStdClass<T>::_Tv_fptr.set_native_pointer(&ret, Unsafe::Read<nint_t>(_Ptr), false);
                    ret->Destruct();
                }
            }
            else
            {
                auto ret = gcnew T;
                ICppStdClass<T>::_Tr_fptr.set_native_pointer(ret, Unsafe::Read<nint_t>(_Ptr), false);
                ret->Destruct();
            }

            ::operator delete(_Ptr);
        }

        /// <summary>
        /// C++ operator delete[]
        /// </summary>
        void DeleteArray()
        {
            auto _Ptrfirst = static_cast<byte_t*>(pInstance.ToPointer());

            if (ICppStdClass<T>::isICppClass)
            {
                uint32_t _Length = *reinterpret_cast<uint32_t*>(_Ptrfirst - sizeof(int32_t));
                if (_Length + 39 <= _Length)
                    throw gcnew LiteLoader::NET::MemoryCorruptedException(String::Format("address:{0}.", (intptr_t)_Ptrfirst));

                auto _Ptrend = _Ptrfirst + _Length * type_size;

                if (isValueType)
                {
                    auto ret = T();
                    for (auto p = _Ptrfirst; p < _Ptrend; p += type_size)
                    {
                        ICppStdClass<T>::_Tv_fptr.set_native_pointer(&ret, nint_t(p), false);
                        ICppStdClass<T>::_Tv_fptr.dtor(&ret);
                    }
                }
                else
                {
                    auto ret = gcnew T;
                    for (auto p = _Ptrfirst; p < _Ptrend; p += type_size)
                    {
                        ICppStdClass<T>::_Tr_fptr.set_native_pointer(ret, nint_t(p), false);
                        ICppStdClass<T>::_Tr_fptr.dtor(ret);
                    }
                }

                ::operator delete[](_Ptrfirst);
            }
        }

        /// <summary>
        /// C++ operator*()
        /// </summary>
        T Dereference()
        {
            auto ret = gcnew T;
            ICppStdClass<T>::_Tv_fptr.set_native_pointer(&ret, Unsafe::Read<nint_t>(pInstance.ToPointer()), false);
            return ret;
        }
    };
}