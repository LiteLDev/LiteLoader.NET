#pragma once
#include "internal.hpp"

namespace LiteLoader::NET::Std::Internal
{
    generic<typename T, typename TAlloc>
    where T : gcnew()
    where TAlloc : gcnew(), ICppStdAllocator
    public ref class _Vector_base :
        IList<T>,
        ICppStdClass<T>,
        IConstructableCppClass,
        ICopyable<_Vector_base<T, TAlloc>^>,
        IMoveable<_Vector_base<T, TAlloc>^>
    {
    private:
        static size_t type_size = ICppStdClass::type_size;
        static bool isValueType = ICppStdClass::isValueType;

    private:
        using _value_vector = LiteLoader::NET::Std::Internal::vector;
        using pointer_t = ICppStdClass::pointer_t;
    public:
        value class iterator sealed : IEnumerator<T>
        {
        internal:
            _value_vector::iterator _this;
            _Vector_base^ instance;
            bool isIterSet;

        public:
            iterator(_value_vector::iterator iter, _Vector_base^ vec)
                :_this(iter), instance(vec), isIterSet(true) {}

        private:
            property Object^ CurrentNonGgeneric
            {
                virtual Object^ get() sealed = IEnumeratorNonGgeneric::Current::get;
            }
        public:
            virtual bool MoveNext();
            virtual void Reset();
            property T Current
            {
                virtual T get();
            }

            static bool operator==(iterator _Left, iterator _Right)
            {
                return _Left._this == _Right._this;
            }
            static bool operator!=(iterator _Left, iterator _Right)
            {
                return _Left._this != _Right._this;
            }
            static iterator operator++(iterator _Val)
            {
                auto _Temp = decltype(_Val._this)::operator++(_Val._this);
                return iterator(_Temp, _Val.instance);
            }
            static iterator operator--(iterator _Val)
            {
                auto _Temp = decltype(_Val._this)::operator--(_Val._this);
                return iterator(_Temp, _Val.instance);
            }
            static iterator operator+(iterator _Left, int _Val)
            {
                return iterator(_Left._this + _Val, _Left.instance);
            }
            static iterator operator-(iterator _Left, int _Val)
            {
                return iterator(_Left._this - _Val, _Left.instance);
            }
            static bool operator>(iterator a, iterator b)
            {
                return a._this > b._this;
            }
            static bool operator<(iterator a, iterator b)
            {
                return a._this < b._this;
            }
            static bool operator>=(iterator a, iterator b)
            {
                return a._this >= b._this;
            }
            static bool operator<=(iterator a, iterator b)
            {
                return a._this <= b._this;
            }
            static T operator*(iterator _Val)
            {
                return _Val.Current;
            }
            property iterator default[int]
            {
                iterator get(int index);
            };
        };
    private:
        using _value_vector = LiteLoader::NET::Std::Internal::vector;
    private:
        _value_vector _this;
        bool ownsNativeInstance;
        TAlloc _al = gcnew TAlloc;
    internal:
        static T _Copy_Instance(T% val);
        static T _Move_Instance(T% val);
        static void _Destruct_Instance(T% val);
        static void _Construct(pointer_t _Dest, T% val, bool byMove);
        static iterator _Make_iterator(pointer_t _Ptr);
    internal:
        TAlloc _Getal();
        void _Change_array(pointer_t _Newvec, size_t _Newsize, size_t _Newcapacity);
        size_t _Calculate_growth(const size_t _Newsize);
        pointer_t _Emplace_reallocate(pointer_t _Whereptr, bool byMove, T% val);
        void _Resize_reallocate(size_t _Newsize, T% val);
        T% _Emplace_back_with_unused_capacity(bool byMove, T% val);
        void _Destroy_range(pointer_t _First, pointer_t _Last);
        void _Uninitialized_move(pointer_t _First, pointer_t _Last, pointer_t _Dest);
        void _Uninitialized_copy(pointer_t _First, pointer_t _Last, pointer_t _Dest);
        pointer_t _Uninitialized_fill_n(pointer_t _First, size_t _Count, T% val);
        pointer_t _Copy_backward_memmove(pointer_t _First, pointer_t _Last, pointer_t _Dest);
        pointer_t _Copy_memmove(pointer_t _First, pointer_t _Last, pointer_t _Dest);
        pointer_t _Move_backward_unchecked(pointer_t _First, pointer_t _Last, pointer_t _Dest);
        pointer_t _Move_unchecked(pointer_t _First, pointer_t _Last, pointer_t _Dest);
    public:
        _Vector_base();
        _Vector_base(nint_t ptr);
        _Vector_base(_Vector_base^ vec);
        _Vector_base(move<_Vector_base^> vec);
        !_Vector_base();
        virtual ~_Vector_base();

        //cpp api
    public:
        //Member functions
        TAlloc get_allocator();
        //Element access
        iterator at(size_t pos);
        T front();
        T back();
        void* data();
        //Iterators
        iterator begin();
        iterator end();
        //Capacity
        bool empty();
        size_t size();
        size_t max_size();
        void reserve(size_t newCapacity);
        size_t capacity();
        //Modifiers
        void clear();
        iterator insert(iterator where, T val);
        iterator insert(iterator where, move<T> val);
        iterator emplace(iterator where, T val);
        iterator emplace(iterator where, move<T> val);
        iterator erase(iterator where);
        T push_back(T val);
        T push_back(move<T> val);
        T emplace_back(T val);
        T emplace_back(move<T> val);
        void resize(size_t newSize, T% val);
        void resize(size_t newSize);
        void swap(_Vector_base^ right);
    private:
        //IEnumerable
        virtual IEnumeratorNonGgeneric^ GetEnumeratorNonGgeneric() sealed = IEnumerableNonGgeneric::GetEnumerator;
    public:
        //ICollection
        virtual IEnumerator<T>^ GetEnumerator();
        //IList
        property int Count
        {
            virtual int get();
        }
        property T default[int]
        {
            virtual T get(int index);
            virtual void set(int index, T val);
        };
        property bool IsReadOnly
        {
            virtual bool get();
        };
        virtual bool Contains(T item);
        virtual int IndexOf(T item);
        virtual void Add(T item);
        virtual void Clear();
        virtual void CopyTo(array<T, 1>^ array, int arrayIndex);
        virtual bool Remove(T item);
        virtual void Insert(int index, T item);
        virtual void RemoveAt(int index);

        //IConstructableCppClass
        property nint_t Intptr
        {
            virtual nint_t get();
            virtual void set(nint_t value);
        }
        property bool OwnsNativeInstance
        {
        public:
            virtual bool get();
            virtual void set(bool value);
        }
        virtual void Destruct();
        virtual void SetNativePointer(nint_t ptr, bool ownsInstance);

        literal size_t NativeClassSize = 24L;
        virtual size_t GetClassSize();

        virtual _Vector_base^ ConstructInstanceByCopy(_Vector_base^ _Right);
        virtual _Vector_base^ ConstructInstanceByMove(move<_Vector_base^> _Right);
    };
}
