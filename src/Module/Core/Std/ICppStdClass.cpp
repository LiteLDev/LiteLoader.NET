#include "ICppStdClass.hpp"

namespace LiteLoader::NET::Std::Internal
{
    generic<typename T>
    void ICppStdClass<T>::_init()
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

            set_native_pointer__pointer = reinterpret_cast<_Set_native_pointer__pointer_fptr>(
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
            throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + " must implements 'IConstructableCppClass' interface.");


        {auto method_get_intptr = type->GetMethod("get_Intptr");
        if (method_get_intptr == nullptr)
            throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + L',' + "missing property 'Intptr'.");
        else
            get_intptr = reinterpret_cast<_Get_intptr_fptr>(method_get_intptr->MethodHandle.GetFunctionPointer().ToPointer()); }


        {auto method_set_native_pointer = type->GetMethod("SetNativePointer", PackArray(typeof(nint_t), typeof(bool)));
        if (method_set_native_pointer == nullptr)
            throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + L',' + "missing Method 'SetNativePointer'.");
        else
            set_native_pointer = reinterpret_cast<_Set_native_pointer_fptr>(method_set_native_pointer->MethodHandle.GetFunctionPointer().ToPointer()); }


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
}