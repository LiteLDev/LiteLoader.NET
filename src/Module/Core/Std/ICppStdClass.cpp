#include "ICppStdClass.hpp"

namespace LiteLoader::NET::Std::Internal
{
    generic<typename T>
    ICppStdClass<T>::_Value_type_funcptr_def ICppStdClass<T>::_handle_value_type(SystemType^ _Ty)
    {
        auto ret = _Value_type_funcptr_def();

        type_size = Unsafe::SizeOf<T>();
        isValueType = true;
        isCopyable = true;

        if (_Ty->Name == "pointer`1" && _Ty->Namespace == "LiteLoader.NET")
        {
            isValueType = true;
            isPointer = true;


            ret.get_intptr = reinterpret_cast<decltype(ret)::_Get_intptr_fptr>(
                _get_method_fptr(true, "get_Intptr", PackArray<SystemType^>()));

            ret.set_native_pointer = reinterpret_cast<decltype(ret)::_Set_native_pointer_fptr>(
                _get_method_fptr(true, "SetNativePointer", PackArray(typeof(nint_t), typeof(bool))));

            return ret;
        }

        if (_Ty->IsAssignableTo(typeof(ICppClass)))
        {
            isICppClass = true;

            ret.get_intptr = reinterpret_cast<decltype(ret)::_Get_intptr_fptr>(
                _get_method_fptr(false, "get_Intptr", PackArray<SystemType^>()));

            ret.set_intptr = reinterpret_cast<decltype(ret)::_Set_intptr_fptr>(
                _get_method_fptr(false, "set_Intptr", PackArray(typeof(nint_t))));

            ret.get_own_instance = reinterpret_cast<decltype(ret)::_Get_OwnInstance_fptr>(
                _get_method_fptr(false, "get_OwnsNativeInstance", PackArray<SystemType^>()));

            ret.set_own_instance = reinterpret_cast<decltype(ret)::_Set_OwnInstance_fptr>(
                _get_method_fptr(false, "set_OwnsNativeInstance", PackArray(typeof(bool))));

            ret.dtor = reinterpret_cast<decltype(ret)::_Dtor_fptr>(
                _get_method_fptr(false, "Destruct", PackArray<SystemType^>()));
        }

        if (_Ty->IsAssignableTo(typeof(IPointerConstructable)))
        {
            isIPointerConstructable = true;

            ret.set_native_pointer = reinterpret_cast<decltype(ret)::_Set_native_pointer_fptr>(
                _get_method_fptr(false, "SetNativePointer", PackArray(typeof(nint_t), typeof(bool))));
        }

        if (_Ty->IsAssignableTo(_ICopyable_type->MakeGenericType(_Ty)))
        {
            if (_Ty->GetConstructor(PackArray(_Ty)) != nullptr)
            {
                ret.ctor_copy = reinterpret_cast<decltype(ret)::_Ctor_copy_fptr>(
                    _get_method_fptr(false, "ConstructInstanceByCopy", PackArray(_Ty)));

                if (ret.ctor_copy != nullptr)
                    isCopyable = true;
            }
        }

        if (_Ty->IsAssignableTo(_IMoveable_type->MakeGenericType(_Ty)))
        {
            if (_Ty->GetConstructor(PackArray(_Ty)) != nullptr)
            {
                ret.ctor_move = reinterpret_cast<decltype(ret)::_Ctor_move_fptr>(
                    _get_method_fptr(false, "ConstructInstanceByMove", PackArray(_Move_type->MakeGenericType(_Ty))));

                if (ret.ctor_move != nullptr)
                    isMoveable = true;
            }
        }

        return ret;
    }

    generic<typename T>
    ICppStdClass<T>::_Ref_type_funcptr_def ICppStdClass<T>::_handle_ref_type(SystemType^ _Ty)
    {
        auto ret = _Ref_type_funcptr_def();

        using System::Reflection::BindingFlags;
        auto field = _Ty->GetField(
            "NativeClassSize", BindingFlags::Public | BindingFlags::Static | BindingFlags::FlattenHierarchy);


        if (field != nullptr && field->IsLiteral)
            type_size = static_cast<size_t>(field->GetValue(nullptr));
        else
            throw gcnew LiteLoader::NET::InvalidTypeException(_Ty->FullName + " missing const(literal) field 'NativeClassSize'.");

        if (_Ty->IsAssignableTo(typeof(IConstructableCppClass)))
        {
            isICppClass = true;
            isIPointerConstructable = true;

            ret.get_intptr = reinterpret_cast<decltype(ret)::_Get_intptr_fptr>(
                _get_method_fptr(true, "get_Intptr", PackArray<SystemType^>()));

            ret.set_intptr = reinterpret_cast<decltype(ret)::_Set_intptr_fptr>(
                _get_method_fptr(true, "set_Intptr", PackArray(typeof(nint_t))));

            ret.get_own_instance = reinterpret_cast<decltype(ret)::_Get_OwnInstance_fptr>(
                _get_method_fptr(true, "get_OwnsNativeInstance", PackArray<SystemType^>()));

            ret.set_own_instance = reinterpret_cast<decltype(ret)::_Set_OwnInstance_fptr>(
                _get_method_fptr(true, "set_OwnsNativeInstance", PackArray(typeof(bool))));

            ret.dtor = reinterpret_cast<decltype(ret)::_Dtor_fptr>(
                _get_method_fptr(true, "Destruct", PackArray<SystemType^>()));

            ret.set_native_pointer = reinterpret_cast<decltype(ret)::_Set_native_pointer_fptr>(
                _get_method_fptr(true, "SetNativePointer", PackArray(typeof(nint_t), typeof(bool))));
        }
        else
            throw gcnew LiteLoader::NET::InvalidTypeException(_Ty->FullName  + " missing const(literal) field 'NativeClassSize'.");


        if (_Ty->IsAssignableTo(_ICopyable_type->MakeGenericType(_Ty)))
        {
            if (_Ty->GetConstructor(PackArray(_Ty)) != nullptr)
            {
                ret.ctor_copy = reinterpret_cast<decltype(ret)::_Ctor_copy_fptr>(
                    _get_method_fptr(true, "ConstructInstanceByCopy", PackArray(_Ty)));

                if (ret.ctor_copy != nullptr)
                    isCopyable = true;
            }
            else
                throw gcnew LiteLoader::NET::InvalidTypeException(_Ty->FullName + " implements the 'ICopyable' interface but does not have the copy ctor.");
        }

        if (_Ty->IsAssignableTo(_IMoveable_type->MakeGenericType(_Ty)))
        {
            if (_Ty->GetConstructor(PackArray(_Ty)) != nullptr)
            {
                ret.ctor_move = reinterpret_cast<decltype(ret)::_Ctor_move_fptr>(
                    _get_method_fptr(false, "ConstructInstanceByMove", PackArray(_Move_type->MakeGenericType(_Ty))));

                if (ret.ctor_move != nullptr)
                    isMoveable = true;
            }
            else
                throw gcnew LiteLoader::NET::InvalidTypeException(_Ty->FullName + " implements the 'IMoveable' interface but does not have the move ctor.");
        }

        return ret;
    }

    generic<typename T>
    void* ICppStdClass<T>::_get_method_fptr(bool _ThrowExc, String^ _Name, array<SystemType^>^ _Params)
    {
        auto _Fty = typeof(T)->GetMethod(_Name, _Params);

        if (_Fty == nullptr)
            if (_ThrowExc)
                goto THROW;

        auto ret = _Fty->MethodHandle.GetFunctionPointer().ToPointer();

        if (ret == nullptr)
            if (_ThrowExc)
                goto THROW;

        return ret;

    THROW:
        throw gcnew LiteLoader::NET::InvalidTypeException(
            String::Format("{0} missing Method '{1}'.", typeof(T)->FullName, _Name));
    }
}