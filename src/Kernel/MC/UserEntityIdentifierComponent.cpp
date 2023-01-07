#include <src/Header/MC/UserEntityIdentifierComponent.hpp>

#include <src/Header/MC/NetworkIdentifier.hpp>

namespace MC
{
    inline NetworkIdentifier^ UserEntityIdentifierComponent::NetworkId::get()
    {
        return gcnew NetworkIdentifier(&NativePtr->mNetworkId);
    }

    inline System::Byte UserEntityIdentifierComponent::ClientSubId::get()
    {
        return NativePtr->mClientSubId;
    }

    inline Mce::UUID UserEntityIdentifierComponent::Uuid::get()
    {
        return NativePtr->mUUID;
    }

    inline String^ UserEntityIdentifierComponent::PlayFabId::get()
    {
        return marshalString(NativePtr->mPlayFabId);
    }

    inline Certificate^ UserEntityIdentifierComponent::Certificate::get()
    {
        return gcnew MC::Certificate(&NativePtr->mCertificate);
    }

    inline bool UserEntityIdentifierComponent::IsPrimaryClient::get()
    {
        return NativePtr->isPrimaryClient();
    }
}
