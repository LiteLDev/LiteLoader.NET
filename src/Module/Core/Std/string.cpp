#include "string.hpp"

namespace LiteLoader::NET::Std
{
    inline string::string()
        :ClassTemplate(std::string())
    {
    }
    inline string::string(string^ str)
        : ClassTemplate(*str->NativePtr)
    {
    }
    inline string::string(move<string^> str)
        : ClassTemplate(std::move(*static_cast<string^>(str)->NativePtr))
    {
    }
    inline string::string(String^ str)
        : ClassTemplate(marshalString(str))
    {
    }
    inline string::iterator^ string::begin() 
    {
        return gcnew iterator(NativePtr->begin());
    }
    inline string::iterator^ string::end() 
    {
        return gcnew iterator(NativePtr->end());
    }
    inline size_t string::size()
    {
        return NativePtr->size();
    }
    inline size_t string::length()
    {
        return NativePtr->length();
    }
    inline size_t string::max_size()
    {
        return NativePtr->max_size();
    }
    inline void string::resize(size_t size)
    {
        NativePtr->resize(size);
    }
    inline size_t string::capacity()
    {
        return NativePtr->capacity();
    }
    inline void string::reserve(size_t size)
    {
        NativePtr->reserve(size);
    }
    inline void string::clear()
    {
        NativePtr->clear();
    }
    inline bool string::empty()
    {
        return NativePtr->empty();
    }
    inline void string::shrink_to_fit()
    {
        NativePtr->shrink_to_fit();
    }
    inline char% string::at(size_t size)
    {
        return NativePtr->at(size);
    }
    inline char% string::back()
    {
        return NativePtr->back();
    }
    inline char% string::front()
    {
        return NativePtr->front();
    }
    inline string^ string::append(string^ str)
    {
        NativePtr->append(*str->NativePtr);
        return this;
    }
    inline string^ string::push_back(char c)
    {
        NativePtr->push_back(c);
        return this;
    }
    inline string^ string::assign(string^ str)
    {
        NativePtr->assign(*str->NativePtr);
        return this;
    }
    inline string^ string::insert(size_t pos, string^ str)
    {
        NativePtr->insert(pos, *str->NativePtr);
        return this;
    }
    inline string^ string::erase(size_t pos, size_t len)
    {
        NativePtr->erase(pos, len);
        return this;
    }
    inline string^ string::replace(size_t pos, size_t len, string^ str)
    {
        NativePtr->replace(pos, len, *str->NativePtr);
        return this;
    }
    inline void string::swap(string^ str)
    {
        NativePtr->swap(*str->NativePtr);
    }
    inline void string::pop_back()
    {
        NativePtr->pop_back();
    }
    inline nint_t string::c_str_intptr()
    {
        return nint_t((void*)NativePtr->c_str());
    }
    inline char const* string::c_str()
    {
        return NativePtr->c_str();
    }
    inline nint_t string::data_intptr()
    {
        return nint_t((void*)NativePtr->data());
    }
    inline char const* string::data()
    {
        return NativePtr->data();
    }

    inline String^ string::ToString()
    {
        return marshalString(*NativePtr);
    }

    //IMoveable

    inline string^ string::ConstructInstanceByMove(move<string^> _Right)
    {
        return gcnew string(_Right);
    }
    inline string^ string::ConstructInstanceByCopy(string^ _Right)
    {
        return gcnew string(_Right);
    }
    inline char string::default::get(int index)
    {
        return NativePtr->operator[](index);
    }
    inline void string::default::set(int index, char value)
    {
        NativePtr->operator[](index) = value;
    }
}