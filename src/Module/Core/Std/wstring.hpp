#pragma once
#include <src/Tools/clix.hpp>
#include <src/Main/ClassTemplate.hpp>
#include <memory>

#using <../Modules/LiteLoader.NET.InteropServices.dll>

namespace LiteLoader::NET::Std
{
    using LiteLoader::NET::InteropServices::IMoveable;
    using LiteLoader::NET::InteropServices::ICopyable;
    using LiteLoader::NET::InteropServices::move;

    public ref class wstring : ClassTemplate<wstring, std::wstring>,
        IMoveable<wstring^>,
        ICopyable<wstring^>
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
            static operator wchar_t(iterator^ obj) {
                return obj->Dereference();
            }
        };

    public:
        wstring();
        wstring(wstring^ str);
        wstring(move<wstring^> str);
        wstring(String^ str);
        iterator^ begin();
        iterator^ end();
        property wchar_t default[int]
        {
            wchar_t get(int index);
            void set(int index, wchar_t value);
        };
        size_t size();
        size_t length();
        size_t max_size();
        void resize(size_t size);
        size_t capacity();
        void reserve(size_t size);
        void clear();
        bool empty();
        void shrink_to_fit();
        wchar_t% at(size_t size);
        wchar_t% back();
        wchar_t% front();
        wstring^ append(wstring^ str);
        wstring^ push_back(wchar_t c);
        wstring^ assign(wstring^ str);
        wstring^ insert(size_t pos, wstring^ str);
        wstring^ erase(size_t pos, size_t len);
        wstring^ replace(size_t pos, size_t len, wstring^ str);
        void swap(wstring^ str);
        void pop_back();
        nint_t c_str_intptr();
        wchar_t const* c_str();
        nint_t data_intptr();
        wchar_t const* data();
        //nint_t get_allocator_intptr() {
        //        return nint_t((void*)NativePtr->get_allocator());
        //}
        //nint_t get_allocator() {
        //        return NativePtr->get_allocator();
        //}
        //size_t copy() {
        //}

        //find_first_of

        String^ ToString() override;

        static bool operator==(wstring^ a, wstring^ b)
        {
            return *a->NativePtr == *b->NativePtr;
        }
        static bool operator!=(wstring^ a, wstring^ b)
        {
            return *a->NativePtr != *b->NativePtr;
        }
        static wstring^ operator+(wstring^ a, wstring^ b)
        {
            return gcnew wstring(*a->NativePtr + *b->NativePtr);
        }
        static operator String ^ (wstring^ str)
        {
            return str->ToString();
        }
        static operator wstring ^ (String^ str)
        {
            return gcnew wstring(str);
        }

        //IMoveable
        virtual wstring^ ConstructInstanceByMove(move<wstring^> _Right);
        virtual wstring^ ConstructInstanceByCopy(wstring^ _Right);
    };
} // namespace LiteLoader::NET::Std
