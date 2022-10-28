#pragma once
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <LiteLoader.NET/Header/Core/ICppClass.hpp>

#include <vector>

namespace LLNET::Core::Std
{
	using byte = unsigned char;
	using LLNET::Core::ICppClass;

	namespace Internal
	{
		using System::Runtime::InteropServices::FieldOffsetAttribute;

		[StructLayout(LayoutKind::Explicit, Size = sizeof(void*) * 4)]
		public value struct _Vector_data {
			[FieldOffset(0)]
			byte* _Std_container_base_Myproxy;
			[FieldOffset(8)]
			byte* _Myfirst;
			[FieldOffset(16)]
			byte* _Mylast;
			[FieldOffset(24)]
			byte* _Myend;
		};

		[StructLayout(LayoutKind::Explicit, Size = sizeof(void*) * 3)]
		public value struct _Vector_iterator_data {
			[FieldOffset(0)]
			byte* _Std_iterator_base_Myproxy;
			[FieldOffset(8)]
			byte* _Std_iterator_base_Mynextiter;
			[FieldOffset(16)]
			byte* _Ptr;
		};

		public value class vector
		{
		public:
			value struct iterator
			{
			public:
				iterator(void* stdVectorIteratorPtr, size_t elementTypeSize);
				iterator(IntPtr stdVectorIteratorPtr, size_t elementTypeSize);
				iterator(_Vector_iterator_data data, size_t elementTypeSize);
			public:
				property _Vector_iterator_data% InternalData
				{
					_Vector_iterator_data% get()
					{
						return _Iter;
					}
				}
			public:
				static iterator operator++(iterator val)
				{
					auto ret = val;
					ret._Iter._Ptr += ret._Element_type_size;
					return ret;
				}
				static iterator operator--(iterator val)
				{
					auto ret = val;
					ret._Iter._Ptr -= ret._Element_type_size;
					return ret;
				}
				static iterator operator+(iterator a, int b)
				{
					auto ret = a;
					ret._Iter._Ptr += ret._Element_type_size * b;
					return ret;
				}
				static iterator operator-(iterator a, int b)
				{
					auto ret = a;
					ret._Iter._Ptr -= ret._Element_type_size * b;
					return ret;
				}
				static bool operator>(iterator a, iterator b)
				{
					return a._Iter._Ptr > b._Iter._Ptr;
				}
				static bool operator<(iterator a, iterator b)
				{
					return a._Iter._Ptr < b._Iter._Ptr;
				}
				static bool operator>=(iterator a, iterator b)
				{
					return a._Iter._Ptr >= b._Iter._Ptr;
				}
				static bool operator<=(iterator a, iterator b)
				{
					return a._Iter._Ptr <= b._Iter._Ptr;
				}
				static bool operator==(iterator a, iterator b)
				{
					return a._Iter._Ptr == b._Iter._Ptr;
				}
				property iterator default[int]
				{
					iterator get(int index)
					{
						auto ret = *this;
						ret._Iter._Ptr += ret._Element_type_size * index;
						return ret;
					}
				};
			internal:
				_Vector_iterator_data _Iter;
				size_t _Element_type_size;
			};

		public:
			vector(void* stdVectorPtr, size_t elementTypeSize);
			vector(IntPtr stdVectorPtr, size_t elementTypeSize);
		public:
			size_t size();
			iterator begin();
			iterator end();
			iterator at(size_t pos);
			bool empty();
			bool capacity();
			void* data();
		public:
			property _Vector_data% internal_data
			{
				_Vector_data% get()
				{
					return _Data;
				}
			}
		internal:
			_Vector_data _Data;
			size_t _Element_type_size;
		};

		generic<typename T>
		private ref class _Vector_base
		{
			using _value_vector = LLNET::Core::Std::Internal::vector;

		private:
			_value_vector _Vector;
			size_t _Element_type_size;
			bool _Is_class;
			bool _Initialized_by_managed;
			void(*_Dtor_func)(void*);
		public:
			_Vector_base();
			_Vector_base(void* vector);
		public:

		protected:
			//void _Reallocate(size_t size)
			//{
			//	if (_vector.size() == size)
			//		return;

			//	auto% _data = _vector._data;

			//	auto _original_size = _vector.size() * _element_type_size;

			//	auto _data_mem_length = _data._Myfirst - _data._Mylast;

			//	auto _allocate_size = size * _element_type_size;
			//	auto _allocate_mem = new byte[_allocate_size];
			//	auto _cpy_size = _allocate_size > _original_size ? _original_size : _allocate_size;

			//	memcpy(_allocate_mem, _vector.data(), _cpy_size);

			//	_data._Myfirst = _allocate_mem;
			//	_data._Myend = _allocate_mem + _allocate_size - 1;

			//	if ()

			//}
		private:
			static size_t _Get_element_type_size();
		};
	}

} // namespace LLNET::Core::Std



void Test() {
	std::vector<int>::iterator a;
	std::vector<int> vec;
	vec.emplace_back();

}