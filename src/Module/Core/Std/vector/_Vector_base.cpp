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
        std::vector<int> a;
        a.resize(1);
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::iterator::Reset()
    {
        isIterSet = false;
    }

    GENERIC_HEADER inline T _Vector_base<T, TAlloc>::iterator::Current::get()
    {
        if (isValueType)
        {
            if (ICppStdClass::isPointer)
            {
                T ret;
                ICppStdClass::set_native_pointer__pointer(&ret, static_cast<nint_t>(_this.get()), false);
                return ret;
            }
            return Unsafe::Read<T>(_this.get());
        }
        else
        {
            auto ret = gcnew T();
            ICppStdClass::set_native_pointer(ret, static_cast<nint_t>(_this.get()), false);
            return ret;
        }
    }

    GENERIC_HEADER inline TAlloc _Vector_base<T, TAlloc>::_Getal()
    {
        return _al;
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::_Change_array(byte_t* _Newvec, size_t _Newsize, size_t _Newcapacity)
    {
        auto _Al = _Getal();
        auto% _My_data = _this._Data._Mypair._Myval2;
        byte_t*% _Myfirst = _My_data._Myfirst;
        byte_t*% _Mylast = _My_data._Mylast;
        byte_t*% _Myend = _My_data._Myend;

        if (_Myfirst)
        {
            _Destroy_range(_Myfirst, _Mylast);
            _Al->deallocate(_Myfirst, static_cast<size_t>(_Myend - _Myfirst) / type_size);
        }

        _Myfirst = _Newvec;
        _Mylast = _Newvec + _Newsize * type_size;
        _Myend = _Newvec + _Newcapacity * type_size;
    }

    GENERIC_HEADER inline size_t _Vector_base<T, TAlloc>::_Calculate_growth(const size_t _Newsize)
    {
        const size_t _Oldcapacity = capacity();
        const auto _Max = max_size();

        if (_Oldcapacity > _Max - _Oldcapacity / 2) {
            return _Max;
        }

        const size_t _Geometric = _Oldcapacity + _Oldcapacity / 2;

        if (_Geometric < _Newsize) {
            return _Newsize;
        }

        return _Geometric;
    }

    GENERIC_HEADER inline byte_t* _Vector_base<T, TAlloc>::_Emplace_reallocate(byte_t* _Whereptr, bool byMove, T% val)
    {
        auto% _Myfirst = _this._Data._Mypair._Myval2._Myfirst;
        auto% _Mylast = _this._Data._Mypair._Myval2._Mylast;

        const auto _Whereoff = static_cast<size_t>((_Whereptr - _Myfirst) / type_size);
        const auto _Oldsize = static_cast<size_t>((_Mylast - _Myfirst) / type_size);

        if (_Oldsize == max_size())
            throw gcnew System::OutOfMemoryException("vector too long.");

        const size_t _Newsize = _Oldsize + 1;
        const size_t _Newcapacity = _Calculate_growth(_Newsize);

        byte_t* _Newvec = static_cast<byte_t*>(_al->allocate(_Newcapacity));
        byte_t* _Constructed_last = _Newvec + (_Whereoff + 1) * type_size;
        byte_t* _Constructed_first = _Constructed_last;

        try
        {
            if (isValueType)
            {
                Unsafe::Write(_Newvec + (_Whereoff)*type_size, val);
            }
            else
            {
                auto _Temp = gcnew T();
                if (byMove)
                    ICppStdClass::ctor_move(_Temp, move<T>(val));
                else
                    ICppStdClass::ctor_copy(_Temp, val);

                auto _Ptr = ICppStdClass::get_intptr(_Temp);
                Unsafe::CopyBlock(_Newvec + (_Whereoff)*type_size, _Ptr.ToPointer(), static_cast<uint32_t>(type_size));
                ICppStdClass::set_native_pointer(_Temp, nint_t::Zero, false);
            }
            _Constructed_first = _Newvec + _Whereoff * type_size;

            if (_Whereptr == _Mylast)
            {
                if (ICppStdClass::isMoveable)
                    _Uninitialized_move(_Myfirst, _Mylast, _Newvec);
                else
                    _Uninitialized_copy(_Myfirst, _Mylast, _Newvec);
            }
            else
            {
                _Uninitialized_move(_Myfirst, _Whereptr, _Newvec);
                _Constructed_first = _Newvec;
                _Uninitialized_move(_Whereptr, _Mylast, _Newvec + (_Whereoff + 1) * type_size);
            }
        }
        catch (...)
        {
            _Destroy_range(_Constructed_first, _Constructed_last);
            _al->deallocate(_Newvec, _Newcapacity);
            throw;
        }

        _Change_array(_Newvec, _Newsize, _Newcapacity);
        return _Newvec + _Whereoff * type_size;
    }

    GENERIC_HEADER inline T% _Vector_base<T, TAlloc>::_Emplace_back_with_unused_capacity(bool byMove, T% val)
    {
        auto temp_ptr = _this._Data._Mypair._Myval2._Mylast;

        auto dval = uintptr_t(_this._Data._Mypair._Myval2._Myend) - uintptr_t(_this._Data._Mypair._Myval2._Mylast);

        if (dval <= 0 && dval % type_size != 0)
            throw gcnew LiteLoader::NET::MemoryCorruptedException(
                String::Format("Error internal vector data has been detected. _Myend:{0},_Mylast:{1}.",
                    uintptr_t(_this._Data._Mypair._Myval2._Myend),
                    uintptr_t(_this._Data._Mypair._Myval2._Mylast)));

        _this._Data._Mypair._Myval2._Mylast += type_size;

        if (isValueType)
        {
            Unsafe::Write(temp_ptr, val);
            return val;
        }
        else
        {
            auto _Temp = gcnew T();
            if (byMove)
                ICppStdClass::ctor_move(_Temp, move<T>(val));
            else
                ICppStdClass::ctor_copy(_Temp, val);

            auto pInstance = ICppStdClass::get_intptr(_Temp);
            memcpy(temp_ptr, pInstance.ToPointer(), type_size);
            ICppStdClass::set_native_pointer(val, pInstance, false);
            return val;
        }
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::_Destroy_range(pointer_t _First, pointer_t _Last)
    {
        if (isValueType)
            return;

        auto _Temp = gcnew T();
        for (auto* ptr = _First; ptr != _Last; ptr += type_size)
        {
            ICppStdClass::set_native_pointer(_Temp, nint_t(ptr), false);
            ICppStdClass::dtor(_Temp);
        }
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::_Uninitialized_move(pointer_t _First, pointer_t _Last, pointer_t _Dest)
    {
        Unsafe::CopyBlock(_Dest, _First, static_cast<uint32_t>(_Last - _First));
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::_Uninitialized_copy(pointer_t _First, pointer_t _Last, pointer_t _Dest)
    {
        Unsafe::CopyBlock(_Dest, _First, static_cast<uint32_t>(_Last - _First));
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::_Vector_base()
    {
        _this = _value_vector();
        _this._Element_type_size = type_size;
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::_Vector_base(nint_t ptr)
        :_this(ptr, type_size)
    {
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::_Vector_base(_Vector_base^ vec)
    {
        throw gcnew System::NotSupportedException(NotSupportedMessage);
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
        return _al;
    }

    GENERIC_HEADER inline T _Vector_base<T, TAlloc>::emplace_back(T val)
    {
        if (!isValueType && !ICppStdClass::isCopyable)
            throw gcnew LiteLoader::NET::InvalidTypeException(typeof(T)->FullName + " is not copyable.");

        auto% _My_data = _this._Data._Mypair._Myval2;
        auto% _Mylast = _My_data._Mylast;

        if (_Mylast != _My_data._Myend)
        {
            return _Emplace_back_with_unused_capacity(false, val);
        }
        else
        {
            if (_Mylast > _My_data._Myend)
            {
                throw gcnew LiteLoader::NET::MemoryCorruptedException(
                    String::Format("Error internal vector data has been detected. size:{0},capacity:{1}.",
                        size(), capacity()));
            }

            auto _ptr = _Emplace_reallocate(_this._Data._Mypair._Myval2._Mylast, false, val);

            if (isValueType)
                return Unsafe::AsRef<T>(_ptr);
            else
            {
                auto _temp = gcnew T();
                ICppStdClass::set_native_pointer(_temp, nint_t(_ptr), false);
                return _temp;
            }
        }
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::resize(size_t newSize)
    {
        auto _Al = _Getal();
        auto% _My_data = _this._Data._Mypair._Myval2;
        byte_t*% _Myfirst = _My_data._Myfirst;
        byte_t*% _Mylast = _My_data._Mylast;
        const auto _Oldsize = static_cast<size_t>((_Mylast - _Myfirst) / type_size);

        if (newSize < _Oldsize)
        {
            const byte_t* _Newlast = _Myfirst + newSize * type_size;
        }
    }

    GENERIC_HEADER inline size_t _Vector_base<T, TAlloc>::max_size()
    {
        return std::min(std::numeric_limits<size_t>::max(), _al->max_size());
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
            ICppStdClass::set_native_pointer(ret, Unsafe::Read<nint_t>(_this.at(index).get()), false);
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
        emplace_back(item);
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