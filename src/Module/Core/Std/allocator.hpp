#pragma once

//#define private public
//#define protected public
#include <memory>
#include "pointer.hpp"
#include "move.hpp"
#include "ICppStdClass.hpp"

namespace LiteLoader::NET::Std
{
    using LiteLoader::NET::Std::Internal::ICppStdClass;

    namespace Internal
    {
        [StructLayout(LayoutKind::Explicit, Size = 1)]
        value struct _Allocator_data {};

        public value class allocator
        {
        public:
            allocator(void* stdAllocatorPtr, size_t elementTypeSize);
            allocator(nint_t stdAllocatorPtr, size_t elementTypeSize);
        public:
            void* allocate(size_t count);
            void deallocate(void* ptr, size_t count);
        public:
            property _Allocator_data% internal_data
            {
                _Allocator_data% get()
                {
                    return _Data;
                }
            }
        internal:
            static void* std_Allocate_manually_vector_aligned_struct_std__Default_allocate_traits_(uint64_t _Bytes);
        internal:
            _Allocator_data _Data;
            size_t _Element_type_size;
        };
    }

    generic<typename T> where T:
    IConstructableCppClass
        public ref class allocator :ICppStdClass<T>, IConstructableCppClass, IMoveable
    {
    private:
        static size_t elementTypeSize;
        static bool isValueType;
        static bool isPointer;

        static ICppStdClass::_Get_intptr_fptr get_intptr;
        static ICppStdClass::_Set_native_pointer_fptr set_native_pointer;
        static ICppStdClass::_Set_native_pointer__pointer_fptr set_native_pointer__pointer;

        static allocator()
        {
            ICppStdClass::GetElementTypeInfo(elementTypeSize, isValueType, isPointer,
                get_intptr, set_native_pointer, set_native_pointer__pointer);
        }
    private:
        using _value_allocator = LiteLoader::NET::Std::Internal::allocator;
    private:
        _value_allocator _this;

    public:

        // Í¨¹ý IConstructableCppClass ¼Ì³Ð
        property nint_t Intptr
        {
            virtual nint_t get()
            {
                pin_ptr<decltype(_this)> ptr = &_this;
                return nint_t(ptr);
            }
        }
        virtual void Destruct()
        {
        }
        virtual void SetNativePointer(nint_t ptr, bool ownsInstance)
        {
            _this = *reinterpret_cast<decltype(_this)*>(ptr.ToPointer());
        }

        virtual size_t GetClassSize()
        {
            return 1;
        }
    };
}

