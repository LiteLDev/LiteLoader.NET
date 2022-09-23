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

#ifdef INCLUDE_MCAPI

    HashedString(MC::HashedString ^ _0);

    HashedString(::String^ _0);

    HashedString(unsigned long long _0, ::String^ _1);

    property ::String^ CStr {
        ::String^ get();
    };

    property bool Empty
    {
        bool get();
    };

    property unsigned long long Hash
    {
        unsigned long long get();
    }

    property ::String^ String {
        ::String^ get();
    };

    property bool IsEmpty
    {
        bool get();
    }

    static property MC::HashedString ^ EmptyString {
        MC::HashedString ^ get();
    };

    void Clear();

    static bool operator!=(MC::HashedString ^ __op, MC::HashedString ^ _0);

    static bool operator<(MC::HashedString ^ __op, MC::HashedString ^ _0);

    static bool operator==(MC::HashedString ^ __op, MC::HashedString ^ _0);

    virtual bool Equals(::System::Object ^ obj) override;

    //static void BindType();

    static unsigned long long ComputeHash(::String^ _0);

    static property MC::HashedString ^ DefaultErrorValue {
        MC::HashedString ^ get();
        void set(MC::HashedString ^);
    }

#endif // INCLUDE_MCAPI
};
} // namespace MC
