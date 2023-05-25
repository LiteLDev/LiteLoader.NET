#pragma once
#include <mc/HashedString.hpp>
#include "Types.hpp"
namespace MC
{
public
ref class HashedString : ClassTemplate<HashedString, ::HashedString>
{
public:
    __ctor_all(HashedString, ::HashedString);
    __ctor_default(HashedString, ::HashedString);


    HashedString(MC::HashedString ^ _0);

    HashedString(::String^ _0);

    HashedString(unsigned long long _0, ::String^ _1);

    property ::String^ CStr {
        ::String^ get();
    };

    property unsigned long long Hash
    {
        unsigned long long get();
    }

    ::String^ ToString() override;

    property bool IsEmpty
    {
        bool get();
    }

    static property MC::HashedString ^ EmptyString {
        MC::HashedString ^ get();
    };

    void Clear();

    static bool operator!=(MC::HashedString ^ __op, MC::HashedString ^ _0);

    static bool operator==(MC::HashedString ^ __op, MC::HashedString ^ _0);

    static bool operator!=(MC::HashedString^ __op, String^ _0);

    static bool operator==(MC::HashedString^ __op, String^ _0);

    static operator String^(HashedString);

    virtual bool Equals(::System::Object ^ obj) override;

    //static void BindType();

    static unsigned long long ComputeHash(::String^ _0);

    static property MC::HashedString ^ DefaultErrorValue {
        MC::HashedString ^ get();
        void set(MC::HashedString ^);
    }

};
} // namespace MC
