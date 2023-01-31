#pragma once
#define __ctor(RefClass, NativeClass)                   \
    RefClass(nint_t p)                                  \
        : ClassTemplate(p)                              \
    {                                                   \
    }                                                   \
    RefClass(nint_t p, bool ownsNativeInstance)         \
        : ClassTemplate(p, ownsNativeInstance)          \
    {                                                   \
    }                                                   \
    RefClass(NativeClass* p)                            \
        : ClassTemplate(p)                              \
    {                                                   \
    }                                                   \
    RefClass(NativeClass* p, bool ownsNativeInstance)   \
        : ClassTemplate(p, ownsNativeInstance)          \
    {                                                   \
    }                                                   \
    RefClass(void* p)                                   \
        : ClassTemplate(p)                              \
    {                                                   \
    }                                                   \
    RefClass(void* p, bool ownsNativeInstance)          \
        : ClassTemplate(p, ownsNativeInstance)          \
    {                                                   \
    }

#define __ctor_default(RefClass, NativeClass)   \
    RefClass()                                  \
    : ClassTemplate((void*)nullptr, false)      \
    {                                           \
    }

#define __ctor_copy(RefClass, NativeClass) \
    RefClass(NativeClass& r)               \
        : ClassTemplate(r)                 \
    {                                      \
    }

#define __ctor_move(RefClass, NativeClass) \
    RefClass(NativeClass&& m)              \
        : ClassTemplate(m)                 \
    {                                      \
    }

#define __ctor_all(RefClass, NativeClass) \
    __ctor(RefClass, NativeClass);        \
    internal:                             \
    __ctor_copy(RefClass, NativeClass);   \
    __ctor_move(RefClass, NativeClass);   \
                                          \
public:


#define __ctor_base(RefClass, NativeClass, BaseClass)                   \
    RefClass(nint_t p)                                                  \
        : BaseClass(p)                                                  \
    {                                                                   \
    }                                                                   \
    RefClass(nint_t p, bool ownsNativeInstance)                         \
        : BaseClass(p, ownsNativeInstance)                              \
    {                                                                   \
    }                                                                   \
    RefClass(NativeClass* p)                                            \
        : BaseClass(p)                                                  \
    {                                                                   \
    }                                                                   \
    RefClass(NativeClass* p, bool ownsNativeInstance)                   \
        : BaseClass(p, ownsNativeInstance)                              \
    {                                                                   \
    }                                                                   \
    RefClass(void* p)                                                   \
        : BaseClass(p)                                                  \
    {                                                                   \
    }                                                                   \
    RefClass(void* p, bool ownsNativeInstance)                          \
        : BaseClass(p, ownsNativeInstance)                              \
    {                                                                   \
    }                                                                   \
    property NativeClass* NativePtr                                     \
    {                                                                   \
    public:                                                             \
        NativeClass* get()                                              \
        {                                                               \
            return static_cast<NativeClass*>(BaseClass::NativePtr);     \
        }                                                               \
                                                                        \
    protected:                                                          \
        void set(NativeClass* value)                                    \
        {                                                               \
            BaseClass::NativePtr = value;                               \
        }                                                               \
    }                                                                   \
    virtual void Destruct() override                                    \
    {                                                                   \
        reinterpret_cast<NativeClass*>(handle.ToPointer())->~RefClass();\
    }                                                                   \
    literal size_t NativeClassSize = sizeof(NativeClass);


#define __ctor_default_base(RefClass, NativeClass, BaseClass)   \
    RefClass()                                                  \
        : BaseClass()                                           \
    {                                                           \
    }

#define __ctor_copy_base(RefClass, NativeClass, BaseClass) \
    RefClass(NativeClass& r)                               \
        : BaseClass(r)                                     \
    {                                                      \
    }

#define __ctor_move_base(RefClass, NativeClass, BaseClass) \
    RefClass(NativeClass&& m)                              \
        : BaseClass(m)                                     \
    {                                                      \
    }

#define __ctor_all_base(RefClass, NativeClass, BaseClass) \
    __ctor_base(RefClass, NativeClass, BaseClass);        \
    internal:                                             \
    __ctor_copy_base(RefClass, NativeClass, BaseClass);   \
    __ctor_move_base(RefClass, NativeClass, BaseClass);   \
                                                          \
public:


#define __ClassTemplateAPIs(RefClass, NativeClass)                      \
    NativeClass* ReleasePointer()                                       \
    {                                                                   \
        return ClassTemplate::Release();                                \
    }                                                                   \
    void ResetPointer(NATIVECLASS const* p)()                           \
    {                                                                   \
        ClassTemplate::ResetPointer(p);                                 \
    }                                                                   \
    void ResetPointer(NATIVECLASS const* p, bool ownsNativeInstance)    \
    {                                                                   \
        ClassTemplate::ResetPointer(p, ownsNativeInstance);             \
    }

#using <../Modules/LiteLoader.NET.InteropServices.dll>

namespace LiteLoader::NET::Internal
{
    using System::Runtime::InteropServices::SafeHandle;
    using System::Runtime::InteropServices::CriticalHandle;
    using LiteLoader::NET::InteropServices::IConstructableCppClass;
    using LiteLoader::NET::InteropServices::IAbstractCppClass;

    template<typename _Ref_type, bool _Is_abstract>
    struct _Selected_interface;

    template<typename _Ref_type>
    struct _Selected_interface<_Ref_type, false> {
        using _Interface = IConstructableCppClass<_Ref_type^>;
    };

    template<typename _Ref_type>
    struct _Selected_interface<_Ref_type, true> {
        using _Interface = IAbstractCppClass;
    };

    template<typename _Ref_type, bool _Is_abstract>
    struct _Select_Interface {
        using type = typename _Selected_interface<_Ref_type, _Is_abstract>::_Interface;
    };
}