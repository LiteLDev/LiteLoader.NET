#pragma once
#include <src/Main/DotNETGlobal.hpp>
#include <src/Header/Core/ICppClass.hpp>

namespace LiteLoader::NET
{
    generic<typename T> where T:IConstructableCppClass, gcnew()

        public value class pointer : IConstructableCppClass
    {
    private:
        nint_t pInstance;

    public:
        T Deference()
        {
            auto ret = gcnew T;
            ret->SetNativePointer(Unsafe::Read<nint_t>(pInstance.ToPointer()), false);
            return ret;
        }

        // Í¨¹ý IConstructableCppClass ¼Ì³Ð
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
    };
}