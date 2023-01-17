#pragma once
#include "internal.hpp"

namespace LiteLoader::NET::Std::Internal
{
    generic<typename T, typename TAlloc>
    where T : gcnew()
    where TAlloc : gcnew(), ICppStdAllocator
    public ref class _Vector_base :IList<T>, ICppStdClass<T>, IConstructableCppClass, IMoveable
    {
    private:
        static size_t type_size = ICppStdClass::elementTypeSize;
        static bool isValueType = ICppStdClass::isValueType;

        literal String^ NotSupportedMessage = L"Will support after Allocator finished.";

    private:
        using _value_vector = LiteLoader::NET::Std::Internal::vector;
    public:
        value class iterator sealed : IEnumerator<T>
        {
        internal:
            _value_vector::iterator _this;
            _Vector_base^ instance;
            bool isIterSet;

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
        };
    private:
        using _value_vector = LiteLoader::NET::Std::Internal::vector;
    private:
        _value_vector _this;
        bool ownsNativeInstance;
        TAlloc _al = gcnew TAlloc;
    private:
        TAlloc _Getal();
        void _Change_array(byte_t* _Newvec, size_t _Newsize, size_t _Newcapacity);
        size_t _Calculate_growth(const size_t _Newsize);
        byte_t* _Emplace_reallocate(byte_t* _Whereptr, bool byMove, T% val);
        T% _Emplace_back_with_unused_capacity(bool byMove, T% val);
    public:
        _Vector_base();
        _Vector_base(nint_t ptr);
        _Vector_base(move<_Vector_base^> vec);
        //cpp api
    public:
        size_t size();
        iterator begin();
        iterator end();
        iterator at(size_t pos);
        bool empty();
        size_t capacity();
        void* data();
        TAlloc get_allocator();
        T emplace_back(T val);
        size_t max_size();
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
        }
        virtual void Destruct();
        virtual void SetNativePointer(nint_t ptr, bool ownsInstance);

        literal size_t NativeClassSize = 24L;
        virtual size_t GetClassSize();
    };
}
