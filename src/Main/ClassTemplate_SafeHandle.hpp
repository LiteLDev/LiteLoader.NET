#pragma once

#include "DotNETGlobal.hpp"
#include "ClassTemplateDecl.hpp"
#include <src/Tools/ClassTemplateHelper.hpp>
#include <src/Header/Core/ICppClass.hpp>

namespace LiteLoader::NET
{
    using System::Runtime::InteropServices::SafeHandle;

    template <typename REFCLASS, typename NATIVECLASS>
    public ref class ClassTemplate<REFCLASS, NATIVECLASS, false>
        abstract : SafeHandle, ICppClass
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
                handle = IntPtr(value);
            }
        }

        property IntPtr Intptr
        {
            virtual IntPtr get()
            {
                return handle;
            }
        }

        property bool OwnsNativeInstance
        {
        public:
            bool get()
            {
                return ownsNativeInstance;
            }

        protected:
            void set(bool value)
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
                if (handle == IntPtr::Zero)
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
            , SafeHandle(IntPtr::Zero, true)
        {
        }

    public:
        ClassTemplate(System::IntPtr p)
            : ownsNativeInstance(false)
            , SafeHandle(p, true)
        {
        }

        ClassTemplate(System::IntPtr p, bool ownsNativeInstance)
            : ownsNativeInstance(ownsNativeInstance)
            , SafeHandle(p, true)
        {
        }

        ClassTemplate(NATIVECLASS* p, bool ownsNativeInstance)
            : ownsNativeInstance(ownsNativeInstance)
            , SafeHandle(IntPtr(p), true)
        {
        }

        ClassTemplate(NATIVECLASS* p)
            : ownsNativeInstance(false)
            , SafeHandle(IntPtr(p), true)
        {
        }

        ClassTemplate(void* p, bool ownsNativeInstance)
            : ownsNativeInstance(ownsNativeInstance)
            , SafeHandle(IntPtr(p), true)
        {
        }

        ClassTemplate(void* p)
            : ownsNativeInstance(false)
            , SafeHandle(IntPtr(p), true)
        {
        }

        ClassTemplate(NATIVECLASS& r)
            : ownsNativeInstance(true)
            , SafeHandle(IntPtr(new NATIVECLASS((NATIVECLASS&)r)), true)
        {
        }

        ClassTemplate(NATIVECLASS&& m)
            : ownsNativeInstance(true)
            , SafeHandle(IntPtr(new NATIVECLASS(m)), true)
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
            handle = IntPtr::Zero;
            ownsNativeInstance = false;
            return ret;
        }
        virtual void ResetPointer(NATIVECLASS* p)
        {
            if (ownsNativeInstance)
                delete reinterpret_cast<NATIVECLASS*>(static_cast<void*>(handle));
            handle = IntPtr(p);
            ownsNativeInstance = false;
        }
        virtual void ResetPointer(NATIVECLASS* p, bool ownsNativeInstance)
        {
            if (this->ownsNativeInstance)
                delete reinterpret_cast<NATIVECLASS*>(static_cast<void*>(handle));
            handle = IntPtr(p);
            this->ownsNativeInstance = ownsNativeInstance;
        }
        virtual void Destructor(void* ptr)
        {
            reinterpret_cast<NATIVECLASS*>(ptr)->~NATIVECLASS();
        }
    };
}
