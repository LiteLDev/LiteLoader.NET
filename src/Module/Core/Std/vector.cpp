#include "vector.hpp"

namespace LiteLoader::NET::Std::Internal
{
    inline vector::iterator::iterator(void* stdVectorIteratorPtr, size_t elementTypeSize)
        :_Element_type_size(elementTypeSize)
    {
        _Iter = *reinterpret_cast<_Vector_iterator_data*>(stdVectorIteratorPtr);
    }
    inline vector::iterator::iterator(IntPtr stdVectorIteratorPtr, size_t elementTypeSize)
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
    inline vector::vector(IntPtr stdVectorPtr, size_t elementTypeSize)
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
        return (_Data._Mypair._Myval2._Myfirst - _Data._Mypair._Myval2._Myend) / _Element_type_size;
    }
    inline void* vector::data()
    {
        return _Data._Mypair._Myval2._Myfirst;
    }
    /*generic<typename T>
    inline _Vector_base<T>::_Vector_base()
        :_Initialized_by_managed(true)
    {
        if (T::typeid->IsValueType)
        {
            _Element_type_size = sizeof(T);
            _Is_class = false;
        }
        else
        {
            _Element_type_size = _Get_element_type_size();
            _Is_class = true;
        }

        if (_Element_type_size == 0)
            throw gcnew LiteLoader::NET::InvalidValueException("Field '_element_type_size' equals zero.");
    }
    generic<typename T>
    inline _Vector_base<T>::_Vector_base(void* vector)
        :_Initialized_by_managed(false)
    {
        if (T::typeid->IsValueType)
        {
            _Element_type_size = sizeof(T);
            _Is_class = false;
        }
        else
        {
            _Element_type_size = _Get_element_type_size();
            _Is_class = true;
        }

        if (_Element_type_size == 0)
            throw gcnew LiteLoader::NET::InvalidValueException("Field '_element_type_size' equals zero.");

        _Vector = _value_vector(vector, _Element_type_size);
    }
    generic<typename T>
    inline size_t _Vector_base<T>::_Get_element_type_size()
    {
        if (!typeof(T)->IsAssignableTo(typeof(ICppClass)))
            throw gcnew LiteLoader::NET::InvalidTypeException(typeof(T)->FullName);

        using System::Reflection::BindingFlags;
        auto field = typeof(T)->GetField(
            "NativeClassSize",
            BindingFlags::Public |
            BindingFlags::Static |
            BindingFlags::FlattenHierarchy);

        if (field == nullptr)
            return 0;

        if ((!field->IsLiteral) || !(field->IsInitOnly))
            return 0;

        return static_cast<size_t>(field->GetValue(nullptr));
    }*/
}