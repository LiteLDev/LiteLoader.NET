#pragma once
#include <src/Tools/clix.hpp>
#include <src/Main/ClassTemplate.hpp>

#include "move.hpp"
#include "ICopyable.hpp"

namespace LiteLoader::NET::Std
{
    using namespace clix;

    public ref class string : ClassTemplate<string, std::string>,
        IMoveable<string^>,
        ICopyable<string^>
    {
    public:
        __ctor_all(string, std::string);

    public:
        ref class iterator : ClassTemplate<iterator, std::string::iterator>
        {
        public:
            __ctor_all(iterator, std::string::iterator);
            __ctor_default(iterator, std::string::iterator);

        public:
            char% Dereference()
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
        string();
        string(string^ str);
        string(move<string^> str);
        string(String^ str);
        iterator^ begin();
        iterator^ end();
        property char default[int]
        {
            char get(int index);
            void set(int index, char value);
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
        char% at(size_t size);
        char% back();
        char% front();
        string^ append(string^ str);
        string^ push_back(char c);
        string^ assign(string^ str);
        string^ insert(size_t pos, string^ str);
        string^ erase(size_t pos, size_t len);
        string^ replace(size_t pos, size_t len, string^ str);
        void swap(string^ str);
        void pop_back();
        nint_t c_str_intptr();
        char const* c_str();
        nint_t data_intptr();
        char const* data();
        //nint_t get_allocator_intptr() {
        //        return nint_t((void*)NativePtr->get_allocator());
        //}
        //nint_t get_allocator() {
        //        return NativePtr->get_allocator();
        //}
        //size_t copy() {
        //}

        //find_first_of

        property nint_t Intptr
        {
            virtual nint_t get() override
            {
                return nint_t(this->NativePtr);
            }

        }

        String^ ToString() override;

        static bool operator==(string^ a, string^ b)
        {
            return *a->NativePtr == *b->NativePtr;
        }
        static bool operator!=(string^ a, string^ b)
        {
            return *a->NativePtr != *b->NativePtr;
        }
        static string^ operator+(string^ a, string^ b)
        {
            return gcnew string(*a->NativePtr + *b->NativePtr);
        }

        //IMoveable
        virtual string^ ConstructInstanceByMove(move<string^> _Right);
        virtual string^ ConstructInstanceByCopy(string^ _Right);
    };
} // namespace LiteLoader::NET::Std
