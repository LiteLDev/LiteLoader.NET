#pragma once
#include <LiteLoader.NET/Tools/clix.hpp>
#include <LiteLoader.NET/Main/ClassTemplate.hpp>
#include <memory>

namespace LLNET::Core::Std
{
	using namespace clix;

	public ref class string : ClassTemplate<string, std::string>
	{
	public:
		__ctor_all(string, std::string);

	public:
		ref class iterator : ClassTemplate<iterator, std::string::iterator>
		{
		public:
			__ctor_all(iterator, std::string::iterator);

		public:
			char% Dereference()
			{
				return NativePtr->operator*();
			}
			static iterator^ operator+(iterator^ a, int b)
			{
				return gcnew iterator(a->NativePtr->operator+(b));
			}
			static iterator^ operator-(iterator^ a, int b)
			{
				return gcnew iterator(a->NativePtr->operator-(b));
			}
			static bool operator>(iterator^ a, iterator^ b)
			{
				return a->NativePtr->operator>(*b->NativePtr);
			}
			static bool operator<(iterator^ a, iterator^ b)
			{
				return a->NativePtr->operator<(*b->NativePtr);
			}
			static bool operator>=(iterator^ a, iterator^ b)
			{
				return a->NativePtr->operator>=(*b->NativePtr);
			}
			static bool operator<=(iterator^ a, iterator^ b)
			{
				return a->NativePtr->operator<=(*b->NativePtr);
			}
			iterator^ operator++(int val)
			{
				NativePtr->operator++(val);
				return this;
			}
			iterator^ operator--(int val)
			{
				NativePtr->operator++(val);
				return this;
			}
			static bool operator==(iterator^ a, iterator^ b)
			{
				return *a->NativePtr == *b->NativePtr;
			}
			static bool operator!=(iterator^ a, iterator^ b)
			{
				return *a->NativePtr != *b->NativePtr;
			}
			static operator char(iterator^ obj) {
				return obj->Dereference();
			}
		};

	public:
		string()
			:ClassTemplate(std::string())
		{
		}
		string(String^ str)
			:ClassTemplate(marshalString(str))
		{
		}
		iterator^ begin() {
			return gcnew iterator(NativePtr->begin());
		};
		iterator^ end() {
			return gcnew iterator(NativePtr->end());
		};
		property char% default[int]
		{
			char% get(int index) {
				return NativePtr->operator[](index);
			}
		};
		size_t size()
		{
			return NativePtr->size();
		}
		size_t length()
		{
			return NativePtr->length();
		}
		size_t max_size()
		{
			return NativePtr->max_size();
		}
		void resize(size_t size)
		{
			NativePtr->resize(size);
		}
		size_t capacity()
		{
			return NativePtr->capacity();
		}
		void reserve(size_t size)
		{
			NativePtr->reserve(size);
		}
		void clear()
		{
			NativePtr->clear();
		}
		bool empty()
		{
			return NativePtr->empty();
		}
		void shrink_to_fit()
		{
			NativePtr->shrink_to_fit();
		}
		char% at(size_t size)
		{
			return NativePtr->at(size);
		}
		char% back()
		{
			return NativePtr->back();
		}
		char% front()
		{
			return NativePtr->front();
		}
		string^ operator+=(string^ str)
		{
			*NativePtr += *str->NativePtr;
			return this;
		}
		string^ append(string^ str) {
			NativePtr->append(*str->NativePtr);
			return this;
		};
		string^ push_back(char c) {
			NativePtr->push_back(c);
			return this;
		};
		string^ assign(string^ str) {
			NativePtr->assign(*str->NativePtr);
			return this;
		};
		string^ insert(size_t pos, string^ str) {
			NativePtr->insert(pos, *str->NativePtr);
			return this;
		}
		string^ erase(size_t pos, size_t len) {
			NativePtr->erase(pos, len);
			return this;
		}
		string^ replace(size_t pos, size_t len, string^ str) {
			NativePtr->replace(pos, len, *str->NativePtr);
			return this;
		}
		void swap(string^ str) {
			NativePtr->swap(*str->NativePtr);
		}
		void pop_back() {
			NativePtr->pop_back();
		}
		IntPtr c_str_intptr() {
			return IntPtr((void*)NativePtr->c_str());
		}
		char const* c_str() {
			return NativePtr->c_str();
		}
		IntPtr data_intptr() {
			return IntPtr((void*)NativePtr->data());
		}
		char const* data() {
			return NativePtr->data();
		}
		//IntPtr get_allocator_intptr() {
		//		return IntPtr((void*)NativePtr->get_allocator());
		//}
		//IntPtr get_allocator() {
		//		return NativePtr->get_allocator();
		//}
		//size_t copy() {
		//}

		//find_first_of

		//开摆

		String^ ToString() override
		{
			return marshalString(*NativePtr);
		}

		static bool operator==(string^ a, string^ b) {
			return *a->NativePtr == *b->NativePtr;
		}
		static bool operator!=(string^ a, string^ b) {
			return *a->NativePtr != *b->NativePtr;
		}
		static string^ operator+(string^ a, string^ b) {
			return gcnew string(*a->NativePtr + *b->NativePtr);
		}
	};
} // namespace LLNET::Core::Std
