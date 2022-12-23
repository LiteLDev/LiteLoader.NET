#pragma once

#include <msclr/marshal_cppstd.h>

using System::String;

#include "clix.hpp"



String^ marshalString(std::string const& str)
{
    return clix::marshalString<clix::Encoding::E_UTF8>(str);
}

std::string marshalString(String^ str)
{
    return clix::marshalString<clix::Encoding::E_UTF8>(str);
}

String^ marshalStringW(std::wstring const& str)
{
    return clix::marshalString<clix::Encoding::E_UTF16>(str);
}

std::wstring marshalStringW(String^ str)
{
    return clix::marshalString<clix::Encoding::E_UTF16>(str);
}