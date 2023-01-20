#pragma once
#include <src/Main/DotNETGlobal.hpp>
#include <src/Module/Core/ICppClass.hpp>

#include <src/Module/Core/Std/move.hpp>
#include <src/Module/Core/Std/pointer.hpp>
#include <src/Module/Core/Std/ICppStdClass.hpp>
#include <src/Module/Core/Std/allocator.hpp>

namespace LiteLoader::NET::Std::Internal
{
    using LiteLoader::NET::ICppClass;
    using LiteLoader::NET::IPointerConstructable;
    using LiteLoader::NET::Std::Internal::ICppStdClass;
    using System::Collections::Generic::IList;

    using System::Runtime::InteropServices::FieldOffsetAttribute;

    [StructLayout(LayoutKind::Explicit, Size = 24)]
    public value struct _Vector_data 
    {
        [StructLayout(LayoutKind::Explicit, Size = 24)]
        value struct _Compressed_pair
        {
            [StructLayout(LayoutKind::Explicit, Size = 24)]
            value struct _Vector_val
            {
                [FieldOffset(0)]
                byte_t* _Myfirst;
                [FieldOffset(8)]
                byte_t* _Mylast;
                [FieldOffset(16)]
                byte_t* _Myend;
            };
            [FieldOffset(0)]
            _Vector_val _Myval2;
        };
        [FieldOffset(0)]
        _Compressed_pair _Mypair;
    };

    [StructLayout(LayoutKind::Explicit, Size = 8)]
    public value struct _Vector_iterator_data {
        [FieldOffset(0)]
        byte_t* _Ptr;
    };

    public value class vector
    {
    public:
        value struct iterator
        {
        public:
            iterator(void* stdVectorIteratorPtr, size_t elementTypeSize);
            iterator(nint_t stdVectorIteratorPtr, size_t elementTypeSize);
            iterator(_Vector_iterator_data data, size_t elementTypeSize);
        public:
            property _Vector_iterator_data% InternalData
            {
                _Vector_iterator_data% get()
                {
                    return _Iter;
                }
            }
        public:
            static iterator operator++(iterator val)
            {
                auto ret = val;
                ret._Iter._Ptr += ret._Element_type_size;
                return ret;
            }
            static iterator operator--(iterator val)
            {
                auto ret = val;
                ret._Iter._Ptr -= ret._Element_type_size;
                return ret;
            }
            static iterator operator+(iterator a, int b)
            {
                auto ret = a;
                ret._Iter._Ptr += ret._Element_type_size * b;
                return ret;
            }
            static iterator operator-(iterator a, int b)
            {
                auto ret = a;
                ret._Iter._Ptr -= ret._Element_type_size * b;
                return ret;
            }
            static bool operator>(iterator a, iterator b)
            {
                return a._Iter._Ptr > b._Iter._Ptr;
            }
            static bool operator<(iterator a, iterator b)
            {
                return a._Iter._Ptr < b._Iter._Ptr;
            }
            static bool operator>=(iterator a, iterator b)
            {
                return a._Iter._Ptr >= b._Iter._Ptr;
            }
            static bool operator<=(iterator a, iterator b)
            {
                return a._Iter._Ptr <= b._Iter._Ptr;
            }
            static bool operator==(iterator a, iterator b)
            {
                return a._Iter._Ptr == b._Iter._Ptr;
            }
            static bool operator!=(iterator a, iterator b)
            {
                return !(a == b);
            }
            property iterator default[int]
            {
                iterator get(int index)
                {
                    auto ret = *this;
                    ret._Iter._Ptr += ret._Element_type_size * index;
                    return ret;
                }
            };
            void* get()
            {
                return this->_Iter._Ptr;
            }
        internal:
            _Vector_iterator_data _Iter;
            size_t _Element_type_size;
        };

    public:
        vector(void* stdVectorPtr, size_t elementTypeSize);
        vector(nint_t stdVectorPtr, size_t elementTypeSize);
    public:
        size_t size();
        iterator begin();
        iterator end();
        iterator at(size_t pos);
        bool empty();
        size_t capacity();
        void* data();
    public:
        property _Vector_data% internal_data
        {
            _Vector_data% get()
            {
                return *_Data;
            }
        }
    internal:
        _Vector_data* _Data;
        size_t _Element_type_size;
        bool _Constructed_by_managed;
    };
}

