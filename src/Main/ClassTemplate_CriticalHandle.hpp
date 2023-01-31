#pragma once
#include "DotNETGlobal.hpp"
#include "ClassTemplateDecl.hpp"
#include <src/Tools/ClassTemplateHelper.hpp>


namespace LiteLoader::NET::Internal
{
    template <typename REFCLASS, typename NATIVECLASS, bool IsAbstract>
    public ref class ClassTemplate<REFCLASS, NATIVECLASS, IsAbstract, true>
        abstract : CriticalHandle, _Select_Interface<REFCLASS, IsAbstract>::type
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
        virtual bool ReleaseHandle() override sealed
        {
            if (ownsNativeInstance)
                delete reinterpret_cast<NATIVECLASS*>(static_cast<void*>(handle));

            return true;
        }

    public:
        ClassTemplate()
            : ownsNativeInstance(false)
            , CriticalHandle(nint_t::Zero)
        {
        }

    public:
        ClassTemplate(nint_t p)
            : ownsNativeInstance(false)
            , CriticalHandle(p)
        {
        }

        ClassTemplate(nint_t p, bool ownsNativeInstance)
            : ownsNativeInstance(ownsNativeInstance)
            , CriticalHandle(p)
        {
        }

        ClassTemplate(NATIVECLASS* p, bool ownsNativeInstance)
            : ownsNativeInstance(ownsNativeInstance)
            , CriticalHandle(nint_t(p))
        {
        }

        ClassTemplate(NATIVECLASS* p)
            : ownsNativeInstance(false)
            , CriticalHandle(nint_t(p))
        {
        }

        ClassTemplate(void* p, bool ownsNativeInstance)
            : ownsNativeInstance(ownsNativeInstance)
            , CriticalHandle(nint_t(p))
        {
        }

        ClassTemplate(void* p)
            : ownsNativeInstance(false)
            , CriticalHandle(nint_t(p))
        {
        }

        ClassTemplate(NATIVECLASS& r)
            : ownsNativeInstance(true)
            , CriticalHandle(nint_t(new NATIVECLASS((NATIVECLASS&)r)))
        {
        }

        ClassTemplate(NATIVECLASS&& m)
            : ownsNativeInstance(true)
            , CriticalHandle(nint_t(new NATIVECLASS(m)))
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
            ResetPointer(reinterpret_cast<NATIVECLASS*>(ptr.ToPointer()), ownsInstance);
        }
        virtual size_t GetClassSize()
        {
            return NativeClassSize;
        }
    };
}