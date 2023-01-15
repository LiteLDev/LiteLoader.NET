#pragma once
#include <src/Main/DotNETGlobal.hpp>
#include <src/Header/Core/ICppClass.hpp>

namespace LiteLoader::NET::Std::Internal
{
    generic<typename T>
    public interface class ICppStdClass
    {
        typedef nint_t(__clrcall* _Get_intptr_fptr)(T);
        typedef void(__clrcall* _Set_native_pointer_fptr)(Object^, nint_t, bool);
        typedef void(__clrcall* _Set_native_pointer__pointer_fptr)(void*, nint_t, bool);

        static void GetElementTypeInfo(
            [Out]size_t% elementTypeSize,
            [Out]bool% isValueType,
            [Out]bool% isPointer,
            [Out]_Get_intptr_fptr% get_intptr,
            [Out]_Set_native_pointer_fptr% set_nptr,
            [Out]_Set_native_pointer__pointer_fptr% set_nptr_ptr)
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
                throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName);

            auto method_get_intptr = type->GetMethod("get_Intptr");
            if (get_intptr == nullptr)
                throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + L',' + "missing property 'Intptr'");
            else
                get_intptr = reinterpret_cast<nint_t(__clrcall*)(T)>(method_get_intptr->MethodHandle.GetFunctionPointer().ToPointer());

            auto method_set_native_pointer = type->GetMethod("SetNativePointer", PackArray(typeof(nint_t), typeof(bool)));
            if (get_intptr == nullptr)
                throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + L',' + "missing Method 'SetNativePointer'");
            else
                set_nptr = reinterpret_cast<void(__clrcall*)(Object^, nint_t, bool)>(method_set_native_pointer->MethodHandle.GetFunctionPointer().ToPointer());

            using System::Reflection::BindingFlags;
            auto field = type->GetField(
                "NativeClassSize", BindingFlags::Public | BindingFlags::Static | BindingFlags::FlattenHierarchy);

            if (field != nullptr && field->IsLiteral)
                elementTypeSize = static_cast<size_t>(field->GetValue(nullptr));
            else
                throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + L',' + "missing const(literal) field 'NativeClassSize'");
        }
    };
}