#include "_Vector_base.hpp"

namespace LiteLoader::NET::Std::Internal
{
#define GENERIC_HEADER generic<typename T, typename TAlloc>     \
    where T : gcnew()                                           \
    where TAlloc : gcnew(), ICppStdAllocator                    \

    GENERIC_HEADER inline Object^ _Vector_base<T, TAlloc>::iterator::CurrentNonGgeneric::get()
    {
        return Current;
    }


    GENERIC_HEADER inline bool _Vector_base<T, TAlloc>::iterator::MoveNext()
    {
        if (isIterSet)
        {
            ++_this;
            return _this != instance->_this.end();
        }
        else
        {
            _this = instance->_this.begin();
            if (_this == instance->_this.end())
                return false;

            isIterSet = true;
            return true;
        }
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::iterator::Reset()
    {
        isIterSet = false;
    }

    GENERIC_HEADER inline T _Vector_base<T, TAlloc>::iterator::Current::get()
    {
        if (isValueType)
        {
            if (isPointer)
            {
                T ret;
                set_native_pointer__pointer(&ret, static_cast<nint_t>(_this.get()), false);
                return ret;
            }
            return Unsafe::Read<T>(_this.get());
        }
        else
        {
            auto ret = gcnew T();
            set_native_pointer(ret, static_cast<nint_t>(_this.get()), false);
            return ret;
        }
    }

    GENERIC_HEADER inline T _Vector_base<T, TAlloc>::_Emplace_reallocate(T% val)
    {
        throw gcnew System::NotImplementedException;
    }

    GENERIC_HEADER inline T _Vector_base<T, TAlloc>::_Emplace(T% val)
    {
        auto temp_ptr = _this._Data._Mypair._Myval2._Mylast;

        auto dval = uintptr_t(_this._Data._Mypair._Myval2._Myend) - uintptr_t(_this._Data._Mypair._Myval2._Mylast);

        if (dval <= 0 && dval % elementTypeSize != 0)
            throw gcnew LiteLoader::NET::MemoryCorruptedException(
                String::Format("Error internal vector data has been detected. _Myend:{0},_Mylast:{1}.",
                    uintptr_t(_this._Data._Mypair._Myval2._Myend),
                    uintptr_t(_this._Data._Mypair._Myval2._Mylast)));

        _this._Data._Mypair._Myval2._Mylast += elementTypeSize;

        if (isValueType)
        {
            Unsafe::Write(temp_ptr, val);
            return val;
        }
        else
        {
            auto pInstance = get_intptr(val);
            memcpy(temp_ptr, pInstance.ToPointer(), elementTypeSize);
            set_native_pointer(val, pInstance, false);
            return val;
        }
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::_Vector_base() {}

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::_Vector_base(nint_t ptr)
        :_this(ptr, elementTypeSize)
    {
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::_Vector_base(move<_Vector_base^> vec)
    {
        throw gcnew System::NotSupportedException(NotSupportedMessage);
    }

    GENERIC_HEADER inline size_t _Vector_base<T, TAlloc>::size()
    {
        return _this.size();
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::iterator _Vector_base<T, TAlloc>::begin()
    {
        iterator ret;
        ret._this = _this.begin();
        ret.instance = this;
        ret.isIterSet = true;
        return ret;
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::iterator _Vector_base<T, TAlloc>::end()
    {
        iterator ret;
        ret._this = _this.end();
        ret.instance = this;
        ret.isIterSet = true;
        return ret;
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::iterator _Vector_base<T, TAlloc>::at(size_t pos)
    {
        iterator ret;
        ret._this = _this.at(pos);
        ret.instance = this;
        ret.isIterSet = true;
        return ret;
    }

    GENERIC_HEADER inline bool _Vector_base<T, TAlloc>::empty()
    {
        return _this.empty();
        std::string str;
        new std::string(std::move(str));
    }

    GENERIC_HEADER inline size_t _Vector_base<T, TAlloc>::capacity()
    {
        return _this.capacity();
    }

    GENERIC_HEADER inline void* _Vector_base<T, TAlloc>::data()
    {
        return _this.data();
    }

    GENERIC_HEADER inline TAlloc _Vector_base<T, TAlloc>::get_allocator()
    {
        return allocator;
        std::vector<int> a;
        a.emplace_back(1);
    }

    GENERIC_HEADER inline T _Vector_base<T, TAlloc>::emplace_back(T val)
    {
        if (!isCopyable)
            throw gcnew LiteLoader::NET::InvalidTypeException(typeof(T)->FullName + "is not copyable.");

        auto _size = size();
        auto _capacity = size();

        T temp;
        if (isValueType)
            temp = val;
        else
        {
            temp = gcnew T();
            ctor_copy(temp, val);
        }

        T ret;
        if (_size < _capacity)
            ret = _Emplace(temp);
        else
        {
            if (_size > _capacity)
            {
                throw gcnew LiteLoader::NET::MemoryCorruptedException(
                    String::Format("Error internal vector data has been detected. size:{0},capacity:{1}.",
                        _size, _capacity));
            }

            ret = _Emplace_reallocate(temp);
        }

        return ret;
    }

    GENERIC_HEADER inline IEnumeratorNonGgeneric^ _Vector_base<T, TAlloc>::GetEnumeratorNonGgeneric()
    {
        return GetEnumerator();
    }

    GENERIC_HEADER inline IEnumerator<T>^ _Vector_base<T, TAlloc>::GetEnumerator()
    {
        auto ret = iterator();
        ret.instance = this;
        return ret;
    }

    GENERIC_HEADER inline int _Vector_base<T, TAlloc>::Count::get()
    {
        return static_cast<int>(_this.size());
    }

    GENERIC_HEADER inline T _Vector_base<T, TAlloc>::default::get(int index)
    {
        if (isValueType)
        {
            return Unsafe::Read<T>(_this.at(index).get());
        }
        else
        {
            auto ret = gcnew T();
            set_native_pointer(ret, Unsafe::Read<nint_t>(_this.at(index).get()), false);
            return ret;
        }
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::default::set(int index, T val)
    {
        throw gcnew System::NotSupportedException(NotSupportedMessage);
    }

    GENERIC_HEADER inline bool _Vector_base<T, TAlloc>::IsReadOnly::get()
    {
        return true;
    }

    GENERIC_HEADER inline bool _Vector_base<T, TAlloc>::Contains(T item)
    {
        throw gcnew System::NotSupportedException(NotSupportedMessage);
    }

    GENERIC_HEADER inline int _Vector_base<T, TAlloc>::IndexOf(T item)
    {
        throw gcnew System::NotSupportedException(NotSupportedMessage);
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::Add(T item)
    {
        throw gcnew System::NotSupportedException(NotSupportedMessage);
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::Clear()
    {
        throw gcnew System::NotSupportedException(NotSupportedMessage);
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::CopyTo(array<T, 1>^ array, int arrayIndex)
    {
        throw gcnew System::NotSupportedException(NotSupportedMessage);
    }

    GENERIC_HEADER inline bool _Vector_base<T, TAlloc>::Remove(T item)
    {
        throw gcnew System::NotSupportedException(NotSupportedMessage);
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::Insert(int index, T item)
    {
        throw gcnew System::NotSupportedException(NotSupportedMessage);
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::RemoveAt(int index)
    {
        throw gcnew System::NotSupportedException(NotSupportedMessage);
    }

    GENERIC_HEADER inline nint_t _Vector_base<T, TAlloc>::Intptr::get()
    {
        pin_ptr<decltype(_this)> ptr = &_this;
        return nint_t(ptr);
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::Destruct()
    {
        throw gcnew System::NotSupportedException(NotSupportedMessage);
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::SetNativePointer(nint_t ptr, bool ownsInstance)
    {
        _this = *reinterpret_cast<decltype(_this)*>(ptr.ToPointer());
        this->ownsNativeInstance = ownsInstance;
    }

    GENERIC_HEADER inline size_t _Vector_base<T, TAlloc>::GetClassSize()
    {
        return NativeClassSize;
    }
}