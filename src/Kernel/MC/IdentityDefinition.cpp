#include <src/Header/MC/IdentityDefinition.hpp>

MC::ActorUniqueID  MC::IdentityDefinition::EntityId::get()
{
    return NativePtr->getEntityId();
}

::String^ MC::IdentityDefinition::FakePlayerName::get()
{
    auto& __ret = NativePtr->getFakePlayerName();
    return (::String^)(clix::marshalString<clix::E_UTF8>(__ret));
}

MC::IdentityDefinition::Type MC::IdentityDefinition::IdentityType::get()
{
    auto __ret = NativePtr->getIdentityType();
    return (MC::IdentityDefinition::Type)__ret;
}

bool MC::IdentityDefinition::IsEntityType::get()
{
    auto __ret = NativePtr->isEntityType();
    return __ret;
}

bool MC::IdentityDefinition::IsPlayerType::get()
{
    auto __ret = NativePtr->isPlayerType();
    return __ret;
}

bool MC::IdentityDefinition::IsValid::get()
{
    auto __ret = NativePtr->isValid();
    return __ret;
}

MC::IdentityDefinition^ MC::IdentityDefinition::Invalid::get()
{
    return (&::IdentityDefinition::Invalid == nullptr) ? nullptr : gcnew ::MC::IdentityDefinition((class ::IdentityDefinition*) & ::IdentityDefinition::Invalid);
}
