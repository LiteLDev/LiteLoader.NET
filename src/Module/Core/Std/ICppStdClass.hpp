#pragma once
#include <src/Main/DotNETGlobal.hpp>
#include <src/Module/Core/ICppClass.hpp>
#include "ICopyable.hpp"
#include "move.hpp"

namespace LiteLoader::NET::Std::Internal
{
    using System::Reflection::MethodInfo;

    generic<typename T>
    public interface class ICppStdClass
    {
        using bool_t = System::Boolean;

        value struct _Value_type_funcptr_def
        {
            typedef nint_t(__clrcall* _Get_intptr_fptr)(interior_ptr<T>);
            typedef void(__clrcall* _Set_intptr_fptr)(interior_ptr<T>, nint_t);

            typedef bool(__clrcall* _Get_OwnInstance_fptr)(interior_ptr<T>);
            typedef void(__clrcall* _Set_OwnInstance_fptr)(interior_ptr<T>, bool_t);

            typedef void(__clrcall* _Set_native_pointer_fptr)(interior_ptr<T>, nint_t, bool_t);

            typedef T(__clrcall* _Ctor_copy_fptr)(interior_ptr<T>, T);
            typedef T(__clrcall* _Ctor_move_fptr)(interior_ptr<T>, move<T>);
            typedef void(__clrcall* _Dtor_fptr)(interior_ptr<T>);


            static _Get_intptr_fptr get_intptr;
            static _Set_intptr_fptr set_intptr;

            static _Get_OwnInstance_fptr get_own_instance;
            static _Set_OwnInstance_fptr set_own_instance;

            static _Set_native_pointer_fptr set_native_pointer;

            static _Ctor_copy_fptr ctor_copy;
            static _Ctor_move_fptr ctor_move;
            static _Dtor_fptr dtor;
        };

        value struct _Ref_type_funcptr_def
        {
            typedef nint_t(__clrcall* _Get_intptr_fptr)(Object^);
            typedef void(__clrcall* _Set_intptr_fptr)(Object^, nint_t);

            typedef bool(__clrcall* _Get_OwnInstance_fptr)(Object^);
            typedef void(__clrcall* _Set_OwnInstance_fptr)(Object^, bool_t);

            typedef void(__clrcall* _Set_native_pointer_fptr)(Object^, nint_t, bool_t);

            typedef T(__clrcall* _Ctor_copy_fptr)(Object^, T);
            typedef T(__clrcall* _Ctor_move_fptr)(Object^, move<T>);
            typedef void(__clrcall* _Dtor_fptr)(Object^);

            static _Get_intptr_fptr get_intptr;
            static _Set_intptr_fptr set_intptr;

            static _Get_OwnInstance_fptr get_own_instance;
            static _Set_OwnInstance_fptr set_own_instance;

            static _Set_native_pointer_fptr set_native_pointer;

            static _Ctor_copy_fptr ctor_copy;
            static _Ctor_move_fptr ctor_move;
            static _Dtor_fptr dtor;
        };

        using pointer_t = byte_t*;

        static initonly SystemType^ _Pointer_type = SystemType::GetType("LiteLoader.NET.pointer`1");
        static initonly SystemType^ _Move_type = SystemType::GetType("LiteLoader.NET.Std.move`1");
        static initonly SystemType^ _ICopyable_type = SystemType::GetType("LiteLoader.NET.Std.Internal.ICopyable`1");
        static initonly SystemType^ _IMoveable_type = SystemType::GetType("LiteLoader.NET.Std.Internal.IMoveable`1");

        static size_t type_size;
        static bool isValueType;
        static bool isPointer;
        static bool isCopyable;
        static bool isMoveable;
        static bool isICppClass;
        static bool isIPointerConstructable;

        static _Value_type_funcptr_def _Tv_fptr;
        static _Ref_type_funcptr_def _Tr_fptr;


        static void* _get_method_fptr(bool _ThrowExc, String^ _Name, array<SystemType^>^ _Params);
        static _Value_type_funcptr_def _handle_value_type(SystemType^ _Ty);
        static _Ref_type_funcptr_def _handle_ref_type(SystemType^ _Ty);
        static ICppStdClass()
        {
            auto type = typeof(T);
            if (type->IsValueType)
                _Tv_fptr = _handle_value_type(type);
            else
                _Tr_fptr = _handle_ref_type(type);
        }
    };
}