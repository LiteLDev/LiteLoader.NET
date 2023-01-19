#include "wstring.hpp"

namespace LiteLoader::NET::Std
{
    inline wstring::wstring()
        :ClassTemplate(std::wstring())
    {
    }
    inline wstring::wstring(wstring^ str)
        : ClassTemplate(*str->NativePtr)
    {
    }
    inline wstring::wstring(move<wstring^> str)
        : ClassTemplate(std::move(*static_cast<wstring^>(str)->NativePtr))
    {
    }
    inline wstring::wstring(String^ str)
        : ClassTemplate(marshalWstring(str))
    {
    }
    inline wstring::iterator^ wstring::begin()
    {
        return gcnew iterator(NativePtr->begin());
    }
    inline wstring::iterator^ wstring::end()
    {
        return gcnew iterator(NativePtr->end());
    }
    inline size_t wstring::size()
    {
        return NativePtr->size();
    }
    inline size_t wstring::length()
    {
        return NativePtr->length();
    }
    inline size_t wstring::max_size()
    {
        return NativePtr->max_size();
    }
    inline void wstring::resize(size_t size)
    {
        NativePtr->resize(size);
    }
    inline size_t wstring::capacity()
    {
        return NativePtr->capacity();
    }
    inline void wstring::reserve(size_t size)
    {
        NativePtr->reserve(size);
    }
    inline void wstring::clear()
    {
        NativePtr->clear();
    }
    inline bool wstring::empty()
    {
        return NativePtr->empty();
    }
    inline void wstring::shrink_to_fit()
    {
        NativePtr->shrink_to_fit();
    }
    inline wchar_t% wstring::at(size_t size)
    {
        return NativePtr->at(size);
    }
    inline wchar_t% wstring::back()
    {
        return NativePtr->back();
    }
    inline wchar_t% wstring::front()
    {
        return NativePtr->front();
    }
    inline wstring^ wstring::append(wstring^ str)
    {
        NativePtr->append(*str->NativePtr);
        return this;
    }
    inline wstring^ wstring::push_back(wchar_t c)
    {
        NativePtr->push_back(c);
        return this;
    }
    inline wstring^ wstring::assign(wstring^ str)
    {
        NativePtr->assign(*str->NativePtr);
        return this;
    }
    inline wstring^ wstring::insert(size_t pos, wstring^ str)
    {
        NativePtr->insert(pos, *str->NativePtr);
        return this;
    }
    inline wstring^ wstring::erase(size_t pos, size_t len)
    {
        NativePtr->erase(pos, len);
        return this;
    }
    inline wstring^ wstring::replace(size_t pos, size_t len, wstring^ str)
    {
        NativePtr->replace(pos, len, *str->NativePtr);
        return this;
    }
    inline void wstring::swap(wstring^ str)
    {
        NativePtr->swap(*str->NativePtr);
    }
    inline void wstring::pop_back()
    {
        NativePtr->pop_back();
    }
    inline nint_t wstring::c_str_intptr()
    {
        return nint_t((void*)NativePtr->c_str());
    }
    inline wchar_t const* wstring::c_str()
    {
        return NativePtr->c_str();
    }
    inline nint_t wstring::data_intptr()
    {
        return nint_t((void*)NativePtr->data());
    }
    inline wchar_t const* wstring::data()
    {
        return NativePtr->data();
    }

    inline String^ wstring::ToString()
    {
        return marshalWstring(*NativePtr);
    }

    //IMoveable

    inline wstring^ wstring::ConstructInstanceByMove(move<wstring^> _Right)
    {
        return gcnew wstring(_Right);
    }
    inline wstring^ wstring::ConstructInstanceByCopy(wstring^ _Right)
    {
        return gcnew wstring(_Right);
    }
    inline wchar_t wstring::default::get(int index)
    {
        return NativePtr->operator[](index);
    }
    inline void wstring::default::set(int index, wchar_t value)
    {
        NativePtr->operator[](index) = value;
    }
}