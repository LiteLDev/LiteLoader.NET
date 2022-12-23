#pragma once

#include "DotNETGlobal.hpp"
#include <LiteLoader.NET/Tools/ClassTemplateHelper.hpp>
#include <LiteLoader.NET/Header/Core/ICppClass.hpp>

template <typename REFCLASS, typename NATIVECLASS>
public ref class ClassTemplate abstract : LiteLoader::NET::ICppClass
{
protected:
	bool ownsNativeInstance;
	NATIVECLASS* nativePtr;

public:
	property NATIVECLASS* NativePtr
	{
	public:
		NATIVECLASS* get()
		{
			return nativePtr;
		}

	protected:
		void set(NATIVECLASS* value)
		{
			nativePtr = value;
		}
	}

	property IntPtr Intptr
	{
		virtual IntPtr get()
		{
			return IntPtr(nativePtr);
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
	ClassTemplate()
		: ownsNativeInstance(false)
		, nativePtr(nullptr)
	{
	}

	!ClassTemplate()
	{
		if (ownsNativeInstance)
			delete nativePtr;
	}

	virtual ~ClassTemplate()
	{
		this->!ClassTemplate();
	}

public:
	ClassTemplate(System::IntPtr p)
		: ownsNativeInstance(false)
		, nativePtr((NATIVECLASS*)(void*)p)
	{
	}

	ClassTemplate(System::IntPtr p, bool ownsNativeInstance)
		: ownsNativeInstance(ownsNativeInstance)
		, nativePtr((NATIVECLASS*)(void*)p)
	{
	}

	ClassTemplate(NATIVECLASS* p, bool ownsNativeInstance)
		: ownsNativeInstance(ownsNativeInstance)
		, nativePtr((NATIVECLASS*)p)
	{
	}

	ClassTemplate(NATIVECLASS* p)
		: ownsNativeInstance(false)
		, nativePtr((NATIVECLASS*)p)
	{
	}

	ClassTemplate(void* p, bool ownsNativeInstance)
		: ownsNativeInstance(ownsNativeInstance)
		, nativePtr((NATIVECLASS*)p)
	{
	}

	ClassTemplate(void* p)
		: ownsNativeInstance(false)
		, nativePtr((NATIVECLASS*)p)
	{
	}

	ClassTemplate(NATIVECLASS& r)
		: ownsNativeInstance(true)
		, nativePtr(new NATIVECLASS((NATIVECLASS&)r))
	{
	}

	ClassTemplate(NATIVECLASS&& m)
		: ownsNativeInstance(true)
		, nativePtr(new NATIVECLASS(m))
	{
	}

internal:
	operator NATIVECLASS& ()
	{
		return *nativePtr;
	}
	operator NATIVECLASS* ()
	{
		return nativePtr;
	}

public:
	virtual NATIVECLASS* Release()
	{
		auto ret = nativePtr;
		nativePtr = nullptr;
		ownsNativeInstance = false;
		this->~ClassTemplate();
		return ret;
	}
	virtual void Reset(NATIVECLASS* p)
	{
		if (ownsNativeInstance)
			delete nativePtr;
		nativePtr = p;
		ownsNativeInstance = false;
	}
	virtual void Reset(NATIVECLASS* p, bool ownsNativeInstance)
	{
		if (this->ownsNativeInstance)
			delete nativePtr;
		nativePtr = (NATIVECLASS*)p;
		this->ownsNativeInstance = ownsNativeInstance;
	}
	virtual void Destructor(void* ptr)
	{
		reinterpret_cast<NATIVECLASS*>(ptr)->~NATIVECLASS();
	}
};
