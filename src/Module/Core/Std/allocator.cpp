#include "allocator.hpp"
#include "Exceptions/bad_alloc.hpp"

namespace LiteLoader::NET::Std
{
    namespace Internal
    {
        inline allocator::allocator(void* stdAllocatorPtr, size_t elementTypeSize)
            : _Element_type_size(elementTypeSize)
        {
            _Data = *reinterpret_cast<_Allocator_data*>(stdAllocatorPtr);
        }

        inline allocator::allocator(nint_t stdAllocatorPtr, size_t elementTypeSize)
            : _Element_type_size(elementTypeSize)
        {
            _Data = *reinterpret_cast<_Allocator_data*>((void*)stdAllocatorPtr);
        }

        inline void* allocator::allocate(size_t count)
        {
            if (count > 4611686018427387903L)
            {
                throw gcnew bad_array_new_length(
                    gcnew __Exception(std::bad_array_new_length()));
            }
            uint64_t num = count * _Element_type_size;
            if (num >= 4096)
            {
                return std_Allocate_manually_vector_aligned_struct_std__Default_allocate_traits_(num);
            }
            if (num != 0L)
            {
                return ::operator new(num);
            }
            return nullptr;
        }

        inline void allocator::deallocate(void* ptr, size_t count)
        {
            if (ptr == nullptr || count == 0)
                throw gcnew System::ArgumentException("null pointer cannot point to a block of non-zero size");

            ::operator delete(ptr, count * _Element_type_size);
        }

        inline _Allocator_data% allocator::internal_data::get()
        {
            return _Data;
        }

        inline void* allocator::std_Allocate_manually_vector_aligned_struct_std__Default_allocate_traits_(uint64_t _Bytes)
        {
            uint64_t num = _Bytes + 39;
            if (num <= _Bytes)
            {
                throw gcnew bad_array_new_length(
                    gcnew __Exception(std::bad_array_new_length()));
            }
            uint64_t num2 = uint64_t(::operator new(num));
            if (num2 != 0L)
            {
                void* ptr = (void*)((num2 + 39) & 0xFFFFFFFFFFFFFFE0uL);
                *(uint64_t*)((uint64_t)ptr - 8uL) = num2;
                return ptr;
            }
            _invalid_parameter_noinfo_noreturn();
            return (void*)0uL;
        }
    }

#define GENERIC_HEADER generic<typename T> where T: gcnew()

    GENERIC_HEADER inline allocator<T>::allocator()
    {
        auto _al = _value_allocator();
        _al._Data = LiteLoader::NET::Std::Internal::_Allocator_data();
        _al._Element_type_size = type_size;

        _this = _al;
    }

    GENERIC_HEADER inline allocator<T>::allocator(nint_t ptr)
        : _this(ptr, type_size)
    {
    }

    GENERIC_HEADER inline allocator<T>::allocator(move<allocator<T>^> al)
        : _this(static_cast<allocator<T>^>(al)->_this)
    {
        static_cast<allocator<T>^>(al)->_this = _value_allocator();
    }

    GENERIC_HEADER inline void* allocator<T>::allocate(size_t count)
    {
        return _this.allocate(count);
    }

    GENERIC_HEADER inline void allocator<T>::deallocate(void* ptr, size_t count)
    {
        _this.deallocate(ptr, count);
    }

    GENERIC_HEADER inline size_t allocator<T>::max_size()
    {
        return std::numeric_limits<size_t>::max() / type_size;
    }

    GENERIC_HEADER inline nint_t allocator<T>::Intptr::get()
    {
        pin_ptr<decltype(_this)> ptr = &_this;
        return nint_t(ptr);
    }

    GENERIC_HEADER inline void allocator<T>::Destruct()
    {
    }

    GENERIC_HEADER inline void allocator<T>::SetNativePointer(nint_t ptr, bool ownsInstance)
    {
        _this = *reinterpret_cast<decltype(_this)*>(ptr.ToPointer());
    }

    GENERIC_HEADER inline size_t allocator<T>::GetClassSize()
    {
        return NativeClassSize;
    }
}