#pragma once

#include "DotNETGlobal.hpp"
#include "ClassTemplateDecl.hpp"
#include <src/Tools/ClassTemplateHelper.hpp>

namespace LiteLoader::NET::Internal
{
    template <typename REFCLASS, typename NATIVECLASS, bool IsAbstract>
    public ref class ClassTemplate<REFCLASS, NATIVECLASS, IsAbstract, false>
        abstract : SafeHandle, _Select_Interface<REFCLASS, IsAbstract>::type
    {
    protected:
        bool ownsNativeInstance;

    public:
        property NATIVECLASS* NativePtr
        {
        public:
            NATIVECLASS* get()
            {
                return reinterpret_cast<NATIVECLASS*>(static_cast<void*>(handle));
            }

        protected:
            void set(NATIVECLASS* value)
            {
                handle = nint_t(value);
            }
        }

        property nint_t NativePointer
        {
        public:
            virtual nint_t get()
            {
                return handle;
            }
            virtual void set(nint_t value)
            {
                handle = value;
            }
        }

        property bool OwnsNativeInstance
        {
        public:
            virtual bool get()
            {
                return ownsNativeInstance;
            }
            virtual void set(bool value)
            {
                ownsNativeInstance = value;
            }
        }

        literal size_t NativeClassSize = sizeof(NATIVECLASS);

    public:
        property bool IsInvalid
        {
            virtual bool get() override sealed
            {
                if (handle == nint_t::Zero)
                    return true;

                return false;
            }
        }
    protected:
        virtual bool ReleaseHandle() override
        {
            if (ownsNativeInstance)
                delete reinterpret_cast<NATIVECLASS*>(static_cast<void*>(handle));

            return true;
        }

    public:
        ClassTemplate()
            : ownsNativeInstance(false)
            , SafeHandle(nint_t::Zero, true)
        {
        }

    public:
        ClassTemplate(nint_t p)
            : ownsNativeInstance(false)
            , SafeHandle(p, true)
        {
        }

        ClassTemplate(nint_t p, bool ownsNativeInstance)
            : ownsNativeInstance(ownsNativeInstance)
            , SafeHandle(p, true)
        {
        }

        ClassTemplate(NATIVECLASS* p, bool ownsNativeInstance)
            : ownsNativeInstance(ownsNativeInstance)
            , SafeHandle(nint_t(p), true)
        {
        }

        ClassTemplate(NATIVECLASS* p)
            : ownsNativeInstance(false)
            , SafeHandle(nint_t(p), true)
        {
        }

        ClassTemplate(void* p, bool ownsNativeInstance)
            : ownsNativeInstance(ownsNativeInstance)
            , SafeHandle(nint_t(p), true)
        {
        }

        ClassTemplate(void* p)
            : ownsNativeInstance(false)
            , SafeHandle(nint_t(p), true)
        {
        }

        ClassTemplate(NATIVECLASS& r)
            : ownsNativeInstance(true)
            , SafeHandle(nint_t(new NATIVECLASS((NATIVECLASS&)r)), true)
        {
        }

        ClassTemplate(NATIVECLASS&& m)
            : ownsNativeInstance(true)
            , SafeHandle(nint_t(new NATIVECLASS(m)), true)
        {
        }

    internal:
        operator NATIVECLASS& ()
        {
            return *reinterpret_cast<NATIVECLASS*>(static_cast<void*>(handle));
        }
        operator NATIVECLASS* ()
        {
            return reinterpret_cast<NATIVECLASS*>(static_cast<void*>(handle));
        }

    public:
        virtual NATIVECLASS* ReleasePointer()
        {
            auto ret = reinterpret_cast<NATIVECLASS*>(static_cast<void*>(handle));
            handle = nint_t::Zero;
            ownsNativeInstance = false;
            return ret;
        }
        virtual void ResetPointer(NATIVECLASS* p)
        {
            if (ownsNativeInstance)
                delete reinterpret_cast<NATIVECLASS*>(static_cast<void*>(handle));
            handle = nint_t(p);
            ownsNativeInstance = false;
        }
        virtual void ResetPointer(NATIVECLASS* p, bool ownsNativeInstance)
        {
            if (this->ownsNativeInstance)
                delete reinterpret_cast<NATIVECLASS*>(static_cast<void*>(handle));
            handle = nint_t(p);
            this->ownsNativeInstance = ownsNativeInstance;
        }
        virtual void Destruct()
        {
            reinterpret_cast<NATIVECLASS*>(handle.ToPointer())->~NATIVECLASS();
        }
        virtual void SetNativePointer(nint_t ptr, bool ownsInstance)
        {
            handle = nint_t(ptr);
            this->ownsNativeInstance = ownsInstance;
        }
        virtual REFCLASS^ ConstructInstance(nint_t ptr, bool ownsInstance)
        {
            if constexpr (IsAbstract)
                throw gcnew System::InvalidOperationException(String::Format("<{0}> cannot be constructed which is an abstract class."));
            else
                return gcnew REFCLASS(ptr, ownsInstance);
        }
        virtual size_t GetClassSize()
        {
            return NativeClassSize;
        }
    };
}
