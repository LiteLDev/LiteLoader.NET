#include "MemoryHelper.hpp"

namespace LiteLoader::RemoteCall::Helper
{
    using array_type = ::RemoteCall::ValueType::ArrayType;

    bool MemoryHelper::FreeArrayType(void* ptr)
    {
        reinterpret_cast<array_type*>(ptr)->~vector();
        ::operator delete(ptr, sizeof(array_type));
    }
}