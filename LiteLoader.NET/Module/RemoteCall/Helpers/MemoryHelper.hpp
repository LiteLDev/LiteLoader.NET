#pragma once
#include <RemoteCallAPI.h>

#include <LiteLoader.NET/Main/DotNETGlobal.hpp>

#include "TypeHelper.hpp"

namespace LiteLoader::RemoteCall::Helper
{
    using array_type = ::RemoteCall::ValueType::ArrayType;
    using array_type_native_iterator = ::RemoteCall::ValueType::ArrayType::iterator;

    public ref class MemoryHelper __static
    {
    public:

        static bool FreeArrayType(void* ptr);
    };
}

#define MEMORYHELPER_METHOD_INFO(funcname) ::LiteLoader::RemoteCall::Helper::MemoryHelper::typeid->GetMethod(#funcname)
