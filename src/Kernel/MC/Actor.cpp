#include <src/Header/MC/Actor.hpp>

#include <src/Header/MC/BlockSource.hpp>
#include <src/Header/MC/Tick.hpp>
#include <src/Header/MC/BlockInstance.hpp>
#include <src/Header/MC/UserEntityIdentifierComponent.hpp>
#include <src/Header/MC/MobEffect.hpp>
#include <src/Header/MC/Vec2.hpp>
#include <src/Header/MC/Vec3.hpp>
#include <src/Header/MC/ItemStack.hpp>
#include <src/Header/MC/CompoundTag.hpp>
#include <src/Header/MC/MobEffectInstance.hpp>
#include <src/Header/MC/AABB.hpp>
#include <src/Header/MC/Level.hpp>
#include <src/Header/MC/Player.hpp>

#include "src/Header/MC/Attribute.hpp"
#include "src/Header/MC/AttributeInstance.hpp"

namespace MC
{
    String^ Actor::TypeName::get()
    {
        return marshalString(NativePtr->getTypeName());
    }

    inline Vec3 Actor::Position::get()
    {
        return ::Vec3(NativePtr->getPosition());
    }

    inline BlockSource^ Actor::Blocksource::get()
    {
        return gcnew MC::BlockSource(NativePtr->getBlockSource());
    }

    inline Vec2 Actor::Direction::get()
    {
        return *NativePtr->getDirection();
    }

    inline ActorUniqueID Actor::ActorUniqueId::get()
    {
        return NativePtr->getActorUniqueId();
    }

    inline Vec3 Actor::CameraPos::get()
    {
        return NativePtr->getCameraPos();
    }

    inline Tick^ Actor::LastTick::get()
    {
        return gcnew Tick(NativePtr->getLastTick());
    }

    inline MC::Level^ Actor::Level::get()
    {
        return gcnew MC::Level(&NativePtr->getLevel());
    }

    inline List<String^>^ Actor::GetAllTags()
    {
        std::vector<std::string>& stdTags = NativePtr->getAllTags();
        auto len = stdTags.size();
        auto Tags = gcnew List<String^>(int(len));
        for (auto i = 0; i < len; i++)
        {
            Tags[i] = marshalString(stdTags[i]);
        }
        return Tags;
    }

    inline BlockInstance^ Actor::GetBlockFromViewVector(bool includeLiquid, bool solidOnly, float maxDistance, bool ignoreBorderBlocks, bool fullOnly)
    {
        return gcnew BlockInstance(NativePtr->getBlockFromViewVector(includeLiquid, solidOnly, maxDistance, ignoreBorderBlocks, fullOnly));
    }
    inline BlockInstance^ Actor::GetBlockFromViewVector(bool includeLiquid, bool solidOnly, float maxDistance, bool ignoreBorderBlocks)
    {
        return gcnew BlockInstance(NativePtr->getBlockFromViewVector(includeLiquid, solidOnly, maxDistance, ignoreBorderBlocks));
    }
    inline BlockInstance^ Actor::GetBlockFromViewVector(bool includeLiquid, bool solidOnly, float maxDistance)
    {
        return gcnew BlockInstance(NativePtr->getBlockFromViewVector(includeLiquid, solidOnly, maxDistance));
    }
    inline BlockInstance^ Actor::GetBlockFromViewVector(bool includeLiquid, bool solidOnly)
    {
        return gcnew BlockInstance(NativePtr->getBlockFromViewVector(includeLiquid, solidOnly));
    }
    inline BlockInstance^ Actor::GetBlockFromViewVector(bool includeLiquid)
    {
        return gcnew BlockInstance(NativePtr->getBlockFromViewVector(includeLiquid));
    }
    inline BlockInstance^ Actor::GetBlockFromViewVector()
    {
        return gcnew BlockInstance(NativePtr->getBlockFromViewVector());
    }
    BlockInstance^ Actor::GetBlockFromViewVector(FaceID face, bool includeLiquid, bool solidOnly, float maxDistance, bool ignoreBorderBlocks, bool fullOnly)
    {
        return gcnew BlockInstance(NativePtr->getBlockFromViewVector((::FaceID&)face, includeLiquid, solidOnly, maxDistance, ignoreBorderBlocks, fullOnly));
    }
    BlockInstance^ Actor::GetBlockFromViewVector(FaceID face, bool includeLiquid, bool solidOnly, float maxDistance, bool ignoreBorderBlocks)
    {
        return gcnew BlockInstance(NativePtr->getBlockFromViewVector((::FaceID&)face, includeLiquid, solidOnly, maxDistance, ignoreBorderBlocks));
    }
    BlockInstance^ Actor::GetBlockFromViewVector(FaceID face, bool includeLiquid, bool solidOnly, float maxDistance)
    {
        return gcnew BlockInstance(NativePtr->getBlockFromViewVector((::FaceID&)face, includeLiquid, solidOnly, maxDistance));
    }
    BlockInstance^ Actor::GetBlockFromViewVector(FaceID face, bool includeLiquid, bool solidOnly)
    {
        return gcnew BlockInstance(NativePtr->getBlockFromViewVector((::FaceID&)face, includeLiquid, solidOnly));
    }
    BlockInstance^ Actor::GetBlockFromViewVector(FaceID face, bool includeLiquid)
    {
        return gcnew BlockInstance(NativePtr->getBlockFromViewVector((::FaceID&)face, includeLiquid));
    }
    BlockInstance^ Actor::GetBlockFromViewVector(FaceID face)
    {
        return gcnew BlockInstance(NativePtr->getBlockFromViewVector((::FaceID&)face));
    }

    inline UserEntityIdentifierComponent^ Actor::UserEntityIdentifierComponent::get()
    {
        return gcnew MC::UserEntityIdentifierComponent(
            NativePtr->getUserEntityIdentifierComponent());
    }

    inline Actor^ Actor::GetActorFromViewVector(float maxDistance)
    {
        return gcnew Actor(NativePtr->getActorFromViewVector(maxDistance));
    }

    inline BlockPos Actor::BlockPos::get()
    {
        return MC::BlockPos(NativePtr->getBlockPos());
    }

    inline BlockInstance^ Actor::BlockStandingOn::get()
    {
        return gcnew BlockInstance(NativePtr->getBlockStandingOn());
    }

    inline bool Actor::IsSimulatedPlayer::get()
    {
        return NativePtr->isSimulatedPlayer();
    }
    inline bool Actor::IsPlayer::get()
    {
        return NativePtr->isPlayer();
    }
    inline bool Actor::IsItemActor::get()
    {
        return NativePtr->isItemActor();
    }
    inline bool Actor::IsOnGround::get()
    {
        return NativePtr->isOnGround();
    }
    inline int Actor::DimensionId::get()
    {
        return (int)NativePtr->getDimensionId();
    }
    inline bool Actor::SetOnFire(int time, bool isEffect)
    {
        return NativePtr->setOnFire(time, isEffect);
    }
    inline bool Actor::StopFire()
    {
        return NativePtr->stopFire();
    }
    inline bool Actor::HasTag(String^ tag)
    {
        return NativePtr->hasTag(marshalString(tag));
    }
    inline bool Actor::HurtEntity(float damage)
    {
        return NativePtr->hurtEntity(damage);
    }
    inline bool Actor::Teleport(Vec3 pos, int dimid)
    {
        return NativePtr->teleport(pos, dimid);
    }
    inline ItemStack^ Actor::HandSlot::get()
    {
        return gcnew ItemStack(NativePtr->getHandSlot());
    }
    inline bool Actor::Rename(String^ name)
    {
        return NativePtr->rename(marshalString(name));
    }
    inline float Actor::QuickEvalMolangScript(String^ expression)
    {
        return NativePtr->quickEvalMolangScript(marshalString(expression));
    }

    inline CompoundTag^ Actor::Nbt::get()
    {
        return gcnew CompoundTag(NativePtr->getNbt().release(), true);
    }
    inline void Actor::Nbt::set(CompoundTag^ nbt)
    {
        NativePtr->setNbt(nbt->NativePtr);
    }
    inline bool Actor::RefreshActorData()
    {
        return NativePtr->refreshActorData();
    }
    inline bool Actor::AddEffect(MobEffect::EffectType type, int tick, int level, bool ambient, bool showParticles, bool showAnimation)
    {
        return NativePtr->addEffect(::MobEffect::EffectType(type), tick, level, ambient, showParticles, showAnimation);
    }
    inline bool Actor::AddEffect(MobEffect::EffectType type, int tick, int level, bool ambient, bool showParticles)
    {
        return NativePtr->addEffect(::MobEffect::EffectType(type), tick, level, ambient, showParticles);
    }
    inline bool Actor::AddEffect(MobEffect::EffectType type, int tick, int level, bool ambient)
    {
        return NativePtr->addEffect(::MobEffect::EffectType(type), tick, level, ambient);
    }
    inline bool Actor::AddEffect(MobEffect::EffectType type, int tick, int level)
    {
        return NativePtr->addEffect(::MobEffect::EffectType(type), tick, level);
    }
} // namespace MC

#ifdef MANUAL_MAINTENANCE

bool MC::Actor::Teleport(MC::Vec3 to, int dimID, float x, float y)
{
    return NativePtr->teleport(to, dimID, x, y);
}

void MC::Actor::OutOfWorld()
{
    NativePtr->outOfWorld();
}

void MC::Actor::DoInitialMove()
{
    NativePtr->_doInitialMove();
}

void MC::Actor::ResetUserPos(bool _0)
{
    NativePtr->resetUserPos(_0);
}

float MC::Actor::GetInterpolatedBodyRot(float _0)
{
    auto __ret = NativePtr->getInterpolatedBodyRot(_0);
    return __ret;
}

float MC::Actor::GetInterpolatedHeadRot(float _0)
{
    auto __ret = NativePtr->getInterpolatedHeadRot(_0);
    return __ret;
}

float MC::Actor::GetInterpolatedBodyYaw(float _0)
{
    auto __ret = NativePtr->getInterpolatedBodyYaw(_0);
    return __ret;
}

//void MC::Actor::UnkVfn40()
//{
//    NativePtr->__unk_vfn_40();
//}

void MC::Actor::TeleportTo(MC::Vec3 _0, bool _1, int _2, int _3, bool _4)
{
    NativePtr->teleportTo(_0, _1, _2, _3, _4);
}

void MC::Actor::NormalTick()
{
    NativePtr->normalTick();
}

void MC::Actor::BaseTick()
{
    NativePtr->baseTick();
}

//void MC::Actor::VehicleTick()
//{
//    NativePtr->vehicleTick();
//}

bool MC::Actor::StartRiding(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->startRiding(__arg0);
    return __ret;
}

void MC::Actor::AddPassenger(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    NativePtr->addPassenger(__arg0);
}

//void MC::Actor::UnkVfn61()
//{
//    NativePtr->__unk_vfn_61();
//}
//
//void MC::Actor::UnkVfn68()
//{
//    NativePtr->__unk_vfn_68();
//}
//
//void MC::Actor::UnkVfn82()
//{
//    NativePtr->__unk_vfn_82();
//}

/*bool MC::Actor::CanInteractWithOtherEntitiesInGame()
{
    auto __ret = NativePtr->canInteractWithOtherEntitiesInGame();
    return __ret;
}*/

//void MC::Actor::UnkVfn88()
//{
//    NativePtr->__unk_vfn_88();
//}

void MC::Actor::PlayerTouch(MC::Player^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Player*)_0->NativePtr;
    NativePtr->playerTouch(__arg0);
}

//void MC::Actor::UnkVfn95()
//{
//    NativePtr->__unk_vfn_95();
//}
//
//void MC::Actor::UnkVfn98()
//{
//    NativePtr->__unk_vfn_98();
//}
//
//void MC::Actor::UnkVfn105()
//{
//    NativePtr->__unk_vfn_105();
//}
//
//void MC::Actor::UnkVfn107()
//{
//    NativePtr->__unk_vfn_107();
//}
//
//void MC::Actor::UnkVfn108()
//{
//    NativePtr->__unk_vfn_108();
//}
//
//void MC::Actor::UnkVfn109()
//{
//    NativePtr->__unk_vfn_109();
//}

bool MC::Actor::IsValidTarget(MC::Actor^ _0)
{
    auto __arg0 = (class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->isValidTarget(__arg0);
    return __ret;
}

bool MC::Actor::Attack(MC::Actor^ _0, MC::ActorDamageCause _1)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto __arg0 = _0->NativePtr;
    auto __arg1 = (::ActorDamageCause)_1;
    auto __ret = NativePtr->attack(*__arg0, __arg1);
    return __ret;
}

void MC::Actor::OnTame()
{
    NativePtr->onTame();
}

void MC::Actor::OnFailedTame()
{
    NativePtr->onFailedTame();
}

void MC::Actor::VehicleLanded(MC::Vec3 _0, MC::Vec3 _1)
{
    NativePtr->vehicleLanded(_0, _1);
}

void MC::Actor::AnimateHurt()
{
    NativePtr->animateHurt();
}

bool MC::Actor::DoFireHurt(int _0)
{
    auto __ret = NativePtr->doFireHurt(_0);
    return __ret;
}

void MC::Actor::AwardKillScore(MC::Actor^ _0, int _1)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    NativePtr->awardKillScore(__arg0, _1);
}

bool MC::Actor::CanFreeze()
{
    auto __ret = NativePtr->canFreeze();
    return __ret;
}

/*bool MC::Actor::CanChangeDimensions()
{
    auto __ret = NativePtr->canChangeDimensions();
    return __ret;
}*/

//void MC::Actor::UnkVfn181()
//{
//    NativePtr->__unk_vfn_181();
//}

bool MC::Actor::CanBePulledIntoVehicle()
{
    auto __ret = NativePtr->canBePulledIntoVehicle();
    return __ret;
}

//void MC::Actor::UnkVfn195()
//{
//    NativePtr->__unk_vfn_195();
//}

bool MC::Actor::CanSynchronizeNewEntity()
{
    auto __ret = NativePtr->canSynchronizeNewEntity();
    return __ret;
}

void MC::Actor::StopRiding(bool _0, bool _1, bool _2)
{
    NativePtr->stopRiding(_0, _1, _2);
}

void MC::Actor::BuildDebugInfo(::System::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    NativePtr->buildDebugInfo(__arg0);
}

void MC::Actor::Swing()
{
    NativePtr->swing();
}

//void MC::Actor::UnkVfn220()
//{
//    NativePtr->__unk_vfn_220();
//}
//
//void MC::Actor::UnkVfn221()
//{
//    NativePtr->__unk_vfn_221();
//}

void MC::Actor::SetAuxValue(int _0)
{
    NativePtr->setAuxValue(_0);
}

void MC::Actor::StopSpinAttack()
{
    NativePtr->stopSpinAttack();
}

//void MC::Actor::UnkVfn246()
//{
//    NativePtr->__unk_vfn_246();
//}
//
//void MC::Actor::UnkVfn249()
//{
//    NativePtr->__unk_vfn_249();
//}

void MC::Actor::Kill()
{
    NativePtr->kill();
}

bool MC::Actor::ShouldDropDeathLoot()
{
    auto __ret = NativePtr->shouldDropDeathLoot();
    return __ret;
}

//void MC::Actor::UnkVfn261()
//{
//    NativePtr->__unk_vfn_261();
//}

void MC::Actor::AddAdditionalSaveData(MC::CompoundTag^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::CompoundTag*)_0->NativePtr;
    NativePtr->addAdditionalSaveData(__arg0);
}

//void MC::Actor::UnkVfn269()
//{
//    NativePtr->__unk_vfn_269();
//}

void MC::Actor::RemovePassenger(MC::ActorUniqueID _0, bool _1, bool _2, bool _3)
{
    NativePtr->_removePassenger(_0, _1, _2, _3);
}

void MC::Actor::OnSizeUpdated()
{
    NativePtr->_onSizeUpdated();
}

void MC::Actor::SetLastHurtMob(MC::Actor^ _0)
{
    auto __arg0 = (class ::Actor*)_0->NativePtr;
    NativePtr->setLastHurtMob(__arg0);
}

void MC::Actor::ServerInitItemStackIds()
{
    NativePtr->_serverInitItemStackIds();
}

//void MC::Actor::Reset()
//{
//    NativePtr->reset();
//}

void MC::Actor::Remove()
{
    NativePtr->remove();
}

MC::Vec3 MC::Actor::GetPosExtrapolated(float _0)
{
    return NativePtr->getPosExtrapolated(_0);
}

/*void MC::Actor::SetRot(MC::Vec2% _0)
{
    pin_ptr<Vec2> p = &_0;
    NativePtr->setRot(*(::Vec2*)p);
}*/

void MC::Actor::Move(MC::Vec3 _0)
{
    NativePtr->move(_0);
}

MC::Vec3 MC::Actor::GetInterpolatedRidingPosition(float _0)
{
    return NativePtr->getInterpolatedRidingPosition(_0);
}

float MC::Actor::GetInterpolatedWalkAnimSpeed(float _0)
{
    return NativePtr->getInterpolatedWalkAnimSpeed(_0);
}

MC::Vec3 MC::Actor::GetInterpolatedRidingOffset(float _0, int _1)
{
    return NativePtr->getInterpolatedRidingOffset(_0, _1);
}

void MC::Actor::UpdateEntityInside()
{
    NativePtr->updateEntityInside();
}

void MC::Actor::UpdateEntityInside(MC::AABB _0)
{
    NativePtr->updateEntityInside(_0);
}

bool MC::Actor::CanDisableShield()
{
    auto __ret = NativePtr->canDisableShield();
    return __ret;
}

bool MC::Actor::TryTeleportTo(MC::Vec3 _0, bool _1, bool _2, int _3, int _4)
{
    return NativePtr->tryTeleportTo(_0, _1, _2, _3, _4);
}

void MC::Actor::ChorusFruitTeleport(MC::Vec3 _0)
{
    NativePtr->chorusFruitTeleport(_0);
}

void MC::Actor::LerpMotion(MC::Vec3 _0)
{
    NativePtr->lerpMotion(_0);
}

void MC::Actor::PositionPassenger(MC::Actor^ _0, float _1)
{
    NativePtr->positionPassenger(_0, _1);
}

void MC::Actor::FlagPassengerToRemove(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    NativePtr->flagPassengerToRemove(__arg0);
}

bool MC::Actor::Intersects(MC::Vec3 _0, MC::Vec3 _1)
{
    return NativePtr->intersects(_0, _1);
}

bool MC::Actor::CanShowNameTag()
{
    auto __ret = NativePtr->canShowNameTag();
    return __ret;
}

void MC::Actor::SetNameTagVisible(bool _0)
{
    NativePtr->setNameTagVisible(_0);
}

void MC::Actor::ResetBlockMovementSlowdownMultiplier()
{
    NativePtr->resetBlockMovementSlowdownMultiplier();
}

MC::Vec3 MC::Actor::GetHeadLookVector(float _0)
{
    return NativePtr->getHeadLookVector(_0);
}

bool MC::Actor::CanSee(MC::Vec3 _0)
{
    return NativePtr->canSee(_0);
}

bool MC::Actor::CanSee(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->canSee(__arg0);
    return __ret;
}

bool MC::Actor::IsSkyLit(float _0)
{
    auto __ret = NativePtr->isSkyLit(_0);
    return __ret;
}

float MC::Actor::GetBrightness(float _0)
{
    auto __ret = NativePtr->getBrightness(_0);
    return __ret;
}

void MC::Actor::OnAboveBubbleColumn(bool _0)
{
    NativePtr->onAboveBubbleColumn(_0);
}

void MC::Actor::OnInsideBubbleColumn(bool _0)
{
    NativePtr->onInsideBubbleColumn(_0);
}

bool MC::Actor::CanAttack(MC::Actor^ _0, bool _1)
{
    auto __arg0 = (class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->canAttack(__arg0, _1);
    return __ret;
}

void MC::Actor::PerformRangedAttack(MC::Actor^ _0, float _1)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    NativePtr->performRangedAttack(__arg0, _1);
}

void MC::Actor::SetOwner(MC::ActorUniqueID _0)
{
    NativePtr->setOwner(_0);
}

bool MC::Actor::ShouldRender()
{
    auto __ret = NativePtr->shouldRender();
    return __ret;
}

void MC::Actor::PlayAmbientSound()
{
    NativePtr->playAmbientSound();
}

void MC::Actor::OnLightningHit()
{
    NativePtr->onLightningHit();
}

void MC::Actor::Feed(int _0)
{
    NativePtr->feed(_0);
}

void MC::Actor::Despawn()
{
    NativePtr->despawn();
}

void MC::Actor::Killed(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    NativePtr->killed(__arg0);
}

bool MC::Actor::ConsumeTotem()
{
    auto __ret = NativePtr->consumeTotem();
    return __ret;
}

bool MC::Actor::Save(MC::CompoundTag^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::CompoundTag*)_0->NativePtr;
    auto __ret = NativePtr->save(__arg0);
    return __ret;
}

void MC::Actor::SaveWithoutId(MC::CompoundTag^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::CompoundTag*)_0->NativePtr;
    NativePtr->saveWithoutId(__arg0);
}

void MC::Actor::ThawFreezeEffect()
{
    NativePtr->thawFreezeEffect();
}

void MC::Actor::HandleInsidePortal(MC::BlockPos _0)
{
    NativePtr->handleInsidePortal(_0);
}

void MC::Actor::CheckFallDamage(float _0, bool _1)
{
    NativePtr->checkFallDamage(_0, _1);
}

void MC::Actor::HandleFallDistanceOnServer(float _0, float _1, bool _2)
{
    NativePtr->handleFallDistanceOnServer(_0, _1, _2);
}

void MC::Actor::OnSynchedFlagUpdate(int _0, long long _1, long long _2)
{
    NativePtr->onSynchedFlagUpdate(_0, _1, _2);
}

void MC::Actor::OnSynchedDataUpdate(int _0)
{
    NativePtr->onSynchedDataUpdate(_0);
}

bool MC::Actor::CanAddPassenger(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->canAddPassenger(__arg0);
    return __ret;
}

void MC::Actor::TickLeash()
{
    NativePtr->tickLeash();
}

void MC::Actor::SendMotionPacketIfNeeded()
{
    NativePtr->sendMotionPacketIfNeeded();
}

void MC::Actor::StartSwimming()
{
    NativePtr->startSwimming();
}

void MC::Actor::StopSwimming()
{
    NativePtr->stopSwimming();
}

void MC::Actor::Heal(int _0)
{
    NativePtr->heal(_0);
}

bool MC::Actor::CanBeAffected(MC::MobEffectInstance^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::MobEffectInstance*)_0->NativePtr;
    auto __ret = NativePtr->canBeAffected(__arg0.getId());
    return __ret;
}

bool MC::Actor::CanBeAffected(int _0)
{
    auto __ret = NativePtr->canBeAffected(_0);
    return __ret;
}

bool MC::Actor::CanBeAffectedByArrow(MC::MobEffectInstance^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::MobEffectInstance*)_0->NativePtr;
    auto __ret = NativePtr->canBeAffectedByArrow(__arg0);
    return __ret;
}

void MC::Actor::OnEffectAdded(MC::MobEffectInstance^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::MobEffectInstance*)_0->NativePtr;
    NativePtr->onEffectAdded(__arg0);
}

void MC::Actor::OnEffectUpdated(MC::MobEffectInstance^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::MobEffectInstance*)_0->NativePtr;
    NativePtr->onEffectUpdated(__arg0);
}

void MC::Actor::OnEffectRemoved(MC::MobEffectInstance^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::MobEffectInstance*)_0->NativePtr;
    NativePtr->onEffectRemoved(__arg0);
}

void MC::Actor::OpenContainerComponent(MC::Player^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Player*)_0->NativePtr;
    NativePtr->openContainerComponent(__arg0);
}

void MC::Actor::GetDebugText(::System::Collections::Generic::List<::System::String^>^ _0)
{
    auto _tmp_0 = std::vector<::std::string>();
    for each (::System::String ^ _element in _0)
    {
        auto _marshalElement = clix::marshalString<clix::E_UTF8>(_element);
        _tmp_0.push_back(_marshalElement);
    }
    auto& __arg0 = _tmp_0;
    NativePtr->getDebugText(__arg0);
}

float MC::Actor::GetPassengerYRotation(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->getPassengerYRotation(__arg0);
    return __ret;
}

void MC::Actor::SetSize(float _0, float _1)
{
    NativePtr->setSize(_0, _1);
}

void MC::Actor::OnOrphan()
{
    NativePtr->onOrphan();
}

void MC::Actor::Wobble()
{
    NativePtr->wobble();
}

bool MC::Actor::WasHurt()
{
    auto __ret = NativePtr->wasHurt();
    return __ret;
}

void MC::Actor::StartSpinAttack()
{
    NativePtr->startSpinAttack();
}

void MC::Actor::ReloadLootTable()
{
    NativePtr->reloadLootTable();
}

bool MC::Actor::ShouldTick()
{
    auto __ret = NativePtr->shouldTick();
    return __ret;
}

float MC::Actor::GetNextStep(float _0)
{
    auto __ret = NativePtr->getNextStep(_0);
    return __ret;
}

void MC::Actor::InterpolatorTick()
{
    NativePtr->interpolatorTick();
}

bool MC::Actor::ShouldTryMakeStepSound()
{
    auto __ret = NativePtr->shouldTryMakeStepSound();
    return __ret;
}

void MC::Actor::MarkHurt()
{
    NativePtr->markHurt();
}

void MC::Actor::CheckInsideBlocks(float _0)
{
    NativePtr->checkInsideBlocks(_0);
}

void MC::Actor::PushOutOfBlocks(MC::Vec3 _0)
{
    NativePtr->pushOutOfBlocks(_0);
}

void MC::Actor::DoWaterSplashEffect()
{
    NativePtr->doWaterSplashEffect();
}

void MC::Actor::SpawnTrailBubbles()
{
    NativePtr->spawnTrailBubbles();
}

void MC::Actor::UpdateInsideBlock()
{
    NativePtr->updateInsideBlock();
}

bool MC::Actor::SetNbt(MC::CompoundTag^ nbt)
{
    auto __arg0 = (class ::CompoundTag*)nbt->NativePtr;
    auto __ret = NativePtr->setNbt(__arg0);
    return __ret;
}

void MC::Actor::SendDirtyActorData()
{
    NativePtr->_sendDirtyActorData();
}

void MC::Actor::AddDefinitionGroup(::System::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    NativePtr->addDefinitionGroup(__arg0);
}

void MC::Actor::AddEffect(MC::MobEffectInstance^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::MobEffectInstance*)_0->NativePtr;
    NativePtr->addEffect(__arg0);
}

bool MC::Actor::AddTag(::System::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __ret = NativePtr->addTag(__arg0);
    return __ret;
}

void MC::Actor::BuildDebugGroupInfo(::System::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    NativePtr->buildDebugGroupInfo(__arg0);
}

MC::Vec3 MC::Actor::BuildForward()
{
    return NativePtr->buildForward();
}

void MC::Actor::Burn(int _0, bool _1)
{
    NativePtr->burn(_0, _1);
}

void MC::Actor::CacheComponentData()
{
    NativePtr->cacheComponentData();
}

float MC::Actor::CalculateAttackDamage(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->calculateAttackDamage(__arg0);
    return __ret;
}

bool MC::Actor::CanAscendCurrentBlockByJumping()
{
    auto __ret = NativePtr->canAscendCurrentBlockByJumping();
    return __ret;
}

bool MC::Actor::CanBeginOrContinueClimbingLadder()
{
    auto __ret = NativePtr->canBeginOrContinueClimbingLadder();
    return __ret;
}

bool MC::Actor::CanCurrentlySwim()
{
    auto __ret = NativePtr->canCurrentlySwim();
    return __ret;
}

bool MC::Actor::CanDescendBlockBelowByCrouching()
{
    auto __ret = NativePtr->canDescendBlockBelowByCrouching();
    return __ret;
}

bool MC::Actor::CanMate(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->canMate(__arg0);
    return __ret;
}

bool MC::Actor::CanSeeDaylight()
{
    auto __ret = NativePtr->canSeeDaylight();
    return __ret;
}

void MC::Actor::CelebrateHunt(int _0, bool _1)
{
    NativePtr->celebrateHunt(_0, _1);
}

//void MC::Actor::CheckForPropertyUpdate()
//{
//    NativePtr->checkForPropertyUpdate();
//}

void MC::Actor::ClearFishingHookID()
{
    NativePtr->clearFishingHookID();
}

bool MC::Actor::CloserThan(MC::Actor^ _0, float _1)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->closerThan(__arg0, _1);
    return __ret;
}

void MC::Actor::DeregisterTagsFromLevelCache()
{
    NativePtr->deregisterTagsFromLevelCache();
}

float MC::Actor::DistanceSqrToBlockPosCenter(MC::BlockPos _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto __ret = NativePtr->distanceSqrToBlockPosCenter(_0);
    return __ret;
}

float MC::Actor::DistanceTo(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->distanceTo(__arg0);
    return __ret;
}

float MC::Actor::DistanceTo(MC::Vec3 _0)
{
    return NativePtr->distanceTo(_0);
}

float MC::Actor::DistanceToSqr(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->distanceToSqr(__arg0);
    return __ret;
}

float MC::Actor::DistanceToSqr(MC::Vec3 _0)
{
    return NativePtr->distanceToSqr(_0);
}

void MC::Actor::DropLeash(bool _0, bool _1)
{
    NativePtr->dropLeash(_0, _1);
}

MC::BlockPos MC::Actor::GetBlockPosCurrentlyStandingOn(MC::Actor^ _0)
{
    auto __arg0 = (class ::Actor*)_0->NativePtr;
    return NativePtr->getBlockPosCurrentlyStandingOn(__arg0);
}

MC::MobEffectInstance^ MC::Actor::GetEffect(MC::MobEffect^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::MobEffect*)_0->NativePtr;
    auto __ret = NativePtr->getEffect(__arg0);
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::MobEffectInstance((class ::MobEffectInstance*)__ret);
}

bool MC::Actor::GetFirstAvailableSeatPos(MC::Actor^ _0, MC::Vec3 _1)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    return NativePtr->getFirstAvailableSeatPos(__arg0, ::Vec3(_1));
}

MC::Vec3 MC::Actor::GetInterpolatedPosition(float _0)
{
    return NativePtr->getInterpolatedPosition(_0);
}

MC::Vec2 MC::Actor::GetInterpolatedRotation(float _0)
{
    return NativePtr->getInterpolatedRotation(_0);
}

int MC::Actor::GetPassengerIndex(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->getPassengerIndex(__arg0);
    return __ret;
}

float MC::Actor::GetSwimAmount(float _0)
{
    auto __ret = NativePtr->getSwimAmount(_0);
    return __ret;
}

MC::Vec3 MC::Actor::GetViewVector(float _0)
{
    return NativePtr->getViewVector(_0);
}

bool MC::Actor::HasBeenHurtByMobInLastTicks(int _0)
{
    auto __ret = NativePtr->hasBeenHurtByMobInLastTicks(_0);
    return __ret;
}

bool MC::Actor::HasDefinitionGroup(::System::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __ret = NativePtr->hasDefinitionGroup(__arg0);
    return __ret;
}

bool MC::Actor::HasEffect(MC::MobEffect^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::MobEffect*)_0->NativePtr;
    auto __ret = NativePtr->hasEffect(__arg0);
    return __ret;
}

void MC::Actor::HealEffects(int _0)
{
    NativePtr->healEffects(_0);
}

void MC::Actor::InitActorProperties()
{
    NativePtr->initActorProperties();
}

bool MC::Actor::IsInsideBorderBlock(float _0)
{
    auto __ret = NativePtr->isInsideBorderBlock(_0);
    return __ret;
}

bool MC::Actor::IsPassenger(MC::ActorUniqueID _0)
{
    return NativePtr->isPassenger(*::Level::getEntity(_0));
}

bool MC::Actor::IsPassenger(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->isPassenger(__arg0);
    return __ret;
}

bool MC::Actor::IsRiding(MC::Actor^ _0)
{
    auto __arg0 = (class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->isRiding(__arg0);
    return __ret;
}

bool MC::Actor::IsRiding()
{
    auto __ret = NativePtr->isRiding();
    return __ret;
}

void MC::Actor::LerpTo(MC::Vec3 _0, MC::Vec2 _1, int _2)
{
    NativePtr->lerpTo(_0, _1, _2);
}

void MC::Actor::LerpTo(MC::Vec3 _0, MC::Vec2 _1, float _2, int _3)
{
    NativePtr->lerpTo(_0, _1, _2, _3);
}

void MC::Actor::LerpToRotation(MC::Vec2 _0, int _1)
{
    NativePtr->lerpToRotation(_0, _1);
}

void MC::Actor::MigrateUniqueID(MC::ActorUniqueID _0)
{
    NativePtr->migrateUniqueID(_0);
}

void MC::Actor::MoveBBs(MC::Vec3 _0)
{
    NativePtr->moveBBs(_0);
}

void MC::Actor::MoveRelative(float _0, float _1, float _2, float _3)
{
    NativePtr->moveRelative(_0, _1, _2, _3);
}

void MC::Actor::MoveTo(MC::Vec3 _0, MC::Vec2 _1)
{
    NativePtr->moveTo(_0, _1);
}

void MC::Actor::OnAffectedByWaterBottle()
{
    NativePtr->onAffectedByWaterBottle();
}

bool MC::Actor::OnClimbableBlock()
{
    auto __ret = NativePtr->onClimbableBlock();
    return __ret;
}

bool MC::Actor::OnHoverableBlock()
{
    auto __ret = NativePtr->onHoverableBlock();
    return __ret;
}

void MC::Actor::OnOnewayCollision(MC::AABB _0)
{
    NativePtr->onOnewayCollision(_0);
}

bool MC::Actor::operator==(MC::Actor^ __op, MC::Actor^ _0)
{
    bool __opNull = ReferenceEquals(__op, nullptr);
    bool _0Null = ReferenceEquals(_0, nullptr);
    if (__opNull || _0Null)
        return __opNull && _0Null;
    auto& __arg0 = *(class ::Actor*)__op->NativePtr;
    auto& __arg1 = *(class ::Actor*)_0->NativePtr;
    auto __ret = __arg0 == __arg1;
    return __ret;
}

bool MC::Actor::Equals(::System::Object^ obj)
{
    return this == safe_cast<MC::Actor^>(obj);
}

void MC::Actor::PositionAllPassengers(bool a1)
{
    NativePtr->positionAllPassengers(a1);
}

bool MC::Actor::PullInEntity(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->pullInEntity(__arg0);
    return __ret;
}

void MC::Actor::RefreshComponents()
{
    NativePtr->refreshComponents();
}

void MC::Actor::Reload()
{
    NativePtr->reload();
}

void MC::Actor::RemoveAllEffects()
{
    NativePtr->removeAllEffects();
}

void MC::Actor::RemoveAllPassengers(bool _0, bool _1)
{
    NativePtr->removeAllPassengers(_0, _1);
}

void MC::Actor::RemoveDefinitionGroup(::System::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    NativePtr->removeDefinitionGroup(__arg0);
}

void MC::Actor::RemoveEffect(int _0)
{
    NativePtr->removeEffect(_0);
}

//void MC::Actor::RemoveEffectParticles()
//{
//    NativePtr->removeEffectParticles();
//}

void MC::Actor::RemovePersistingTrade()
{
    NativePtr->removePersistingTrade();
}

bool MC::Actor::RemoveTag(::System::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __ret = NativePtr->removeTag(__arg0);
    return __ret;
}

void MC::Actor::ResetClientAnimations()
{
    NativePtr->resetClientAnimations();
}

void MC::Actor::ResetRegion()
{
    NativePtr->resetRegion();
}

void MC::Actor::SaveEntityFlags(MC::CompoundTag^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::CompoundTag*)_0->NativePtr;
    NativePtr->saveEntityFlags(__arg0);
}

void MC::Actor::SendActorDefinitionEventTriggered(::System::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    NativePtr->sendActorDefinitionEventTriggered(__arg0);
}

void MC::Actor::SendMotionToServer()
{
    NativePtr->sendMotionToServer();
}

void MC::Actor::SerializationSetHealth(int _0)
{
    NativePtr->serializationSetHealth(_0);
}

void MC::Actor::SetCanClimb(bool _0)
{
    NativePtr->setCanClimb(_0);
}

void MC::Actor::SetCollidableMob(bool _0)
{
    NativePtr->setCollidableMob(_0);
}

void MC::Actor::SetDancing(bool _0)
{
    NativePtr->setDancing(_0);
}

void MC::Actor::SetFishingHookID(MC::ActorUniqueID _0)
{
    NativePtr->setFishingHookID(_0);
}

void MC::Actor::SetInLove(MC::Actor^ _0)
{
    auto __arg0 = (class ::Actor*)_0->NativePtr;
    NativePtr->setInLove(__arg0);
}

void MC::Actor::SetInterpolation(bool _0)
{
    NativePtr->setInterpolation(_0);
}

void MC::Actor::SetLastHitBB(MC::Vec3 _0, MC::Vec3 _1)
{
    NativePtr->setLastHitBB(_0, _1);
}

void MC::Actor::SetPersistent()
{
    NativePtr->setPersistent();
}

void MC::Actor::SetPosDirectLegacy(MC::Vec3 _0)
{
    NativePtr->setPosDirectLegacy(_0);
}

void MC::Actor::SetPreviousPosRot(MC::Vec3 _0, MC::Vec2 _1)
{
    NativePtr->setPreviousPosRot(_0, _1);
}

void MC::Actor::SetSaddle(bool _0)
{
    NativePtr->setSaddle(_0);
}

void MC::Actor::SetScared(bool _0)
{
    NativePtr->setScared(_0);
}

void MC::Actor::SetStunned(bool _0)
{
    NativePtr->setStunned(_0);
}

void MC::Actor::SetTempted(bool _0)
{
    NativePtr->setTempted(_0);
}

void MC::Actor::SetVelocity(MC::Vec3 _0)
{
    NativePtr->setVelocity(_0);
}

bool MC::Actor::ShouldUpdateEffects()
{
    auto __ret = NativePtr->shouldUpdateEffects();
    return __ret;
}

//void MC::Actor::SpawnBalloonPopParticles()
//{
//    NativePtr->spawnBalloonPopParticles();
//}
//
//void MC::Actor::SpawnDeathParticles()
//{
//    NativePtr->spawnDeathParticles();
//}
//
//void MC::Actor::SpawnDustParticles(int _0)
//{
//    NativePtr->spawnDustParticles(_0);
//}
//
//void MC::Actor::SpawnTamingParticles(bool _0)
//{
//    NativePtr->spawnTamingParticles(_0);
//}
//
//void MC::Actor::TeleportPassengersTo(MC::Vec3 _0, int _1, int _2)
//{
//    NativePtr->teleportPassengersTo(_0, _1, _2);
//}

//::System::Collections::Generic::List<MC::ItemDescriptor^>^ MC::Actor::TryGetEquippableSlotAllowedItems(int _0)
//{
//    auto __ret = NativePtr->tryGetEquippableSlotAllowedItems(_0);
//    if (__ret == nullptr) return nullptr;
//    auto _tmp__ret = gcnew ::System::Collections::Generic::List<MC::ItemDescriptor^>();
//    auto __list0 = *__ret;
//    for (auto _element : __list0)
//    {
//        auto ___element = new struct ::ItemDescriptor(_element);
//        auto _marshalElement = (___element == nullptr) ? nullptr : gcnew ::MC::ItemDescriptor((struct ::ItemDescriptor*)___element, true);
//        _tmp__ret->Add(_marshalElement);
//    }
//    return _tmp__ret;
//}

/*bool MC::Actor::TryMoveChunks()
{
    auto __ret = NativePtr->tryMoveChunks();
    return __ret;
}*/

void MC::Actor::UpdateAnimationComponentOnServer()
{
    NativePtr->updateAnimationComponentOnServer();
}

void MC::Actor::UpdateBBFromDefinition()
{
    NativePtr->updateBBFromDefinition();
}

void MC::Actor::UpdateDescription()
{
    NativePtr->updateDescription();
}

void MC::Actor::UpdateInvisibilityStatus()
{
    NativePtr->updateInvisibilityStatus();
}

void MC::Actor::UpdateTickingData()
{
    NativePtr->updateTickingData();
}

bool MC::Actor::WasLastHitByPlayer()
{
    auto __ret = NativePtr->wasLastHitByPlayer();
    return __ret;
}

bool MC::Actor::WasLoadedFromNBTThisFrame()
{
    auto __ret = NativePtr->wasLoadedFromNBTThisFrame();
    return __ret;
}

MC::Vec2 MC::Actor::GetInterpolatedRotation(MC::Vec2 _0, MC::Vec2 _1, float _2)
{
    return::Actor::getInterpolatedRotation(_0, _1, _2);
}

MC::Vec3 MC::Actor::GetViewVector(MC::Vec2 _0, MC::Vec2 _1, float _2)
{
    return ::Actor::getViewVector(_0, _1, _2);
}

MC::AttributeInstance^ MC::Actor::GetAttribute(MC::Attribute^ attributeType)
{
    return gcnew AttributeInstance(NativePtr->getMutableAttribute(*attributeType->NativePtr));
}

MC::Vec3 MC::Actor::FeetPosition::get()
{
    return NativePtr->getFeetPosition();
}

::System::Collections::Generic::List<::System::String^>^ MC::Actor::AllTags::get()
{
    auto __ret = NativePtr->getAllTags();
    auto _tmp__ret = gcnew ::System::Collections::Generic::List<::System::String^>();
    auto& __list0 = __ret;
    for (auto& _element : __list0)
    {
        auto _marshalElement = clix::marshalString<clix::E_UTF8>(_element);
        _tmp__ret->Add(_marshalElement);
    }
    return _tmp__ret;
}

bool MC::Actor::IsRuntimePredictedMovementEnabled::get()
{
    auto __ret = NativePtr->isRuntimePredictedMovementEnabled();
    return __ret;
}

float MC::Actor::YawSpeedInDegreesPerSecond::get()
{
    auto __ret = NativePtr->getYawSpeedInDegreesPerSecond();
    return __ret;
}

float MC::Actor::CameraOffset::get()
{
    auto __ret = NativePtr->getCameraOffset();
    return __ret;
}

bool MC::Actor::IsImmobile::get()
{
    auto __ret = NativePtr->isImmobile();
    return __ret;
}

bool MC::Actor::IsPickable::get()
{
    auto __ret = NativePtr->isPickable();
    return __ret;
}

bool MC::Actor::Sleeping::get()
{
    auto __ret = NativePtr->isSleeping();
    return __ret;
}

void MC::Actor::Sleeping::set(bool _0)
{
    NativePtr->setSleeping(_0);
}

bool MC::Actor::IsBlocking::get()
{
    auto __ret = NativePtr->isBlocking();
    return __ret;
}

bool MC::Actor::IsAlive::get()
{
    auto __ret = NativePtr->isAlive();
    return __ret;
}

bool MC::Actor::IsSurfaceMob::get()
{
    auto __ret = NativePtr->isSurfaceMob();
    return __ret;
}

MC::Actor^ MC::Actor::Target::get()
{
    auto __ret = NativePtr->getTarget();
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
}

void MC::Actor::Target::set(MC::Actor^ _0)
{
    auto __arg0 = (class ::Actor*)_0->NativePtr;
    NativePtr->setTarget(__arg0);
}

//MC::Actor^ MC::Actor::FindAttackTarget::get()
//{
//    auto __ret = NativePtr->findAttackTarget();
//    if (__ret == nullptr) return nullptr;
//    return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
//}

bool MC::Actor::CanPowerJump::get()
{
    auto __ret = NativePtr->canPowerJump();
    return __ret;
}

void MC::Actor::CanPowerJump::set(bool _0)
{
    NativePtr->setCanPowerJump(_0);
}

bool MC::Actor::IsJumping::get()
{
    auto __ret = NativePtr->isJumping();
    return __ret;
}

MC::ActorUniqueID MC::Actor::SourceUniqueID::get()
{
    return NativePtr->getSourceUniqueID();

}

int MC::Actor::PortalWaitTime::get()
{
    return NativePtr->getPortalWaitTime();
}

MC::ActorUniqueID MC::Actor::ControllingPlayer::get()
{
    return NativePtr->getControllingPlayer();
}

bool MC::Actor::InCaravan::get()
{
    auto __ret = NativePtr->inCaravan();
    return __ret;
}

int MC::Actor::DeathTime::get()
{
    auto __ret = NativePtr->getDeathTime();
    return __ret;
}

float MC::Actor::YHeadRot::get()
{
    auto __ret = NativePtr->getYHeadRot();
    return __ret;
}

void MC::Actor::YHeadRot::set(float _0)
{
    NativePtr->setYHeadRot(_0);
}

//float MC::Actor::YHeadRotO::get()
//{
//    auto __ret = NativePtr->getYHeadRotO();
//    return __ret;
//}

bool MC::Actor::IsWorldBuilder::get()
{
    auto __ret = NativePtr->isWorldBuilder();
    return __ret;
}

bool MC::Actor::IsCreative::get()
{
    auto __ret = NativePtr->isCreative();
    return __ret;
}

bool MC::Actor::IsAdventure::get()
{
    auto __ret = NativePtr->isAdventure();
    return __ret;
}

bool MC::Actor::IsSurvival::get()
{
    auto __ret = NativePtr->isSurvival();
    return __ret;
}

bool MC::Actor::IsSpectator::get()
{
    auto __ret = NativePtr->isSpectator();
    return __ret;
}

MC::Mob^ MC::Actor::LastHurtByMob::get()
{
    auto __ret = NativePtr->getLastHurtByMob();
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Mob((class ::Mob*)__ret);
}

void MC::Actor::LastHurtByMob::set(MC::Mob^ _0)
{
    auto __arg0 = (class ::Mob*)_0->NativePtr;
    NativePtr->setLastHurtByMob(__arg0);
}

MC::Player^ MC::Actor::LastHurtByPlayer::get()
{
    auto __ret = NativePtr->getLastHurtByPlayer();
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Player((class ::Player*)__ret);
}

void MC::Actor::LastHurtByPlayer::set(MC::Player^ _0)
{
    auto __arg0 = (class ::Player*)_0->NativePtr;
    NativePtr->setLastHurtByPlayer(__arg0);
}

MC::Mob^ MC::Actor::LastHurtMob::get()
{
    auto __ret = NativePtr->getLastHurtMob();
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Mob((class ::Mob*)__ret);
}

MC::Vec3 MC::Actor::Pos::get()
{
    return NativePtr->getPos();
}

void MC::Actor::Pos::set(MC::Vec3 _0)
{
    NativePtr->setPos(_0);
}

MC::Vec3% MC::Actor::PosPrev::get()
{
    return *(Vec3*)(const_cast<::Vec3*>(&NativePtr->getPosPrev()));
}

void MC::Actor::PosPrev::set(MC::Vec3% _0)
{
    pin_ptr<Vec3> p = &_0;
    NativePtr->setPosPrev(*(::Vec3*)p);
}

MC::Vec3 MC::Actor::FiringPos::get()
{
    return NativePtr->getFiringPos();
}

bool MC::Actor::IsFireImmune::get()
{
    auto __ret = NativePtr->isFireImmune();
    return __ret;
}

float MC::Actor::RidingHeight::get()
{
    auto __ret = NativePtr->getRidingHeight();
    return __ret;
}

bool MC::Actor::IsInWall::get()
{
    auto __ret = NativePtr->isInWall();
    return __ret;
}

bool MC::Actor::Invisible::get()
{
    auto __ret = NativePtr->isInvisible();
    return __ret;
}

void MC::Actor::Invisible::set(bool _0)
{
    NativePtr->setInvisible(_0);
}

::System::String^ MC::Actor::NameTag::get()
{
    auto& __ret = NativePtr->getNameTag();
    return (::System::String^)(clix::marshalString<clix::E_UTF8>(__ret));
}

void MC::Actor::NameTag::set(::System::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    NativePtr->setNameTag(__arg0);
}

unsigned long long MC::Actor::NameTagAsHash::get()
{
    auto __ret = NativePtr->getNameTagAsHash();
    return __ret;
}

::System::String^ MC::Actor::FormattedNameTag::get()
{
    auto __ret = NativePtr->getFormattedNameTag();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

::System::String^ MC::Actor::ScoreTag::get()
{
    auto& __ret = NativePtr->getScoreTag();
    return (::System::String^)(clix::marshalString<clix::E_UTF8>(__ret));
}

void MC::Actor::ScoreTag::set(::System::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    NativePtr->setScoreTag(__arg0);
}

bool MC::Actor::IsInWater::get()
{
    auto __ret = NativePtr->isInWater();
    return __ret;
}

bool MC::Actor::HasEnteredWater::get()
{
    auto __ret = NativePtr->hasEnteredWater();
    return __ret;
}

bool MC::Actor::IsInLava::get()
{
    auto __ret = NativePtr->isInLava();
    return __ret;
}

bool MC::Actor::IsOverWater::get()
{
    auto __ret = NativePtr->isOverWater();
    return __ret;
}

float MC::Actor::ShadowHeightOffs::get()
{
    auto __ret = NativePtr->getShadowHeightOffs();
    return __ret;
}

float MC::Actor::ShadowRadius::get()
{
    auto __ret = NativePtr->getShadowRadius();
    return __ret;
}

bool MC::Actor::IsSilent::get()
{
    auto __ret = NativePtr->isSilent();
    return __ret;
}

bool MC::Actor::Sneaking::get()
{
    auto __ret = NativePtr->isSneaking();
    return __ret;
}

void MC::Actor::Sneaking::set(bool _0)
{
    NativePtr->setSneaking(_0);
}

bool MC::Actor::IsOnFire::get()
{
    auto __ret = NativePtr->isOnFire();
    return __ret;
}

bool MC::Actor::IsOnHotBlock::get()
{
    auto __ret = NativePtr->isOnHotBlock();
    return __ret;
}

bool MC::Actor::IsAffectedByWaterBottle::get()
{
    auto __ret = NativePtr->isAffectedByWaterBottle();
    return __ret;
}

int MC::Actor::EquipmentCount::get()
{
    auto __ret = NativePtr->getEquipmentCount();
    return __ret;
}

bool MC::Actor::Sitting::get()
{
    auto __ret = NativePtr->isSitting();
    return __ret;
}

void MC::Actor::Sitting::set(bool _0)
{
    NativePtr->setSitting(_0);
}

int MC::Actor::InventorySize::get()
{
    auto __ret = NativePtr->getInventorySize();
    return __ret;
}

int MC::Actor::EquipSlots::get()
{
    auto __ret = NativePtr->getEquipSlots();
    return __ret;
}

int MC::Actor::ChestSlots::get()
{
    auto __ret = NativePtr->getChestSlots();
    return __ret;
}

bool MC::Actor::Standing::get()
{
    auto __ret = NativePtr->isStanding();
    return __ret;
}

void MC::Actor::Standing::set(bool _0)
{
    NativePtr->setStanding(_0);
}

bool MC::Actor::Enchanted::get()
{
    auto __ret = NativePtr->isEnchanted();
    return __ret;
}

void MC::Actor::Enchanted::set(bool _0)
{
    NativePtr->setEnchanted(_0);
}

float MC::Actor::PickRadius::get()
{
    auto __ret = NativePtr->getPickRadius();
    return __ret;
}

bool MC::Actor::IsWearingLeatherArmor::get()
{
    auto __ret = NativePtr->isWearingLeatherArmor();
    return __ret;
}

int MC::Actor::PortalCooldown::get()
{
    auto __ret = NativePtr->getPortalCooldown();
    return __ret;
}

bool MC::Actor::IsClientSide::get()
{
    auto __ret = NativePtr->isClientSide();
    return __ret;
}

bool MC::Actor::IsInvertedHealAndHarm::get()
{
    auto __ret = NativePtr->isInvertedHealAndHarm();
    return __ret;
}

float MC::Actor::MapDecorationRotation::get()
{
    auto __ret = NativePtr->getMapDecorationRotation();
    return __ret;
}

bool MC::Actor::IsAttackableGamemode::get()
{
    auto __ret = NativePtr->isAttackableGamemode();
    return __ret;
}

bool MC::Actor::DamageNearbyMobs::get()
{
    auto __ret = NativePtr->getDamageNearbyMobs();
    return __ret;
}

void MC::Actor::DamageNearbyMobs::set(bool _0)
{
    NativePtr->setDamageNearbyMobs(_0);
}

bool MC::Actor::UpdateWaterState::get()
{
    auto __ret = NativePtr->updateWaterState();
    return __ret;
}

MC::Vec3 MC::Actor::PosOld::get()
{
    return NativePtr->getPosOld();
}

//MC::Vec3 MC::Actor::RandomHeartPos::get()
//{
//    return NativePtr->_randomHeartPos();
//}

MC::Vec3 MC::Actor::CalcCenterPos::get()
{
    return NativePtr->calcCenterPos();
}

bool MC::Actor::CanFly::get()
{
    auto __ret = NativePtr->canFly();
    return __ret;
}

void MC::Actor::CanFly::set(bool _0)
{
    NativePtr->setCanFly(_0);
}

MC::AABB MC::Actor::AABB::get()
{
    return NativePtr->getAABB();
}

void MC::Actor::AABB::set(MC::AABB _0)
{
    NativePtr->setAABB(_0);
}

MC::Vec2 MC::Actor::AABBDim::get()
{
    return NativePtr->getAABBDim();
}

void MC::Actor::AABBDim::set(MC::Vec2 _0)
{
    NativePtr->setAABBDim(_0);
}

int MC::Actor::ActiveEffectCount::get()
{
    auto __ret = NativePtr->getActiveEffectCount();
    return __ret;
}

::System::Collections::Generic::List<MC::MobEffectInstance^>^ MC::Actor::AllEffects::get()
{
    auto& __ret = NativePtr->getAllEffects();
    auto _tmp__ret = gcnew ::System::Collections::Generic::List<MC::MobEffectInstance^>();
    auto& __list0 = __ret;
    for (auto& _element : __list0)
    {
        auto ___element = new class ::MobEffectInstance(_element);
        auto _marshalElement = (___element == nullptr) ? nullptr : gcnew ::MC::MobEffectInstance((class ::MobEffectInstance*)___element, true);
        _tmp__ret->Add(_marshalElement);
    }
    return (::System::Collections::Generic::List<MC::MobEffectInstance^>^)(_tmp__ret);
}

MC::BlockPos MC::Actor::BlockTarget::get()
{
    return NativePtr->getBlockTarget();
}

void MC::Actor::BlockTarget::set(MC::BlockPos _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    NativePtr->setBlockTarget(_0);
}

bool MC::Actor::CanPickupItems::get()
{
    auto __ret = NativePtr->getCanPickupItems();
    return __ret;
}

bool MC::Actor::ChainedDamageEffects::get()
{
    auto __ret = NativePtr->getChainedDamageEffects();
    return __ret;
}

void MC::Actor::ChainedDamageEffects::set(bool _0)
{
    NativePtr->setChainedDamageEffects(_0);
}

//bool MC::Actor::CollidableMobNear::get()
//{
//    auto __ret = NativePtr->getCollidableMobNear();
//    return __ret;
//}
//
//void MC::Actor::CollidableMobNear::set(bool _0)
//{
//    NativePtr->setCollidableMobNear(_0);
//}

int MC::Actor::ControllingSeat::get()
{
    auto __ret = NativePtr->getControllingSeat();
    return __ret;
}

void MC::Actor::ControllingSeat::set(int _0)
{
    NativePtr->setControllingSeat(_0);
}

float MC::Actor::CurrentSwimAmount::get()
{
    auto __ret = NativePtr->getCurrentSwimAmount();
    return __ret;
}

MC::Actor^ MC::Actor::FirstPassenger::get()
{
    auto __ret = NativePtr->getFirstPassenger();
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
}

int MC::Actor::Health::get()
{
    auto __ret = NativePtr->getHealth();
    return __ret;
}

int MC::Actor::HurtDir::get()
{
    auto __ret = NativePtr->getHurtDir();
    return __ret;
}

void MC::Actor::HurtDir::set(int _0)
{
    NativePtr->setHurtDir(_0);
}

int MC::Actor::HurtTime::get()
{
    auto __ret = NativePtr->getHurtTime();
    return __ret;
}

void MC::Actor::HurtTime::set(int _0)
{
    NativePtr->setHurtTime(_0);
}

bool MC::Actor::IsExperienceDropEnabled::get()
{
    auto __ret = NativePtr->getIsExperienceDropEnabled();
    return __ret;
}

void MC::Actor::IsExperienceDropEnabled::set(bool _0)
{
    NativePtr->setIsExperienceDropEnabled(_0);
}

int MC::Actor::JumpDuration::get()
{
    auto __ret = NativePtr->getJumpDuration();
    return __ret;
}

void MC::Actor::JumpDuration::set(int _0)
{
    NativePtr->setJumpDuration(_0);
}

int MC::Actor::LastHurtByMobTime::get()
{
    auto __ret = NativePtr->getLastHurtByMobTime();
    return __ret;
}

int MC::Actor::LastHurtByMobTimestamp::get()
{
    auto __ret = NativePtr->getLastHurtByMobTimestamp();
    return __ret;
}

MC::ActorDamageCause MC::Actor::LastHurtCause::get()
{
    auto __ret = NativePtr->getLastHurtCause();
    return (MC::ActorDamageCause)__ret;
}

float MC::Actor::LastHurtDamage::get()
{
    auto __ret = NativePtr->getLastHurtDamage();
    return __ret;
}

int MC::Actor::LastHurtMobTimestamp::get()
{
    auto __ret = NativePtr->getLastHurtMobTimestamp();
    return __ret;
}

unsigned long long MC::Actor::LastHurtTimestamp::get()
{
    auto __ret = NativePtr->getLastHurtTimestamp();
    return __ret;
}

MC::ActorUniqueID MC::Actor::LeashHolder::get()
{
    return NativePtr->getLeashHolder();
}

void MC::Actor::LeashHolder::set(MC::ActorUniqueID _0)
{
    NativePtr->setLeashHolder(_0);
}

int MC::Actor::LimitedLifetimeTicks::get()
{
    auto __ret = NativePtr->getLimitedLifetimeTicks();
    return __ret;
}

void MC::Actor::LimitedLifetimeTicks::set(int _0)
{
    NativePtr->setLimitedLifetimeTicks(_0);
}

//::System::Collections::Generic::List<MC::ActorLink^>^ MC::Actor::Links::get()
//{
//    auto __ret = NativePtr->getLinks();
//    auto _tmp__ret = gcnew ::System::Collections::Generic::List<MC::ActorLink^>();
//    auto __list0 = __ret;
//    for (auto _element : __list0)
//    {
//        auto ___element = new struct ::ActorLink(_element);
//        auto _marshalElement = (___element == nullptr) ? nullptr : gcnew ::MC::ActorLink((struct ::ActorLink*)___element, true);
//        _tmp__ret->Add(_marshalElement);
//    }
//    return _tmp__ret;
//}

int MC::Actor::MarkVariant::get()
{
    auto __ret = NativePtr->getMarkVariant();
    return __ret;
}

void MC::Actor::MarkVariant::set(int _0)
{
    NativePtr->setMarkVariant(_0);
}

int MC::Actor::MaxHealth::get()
{
    auto __ret = NativePtr->getMaxHealth();
    return __ret;
}

int MC::Actor::OnDeathExperience::get()
{
    auto __ret = NativePtr->getOnDeathExperience();
    return __ret;
}

MC::Mob^ MC::Actor::Owner::get()
{
    auto __ret = NativePtr->getOwner();
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Mob((class ::Mob*)__ret);
}

MC::ActorUniqueID MC::Actor::OwnerId::get()
{
    return NativePtr->getOwnerId();
}

int MC::Actor::PersistingTradeRiches::get()
{
    auto __ret = NativePtr->getPersistingTradeRiches();
    return __ret;
}

MC::Player^ MC::Actor::PlayerOwner::get()
{
    auto __ret = NativePtr->getPlayerOwner();
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Player((class ::Player*)__ret);
}

//MC::Vec3% MC::Actor::PosDelta::get()
//{
//    return *(Vec3*)const_cast<::Vec3*>(&NativePtr->getPosDelta());
//}
//
//void MC::Actor::PosDelta::set(MC::Vec3% _0)
//{
//    pin_ptr<Vec3> p = &_0;
//    NativePtr->setPosDelta(*(::Vec3*)p);
//}

MC::Vec3% MC::Actor::PosDeltaNonConst::get()
{
    return *(Vec3*)const_cast<::Vec3*>(&NativePtr->getPosDeltaNonConst());
}

float MC::Actor::Radius::get()
{
    auto __ret = NativePtr->getRadius();
    return __ret;
}

MC::Vec2 MC::Actor::Rotation::get()
{
    return NativePtr->getRotation();
}

MC::ActorRuntimeID^ MC::Actor::RuntimeID::get()
{
    auto __ret = NativePtr->getRuntimeID();
    auto ____ret = new class ::ActorRuntimeID(__ret);
    return (____ret == nullptr) ? nullptr : gcnew ::MC::ActorRuntimeID((class ::ActorRuntimeID*)____ret, true);
}

void MC::Actor::RuntimeID::set(MC::ActorRuntimeID^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is passed by value.");
    auto __arg0 = *(class ::ActorRuntimeID*)_0->NativePtr;
    NativePtr->setRuntimeID(__arg0);
}

int MC::Actor::ShakeTime::get()
{
    auto __ret = NativePtr->getShakeTime();
    return __ret;
}

void MC::Actor::ShakeTime::set(int _0)
{
    NativePtr->setShakeTime(_0);
}

int MC::Actor::SkinID::get()
{
    auto __ret = NativePtr->getSkinID();
    return __ret;
}

void MC::Actor::SkinID::set(int _0)
{
    NativePtr->setSkinID(_0);
}

float MC::Actor::SpeedInMetersPerSecond::get()
{
    auto __ret = NativePtr->getSpeedInMetersPerSecond();
    return __ret;
}

int MC::Actor::Strength::get()
{
    auto __ret = NativePtr->getStrength();
    return __ret;
}

void MC::Actor::Strength::set(int _0)
{
    NativePtr->setStrength(_0);
}

int MC::Actor::StrengthMax::get()
{
    auto __ret = NativePtr->getStrengthMax();
    return __ret;
}

void MC::Actor::StrengthMax::set(int _0)
{
    NativePtr->setStrengthMax(_0);
}

int MC::Actor::StructuralIntegrity::get()
{
    auto __ret = NativePtr->getStructuralIntegrity();
    return __ret;
}

void MC::Actor::StructuralIntegrity::set(int _0)
{
    NativePtr->setStructuralIntegrity(_0);
}

MC::ActorUniqueID MC::Actor::TargetId::get()
{
    return NativePtr->getTargetId();
}

bool MC::Actor::TradeInterest::get()
{
    auto __ret = NativePtr->getTradeInterest();
    return __ret;
}

void MC::Actor::TradeInterest::set(bool _0)
{
    NativePtr->setTradeInterest(_0);
}

MC::Player^ MC::Actor::TradingPlayer::get()
{
    auto __ret = NativePtr->getTradingPlayer();
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Player((class ::Player*)__ret);
}

void MC::Actor::TradingPlayer::set(MC::Player^ _0)
{
    auto __arg0 = (class ::Player*)_0->NativePtr;
    NativePtr->setTradingPlayer(__arg0);
}

MC::ActorUniqueID MC::Actor::UniqueID::get()
{
    return NativePtr->getUniqueID();
}

void MC::Actor::UniqueID::set(MC::ActorUniqueID _0)
{
    NativePtr->setUniqueID(_0);
}

int MC::Actor::Variant::get()
{
    auto __ret = NativePtr->getVariant();
    return __ret;
}

void MC::Actor::Variant::set(int _0)
{
    NativePtr->setVariant(_0);
}

MC::Actor^ MC::Actor::Vehicle::get()
{
    auto __ret = NativePtr->getVehicle();
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
}

MC::Actor^ MC::Actor::VehicleRoot::get()
{
    auto __ret = NativePtr->getVehicleRoot();
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
}

MC::ActorRuntimeID^ MC::Actor::VehicleRuntimeID::get()
{
    auto __ret = NativePtr->getVehicleRuntimeID();
    auto ____ret = new class ::ActorRuntimeID(__ret);
    return (____ret == nullptr) ? nullptr : gcnew ::MC::ActorRuntimeID((class ::ActorRuntimeID*)____ret, true);
}

float MC::Actor::VerticalSpeedInMetersPerSecond::get()
{
    auto __ret = NativePtr->getVerticalSpeedInMetersPerSecond();
    return __ret;
}

bool MC::Actor::HasAnyEffects::get()
{
    auto __ret = NativePtr->hasAnyEffects();
    return __ret;
}

bool MC::Actor::HasAnyVisibleEffects::get()
{
    auto __ret = NativePtr->hasAnyVisibleEffects();
    return __ret;
}

bool MC::Actor::HasDimension::get()
{
    auto __ret = NativePtr->hasDimension();
    return __ret;
}

bool MC::Actor::HasFishingHook::get()
{
    auto __ret = NativePtr->hasFishingHook();
    return __ret;
}

bool MC::Actor::HasLevel::get()
{
    auto __ret = NativePtr->hasLevel();
    return __ret;
}

bool MC::Actor::HasPassenger::get()
{
    auto __ret = NativePtr->hasPassenger();
    return __ret;
}

bool MC::Actor::HasPersistingTrade::get()
{
    auto __ret = NativePtr->hasPersistingTrade();
    return __ret;
}

bool MC::Actor::HasPlayerPassenger::get()
{
    auto __ret = NativePtr->hasPlayerPassenger();
    return __ret;
}

bool MC::Actor::HasPriorityAmmunition::get()
{
    auto __ret = NativePtr->hasPriorityAmmunition();
    return __ret;
}

bool MC::Actor::HasRuntimeID::get()
{
    auto __ret = NativePtr->hasRuntimeID();
    return __ret;
}

bool MC::Actor::HasSaddle::get()
{
    auto __ret = NativePtr->hasSaddle();
    return __ret;
}

bool MC::Actor::HasTags::get()
{
    auto __ret = NativePtr->hasTags();
    return __ret;
}

bool MC::Actor::HasTeleported::get()
{
    auto __ret = NativePtr->hasTeleported();
    return __ret;
}

/*bool MC::Actor::HasTickingArea::get()
{
    auto __ret = NativePtr->hasTickingArea();
    return __ret;
}*/

bool MC::Actor::HasTotemEquipped::get()
{
    auto __ret = NativePtr->hasTotemEquipped();
    return __ret;
}

bool MC::Actor::HasUniqueID::get()
{
    auto __ret = NativePtr->hasUniqueID();
    return __ret;
}

bool MC::Actor::InDownwardFlowingLiquid::get()
{
    auto __ret = NativePtr->inDownwardFlowingLiquid();
    return __ret;
}

bool MC::Actor::IsAngry::get()
{
    auto __ret = NativePtr->isAngry();
    return __ret;
}

bool MC::Actor::Autonomous::get()
{
    auto __ret = NativePtr->isAutonomous();
    return __ret;
}

void MC::Actor::Autonomous::set(bool _0)
{
    NativePtr->setAutonomous(_0);
}

bool MC::Actor::IsBaby::get()
{
    auto __ret = NativePtr->isBaby();
    return __ret;
}

bool MC::Actor::BreakingObstruction::get()
{
    auto __ret = NativePtr->isBreakingObstruction();
    return __ret;
}

void MC::Actor::BreakingObstruction::set(bool _0)
{
    NativePtr->setBreakingObstruction(_0);
}

bool MC::Actor::IsBribed::get()
{
    auto __ret = NativePtr->isBribed();
    return __ret;
}

bool MC::Actor::Charged::get()
{
    auto __ret = NativePtr->isCharged();
    return __ret;
}

void MC::Actor::Charged::set(bool _0)
{
    NativePtr->setCharged(_0);
}

bool MC::Actor::IsChested::get()
{
    auto __ret = NativePtr->isChested();
    return __ret;
}

bool MC::Actor::Climbing::get()
{
    auto __ret = NativePtr->isClimbing();
    return __ret;
}

void MC::Actor::Climbing::set(bool _0)
{
    NativePtr->setClimbing(_0);
}

bool MC::Actor::IsControlledByLocalInstance::get()
{
    auto __ret = NativePtr->isControlledByLocalInstance();
    return __ret;
}

bool MC::Actor::DoorBreaker::get()
{
    auto __ret = NativePtr->isDoorBreaker();
    return __ret;
}

void MC::Actor::DoorBreaker::set(bool _0)
{
    NativePtr->setDoorBreaker(_0);
}

bool MC::Actor::DoorOpener::get()
{
    auto __ret = NativePtr->isDoorOpener();
    return __ret;
}

void MC::Actor::DoorOpener::set(bool _0)
{
    NativePtr->setDoorOpener(_0);
}

bool MC::Actor::Global::get()
{
    auto __ret = NativePtr->isGlobal();
    return __ret;
}

void MC::Actor::Global::set(bool _0)
{
    NativePtr->setGlobal(_0);
}

bool MC::Actor::IsIgnited::get()
{
    auto __ret = NativePtr->isIgnited();
    return __ret;
}

bool MC::Actor::IsImmersedInWater::get()
{
    auto __ret = NativePtr->isImmersedInWater();
    return __ret;
}

bool MC::Actor::IsInClouds::get()
{
    auto __ret = NativePtr->isInClouds();
    return __ret;
}

bool MC::Actor::IsInContactWithWater::get()
{
    auto __ret = NativePtr->isInContactWithWater();
    return __ret;
}

bool MC::Actor::IsInLove::get()
{
    auto __ret = NativePtr->isInLove();
    return __ret;
}

bool MC::Actor::IsInPrecipitation::get()
{
    auto __ret = NativePtr->isInPrecipitation();
    return __ret;
}

bool MC::Actor::IsInRain::get()
{
    auto __ret = NativePtr->isInRain();
    return __ret;
}

bool MC::Actor::IsInScaffolding::get()
{
    auto __ret = NativePtr->isInScaffolding();
    return __ret;
}

bool MC::Actor::IsInSnow::get()
{
    auto __ret = NativePtr->isInSnow();
    return __ret;
}

bool MC::Actor::IsInThunderstorm::get()
{
    auto __ret = NativePtr->isInThunderstorm();
    return __ret;
}

bool MC::Actor::IsInWaterOrRain::get()
{
    auto __ret = NativePtr->isInWaterOrRain();
    return __ret;
}

bool MC::Actor::IsInWorld::get()
{
    auto __ret = NativePtr->isInWorld();
    return __ret;
}

bool MC::Actor::IsInsidePortal::get()
{
    auto __ret = NativePtr->isInsidePortal();
    return __ret;
}

bool MC::Actor::LayingDown::get()
{
    auto __ret = NativePtr->isLayingDown();
    return __ret;
}

void MC::Actor::LayingDown::set(bool _0)
{
    NativePtr->setLayingDown(_0);
}

bool MC::Actor::IsLeashed::get()
{
    auto __ret = NativePtr->isLeashed();
    return __ret;
}

bool MC::Actor::MovedToLimbo::get()
{
    auto __ret = NativePtr->isMovedToLimbo();
    return __ret;
}

void MC::Actor::MovedToLimbo::set(bool _0)
{
    NativePtr->setMovedToLimbo(_0);
}

bool MC::Actor::MovedToUnloadedChunk::get()
{
    auto __ret = NativePtr->isMovedToUnloadedChunk();
    return __ret;
}

void MC::Actor::MovedToUnloadedChunk::set(bool _0)
{
    NativePtr->setMovedToUnloadedChunk(_0);
}

bool MC::Actor::Moving::get()
{
    auto __ret = NativePtr->isMoving();
    return __ret;
}

void MC::Actor::Moving::set(bool _0)
{
    NativePtr->setMoving(_0);
}

bool MC::Actor::IsOrphan::get()
{
    auto __ret = NativePtr->isOrphan();
    return __ret;
}

bool MC::Actor::IsOutOfControl::get()
{
    auto __ret = NativePtr->isOutOfControl();
    return __ret;
}

bool MC::Actor::IsOverScaffolding::get()
{
    auto __ret = NativePtr->isOverScaffolding();
    return __ret;
}

bool MC::Actor::IsPacified::get()
{
    auto __ret = NativePtr->isPacified();
    return __ret;
}

bool MC::Actor::IsPersistent::get()
{
    auto __ret = NativePtr->isPersistent();
    return __ret;
}

bool MC::Actor::IsPlayingDead::get()
{
    auto __ret = NativePtr->isPlayingDead();
    return __ret;
}

bool MC::Actor::IsPowered::get()
{
    auto __ret = NativePtr->isPowered();
    return __ret;
}

bool MC::Actor::IsRegionValid::get()
{
    auto __ret = NativePtr->isRegionValid();
    return __ret;
}

bool MC::Actor::IsRemoved::get()
{
    auto __ret = NativePtr->isRemoved();
    return __ret;
}

bool MC::Actor::Resting::get()
{
    auto __ret = NativePtr->isResting();
    return __ret;
}

void MC::Actor::Resting::set(bool _0)
{
    NativePtr->setResting(_0);
}

bool MC::Actor::IsSafeToSleepNear::get()
{
    auto __ret = NativePtr->isSafeToSleepNear();
    return __ret;
}

bool MC::Actor::IsSheared::get()
{
    auto __ret = NativePtr->isSheared();
    return __ret;
}

//bool MC::Actor::IsSoulSpeedEnchantActive::get()
//{
//    auto __ret = NativePtr->isSoulSpeedEnchantActive();
//    return __ret;
//}

bool MC::Actor::IsStackable::get()
{
    auto __ret = NativePtr->isStackable();
    return __ret;
}

bool MC::Actor::Swimmer::get()
{
    auto __ret = NativePtr->isSwimmer();
    return __ret;
}

void MC::Actor::Swimmer::set(bool _0)
{
    NativePtr->setSwimmer(_0);
}

bool MC::Actor::IsSwimming::get()
{
    auto __ret = NativePtr->isSwimming();
    return __ret;
}

bool MC::Actor::IsTame::get()
{
    auto __ret = NativePtr->isTame();
    return __ret;
}

bool MC::Actor::IsTickingEntity::get()
{
    auto __ret = NativePtr->isTickingEntity();
    return __ret;
}

bool MC::Actor::IsTouchingDamageBlock::get()
{
    auto __ret = NativePtr->isTouchingDamageBlock();
    return __ret;
}

bool MC::Actor::IsTrading::get()
{
    auto __ret = NativePtr->isTrading();
    return __ret;
}

bool MC::Actor::IsTrusting::get()
{
    auto __ret = NativePtr->isTrusting();
    return __ret;
}

bool MC::Actor::IsUseNewTradeScreen::get()
{
    auto __ret = NativePtr->isUseNewTradeScreen();
    return __ret;
}

bool MC::Actor::WASDControlled::get()
{
    auto __ret = NativePtr->isWASDControlled();
    return __ret;
}

void MC::Actor::WASDControlled::set(bool _0)
{
    NativePtr->setWASDControlled(_0);
}

bool MC::Actor::Walker::get()
{
    auto __ret = NativePtr->isWalker();
    return __ret;
}

void MC::Actor::Walker::set(bool _0)
{
    NativePtr->setWalker(_0);
}

MC::ActorUniqueID MC::Actor::LovePartnerId::get()
{
    return NativePtr->lovePartnerId();
}

//float MC::Actor::DEFAULT_AMBIENT_SOUND_INTERVAL::get()
//{
//    return ::Actor::DEFAULT_AMBIENT_SOUND_INTERVAL;
//}

//float MC::Actor::DEFAULT_AMBIENT_SOUND_INTERVAL_RANGE::get()
//{
//    return ::Actor::DEFAULT_AMBIENT_SOUND_INTERVAL_RANGE;
//}
//
//float MC::Actor::DEFAULT_MOVEMENT_SOUND_DISTANCE_OFFSET::get()
//{
//    return ::Actor::DEFAULT_MOVEMENT_SOUND_DISTANCE_OFFSET;
//}

//MC::Vec3 MC::Actor::LAVA_AABB_SHRINK_AMOUNT::get()
//{
//    return ::Actor::LAVA_AABB_SHRINK_AMOUNT;
//}
//
//float MC::Actor::LAVA_FLOW_STRENGTH_MULTIPLIER::get()
//{
//    return ::Actor::LAVA_FLOW_STRENGTH_MULTIPLIER;
//}
//
//int MC::Actor::MAX_BYTE_CHARGE_AMOUNT::get()
//{
//    return ::Actor::MAX_BYTE_CHARGE_AMOUNT;
//}
//
//int MC::Actor::PLAYER_HURT_EXPERIENCE_TIME::get()
//{
//    return ::Actor::PLAYER_HURT_EXPERIENCE_TIME;
//}

//float MC::Actor::WATER_FLOW_STRENGTH_MULTIPLIER::get()
//{
//    return ::Actor::WATER_FLOW_STRENGTH_MULTIPLIER;
//}
#endif // MANUAL_MAINTENANCE
