#pragma once
#include <msclr/marshal_cppstd.h>
#include <stdint.h>

#include "Global.hpp"
#include <src/Header/Core/Exceptions.hpp>

#define LLNET_DEFAULT_EXCEPTION_MESSAGE "Uncaught {0} detected!"

#define CATCH                                                                                                \
    catch (System::Exception ^ ex)                                                                           \
    {                                                                                                        \
        GlobalClass::logger->error->WriteLine(LLNET_DEFAULT_EXCEPTION_MESSAGE, ex->GetType()->ToString());   \
        GlobalClass::logger->error->WriteLine(ex->ToString());                                               \
    }                                                                                                        \
    catch (...)                                                                                              \
    {                                                                                                        \
        GlobalClass::logger->error->WriteLine(LLNET_DEFAULT_EXCEPTION_MESSAGE, "exception");                 \
    }

#define NULL_ARG_CHECK(arg)                                                        \
    if (ReferenceEquals(arg, nullptr))                                             \
        throw gcnew ::System::ArgumentNullException(#arg, "Cannot be null.");

#define VALUE_TUPLE System::ValueTuple

#define __ref_class public ref class
#define __static abstract sealed
#define __default_param(obj) [DefaultParameterValue(obj)]

#define typeof(type) type::typeid

#define GET_MODULE(asm) GlobalClass::GetCurrentModule(asm)
#define CALLING_MODULE GET_MODULE(Assembly::GetCallingAssembly())

using System::Console;
using System::GC;
using System::IntPtr;
using System::String;
using System::Object;
using System::Exception;
using System::Delegate;
using System::Collections::Generic::Dictionary;
using System::Collections::Generic::List;
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
using System::Runtime::InteropServices::DefaultParameterValueAttribute;
using System::Runtime::CompilerServices::MethodImplAttribute;
using System::Runtime::CompilerServices::MethodImplOptions;

using System::Collections::Generic::IEnumerator;
using System::Collections::Generic::IAsyncEnumerator;
using System::Collections::Generic::IEnumerable;
using System::Collections::Generic::IAsyncEnumerable;
using IEnumerableNonGgeneric = System::Collections::IEnumerable;
using IEnumeratorNonGgeneric = System::Collections::IEnumerator;

using SystemType = System::Type;
using byte_t = unsigned char;

#include <src/Tools/clix.hpp>
using namespace clix;

inline String^ marshalString(std::string const& str)
{
    return marshalString<clix::CLI_Encoding::E_UTF8>(str);
}

inline std::string marshalString(String ^ str)
{
    return marshalString<clix::CLI_Encoding::E_UTF8>(str);
}

inline uint64_t do_Hash(String ^ str)
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
inline T As(U u)
{
    return dynamic_cast<T>(u);
}

template<typename T, typename U>
inline bool Is(U u)
{
    return As<T>(u) != nullptr;
}

#include <src/Tools/type_traits.hpp>

template<typename T>
inline cli::array<T>^ PackArray()
{
    return System::Array::Empty<T>();
}

template<typename T>
inline cli::array<T>^ PackArray(...cli::array<T>^ args)
{
    using namespace LiteLoader::NET;

    static_assert(is_ref_class_v<remove_handle_t<T>>, "");

    return args;
}

#include "GlobalClass.hpp"
