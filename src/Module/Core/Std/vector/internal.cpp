#include "internal.hpp"
namespace LiteLoader::NET::Std::Internal
{
    inline vector::iterator::iterator(void* stdVectorIteratorPtr, size_t elementTypeSize)
        :_Element_type_size(elementTypeSize)
    {
        _Iter = *reinterpret_cast<_Vector_iterator_data*>(stdVectorIteratorPtr);
    }
    inline vector::iterator::iterator(nint_t stdVectorIteratorPtr, size_t elementTypeSize)
        : _Element_type_size(elementTypeSize)
    {
        _Iter = *reinterpret_cast<_Vector_iterator_data*>((void*)stdVectorIteratorPtr);
    }
    inline vector::iterator::iterator(_Vector_iterator_data data, size_t elementTypeSize)
        : _Iter(data), _Element_type_size(elementTypeSize)
    {

    }
    inline vector::vector(void* stdVectorPtr, size_t elementTypeSize)
        : _Element_type_size(elementTypeSize)
    {
        _Data = *reinterpret_cast<_Vector_data*>(stdVectorPtr);
    }
    inline vector::vector(nint_t stdVectorPtr, size_t elementTypeSize)
        : _Element_type_size(elementTypeSize)
    {
        _Data = *reinterpret_cast<_Vector_data*>((void*)stdVectorPtr);
    }
    inline size_t vector::size()
    {
        return (_Data._Mypair._Myval2._Mylast - _Data._Mypair._Myval2._Myfirst) / _Element_type_size;
    }
    inline vector::iterator vector::begin()
    {
        return iterator(
            _Vector_iterator_data{ _Data._Mypair._Myval2._Myfirst },
            _Element_type_size
        );
    }
    inline vector::iterator vector::end()
    {
        return iterator(
            _Vector_iterator_data{ _Data._Mypair._Myval2._Mylast },
            _Element_type_size
        );
    }
    inline vector::iterator vector::at(size_t pos)
    {
        auto ptr = _Data._Mypair._Myval2._Myfirst + pos * _Element_type_size;
        if (ptr > _Data._Mypair._Myval2._Mylast)
            throw gcnew System::IndexOutOfRangeException;

        return iterator
        {
            _Vector_iterator_data{ ptr },
            _Element_type_size
        };
    }
    inline bool vector::empty()
    {
        return _Data._Mypair._Myval2._Myfirst == _Data._Mypair._Myval2._Mylast;
    }
    inline size_t vector::capacity()
    {
        return (_Data._Mypair._Myval2._Myend - _Data._Mypair._Myval2._Myfirst) / _Element_type_size;
    }
    inline void* vector::data()
    {
        return _Data._Mypair._Myval2._Myfirst;
    }
}