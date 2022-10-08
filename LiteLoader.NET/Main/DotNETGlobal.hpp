#pragma once
#include <msclr/marshal_cppstd.h>
#include <stdint.h>

#include "Global.hpp"
#include <LiteLoader.NET/Header/Core/Pair.hpp>
#include <LiteLoader.NET/Header/Core/Exceptions.hpp>

#define LLNET_DEFAULT_EXCEPTION_MESSAGE "Uncaught {0} detected!"

#define CATCH																								\
    catch (System::Exception ^ ex)																			\
    {																										\
        GlobalClass::logger->error->WriteLine(LLNET_DEFAULT_EXCEPTION_MESSAGE, ex->GetType()->ToString());	\
        GlobalClass::logger->error->WriteLine(ex->ToString());												\
    }																										\
    catch (...)																								\
    {																										\
        GlobalClass::logger->error->WriteLine(LLNET_DEFAULT_EXCEPTION_MESSAGE, "exception");				\
    }

#define NULL_ARG_CHEEK(arg)														\
    if (ReferenceEquals(arg, nullptr))											\
        throw gcnew ::System::ArgumentNullException(#arg, "Cannot be null.");

#define __ref_class public ref class
#define __static abstract sealed

using System::Console;
using System::GC;
using System::IntPtr;
using System::String;
using System::Object;
using System::Exception;
using System::Delegate;
using System::Collections::Generic::Dictionary;
using System::Collections::Generic::List;
using System::Collections::Generic::KeyValuePair;
using System::Collections::Generic::Queue;
using System::Reflection::Assembly;
using System::Reflection::AssemblyName;
using System::Runtime::InteropServices::FieldOffsetAttribute;
using System::Runtime::InteropServices::GCHandle;
using System::Runtime::InteropServices::LayoutKind;
using System::Runtime::InteropServices::Marshal;
using System::Runtime::InteropServices::StructLayoutAttribute;
using System::Runtime::InteropServices::OutAttribute;
using System::Runtime::InteropServices::InAttribute;
using System::Runtime::CompilerServices::MethodImplAttribute;
using System::Runtime::CompilerServices::MethodImplOptions;
using LLNET::Core::Pair;

#include <LiteLoader.NET/Tools/clix.hpp>
using namespace clix;

inline String^ marshalString(std::string const& str) 
{
	return marshalString<clix::CLI_Encoding::E_UTF8>(str);
};

inline std::string marshalString(String^ str)
{
	return marshalString<clix::CLI_Encoding::E_UTF8>(str);
}

inline uint64_t do_Hash(String^ str)
{
	uint64_t rval = 0;
	for (int i = 0; i < str->Length; ++i)
	{
		if (i & 1)
		{
			rval ^= (~((rval << 11) ^ str[i] ^ (rval >> 5)));
		}
		else
		{
			rval ^= (~((rval << 7) ^ str[i] ^ (rval >> 3)));
		}
	}
	return rval;
}

template<typename T, typename U>
inline bool Is(U u)
{
	return dynamic_cast<T>(u) != nullptr;
}

template<typename T,typename U>
inline T As(U u)
{
	return safe_cast<T>(u);
}

#include "GlobalClass.hpp"