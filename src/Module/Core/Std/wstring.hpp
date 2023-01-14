#pragma once
#include <src/Tools/clix.hpp>
#include <src/Main/ClassTemplate.hpp>
#include <memory>

#include "move.hpp"

namespace LiteLoader::NET::Std
{
    using namespace clix;

    public ref class wstring : ClassTemplate<wstring, std::wstring>, IMoveable
    {
    public:
        __ctor_all(wstring, std::wstring);

    public:
        ref class iterator : ClassTemplate<iterator, std::wstring::iterator>
        {
        public:
            __ctor_all(iterator, std::wstring::iterator);
            __ctor_default(iterator, std::wstring::iterator);

        public:
            wchar_t% Dereference()
            {
                return NativePtr->operator*();
            }
            static iterator^ operator+(iterator^ a, int b)
            {
                return gcnew iterator(a->NativePtr->operator+(b));
            }
            static iterator^ operator-(iterator^ a, int b)
            {
                return gcnew iterator(a->NativePtr->operator-(b));
            }
            static bool operator>(iterator^ a, iterator^ b)
            {
                return a->NativePtr->operator>(*b->NativePtr);
            }
            static bool operator<(iterator^ a, iterator^ b)
            {
                return a->NativePtr->operator<(*b->NativePtr);
            }
            static bool operator>=(iterator^ a, iterator^ b)
            {
                return a->NativePtr->operator>=(*b->NativePtr);
            }
            static bool operator<=(iterator^ a, iterator^ b)
            {
                return a->NativePtr->operator<=(*b->NativePtr);
            }
            static iterator^ operator++(iterator^ a)
            {
                return gcnew iterator((*a->NativePtr)++);
            }
            static iterator^ operator--(iterator^ a)
            {
                return gcnew iterator((*a->NativePtr)--);
            }
            static bool operator==(iterator^ a, iterator^ b)
            {
                return *a->NativePtr == *b->NativePtr;
            }
            static bool operator!=(iterator^ a, iterator^ b)
            {
                return *a->NativePtr != *b->NativePtr;
            }
            static operator char(iterator^ obj) {
                return obj->Dereference();
            }
        };

    public:
        wstring()
            :ClassTemplate(std::wstring())
        {
        }
        wstring(wstring^ str)
            :ClassTemplate(*str->NativePtr)
        {
        }
        wstring(move<wstring^> str)
            :ClassTemplate(std::move(*static_cast<wstring^>(str)->NativePtr))
        {
        }
        wstring(String^ str)
            : ClassTemplate(marshalWstring(str))
        {
        }
        iterator^ begin() {
            return gcnew iterator(NativePtr->begin());
        };
        iterator^ end() {
            return gcnew iterator(NativePtr->end());
        };
        property wchar_t% default[int]
        {
            wchar_t% get(int index) {
                return NativePtr->operator[](index);
            }
        };
        size_t size()
        {
            return NativePtr->size();
        }
        size_t length()
        {
            return NativePtr->length();
        }
        size_t max_size()
        {
            return NativePtr->max_size();
        }
        void resize(size_t size)
        {
            NativePtr->resize(size);
        }
        size_t capacity()
        {
            return NativePtr->capacity();
        }
        void reserve(size_t size)
        {
            NativePtr->reserve(size);
        }
        void clear()
        {
            NativePtr->clear();
        }
        bool empty()
        {
            return NativePtr->empty();
        }
        void shrink_to_fit()
        {
            NativePtr->shrink_to_fit();
        }
        wchar_t% at(size_t size)
        {
            return NativePtr->at(size);
        }
        wchar_t% back()
        {
            return NativePtr->back();
        }
        wchar_t% front()
        {
            return NativePtr->front();
        }
        wstring^ operator+=(wstring^ str)
        {
            *NativePtr += *str->NativePtr;
            return this;
        }
        wstring^ append(wstring^ str) {
            NativePtr->append(*str->NativePtr);
            return this;
        };
        wstring^ push_back(char c) {
            NativePtr->push_back(c);
            return this;
        };
        wstring^ assign(wstring^ str) {
            NativePtr->assign(*str->NativePtr);
            return this;
        };
        wstring^ insert(size_t pos, wstring^ str) {
            NativePtr->insert(pos, *str->NativePtr);
            return this;
        }
        wstring^ erase(size_t pos, size_t len) {
            NativePtr->erase(pos, len);
            return this;
        }
        wstring^ replace(size_t pos, size_t len, wstring^ str) {
            NativePtr->replace(pos, len, *str->NativePtr);
            return this;
        }
        void swap(wstring^ str) {
            NativePtr->swap(*str->NativePtr);
        }
        void pop_back() {
            NativePtr->pop_back();
        }
        nint_t c_str_intptr() {
            return nint_t((void*)NativePtr->c_str());
        }
        wchar_t const* c_str() {
            return NativePtr->c_str();
        }
        nint_t data_intptr() {
            return nint_t((void*)NativePtr->data());
        }
        wchar_t const* data() {
            return NativePtr->data();
        }
        //nint_t get_allocator_intptr() {
        //        return nint_t((void*)NativePtr->get_allocator());
        //}
        //nint_t get_allocator() {
        //        return NativePtr->get_allocator();
        //}
        //size_t copy() {
        //}

        //find_first_of

        String^ ToString() override
        {
            return marshalWstring(*NativePtr);
        }

        static bool operator==(wstring^ a, wstring^ b) {
            return *a->NativePtr == *b->NativePtr;
        }
        static bool operator!=(wstring^ a, wstring^ b) {
            return *a->NativePtr != *b->NativePtr;
        }
        static wstring^ operator+(wstring^ a, wstring^ b) {
            return gcnew wstring(*a->NativePtr + *b->NativePtr);
        }
    };
} // namespace LiteLoader::NET::Std
