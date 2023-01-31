#pragma once
#include "_Vector_base.hpp"

namespace LiteLoader::NET::Std
{
    using LiteLoader::NET::Std::Internal::_Vector_base;

    generic<typename T> where T: gcnew()
        public ref class vector sealed : _Vector_base<T, allocator<T>^>
    {
    public:
        vector()
            :_Vector_base()
        {
        }

        vector(nint_t ptr)
            :_Vector_base(ptr)
        {
        }

        vector(move<vector^> vec)
            :_Vector_base(move<_Vector_base^>(static_cast<vector^>(vec)))
        {
        }
    };
}