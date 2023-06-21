#pragma once
#include "Event.hpp"

namespace LiteLoader::Event
{

    ///////////////////////////// Entity Events /////////////////////////////

    Class EntityTransformEvent
        : public EventTemplate<EntityTransformEvent, ::Event::EntityTransformEvent>
    {
        EventAPIs(EntityTransformEvent, 51);

    public:
        property MC::ActorUniqueID BeforeEntityUniqueId
        {
            MC::ActorUniqueID get()
            {
                return *_this->mBeforeEntityUniqueId;
            }

            void set(MC::ActorUniqueID value)
            {
                *_this->mBeforeEntityUniqueId = value;
            }
        }

        Property_Ptr(MC, Actor, mAfterEntity, AfterEntity);
    };

    Class EntityExplodeEvent
        : public EventTemplate<EntityExplodeEvent, ::Event::EntityExplodeEvent>
    {
        EventAPIs(EntityExplodeEvent, 52);

    public:
        Property_Ptr(MC, Actor, mActor, Actor);
        Property_ValueType(MC, Vec3, mPos, Pos);
        Property_Ptr(MC, BlockSource, mDimension, BlockSource);
        Property(float, mRadius, Radius);
        Property(float, mMaxResistance, MaxResistance);
        Property(bool, mBreaking, Breaking);
        Property(bool, mFire, Fire);
    };

    Class MobHurtEvent
        : public EventTemplate<MobHurtEvent, ::Event::MobHurtEvent>
    {
        EventAPIs(MobHurtEvent, 53);

    public:
        Property_Ptr(MC, Mob, mMob, Mob);
        Property_Ptr(MC, ActorDamageSource, mDamageSource, DamageSource);
        Property(float, mDamage, Damage);
    };

    Class MobDieEvent
        : public EventTemplate<MobDieEvent, ::Event::MobDieEvent>
    {
        EventAPIs(MobDieEvent, 54);

    public:
        Property_Ptr(MC, Mob, mMob, Mob);
        Property_Ptr(MC, ActorDamageSource, mDamageSource, DamageSource);
    };

    Class ProjectileHitEntityEvent
        : public EventTemplate<ProjectileHitEntityEvent, ::Event::ProjectileHitEntityEvent>
    {
        EventAPIs(ProjectileHitEntityEvent, 55);

    public:
        Property_Ptr(MC, Actor, mTarget, Target);
        Property_Ptr(MC, Actor, mSource, Source);
    };

    Class WitherBossDestroyEvent
        : public EventTemplate<WitherBossDestroyEvent, ::Event::WitherBossDestroyEvent>
    {
        EventAPIs(WitherBossDestroyEvent, 56);

    public:
        Property_Ptr(MC, WitherBoss, mWitherBoss, WitherBoss);
        Property_ValueType(MC, AABB, mDestroyRange, DestroyRange);
    };

    Class EntityRideEvent
        : public EventTemplate<EntityRideEvent, ::Event::EntityRideEvent>
    {
        EventAPIs(EntityRideEvent, 57);

    public:
        Property_Ptr(MC, Actor, mRider, Rider);
        Property_Ptr(MC, Actor, mVehicle, Vehicle);
    };

    Class EntityStepOnPressurePlateEvent
        : public EventTemplate<EntityStepOnPressurePlateEvent, ::Event::EntityStepOnPressurePlateEvent>
    {
        EventAPIs(EntityStepOnPressurePlateEvent, 58);

    public:
        Property_Ptr(MC, Actor, mActor, Actor);
        Property_Instance(MC, BlockInstance, mBlockInstance, BlockInstance);
    };

    Class ProjectileSpawnEvent
        : public EventTemplate<ProjectileSpawnEvent, ::Event::ProjectileSpawnEvent>
    {
        EventAPIs(ProjectileSpawnEvent, 60);

    public:
        Property_Ptr(MC, Actor, mShooter, Shooter);
        Property_Ptr(MC, ActorDefinitionIdentifier, mIdentifier, Identifier);
        Property_String(mType, Type);
    };

    Class ProjectileCreatedEvent
        : public EventTemplate<ProjectileCreatedEvent, ::Event::ProjectileCreatedEvent>
    {
        EventAPIs(ProjectileCreatedEvent, 61);

    public:
        Property_Ptr(MC, Actor, mShooter, Shooter);
        Property_Ptr(MC, Actor, mProjectile, Projectile);
    };

    Class ArmorStandChangeEvent
        : public EventTemplate<ArmorStandChangeEvent, ::Event::ArmorStandChangeEvent>
    {
        EventAPIs(ArmorStandChangeEvent, 62);

    public:
        Property_Ptr(MC, ArmorStand, mArmorStand, ArmorStand);
        Property_Ptr(MC, Player, mPlayer, Player);
        Property(int, mSlot, Slot);
    };

}