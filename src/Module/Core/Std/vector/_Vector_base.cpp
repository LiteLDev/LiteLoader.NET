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
            if (ICppStdClass::isPointer)
            {
                auto ret = T();
                ICppStdClass::_Tv_fptr.set_native_pointer(&ret, static_cast<nint_t>(_this.get()), false);
                return ret;
            }
            return Unsafe::Read<T>(_this.get());
        }
        else
        {
            auto ret = gcnew T();
            ICppStdClass::_Tr_fptr.set_native_pointer(ret, static_cast<nint_t>(_this.get()), false);
            return ret;
        }
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::iterator _Vector_base<T, TAlloc>::iterator::default::get(int index)
    {
        return iterator(this->_this[index], instance);
    }

    GENERIC_HEADER inline T _Vector_base<T, TAlloc>::_Copy_Instance(T% val)
    {
        if (isValueType)
        {
            if (ICppStdClass::isCopyable)
                return ICppStdClass::_Tv_fptr.ctor_copy(nullptr, val);
            else
                return T(val);
        }
        else
        {
            if (ICppStdClass::isCopyable)
                return ICppStdClass::_Tr_fptr.ctor_copy(nullptr, val);
            else
                throw gcnew LiteLoader::NET::InvalidTypeException(typeof(T)->FullName + " is not a copyable type.");
        }
    }

    GENERIC_HEADER inline T _Vector_base<T, TAlloc>::_Move_Instance(T% val)
    {
        if (isValueType)
        {
            if (ICppStdClass::isMoveable)
                return ICppStdClass::_Tv_fptr.ctor_move(nullptr, move<T>(val));
            else
                return T(val);
        }
        else
        {
            if (ICppStdClass::isMoveable)
                return ICppStdClass::_Tr_fptr.ctor_move(nullptr, move<T>(val));
            else
                throw gcnew LiteLoader::NET::InvalidTypeException(typeof(T)->FullName + " is not a copyable type.");
        }
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::_Destruct_Instance(T% val)
    {
        if (isValueType)
        {
            if (ICppStdClass::isICppClass)
                ICppStdClass::_Tv_fptr.dtor(&val);
        }
        else
        {
            ICppStdClass::_Tr_fptr.dtor(val);
        }
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::_Construct(pointer_t _Dest, T% val, bool byMove)
    {
        auto _Temp = byMove ? _Move_Instance(val) : _Copy_Instance(val);

        auto _Ptr = nint_t();

        if (isValueType)
        {
            if (ICppStdClass::isICppClass)
                _Ptr = ICppStdClass::_Tv_fptr.get_intptr(&_Temp);
            else
            {
                Unsafe::Write(_Dest, val);
                return;
            }
        }
        else
            _Ptr = ICppStdClass::_Tr_fptr.get_intptr(_Temp);


        Unsafe::CopyBlock(_Dest, _Ptr.ToPointer(), static_cast<uint32_t>(type_size));

        if (isValueType)
        {
            if (ICppStdClass::isICppClass)
                ICppStdClass::_Tv_fptr.set_own_instance(&_Temp, false);
        }
        else
            ICppStdClass::_Tr_fptr.set_own_instance(_Temp, false);
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::iterator _Vector_base<T, TAlloc>::_Make_iterator(pointer_t _Ptr)
    {
        auto ret = iterator();
        ret._this._Iter._Ptr = _Ptr;
        return ret;
    }

    GENERIC_HEADER inline TAlloc _Vector_base<T, TAlloc>::_Getal()
    {
        return _al;
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::_Change_array(pointer_t _Newvec, size_t _Newsize, size_t _Newcapacity)
    {
        auto _Al = _Getal();
        auto% _My_data = _this._Data->_Mypair._Myval2;
        pointer_t% _Myfirst = _My_data._Myfirst;
        pointer_t% _Mylast = _My_data._Mylast;
        pointer_t% _Myend = _My_data._Myend;

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

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::pointer_t _Vector_base<T, TAlloc>::_Emplace_reallocate(pointer_t _Whereptr, bool byMove, T% val)
    {
        auto% _Myfirst = _this._Data->_Mypair._Myval2._Myfirst;
        auto% _Mylast = _this._Data->_Mypair._Myval2._Mylast;

        const auto _Whereoff = static_cast<size_t>((_Whereptr - _Myfirst) / type_size);
        const auto _Oldsize = static_cast<size_t>((_Mylast - _Myfirst) / type_size);

        if (_Oldsize == max_size())
            throw gcnew System::OutOfMemoryException("vector too long.");

        const size_t _Newsize = _Oldsize + 1;
        const size_t _Newcapacity = _Calculate_growth(_Newsize);

        pointer_t _Newvec = static_cast<pointer_t>(_al->allocate(_Newcapacity));
        pointer_t _Constructed_last = _Newvec + (_Whereoff + 1) * type_size;
        pointer_t _Constructed_first = _Constructed_last;

        try
        {
            _Construct(_Newvec + (_Whereoff)*type_size, val, byMove);
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

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::_Resize_reallocate(size_t _Newsize, T% val)
    {
        if (_Newsize > max_size()) {
            throw gcnew System::OutOfMemoryException("vector too long.");
        }

        auto% _Al = _Getal();
        auto% _My_data = _this._Data->_Mypair._Myval2;
        pointer_t% _Myfirst = _My_data._Myfirst;
        pointer_t% _Mylast = _My_data._Mylast;

        const auto _Oldsize = size();
        const size_t _Newcapacity = _Calculate_growth(_Newsize);

        const pointer_t _Newvec = reinterpret_cast<pointer_t>(_Al->allocate(_Newcapacity));
        const pointer_t _Appended_first = _Newvec + _Oldsize * type_size;
        pointer_t _Appended_last = _Appended_first;

        try
        {
            _Appended_last = _Uninitialized_fill_n(_Appended_first, _Newsize - _Oldsize, val);

            if (ICppStdClass::isMoveable || !ICppStdClass::isCopyable)
                _Uninitialized_move(_Myfirst, _Mylast, _Newvec);
            else
                _Uninitialized_copy(_Myfirst, _Mylast, _Newvec);
        }
        catch (...)
        {
            _Destroy_range(_Appended_first, _Appended_last);
            _Al->deallocate(_Newvec, _Newcapacity);
            throw;
        }
        _Change_array(_Newvec, _Newsize, _Newcapacity);
    }

    GENERIC_HEADER inline T% _Vector_base<T, TAlloc>::_Emplace_back_with_unused_capacity(bool byMove, T% val)
    {
        auto temp_ptr = _this._Data->_Mypair._Myval2._Mylast;

        auto dval = uintptr_t(_this._Data->_Mypair._Myval2._Myend) - uintptr_t(_this._Data->_Mypair._Myval2._Mylast);

        if (dval <= 0 && dval % type_size != 0)
            throw gcnew LiteLoader::NET::MemoryCorruptedException(
                String::Format("Error internal vector data has been detected. _Myend:{0},_Mylast:{1}.",
                    uintptr_t(_this._Data->_Mypair._Myval2._Myend),
                    uintptr_t(_this._Data->_Mypair._Myval2._Mylast)));

        _Construct(temp_ptr, val, byMove);
        _this._Data->_Mypair._Myval2._Mylast += type_size;

        return val;
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::_Destroy_range(pointer_t _First, pointer_t _Last)
    {
        if (isValueType)
        {
            if (!ICppStdClass::isICppClass)
                return;

            auto _Temp = T();
            for (auto* ptr = _First; ptr != _Last; ptr += type_size)
            {
                ICppStdClass::_Tv_fptr.set_native_pointer(&_Temp, nint_t(ptr), false);
                ICppStdClass::_Tv_fptr.dtor(&_Temp);
            }
        }
        else
        {
            auto _Temp = gcnew T();
            for (auto* ptr = _First; ptr != _Last; ptr += type_size)
            {
                ICppStdClass::_Tr_fptr.set_native_pointer(_Temp, nint_t(ptr), false);
                ICppStdClass::_Tr_fptr.dtor(_Temp);
            }
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

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::pointer_t _Vector_base<T, TAlloc>::_Uninitialized_fill_n(pointer_t _First, size_t _Count, T% val)
    {
        pointer_t _Ptr = nullptr;

        if (isValueType)
        {
            if (ICppStdClass::isICppClass)
                _Ptr = reinterpret_cast<pointer_t>(ICppStdClass::_Tv_fptr.get_intptr(&val).ToPointer());
            else
            {
                pin_ptr<T> p = &val;
                _Ptr = reinterpret_cast<pointer_t>(p);
            }
        }
        else
        {
            _Ptr = reinterpret_cast<pointer_t>(ICppStdClass::_Tr_fptr.get_intptr(val).ToPointer());
        }

        pointer_t _Last = _First + _Count * type_size;

        for (auto ptr = _First; ptr != _Last; _Ptr += type_size)
        {
            Unsafe::CopyBlock(ptr, _Ptr, static_cast<uint32_t>(type_size));
        }

        return _First + _Count * type_size;
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::pointer_t _Vector_base<T, TAlloc>::_Copy_backward_memmove(pointer_t _First, pointer_t _Last, pointer_t _Dest)
    {
        const auto _Count = _Last - _First;
        memmove(_Dest - _Count, _First, _Count);

        return _Dest - (_First - _Last);
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::pointer_t _Vector_base<T, TAlloc>::_Copy_memmove(pointer_t _First, pointer_t _Last, pointer_t _Dest)
    {
        memmove(_Dest, _First, _Last - _First);

        return _Dest + (_Last - _First);
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::pointer_t _Vector_base<T, TAlloc>::_Move_backward_unchecked(pointer_t _First, pointer_t _Last, pointer_t _Dest)
    {
        return _Copy_backward_memmove(_First, _Last, _Dest);
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::pointer_t _Vector_base<T, TAlloc>::_Move_unchecked(pointer_t _First, pointer_t _Last, pointer_t _Dest)
    {
        return _Copy_memmove(_First, _Last, _Dest);
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::_Vector_base()
    {
        this->_this = _value_vector();
        this->_this._Element_type_size = type_size;
        this->_this._Constructed_by_managed = true;
        this->_this._Data = reinterpret_cast<decltype(_this._Data)>(
            ::operator new(sizeof(_Vector_data)));
        *this->_this._Data = _Vector_data();

        this->_al = gcnew TAlloc();
        this->ownsNativeInstance = true;
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::_Vector_base(nint_t ptr)
        :_this(ptr, type_size)
    {
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::_Vector_base(_Vector_base^ vec)
    {
        _Vector_base();

        const auto _Newsize = vec->size();
        const auto _Newcapacity = vec->size();
        auto% _Al = _Getal();

        auto _Newvec = reinterpret_cast<pointer_t>(_Al->allocate(_Newsize));
        auto _Newlast = _Newvec + _Newsize * type_size;
        auto _Newend = _Newlast;

        auto _Constructed_first = _Newvec;
        auto _Constructed_last = _Constructed_first;

        try
        {
            for each (auto var in vec)
            {
                _Construct(_Constructed_last, var, false);
                _Constructed_last += type_size;
            }
        }
        catch (...)
        {
            _Destroy_range(_Constructed_first, _Constructed_last);
            _Al->deallocate(_Newvec, _Newsize);
            throw;
        }

        _Change_array(_Newvec, _Newsize, _Newcapacity);
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::_Vector_base(move<_Vector_base^> vec)
    {
        auto _Instance = vec.instance;
        this->_this = _Instance->_this;
        this->ownsNativeInstance = _Instance->ownsNativeInstance;
        this->_al = _Instance->_al;

        auto _Emptyvec = gcnew _Vector_base();
        _Instance->_this = _Emptyvec->_this;
        _Instance->ownsNativeInstance = _Emptyvec->ownsNativeInstance;
        _Instance->_al = _Emptyvec->_al;
    }

    GENERIC_HEADER _Vector_base<T, TAlloc>::!_Vector_base()
    {
        if (ownsNativeInstance)
        {
            this->Destruct();
            ::operator delete(_this._Data);
        }
    }

    GENERIC_HEADER _Vector_base<T, TAlloc>::~_Vector_base()
    {
        this->!_Vector_base();
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

    GENERIC_HEADER T _Vector_base<T, TAlloc>::front()
    {
        auto% _My_data = _this._Data->_Mypair._Myval2;
        if (isValueType)
        {
            return Unsafe::AsRef<T>(_My_data._Myfirst);
        }
        else
        {
            auto _Temp = gcnew T;
            ICppStdClass::_Tr_fptr.set_native_pointer(_Temp, nint_t(_My_data._Myfirst), false);
            return _Temp;
        }
    }

    GENERIC_HEADER T _Vector_base<T, TAlloc>::back()
    {
        auto% _My_data = _this._Data->_Mypair._Myval2;
        if (isValueType)
        {
            return Unsafe::AsRef<T>(_My_data._Myfirst - type_size);
        }
        else
        {
            auto _Temp = gcnew T;
            ICppStdClass::_Tr_fptr.set_native_pointer(_Temp, nint_t(_My_data._Myfirst - type_size), false);
            return _Temp;
        }
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

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::clear()
    {
        auto% _My_data = _this._Data->_Mypair._Myval2;
        pointer_t% _Myfirst = _My_data._Myfirst;
        pointer_t% _Mylast = _My_data._Mylast;

        if (_Myfirst == _Mylast)
            return;

        _Destroy_range(_Myfirst, _Mylast);
        _Mylast = _Myfirst;
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::iterator _Vector_base<T, TAlloc>::emplace(iterator where, T val)
    {
        if (!isValueType && !ICppStdClass::isCopyable)
            throw gcnew LiteLoader::NET::InvalidTypeException(typeof(T)->FullName + " is not copyable.");

        const pointer_t _Whereptr = where._this._Iter._Ptr;
        auto% _My_data = _this._Data->_Mypair._Myval2;
        const pointer_t _Oldlast = _My_data._Mylast;

        if (_Oldlast != _My_data._Myend)
        {
            if (_Whereptr == _Oldlast)
                _Emplace_back_with_unused_capacity(false, val);
            else
            {
                _My_data._Mylast += type_size;
                _Move_backward_unchecked(_Whereptr, _Oldlast - type_size, _Oldlast);
                _Construct(_Whereptr, val, false);
            }

            return _Make_iterator(_Whereptr);
        }
        else
            return _Make_iterator(_Emplace_reallocate(_Whereptr, false, val));
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::iterator _Vector_base<T, TAlloc>::insert(iterator where, T val)
    {
        return emplace(where, val);
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::iterator _Vector_base<T, TAlloc>::emplace(iterator where, move<T> val)
    {
        if (!isValueType && !ICppStdClass::isCopyable)
            throw gcnew LiteLoader::NET::InvalidTypeException(typeof(T)->FullName + " is not moveable.");

        const pointer_t _Whereptr = where._this._Iter._Ptr;
        auto% _My_data = _this._Data->_Mypair._Myval2;
        const pointer_t _Oldlast = _My_data._Mylast;

        if (_Oldlast != _My_data._Myend)
        {
            if (_Whereptr == _Oldlast)
                _Emplace_back_with_unused_capacity(true, val.instance);
            else
            {
                _My_data._Mylast += type_size;
                _Move_backward_unchecked(_Whereptr, _Oldlast - type_size, _Oldlast);
                _Construct(_Whereptr, val.instance, true);
            }

            return _Make_iterator(_Whereptr);
        }
        else
            return _Make_iterator(_Emplace_reallocate(_Whereptr, true, val.instance));
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::iterator _Vector_base<T, TAlloc>::insert(iterator where, move<T> val)
    {
        return emplace(where, val);
    }

    GENERIC_HEADER inline T _Vector_base<T, TAlloc>::push_back(T val)
    {
        return emplace_back(val);
    }

    GENERIC_HEADER inline T _Vector_base<T, TAlloc>::push_back(move<T> val)
    {
        return emplace_back(val);
    }

    GENERIC_HEADER inline T _Vector_base<T, TAlloc>::emplace_back(T val)
    {
        if (!isValueType && !ICppStdClass::isCopyable)
            throw gcnew LiteLoader::NET::InvalidTypeException(typeof(T)->FullName + " is not copyable.");

        auto% _My_data = _this._Data->_Mypair._Myval2;
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

            auto _ptr = _Emplace_reallocate(_this._Data->_Mypair._Myval2._Mylast, false, val);

            if (isValueType)
                return Unsafe::AsRef<T>(_ptr);
            else
            {
                auto _temp = gcnew T();
                ICppStdClass::_Tr_fptr.set_native_pointer(_temp, nint_t(_ptr), false);
                return _temp;
            }
        }
    }

    GENERIC_HEADER inline T _Vector_base<T, TAlloc>::emplace_back(move<T> val)
    {
        if (!isValueType && !ICppStdClass::isCopyable)
            throw gcnew LiteLoader::NET::InvalidTypeException(typeof(T)->FullName + " is not copyable.");

        auto% _My_data = _this._Data->_Mypair._Myval2;
        auto% _Mylast = _My_data._Mylast;

        if (_Mylast != _My_data._Myend)
        {
            return _Emplace_back_with_unused_capacity(true, val.instance);
        }
        else
        {
            if (_Mylast > _My_data._Myend)
            {
                throw gcnew LiteLoader::NET::MemoryCorruptedException(
                    String::Format("Error internal vector data has been detected. size:{0},capacity:{1}.",
                        size(), capacity()));
            }

            auto _ptr = _Emplace_reallocate(_this._Data->_Mypair._Myval2._Mylast, true, val.instance);

            if (isValueType)
                return Unsafe::AsRef<T>(_ptr);
            else
            {
                auto _temp = gcnew T();
                ICppStdClass::_Tr_fptr.set_native_pointer(_temp, nint_t(_ptr), false);
                return _temp;
            }
        }
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>::iterator _Vector_base<T, TAlloc>::erase(iterator where)
    {
        const pointer_t _Whereptr = where._this._Iter._Ptr;
        auto% _My_data = _this._Data->_Mypair._Myval2;
        pointer_t% _Mylast = _My_data._Mylast;

        if (ICppStdClass::isICppClass)
        {
            T _Temp;
            if (isValueType)
            {
                _Temp = T();
                ICppStdClass::_Tv_fptr.set_native_pointer(&_Temp, nint_t(_Whereptr), false);
                ICppStdClass::_Tv_fptr.dtor(&_Temp);
            }
            else
            {
                _Temp = gcnew T();
                ICppStdClass::_Tr_fptr.set_native_pointer(_Temp, nint_t(_Whereptr), false);
                ICppStdClass::_Tr_fptr.dtor(_Temp);
            }
        }
        _Move_unchecked(_Whereptr + type_size, _Mylast, _Whereptr);

        _Mylast -= type_size;

        return _Make_iterator(_Whereptr);
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::resize(size_t newSize, T% val)
    {
        auto _Al = _Getal();
        auto% _My_data = _this._Data->_Mypair._Myval2;
        pointer_t% _Myfirst = _My_data._Myfirst;
        pointer_t% _Mylast = _My_data._Mylast;
        const auto _Oldsize = size();

        if (newSize < _Oldsize)
        {
            const pointer_t _Newlast = _Myfirst + newSize * type_size;
            _Destroy_range(_Newlast, _Mylast);
            _Mylast = _Newlast;
            return;
        }

        if (newSize > _Oldsize)
        {
            const auto _Oldcapacity = capacity();
            if (newSize > _Oldcapacity) {
                _Resize_reallocate(newSize, val);
                return;
            }

            const pointer_t _Oldlast = _Mylast;
            _Uninitialized_fill_n(_Oldlast, newSize - _Oldsize, val);
        }
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::resize(size_t newSize)
    {
        T _Val;
        if (isValueType)    _Val = T();
        else                _Val = gcnew T;

        resize(newSize, _Val);
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::swap(_Vector_base^ right)
    {
        if (!Object::Equals(this, right))
        {
            auto _Right_al = right->_al;
            auto _Right_vector = right->_this;
            auto _Right_owns = right->ownsNativeInstance;

            right->_this = this->_this;
            right->_al = this->_al;
            right->ownsNativeInstance = this->ownsNativeInstance;

            this->_this = _Right_vector;
            this->_al = _Right_al;
            this->ownsNativeInstance = _Right_owns;
        }
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::reserve(size_t newCapacity)
    {
        auto% _Al = _Getal();
        auto% _My_data = _this._Data->_Mypair._Myval2;
        pointer_t% _Myfirst = _My_data._Myfirst;
        pointer_t% _Mylast = _My_data._Mylast;

        const auto _Size = size();

        const pointer_t _Newvec = reinterpret_cast<pointer_t>(_Al->allocate(newCapacity));

        try
        {
            if (ICppStdClass::isMoveable || !ICppStdClass::isCopyable)
                _Uninitialized_move(_Myfirst, _Mylast, _Newvec);
            else
                _Uninitialized_copy(_Myfirst, _Mylast, _Newvec);
        }
        catch (...)
        {
            _Al->deallocate(_Newvec, newCapacity);
            throw;
        }
        _Change_array(_Newvec, _Size, newCapacity);
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
        if (index < 0 || index > size())
            throw gcnew System::ArgumentOutOfRangeException;

        return at(index).Current;
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::default::set(int index, T val)
    {
        if (IsReadOnly)
            throw gcnew System::NotSupportedException;

        if (index < 0 && index > size())
            throw gcnew System::ArgumentOutOfRangeException;

        _Construct(at(index)._this._Iter._Ptr, val, false);
    }

    GENERIC_HEADER inline bool _Vector_base<T, TAlloc>::IsReadOnly::get()
    {
        return false;
    }

    GENERIC_HEADER inline bool _Vector_base<T, TAlloc>::Contains(T item)
    {
        return IndexOf(item) != -1;
    }

    GENERIC_HEADER inline int _Vector_base<T, TAlloc>::IndexOf(T item)
    {
        if (isValueType)
        {
        CHECK_CONTAINS_BY_BYTES:

            pin_ptr<T> p = &item;
            auto _Ptr = reinterpret_cast<pointer_t>(p);
            auto% _My_data = _this._Data->_Mypair._Myval2;
            auto% _Mylast = _My_data._Mylast;

            int index = 0;
            for (auto _Iterptr = _My_data._Myfirst; _Iterptr != _Mylast; _Iterptr += type_size)
            {
                bool _Isequals = true;
                for (int i = 0; i < type_size; ++i)
                {
                    if (*(_Ptr + i) != *(_Iterptr + i))
                    {
                        _Isequals = false;
                        break;
                    }
                }
                if (_Isequals)
                    return index;
                else
                    ++index;
            }

            return -1;
        }
        else
        {
            auto% op_equality_fptr = ICppStdClass::_Tr_fptr.op_equality;
            if (op_equality_fptr == nullptr)
            {
                goto CHECK_CONTAINS_BY_BYTES;
            }
            else
            {
                int index = 0;
                for each (auto var in this)
                {
                    if (op_equality_fptr(var, item))
                        return index;
                    else
                        ++index;
                }

                return -1;
            }
        }
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::Add(T item)
    {
        if (IsReadOnly)
            throw gcnew System::NotSupportedException;

        emplace_back(item);
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::Clear()
    {
        if (IsReadOnly)
            throw gcnew System::NotSupportedException;

        clear();
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::CopyTo(array<T, 1>^ array, int arrayIndex)
    {
        if (array == nullptr)
            throw gcnew System::ArgumentNullException;

        if (arrayIndex < 0)
            throw gcnew System::ArgumentOutOfRangeException;

        if (size() > (static_cast<uint64_t>(array->Length) - arrayIndex))
            throw gcnew System::ArgumentException;

        for each (auto var in this)
        {
            if (ICppStdClass::isCopyable)
                array[arrayIndex] = _Copy_Instance(var);
            else
                array[arrayIndex] = var;

            ++arrayIndex;
        }
    }

    GENERIC_HEADER inline bool _Vector_base<T, TAlloc>::Remove(T item)
    {
        if (IsReadOnly)
            throw gcnew System::NotSupportedException;

        auto index = IndexOf(item);
        if (index == -1)
            return false;

        erase(at(index));
        return true;
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::Insert(int index, T item)
    {
        if (IsReadOnly)
            throw gcnew System::NotSupportedException;

        if (index < 0 || index > size())
            throw gcnew System::ArgumentOutOfRangeException;

        insert(at(index), item);
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::RemoveAt(int index)
    {
        if (index < 0 || index > size())
            throw gcnew System::ArgumentOutOfRangeException;

        erase(at(index));
    }

    GENERIC_HEADER inline nint_t _Vector_base<T, TAlloc>::Intptr::get()
    {
        return nint_t(_this._Data);
    }
    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::Intptr::set(nint_t value)
    {
        _this._Data = reinterpret_cast<decltype(_this._Data)>(value.ToPointer());
    }
    GENERIC_HEADER inline bool _Vector_base<T, TAlloc>::OwnsNativeInstance::get()
    {
        return ownsNativeInstance;
    }
    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::OwnsNativeInstance::set(bool value)
    {
        ownsNativeInstance = value;
    }

    GENERIC_HEADER inline void _Vector_base<T, TAlloc>::Destruct()
    {
        auto% _Al = _Getal();
        auto% _My_data = _this._Data->_Mypair._Myval2;
        auto% _Myfirst = _My_data._Myfirst;
        auto% _Mylast = _My_data._Mylast;
        auto% _Myend = _My_data._Myend;

        _Destroy_range(_Myfirst, _Mylast);
        _Al->deallocate(_Myfirst, (intptr_t(_Myfirst) - intptr_t(_Myend)) / type_size);
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

    GENERIC_HEADER inline _Vector_base<T, TAlloc>^ _Vector_base<T, TAlloc>::ConstructInstanceByCopy(_Vector_base<T, TAlloc>^ _Right)
    {
        return gcnew _Vector_base(_Right);
    }

    GENERIC_HEADER inline _Vector_base<T, TAlloc>^ _Vector_base<T, TAlloc>::ConstructInstanceByMove(move<_Vector_base<T, TAlloc>^> _Right)
    {
        return gcnew _Vector_base(_Right);
    }
}