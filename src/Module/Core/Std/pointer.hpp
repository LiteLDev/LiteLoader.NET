#pragma once
#include <src/Main/DotNETGlobal.hpp>
#include <src/Module/Core/ICppClass.hpp>

namespace LiteLoader::NET
{
    generic<typename T> where T:IConstructableCppClass, gcnew()

        public value class pointer : IConstructableCppClass
    {
    private:
        static void(__clrcall* set_native_pointer)(Object^, nint_t, bool);

        static pointer()
        {
            set_native_pointer = reinterpret_cast<void(__clrcall*)(Object^, nint_t, bool)>(
                typeof(T)
                ->GetMethod("SetNativePointer", PackArray(typeof(nint_t), typeof(bool)))
                ->MethodHandle
                .GetFunctionPointer()
                .ToPointer());

            if (set_native_pointer == nullptr)
                throw gcnew LiteLoader::NET::InvalidTypeException(typeof(T)->FullName + L',' + "missing Method 'SetNativePointer'");
        }

    private:
        nint_t pInstance;

    public:
        T Deference()
        {
            auto ret = gcnew T;
            set_native_pointer(ret, Unsafe::Read<nint_t>(pInstance.ToPointer()), false);
            return ret;
        }

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
            return sizeof(intptr_t);
        }
    };
}