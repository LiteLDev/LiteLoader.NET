#pragma once
#include <mc/UserEntityIdentifierComponent.hpp>
#include "NetworkIdentifier.hpp"
#include "Certificate.hpp"
#include "Types.hpp"

namespace MC
{
    public
        ref class UserEntityIdentifierComponent : ClassTemplate<
            UserEntityIdentifierComponent, ::UserEntityIdentifierComponent>
    {
    public:
        __ctor(UserEntityIdentifierComponent, ::UserEntityIdentifierComponent);
        __ctor_default(UserEntityIdentifierComponent, ::UserEntityIdentifierComponent);

        property NetworkIdentifier^ NetworkId { NetworkIdentifier^ get(); }
        property System::Byte ClientSubId { System::Byte get(); }
        property Mce::UUID Uuid { Mce::UUID get(); }
        property String^ PlayFabId { String^ get(); }
        property Certificate^ Certificate { MC::Certificate^ get(); }
        property bool IsPrimaryClient { bool get(); }
    };
} // namespace MC
