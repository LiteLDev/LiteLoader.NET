#pragma once
#include <src/Main/DotNETGlobal.hpp>
#include <src/Module/Core/ICppClass.hpp>
#include "ICopyable.hpp"
#include "move.hpp"

namespace LiteLoader::NET::Std::Internal
{
    generic<typename T>
    public interface class ICppStdClass
    {
        typedef nint_t(__clrcall* _Get_intptr_fptr)(T);
        typedef void(__clrcall* _Set_native_pointer_fptr)(T, nint_t, bool);
        typedef void(__clrcall* _Set_native_pointer__pointer_fptr)(void*, nint_t, bool);
        typedef void(__clrcall* _Ctor_copy_fptr)(T, T);
        typedef void(__clrcall* _Ctor_move_fptr)(T, move<T>);
        typedef void(__clrcall* _Dtor_fptr)(T);

        static SystemType^ _Pointer_type = SystemType::GetType("LiteLoader.NET.pointer`1");

        static size_t elementTypeSize;
        static bool isValueType;
        static bool isPointer;
        static bool isCopyable;
        static bool isMoveable;

        static ICppStdClass::_Get_intptr_fptr get_intptr;
        static ICppStdClass::_Set_native_pointer_fptr set_native_pointer;
        static ICppStdClass::_Set_native_pointer__pointer_fptr set_native_pointer__pointer;
        static ICppStdClass::_Ctor_copy_fptr ctor_copy;
        static ICppStdClass::_Ctor_move_fptr ctor_move;
        static ICppStdClass::_Dtor_fptr dtor;

        static void _init();
        static ICppStdClass()
        {
            _init();
        }
    };
}