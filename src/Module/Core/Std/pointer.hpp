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
        static ICppStdClass<T>::_Set_native_pointer_fptr set_native_pointer
            = ICppStdClass<T>::set_native_pointer;
        static ICppStdClass<T>::_Dtor_fptr dtor
            = ICppStdClass<T>::dtor;
        static bool isValueType = ICppStdClass<T>::isValueType;
        static size_t type_size = ICppStdClass<T>::elementTypeSize;

    private:
        nint_t pInstance;

    public:

        literal size_t NativeClassSize = sizeof(intptr_t);

        //IConstructableCppClass
        property nint_t Intptr
        {
            virtual nint_t get()
            {
                return nint_t(pInstance);
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

            if (!isValueType)
            {
                auto ret = gcnew T;
                set_native_pointer(ret, Unsafe::Read<nint_t>(_Ptr), false);
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

            if (!isValueType)
            {
                uint32_t _Length = *reinterpret_cast<uint32_t*>(_Ptrfirst - sizeof(int32_t));
                if (_Length + 39 <= _Length)
                    throw gcnew LiteLoader::NET::MemoryCorruptedException(String::Format("address:{0}.", (intptr_t)_Ptrfirst));

                auto _Ptrend = _Ptrfirst + _Length * type_size;

                auto ret = gcnew T;
                for (auto p = _Ptrfirst; p < _Ptrend; p += type_size)
                {
                    set_native_pointer(ret, nint_t(p), false);
                    dtor(ret);
                }
            }

            ::operator delete[](_Ptrfirst);
        }

        /// <summary>
        /// C++ operator*()
        /// </summary>
        T Dereference()
        {
            auto ret = gcnew T;
            set_native_pointer(ret, Unsafe::Read<nint_t>(pInstance.ToPointer()), false);
            return ret;
        }
    };
}