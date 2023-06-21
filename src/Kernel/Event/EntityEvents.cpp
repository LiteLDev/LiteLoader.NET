#include <src/Header/Event/EntityEvents.hpp>

void InitEntityEvents()
{
    using namespace LiteLoader::Event;
#define REGISTER_NATIVE_EVENT(_event) EventManager::_registerNativeEvent<_event^>(_event::EventId)

    REGISTER_NATIVE_EVENT(EntityTransformEvent);
    REGISTER_NATIVE_EVENT(EntityExplodeEvent);
    REGISTER_NATIVE_EVENT(MobHurtEvent);
    REGISTER_NATIVE_EVENT(MobDieEvent);
    REGISTER_NATIVE_EVENT(ProjectileHitEntityEvent);
    REGISTER_NATIVE_EVENT(WitherBossDestroyEvent);
    REGISTER_NATIVE_EVENT(EntityRideEvent);
    REGISTER_NATIVE_EVENT(EntityStepOnPressurePlateEvent);
    REGISTER_NATIVE_EVENT(ProjectileSpawnEvent);
    REGISTER_NATIVE_EVENT(ProjectileCreatedEvent);
    REGISTER_NATIVE_EVENT(ArmorStandChangeEvent);
}