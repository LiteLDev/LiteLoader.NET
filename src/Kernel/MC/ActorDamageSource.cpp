#include <src/Header/MC/ActorDamageSource.hpp>
#include <src/Header/MC/Actor.hpp>

namespace MC
{
inline Actor ^ ActorDamageSource::Entity::get()
{
    return gcnew Actor(NativePtr->getEntity());
}
bool ActorDamageSource::IsEntitySource::get()
{
    return NativePtr->isEntitySource();
}
//void MC::ActorDamageSource::UnkVfn11()
//{
//    NativePtr->__unk_vfn_11();
//}
//void MC::ActorDamageSource::UnkVfn12()
//{
//    NativePtr->__unk_vfn_12();
//}
MC::ActorDamageCause MC::ActorDamageSource::LookupCause(::String^ causeName)
{
    return MC::ActorDamageCause(::ActorDamageSource::lookupCause(marshalString(causeName)));
}
String^ MC::ActorDamageSource::LookupCauseName(MC::ActorDamageCause cause)
{
    return marshalString(::ActorDamageSource::lookupCauseName(::ActorDamageCause(cause)));
}
bool MC::ActorDamageSource::IsChildEntitySource::get()
{
    return NativePtr->isChildEntitySource();
}
bool MC::ActorDamageSource::IsBlockSource::get()
{
    return NativePtr->isBlockSource();
}
bool MC::ActorDamageSource::IsFire::get()
{
    return NativePtr->isFire();
}
bool MC::ActorDamageSource::IsCreative::get()
{
    return NativePtr->getIsCreative();
}
bool MC::ActorDamageSource::IsWorldBuilder::get()
{
    return NativePtr->getIsWorldBuilder();
}
bool MC::ActorDamageSource::DamagingEntityIsCreative::get()
{
    return NativePtr->getDamagingEntityIsCreative();
}
bool MC::ActorDamageSource::DamagingEntityIsWorldBuilder::get()
{
    return NativePtr->getDamagingEntityIsWorldBuilder();
}
MC::ActorUniqueID MC::ActorDamageSource::DamagingEntityUniqueID::get()
{
    return NativePtr->getDamagingEntityUniqueID();
}
MC::ActorDamageCause MC::ActorDamageSource::Cause::get()
{
    return MC::ActorDamageCause(NativePtr->getCause());
}
void MC::ActorDamageSource::Cause::set(MC::ActorDamageCause cause)
{
    NativePtr->setCause(::ActorDamageCause(cause));
}
} // namespace MC