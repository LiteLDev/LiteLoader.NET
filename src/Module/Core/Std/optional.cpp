#include "optional.hpp"
#include <src/Module/Core/Std/Exceptions/exception.hpp>

namespace LiteLoader::NET::Std
{
#define GENERIC_HEADER generic<typename T> where T : gcnew()

    GENERIC_HEADER inline optional<T>::optional()
    {
        this->ptr = (pointer_t)::operator new(ICppStdClass::type_size + 8);
        *reinterpret_cast<bool*>((this->ptr + ICppStdClass::type_size)) = false;
        ownsNativeInstance = true;
    }

    GENERIC_HEADER inline optional<T>::optional(nint_t ptr)
    {
        this->ptr = (pointer_t)ptr.ToPointer();
        ownsNativeInstance = false;
    }

    GENERIC_HEADER inline optional<T>::optional(nint_t ptr, bool ownsInstance)
    {
        this->ptr = (pointer_t)ptr.ToPointer();
        ownsNativeInstance = ownsInstance;
    }

    GENERIC_HEADER inline optional<T>::optional(optional^ val)
    {
        if (ICppStdClass::isCopyable)
        {
            T _Temp;
            if (ICppStdClass::isValueType)
            {
                _Temp = T();
                ICppStdClass::_Tv_fptr.set_native_pointer(&_Temp, nint_t(val->ptr), false);
                _Temp = ICppStdClass::_Tv_fptr.ctor_copy(nullptr, _Temp);


                this->ptr = (pointer_t)::operator new(ICppStdClass::type_size + 8);
                Unsafe::CopyBlock(ptr, &_Temp, static_cast<uint32_t>(ICppStdClass::type_size + 1));
            }
            else
            {
                _Temp = gcnew T;
                ICppStdClass::_Tr_fptr.set_native_pointer(_Temp, nint_t(val->ptr), false);
                _Temp = ICppStdClass::_Tr_fptr.ctor_copy(nullptr, _Temp);


                this->ptr = (pointer_t)::operator new(ICppStdClass::type_size + 8);
                Unsafe::CopyBlock(ptr, ICppStdClass::_Tr_fptr.get_intptr(_Temp).ToPointer(),
                    static_cast<uint32_t>(ICppStdClass::type_size + 1));

                ICppStdClass::_Tr_fptr.set_own_instance(_Temp, false);
                delete _Temp;
            }
            ownsNativeInstance = true;
        }
        else
        {
            throw gcnew LiteLoader::NET::InvalidTypeException(typeof(T)->FullName + " is not a copyable type.");
        }
    }

    GENERIC_HEADER inline optional<T>::optional(move<optional^> val)
    {
        if (ICppStdClass::isMoveable)
        {
            T _Temp;
            if (ICppStdClass::isValueType)
            {
                _Temp = T();
                ICppStdClass::_Tv_fptr.set_native_pointer(&_Temp, nint_t(val.instance->ptr), false);
                _Temp = ICppStdClass::_Tv_fptr.ctor_move(nullptr, move<T>(_Temp));


                this->ptr = (pointer_t)::operator new(ICppStdClass::type_size + 8);
                Unsafe::CopyBlock(ptr, &_Temp, static_cast<uint32_t>(ICppStdClass::type_size + 1));
            }
            else
            {
                _Temp = gcnew T;
                ICppStdClass::_Tr_fptr.set_native_pointer(_Temp, nint_t(val.instance->ptr), false);
                _Temp = ICppStdClass::_Tr_fptr.ctor_move(nullptr, move<T>(_Temp));


                this->ptr = (pointer_t)::operator new(ICppStdClass::type_size + 8);
                Unsafe::CopyBlock(ptr, ICppStdClass::_Tr_fptr.get_intptr(_Temp).ToPointer(),
                    static_cast<uint32_t>(ICppStdClass::type_size + 1));

                ICppStdClass::_Tr_fptr.set_own_instance(_Temp, false);
                delete _Temp;
            }
        }
        else
        {
            throw gcnew LiteLoader::NET::InvalidTypeException(typeof(T)->FullName + " is not a moveable type.");
        }
    }

    GENERIC_HEADER inline optional<T>::!optional()
    {
        if (ownsNativeInstance)
        {
            this->Destruct();
            ::operator delete(ptr);
        }
    }

    GENERIC_HEADER inline optional<T>::~optional()
    {
        this->!optional();
    }

    GENERIC_HEADER inline bool optional<T>::has_value()
    {
        return *reinterpret_cast<bool*>(*(ptr + ICppStdClass::type_size));
    }

    GENERIC_HEADER inline T optional<T>::value()
    {
        if (!has_value())
            throw gcnew LiteLoader::NET::Std::exception(
                gcnew LiteLoader::NET::Std::Internal::__Exception());
        
        if (ICppStdClass::isValueType)
        {
            if (ICppStdClass::isPointer)
            {
                auto ret = T();
                ICppStdClass::_Tv_fptr.set_native_pointer(&ret, static_cast<nint_t>(ptr), false);
                return ret;
            }
            return Unsafe::Read<T>(ptr);
        }
        else
        {
            auto ret = gcnew T();
            ICppStdClass::_Tr_fptr.set_native_pointer(ret, static_cast<nint_t>(ptr), false);
            return ret;
        }
    }

    GENERIC_HEADER inline T optional<T>::value_or(T val)
    {
        if (has_value())
            return value();
        else
            return val;
    }

    GENERIC_HEADER inline nint_t optional<T>::Intptr::get()
    {
        return nint_t(ptr);
    }

    GENERIC_HEADER inline void optional<T>::Intptr::set(nint_t value)
    {
        ptr = reinterpret_cast<pointer_t>(value.ToPointer());
    }

    GENERIC_HEADER inline bool optional<T>::OwnsNativeInstance::get()
    {
        return ownsNativeInstance;
    }

    GENERIC_HEADER inline void optional<T>::OwnsNativeInstance::set(bool value)
    {
        ownsNativeInstance = value;
    }

    GENERIC_HEADER inline void optional<T>::Destruct()
    {
        if (*reinterpret_cast<bool*>(*(ptr + ICppStdClass::type_size)))
        {
            T _Temp;
            if (ICppStdClass::isValueType)
            {
                if (ICppStdClass::isICppClass)
                {
                    _Temp = T();
                    ICppStdClass::_Tv_fptr.set_native_pointer(&_Temp, nint_t(ptr), false);
                    ICppStdClass::_Tv_fptr.dtor(&_Temp);
                    return;
                }
            }
            else
            {
                _Temp = gcnew T;
                ICppStdClass::_Tr_fptr.set_native_pointer(_Temp, nint_t(ptr), false);
                ICppStdClass::_Tr_fptr.dtor(_Temp);
                delete _Temp;
            }
        }
    }

    GENERIC_HEADER inline size_t optional<T>::GetClassSize()
    {
        return ICppStdClass::type_size + 1;
    }

    GENERIC_HEADER inline void optional<T>::SetNativePointer(nint_t ptr, bool ownsInstance)
    {
        this->ptr = reinterpret_cast<pointer_t>(ptr.ToPointer());
        ownsNativeInstance = ownsInstance;
    }

    //ICopyable
    GENERIC_HEADER inline optional<T>^ optional<T>::ConstructInstanceByCopy(optional<T>^ _Right)
    {
        return gcnew optional(_Right);
    }
    //IMoveable
    GENERIC_HEADER inline optional<T>^ optional<T>::ConstructInstanceByMove(move<optional<T>^> _Right)
    {
        return gcnew optional(_Right);
    }
}