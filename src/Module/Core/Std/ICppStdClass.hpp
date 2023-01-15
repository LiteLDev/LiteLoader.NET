#pragma once
#include <src/Main/DotNETGlobal.hpp>
#include <src/Module/Core/ICppClass.hpp>
#include "ICopyable.hpp"
#include "IMoveable.hpp"

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

        static void GetElementTypeInfo(
            [Out]size_t% elementTypeSize,
            [Out]bool% isValueType,
            [Out]bool% isPointer,
            [Out]bool% isCopyable,
            [Out]bool% isMoveable,
            [Out]_Get_intptr_fptr% get_intptr,
            [Out]_Set_native_pointer_fptr% set_nptr,
            [Out]_Set_native_pointer__pointer_fptr% set_nptr_ptr,
            [Out]_Ctor_copy_fptr ctor_copy,
            [Out]_Ctor_move_fptr ctor_move,
            [Out]_Dtor_fptr dtor)
        {
            auto type = typeof(T);
            if (type->Name == "pointer`1" && type->Namespace == "LiteLoader.NET")
            {
                isValueType = true;
                isPointer = true;
                elementTypeSize = Unsafe::SizeOf<T>();

                get_intptr = reinterpret_cast<_Get_intptr_fptr>(
                    type->GetMethod("get_Intptr")
                    ->MethodHandle
                    .GetFunctionPointer()
                    .ToPointer());

                set_nptr_ptr = reinterpret_cast<_Set_native_pointer__pointer_fptr>(
                    type->GetMethod("SetNativePointer")
                    ->MethodHandle
                    .GetFunctionPointer()
                    .ToPointer());

                return;
            }

            if (type->IsValueType)
            {
                elementTypeSize = Unsafe::SizeOf<T>();
                isValueType = true;
                return;
            }

            if (!type->IsAssignableTo(typeof(IConstructableCppClass)))
                throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName+" must implements 'IConstructableCppClass' interface.");


            {auto method_get_intptr = type->GetMethod("get_Intptr");
            if (method_get_intptr == nullptr)
                throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + L',' + "missing property 'Intptr'.");
            else
                get_intptr = reinterpret_cast<_Get_intptr_fptr>(method_get_intptr->MethodHandle.GetFunctionPointer().ToPointer()); }


            {auto method_set_native_pointer = type->GetMethod("SetNativePointer", PackArray(typeof(nint_t), typeof(bool)));
            if (method_set_native_pointer == nullptr)
                throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + L',' + "missing Method 'SetNativePointer'.");
            else
                set_nptr = reinterpret_cast<_Set_native_pointer_fptr>(method_set_native_pointer->MethodHandle.GetFunctionPointer().ToPointer()); }


            {auto method_dtor = type->GetMethod("Destruct", PackArray(typeof(nint_t), typeof(bool)));
            if (method_dtor == nullptr)
                throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + L',' + "missing Method 'Destruct'.");
            else
                dtor = reinterpret_cast<_Dtor_fptr>(method_dtor->MethodHandle.GetFunctionPointer().ToPointer()); }


            {using System::Reflection::BindingFlags;
            auto field = type->GetField(
                "NativeClassSize", BindingFlags::Public | BindingFlags::Static | BindingFlags::FlattenHierarchy);


            if (field != nullptr && field->IsLiteral)
                elementTypeSize = static_cast<size_t>(field->GetValue(nullptr));
            else
                throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + L',' + "missing const(literal) field 'NativeClassSize'."); }


            if (type->IsAssignableTo(typeof(ICopyable)))
            {
                auto ctor = type->GetConstructor(PackArray(type));
                if (ctor == nullptr)
                    throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + " implements the 'ICopyable' interface but does not have the copy ctor.");

                isCopyable = true;
                ctor_copy = reinterpret_cast<_Ctor_copy_fptr>(ctor->MethodHandle.GetFunctionPointer().ToPointer());
            }


            if (type->IsAssignableTo(typeof(IMoveable)))
            {
                auto ctor = type->GetConstructor(PackArray(typeof(move<T>)));
                if (ctor == nullptr)
                    throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + " implements the 'IMoveable' interface but does not have the copy ctor.");

                isCopyable = true;
                ctor_move = reinterpret_cast<_Ctor_move_fptr>(ctor->MethodHandle.GetFunctionPointer().ToPointer());
            }
        }
    };
}