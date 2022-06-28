#pragma once

template<typename BASE_LLNET_CLASS, typename NATIVECLASS>
public ref class ClassAdapter
	: BASE_LLNET_CLASS
{
public:
	ClassAdapter()
		:BASE_LLNET_CLASS()
	{
	}

	ClassAdapter(System::IntPtr p)
		:BASE_LLNET_CLASS(p)
	{
	}

	ClassAdapter(System::IntPtr p, bool ownsNativeInstance)
		:BASE_LLNET_CLASS(p, ownsNativeInstance)
	{
	}

	ClassAdapter(NATIVECLASS* p, bool ownsNativeInstance)
		:BASE_LLNET_CLASS(p, ownsNativeInstance)
	{
	}

	ClassAdapter(NATIVECLASS* p)
		:BASE_LLNET_CLASS(p)
	{
	}

	ClassAdapter(void* p, bool ownsNativeInstance)
		:BASE_LLNET_CLASS(p)
	{
	}

	ClassAdapter(void* p)
		:BASE_LLNET_CLASS(p)
	{
	}
};

#define __ctor_ex(RefClass, BaseClass,NativeClass)          \
    RefClass(System::IntPtr p)                              \
        : BaseClass(p)                                      \
    {                                                       \
    }                                                       \
    RefClass(System::IntPtr p, bool ownsNativeInstance)     \
        : BaseClass(p, ownsNativeInstance)                  \
    {                                                       \
    }                                                       \
    RefClass(NativeClass* p)                                \
        : BaseClass(p)                                      \
    {                                                       \
    }                                                       \
    RefClass(NativeClass* p, bool ownsNativeInstance)       \
        : BaseClass(p, ownsNativeInstance)                  \
    {                                                       \
    }                                                       \
    RefClass(void* p)                                       \
        : BaseClass(p)                                      \
    {                                                       \
    }                                                       \
    RefClass(void* p, bool ownsNativeInstance)              \
        : BaseClass(p, ownsNativeInstance)                  \
    {                                                       \
    }

#define __ctor_copy_ex(RefClass, NativeClass)   \
    RefClass(NativeClass& r)                    \
        : BaseClass(r)                          \
    {                                           \
    }

#define __ctor_move_ex(RefClass, NativeClass)   \
    RefClass(NativeClass&& m)                   \
        : BaseClass(m)                          \
    {                                           \
    }

#define __ctor_all_ex(RefClass, NativeClass)    \
    __ctor(RefClass, NativeClass);              \
    internal:                                   \
    __ctor_copy(RefClass, NativeClass);         \
    __ctor_move(RefClass, NativeClass);         \
                                                \