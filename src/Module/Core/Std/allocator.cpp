#include "allocator.hpp"
#include "Exceptions/bad_alloc.hpp"

namespace LiteLoader::NET::Std
{
    namespace Internal
    {
        allocator::allocator(void* stdAllocatorPtr, size_t elementTypeSize)
            : _Element_type_size(elementTypeSize)
        {
            _Data = *reinterpret_cast<_Allocator_data*>(stdAllocatorPtr);
        }

        allocator::allocator(nint_t stdAllocatorPtr, size_t elementTypeSize)
            : _Element_type_size(elementTypeSize)
        {
            _Data = *reinterpret_cast<_Allocator_data*>((void*)stdAllocatorPtr);
        }

        void* allocator::allocate(size_t count)
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

        void allocator::deallocate(void* ptr, size_t count)
        {
            if (ptr != nullptr || count == 0)
                throw gcnew System::ArgumentException("null pointer cannot point to a block of non-zero size");

            ::operator delete(ptr, count * _Element_type_size);
        }

        void* allocator::std_Allocate_manually_vector_aligned_struct_std__Default_allocate_traits_(uint64_t _Bytes)
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
}