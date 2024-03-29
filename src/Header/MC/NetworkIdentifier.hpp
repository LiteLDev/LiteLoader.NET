#pragma once
#include <mc/NetworkIdentifier.hpp>
#include "Types.hpp"

namespace MC
{
public
ref class NetworkIdentifier : ClassTemplate<NetworkIdentifier, ::NetworkIdentifier>
{
public:
    __ctor(NetworkIdentifier, ::NetworkIdentifier);
    __ctor_default(NetworkIdentifier, ::NetworkIdentifier);
    property String^ IP { String ^ get(); }

#ifdef INCLUDE_MCAPI
    // NetworkIdentifier(MC::RakNet::RakNetGUID ^ _0);

    property ::String^ Address {
        ::String^ get();
    }

        property unsigned long long Hash
    {
        unsigned long long get();
    }

    property bool IsUnassigned
    {
        bool get();
    }

    static bool operator==(MC::NetworkIdentifier ^ __op, MC::NetworkIdentifier ^ _0);

    virtual bool Equals(::System::Object ^ obj) override;

    ::String^ ToString() override;

    // static operator MC::NetworkIdentifier ^(MC::RakNet::RakNetGUID ^ _0);
#endif // INCLUDE_MCAPI
};
} // namespace MC
