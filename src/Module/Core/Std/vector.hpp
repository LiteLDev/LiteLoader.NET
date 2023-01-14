#pragma once
#include <src/Main/DotNETGlobal.hpp>
#include <src/Header/Core/ICppClass.hpp>

#include <vector>

#include "move.hpp"
#include "pointer.hpp"

namespace LiteLoader::NET::Std
{
    using LiteLoader::NET::ICppClass;
    using LiteLoader::NET::IPointerConstructable;
    using System::Collections::Generic::IList;

    namespace Internal
    {
        using System::Runtime::InteropServices::FieldOffsetAttribute;

        [StructLayout(LayoutKind::Explicit, Size = 24)]
        public value struct _Vector_data {
            [StructLayout(LayoutKind::Explicit, Size = 24)]
            value struct _Compressed_pair
            {
                [StructLayout(LayoutKind::Explicit, Size = 24)]
                value struct _Vector_val
                {
                    [FieldOffset(0)]
                    byte_t* _Myfirst;
                    [FieldOffset(8)]
                    byte_t* _Mylast;
                    [FieldOffset(16)]
                    byte_t* _Myend;
                };
                [FieldOffset(0)]
                _Vector_val _Myval2;
            };
            [FieldOffset(0)]
            _Compressed_pair _Mypair;
        };

        [StructLayout(LayoutKind::Explicit, Size = 8)]
        public value struct _Vector_iterator_data {
            [FieldOffset(0)]
            byte_t* _Ptr;
        };

        public value class vector
        {
        public:
            value struct iterator
            {
            public:
                iterator(void* stdVectorIteratorPtr, size_t elementTypeSize);
                iterator(nint_t stdVectorIteratorPtr, size_t elementTypeSize);
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
                static bool operator!=(iterator a, iterator b)
                {
                    return !(a == b);
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
                void* get()
                {
                    return this->_Iter._Ptr;
                }
            internal:
                _Vector_iterator_data _Iter;
                size_t _Element_type_size;
            };

        public:
            vector(void* stdVectorPtr, size_t elementTypeSize);
            vector(nint_t stdVectorPtr, size_t elementTypeSize);
        public:
            size_t size();
            iterator begin();
            iterator end();
            iterator at(size_t pos);
            bool empty();
            size_t capacity();
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

        /*generic<typename T>
        public ref class _Vector_base
        {
            using _value_vector = LiteLoader::NET::Std::Internal::vector;

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
            void Test() {
                std::vector<int>::iterator a;
                std::vector<int> vec;
                vec.emplace_back();
                vec.back();
                vec.size();
                vec.resize(100);
            }
        private:
            static size_t _Get_element_type_size();
        };*/
    }

    generic<typename T> where T:
    gcnew()
        public ref class vector sealed :IList<T>, IConstructableCppClass, IMoveable
    {
    private:
        static size_t elementTypeSize;
        static bool isValueType;
        static bool isPointer;

        static nint_t(__clrcall* get_intptr)(T);
        static void(__clrcall* set_native_pointer)(Object^, nint_t, bool);
        static void(__clrcall* set_native_pointer__pointer)(void*, nint_t, bool);

        static vector()
        {
            auto type = typeof(T);
            if (type->Name == "pointer`1" && type->Namespace == "LiteLoader.NET")
            {
                isValueType = true;
                isPointer = true;
                elementTypeSize = Unsafe::SizeOf<T>();

                get_intptr = reinterpret_cast<decltype(get_intptr)>(
                    type->GetMethod("get_Intptr")
                    ->MethodHandle
                    .GetFunctionPointer()
                    .ToPointer());

                set_native_pointer__pointer = reinterpret_cast<decltype(set_native_pointer__pointer)>(
                    type->GetMethod("SetNativePointer")
                    ->MethodHandle
                    .GetFunctionPointer()
                    .ToPointer());
            }

            if (type->IsValueType)
            {
                elementTypeSize = Unsafe::SizeOf<T>();
                isValueType = true;
                return;
            }

            if (!type->IsAssignableTo(typeof(IConstructableCppClass)))
                throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName);

            auto get_intptr = type->GetMethod("get_Intptr");
            if (get_intptr == nullptr)
                throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + L',' + "missing property 'Intptr'");
            else
                vector::get_intptr = reinterpret_cast<nint_t(__clrcall*)(T)>(get_intptr->MethodHandle.GetFunctionPointer().ToPointer());

            auto set_native_pointer = type->GetMethod("SetNativePointer", PackArray(typeof(nint_t), typeof(bool)));
            if (get_intptr == nullptr)
                throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + L',' + "missing Method 'SetNativePointer'");
            else
                vector::set_native_pointer = reinterpret_cast<void(__clrcall*)(Object^, nint_t, bool)>(set_native_pointer->MethodHandle.GetFunctionPointer().ToPointer());

            using System::Reflection::BindingFlags;
            auto field = type->GetField(
                "NativeClassSize", BindingFlags::Public | BindingFlags::Static | BindingFlags::FlattenHierarchy);

            if (field != nullptr && field->IsLiteral)
                elementTypeSize = static_cast<size_t>(field->GetValue(nullptr));
            else
                throw gcnew LiteLoader::NET::InvalidTypeException(type->FullName + L',' + "missing const(literal) field 'NativeClassSize'");
        }

        literal String^ NotSupportedMessage = L"Will support after Allocator finished.";

    private:
        using _value_vector = LiteLoader::NET::Std::Internal::vector;
    public:
        value class iterator sealed : IEnumerator<T>
        {
        internal:
            _value_vector::iterator _this;
            vector^ instance;
            bool isIterSet;

        private:
            property Object^ CurrentNonGgeneric
            {
                virtual Object^ get() sealed = IEnumeratorNonGgeneric::Current::get
                {
                    return Current;
                }
            }
        public:
            virtual bool MoveNext()
            {
                if (isIterSet)
                {
                    ++_this;
                    return _this != instance->_this.end();
                }
                else
                {
                    _this = instance->_this.begin();
                    if (_this == instance->_this.end())
                        return false;

                    isIterSet = true;
                    return true;
                }
            }
            virtual void Reset()
            {
                isIterSet = false;
            }
            property T  Current
            {
                virtual T get()
                {
                    if (isValueType)
                    {
                        if (isPointer)
                        {
                            T ret;
                            set_native_pointer__pointer(&ret, static_cast<nint_t>(_this.get()), false);
                            return ret;
                        }
                        return Unsafe::Read<T>(_this.get());
                    }
                    else
                    {
                        auto ret = gcnew T();
                        set_native_pointer(ret, static_cast<nint_t>(_this.get()), false);
                        return ret;
                    }
                }
            }
        };

    private:
        using _value_vector = LiteLoader::NET::Std::Internal::vector;
    private:
        _value_vector _this;

        bool ownsNativeInstance;

    public:
        vector(nint_t ptr)
            :_this(ptr, elementTypeSize)
        {
        }

        vector(move<vector^> vec)
        {
            throw gcnew System::NotSupportedException(NotSupportedMessage);
        }

        //cpp api
    public:
        size_t size()
        {
            return _this.size();
        }
        iterator begin()
        {
            iterator ret;
            ret._this = _this.begin();
            ret.instance = this;
            ret.isIterSet = true;
            return ret;
        }
        iterator end()
        {
            iterator ret;
            ret._this = _this.end();
            ret.instance = this;
            ret.isIterSet = true;
            return ret;
        }
        iterator at(size_t pos)
        {
            iterator ret;
            ret._this = _this.at(pos);
            ret.instance = this;
            ret.isIterSet = true;
            return ret;
        }
        bool empty()
        {
            return _this.empty();
            std::string str;
            new std::string(std::move(str));
        }
        size_t capacity()
        {
            return _this.capacity();
        }
        void* data()
        {
            return _this.data();
        }

    private:
        // 通过 IEnumerable 继承
        virtual IEnumeratorNonGgeneric^ GetEnumeratorNonGgeneric() sealed = IEnumerableNonGgeneric::GetEnumerator
        {
            return GetEnumerator();
        }

    public:
        // 通过 ICollection 继承
        virtual IEnumerator<T>^ GetEnumerator()
        {
            auto ret = iterator();
            ret.instance = this;
            return ret;
        }

        // 通过 IList 继承

        property int Count
        {
            virtual int get()
            {
                return static_cast<int>(_this.size());
            }
        }

        property T default[int]
        {
            virtual T get(int index)
            {
                if (isValueType)
                {
                    return Unsafe::Read<T>(_this.at(index).get());
                }
                else
                {
                    auto ret = gcnew T();
                    ((IConstructableCppClass^)(ret))->SetNativePointer(Unsafe::Read<nint_t>(_this.at(index).get()), false);
                    return ret;
                }
            }
            virtual void set(int index, T val)
            {
                throw gcnew System::NotSupportedException(NotSupportedMessage);
            }
        };

        property bool IsReadOnly
        {
            virtual bool get()
            {
                return true;
            }
        };

        virtual bool Contains(T item)
        {
            throw gcnew System::NotSupportedException(NotSupportedMessage);
        }

        virtual int IndexOf(T item)
        {
            throw gcnew System::NotSupportedException(NotSupportedMessage);
        }

        virtual void Add(T item)
        {
            throw gcnew System::NotSupportedException(NotSupportedMessage);
        }

        virtual void Clear()
        {
            throw gcnew System::NotSupportedException(NotSupportedMessage);
        }

        virtual void CopyTo(array<T, 1>^ array, int arrayIndex)
        {
            throw gcnew System::NotSupportedException(NotSupportedMessage);
        }

        virtual bool Remove(T item)
        {
            throw gcnew System::NotSupportedException(NotSupportedMessage);
        }

        virtual void Insert(int index, T item)
        {
            throw gcnew System::NotSupportedException(NotSupportedMessage);
        }

        virtual void RemoveAt(int index)
        {
            throw gcnew System::NotSupportedException(NotSupportedMessage);
        }


        // 通过 IConstructableCppClass 继承
        property nint_t Intptr
        {
            virtual nint_t get()
            {
                //???
                pin_ptr<decltype(_this)> ptr = &_this;
                return nint_t(ptr);
            }
        }

        virtual void Destruct()
        {
            throw gcnew System::NotSupportedException(NotSupportedMessage);
        }

        virtual void SetNativePointer(nint_t ptr, bool ownsInstance)
        {
            _this = *reinterpret_cast<decltype(_this)*>(ptr.ToPointer());
            this->ownsNativeInstance = ownsInstance;
        }

    };
} // namespace LiteLoader::NET::Std