#pragma once
#include <src/Main/DotNETGlobal.hpp>
#include <src/Module/Core/ICppClass.hpp>

#include <src/Module/Core/Std/move.hpp>
#include <src/Module/Core/Std/pointer.hpp>
#include <src/Module/Core/Std/ICppStdClass.hpp>
#include <src/Module/Core/Std/allocator.hpp>

namespace LiteLoader::NET::Std
{
    generic<typename T> where T :
    gcnew()
    public ref class optional :
        ICppStdClass<T>,
        IConstructableCppClass,
        ICopyable<optional<T>^>,
        IMoveable<optional<T>^>
    {
    private:
        using pointer_t = ICppStdClass::pointer_t;
    private:
        pointer_t ptr;
        bool ownsNativeInstance;
    public:
        optional();
        optional(nint_t ptr);
        optional(nint_t ptr, bool ownsInstance);
        optional(optional^ val);
        optional(move<optional^> val);

        !optional();
        ~optional();
        
    public:
        bool has_value();
        T value();
        T value_or(T val);

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
        virtual size_t GetClassSize();
        virtual void SetNativePointer(nint_t ptr, bool ownsInstance);

        //ICopyable
        virtual optional<T>^ ConstructInstanceByCopy(optional<T>^ _Right);
        //IMoveable
        virtual optional<T>^ ConstructInstanceByMove(move<optional<T>^> _Right);
    };
}

