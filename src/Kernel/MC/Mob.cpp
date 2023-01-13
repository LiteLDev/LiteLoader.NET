#include <src/Header/MC/Mob.hpp>
namespace MC
{
    inline bool Mob::RefreshInventory()
    {
        return NativePtr->refreshInventory();
    }
} // namespace MC

#ifdef MANUAL_MAINTENANCE

#include <src/Header/MC/Vec3.hpp>
#include <src/Header/MC/BlockPos.hpp>
#include <src/Header/MC/AABB.hpp>
#include <src/Header/MC/ItemStack.hpp>
#include <src/Header/MC/Player.hpp>

void MC::Mob::OutOfWorld()
{
    NativePtr->outOfWorld();
}

void MC::Mob::DoInitialMove()
{
    NativePtr->_doInitialMove();
}

void MC::Mob::ResetUserPos(bool _0)
{
    NativePtr->resetUserPos(_0);
}

float MC::Mob::GetInterpolatedBodyRot(float _0)
{
    auto __ret = NativePtr->getInterpolatedBodyRot(_0);
    return __ret;
}

float MC::Mob::GetInterpolatedHeadRot(float _0)
{
    auto __ret = NativePtr->getInterpolatedHeadRot(_0);
    return __ret;
}

float MC::Mob::GetInterpolatedBodyYaw(float _0)
{
    auto __ret = NativePtr->getInterpolatedBodyYaw(_0);
    return __ret;
}

//void MC::Mob::UnkVfn40()
//{
//    NativePtr->__unk_vfn_40();
//}

void MC::Mob::TeleportTo(MC::Vec3 _0, bool _1, int _2, int _3, bool _4)
{
    NativePtr->teleportTo(_0, _1, _2, _3, _4);
}

void MC::Mob::NormalTick()
{
    NativePtr->normalTick();
}

void MC::Mob::BaseTick()
{
    NativePtr->baseTick();
}

//void MC::Mob::VehicleTick()
//{
//    NativePtr->vehicleTick();
//}

bool MC::Mob::StartRiding(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->startRiding(__arg0);
    return __ret;
}

void MC::Mob::AddPassenger(MC::Actor^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    NativePtr->addPassenger(__arg0);
}

//void MC::Mob::UnkVfn61()
//{
//    NativePtr->__unk_vfn_61();
//}
//
//void MC::Mob::UnkVfn68()
//{
//    NativePtr->__unk_vfn_68();
//}
//
//void MC::Mob::UnkVfn82()
//{
//    NativePtr->__unk_vfn_82();
//}

/*bool MC::Mob::CanInteractWithOtherEntitiesInGame()
{
    auto __ret = NativePtr->canInteractWithOtherEntitiesInGame();
    return __ret;
}*/

//void MC::Mob::UnkVfn88()
//{
//    NativePtr->__unk_vfn_88();
//}

void MC::Mob::PlayerTouch(MC::Player^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Player*)_0->NativePtr;
    NativePtr->playerTouch(__arg0);
}

//void MC::Mob::UnkVfn95()
//{
//    NativePtr->__unk_vfn_95();
//}
//
//void MC::Mob::UnkVfn98()
//{
//    NativePtr->__unk_vfn_98();
//}
//
//void MC::Mob::UnkVfn105()
//{
//    NativePtr->__unk_vfn_105();
//}
//
//void MC::Mob::UnkVfn107()
//{
//    NativePtr->__unk_vfn_107();
//}
//
//void MC::Mob::UnkVfn108()
//{
//    NativePtr->__unk_vfn_108();
//}
//
//void MC::Mob::UnkVfn109()
//{
//    NativePtr->__unk_vfn_109();
//}

bool MC::Mob::IsValidTarget(MC::Actor^ _0)
{
    auto __arg0 = (class ::Actor*)_0->NativePtr;
    auto __ret = NativePtr->isValidTarget(__arg0);
    return __ret;
}

bool MC::Mob::Attack(MC::Actor^ _0, MC::ActorDamageCause _1)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    auto __arg1 = (::ActorDamageCause)_1;
    auto __ret = NativePtr->attack(__arg0, __arg1);
    return __ret;
}

void MC::Mob::OnTame()
{
    NativePtr->onTame();
}

void MC::Mob::OnFailedTame()
{
    NativePtr->onFailedTame();
}

bool MC::Mob::canPowerJump()
{
    auto __ret = NativePtr->canPowerJump();
    return __ret;
}

void MC::Mob::VehicleLanded(MC::Vec3 _0, MC::Vec3 _1)
{
    NativePtr->vehicleLanded(_0, _1);
}

void MC::Mob::AnimateHurt()
{
    NativePtr->animateHurt();
}

bool MC::Mob::DoFireHurt(int _0)
{
    auto __ret = NativePtr->doFireHurt(_0);
    return __ret;
}

void MC::Mob::AwardKillScore(MC::Actor^ _0, int _1)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    NativePtr->awardKillScore(__arg0, _1);
}

bool MC::Mob::CanFreeze()
{
    auto __ret = NativePtr->canFreeze();
    return __ret;
}

/*bool MC::Mob::CanChangeDimensions()
{
    auto __ret = NativePtr->canChangeDimensions();
    return __ret;
}*/

//void MC::Mob::UnkVfn181()
//{
//    NativePtr->__unk_vfn_181();
//}

bool MC::Mob::CanBePulledIntoVehicle()
{
    auto __ret = NativePtr->canBePulledIntoVehicle();
    return __ret;
}

//void MC::Mob::UnkVfn195()
//{
//    NativePtr->__unk_vfn_195();
//}

bool MC::Mob::CanSynchronizeNewEntity()
{
    auto __ret = NativePtr->canSynchronizeNewEntity();
    return __ret;
}

void MC::Mob::StopRiding(bool _0, bool _1, bool _2)
{
    NativePtr->stopRiding(_0, _1, _2);
}

void MC::Mob::BuildDebugInfo(::System::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    NativePtr->buildDebugInfo(__arg0);
}

void MC::Mob::Swing()
{
    NativePtr->swing();
}

//void MC::Mob::UnkVfn220()
//{
//    NativePtr->__unk_vfn_220();
//}
//
//void MC::Mob::UnkVfn221()
//{
//    NativePtr->__unk_vfn_221();
//}

void MC::Mob::SetAuxValue(int _0)
{
    NativePtr->setAuxValue(_0);
}

void MC::Mob::StopSpinAttack()
{
    NativePtr->stopSpinAttack();
}

//void MC::Mob::UnkVfn246()
//{
//    NativePtr->__unk_vfn_246();
//}
//
//void MC::Mob::UnkVfn249()
//{
//    NativePtr->__unk_vfn_249();
//}

void MC::Mob::Kill()
{
    NativePtr->kill();
}

bool MC::Mob::ShouldDropDeathLoot()
{
    auto __ret = NativePtr->shouldDropDeathLoot();
    return __ret;
}

//void MC::Mob::UnkVfn261()
//{
//    NativePtr->__unk_vfn_261();
//}

void MC::Mob::AddAdditionalSaveData(MC::CompoundTag^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::CompoundTag*)_0->NativePtr;
    NativePtr->addAdditionalSaveData(__arg0);
}

//void MC::Mob::UnkVfn269()
//{
//    NativePtr->__unk_vfn_269();
//}

void MC::Mob::RemovePassenger(MC::ActorUniqueID _0, bool _1, bool _2, bool _3)
{
    NativePtr->_removePassenger(_0, _1, _2, _3);
}

void MC::Mob::OnSizeUpdated()
{
    NativePtr->_onSizeUpdated();
}

//void MC::Mob::UnkVfn278()
//{
//    NativePtr->__unk_vfn_278();
//}

void MC::Mob::Knockback(MC::Actor^ _0, int _1, float _2, float _3, float _4, float _5, float _6)
{
    auto __arg0 = (class ::Actor*)_0->NativePtr;
    NativePtr->knockback(__arg0, _1, _2, _3, _4, _5, _6);
}

void MC::Mob::SpawnAnim()
{
    NativePtr->spawnAnim();
}

float MC::Mob::GetMeleeWeaponDamageBonus(MC::Mob^ _0)
{
    auto __arg0 = (class ::Mob*)_0->NativePtr;
    auto __ret = NativePtr->getMeleeWeaponDamageBonus(__arg0);
    return __ret;
}

void MC::Mob::Travel(float _0, float _1, float _2)
{
    NativePtr->travel(_0, _1, _2);
}

void MC::Mob::ApplyFinalFriction(float _0, bool _1)
{
    NativePtr->applyFinalFriction(_0, _1);
}

void MC::Mob::AiStep()
{
    NativePtr->aiStep();
}

void MC::Mob::PushActors()
{
    NativePtr->pushActors();
}

void MC::Mob::LookAt(MC::Actor^ _0, float _1, float _2)
{
    auto __arg0 = (class ::Actor*)_0->NativePtr;
    NativePtr->lookAt(__arg0, _1, _2);
}

bool MC::Mob::CheckSpawnRules(bool _0)
{
    auto __ret = NativePtr->checkSpawnRules(_0);
    return __ret;
}

bool MC::Mob::CheckSpawnObstruction()
{
    auto __ret = NativePtr->checkSpawnObstruction();
    return __ret;
}

float MC::Mob::GetAttackAnim(float _0)
{
    auto __ret = NativePtr->getAttackAnim(_0);
    return __ret;
}

//void MC::Mob::UnkVfn307()
//{
//    NativePtr->__unk_vfn_307();
//}

bool MC::Mob::IsAlliedTo(MC::Mob^ _0)
{
    auto __arg0 = (class ::Mob*)_0->NativePtr;
    auto __ret = NativePtr->isAlliedTo(__arg0);
    return __ret;
}

bool MC::Mob::DoHurtTarget(MC::Actor^ _0, MC::ActorDamageCause _1)
{
    auto __arg0 = (class ::Actor*)_0->NativePtr;
    auto __arg1 = (::ActorDamageCause)_1;
    auto __ret = NativePtr->doHurtTarget(__arg0, __arg1);
    return __ret;
}

//void MC::Mob::UnkVfn311()
//{
//    NativePtr->__unk_vfn_311();
//}

void MC::Mob::LeaveCaravan()
{
    NativePtr->leaveCaravan();
}

void MC::Mob::JoinCaravan(MC::Mob^ _0)
{
    auto __arg0 = (class ::Mob*)_0->NativePtr;
    NativePtr->joinCaravan(__arg0);
}

void MC::Mob::ContainerChanged(int _0)
{
    NativePtr->containerChanged(_0);
}

void MC::Mob::UpdateEquipment()
{
    NativePtr->updateEquipment();
}

void MC::Mob::DropEquipmentOnDeath()
{
    NativePtr->dropEquipmentOnDeath();
}

void MC::Mob::ClearVanishEnchantedItemsOnDeath()
{
    NativePtr->clearVanishEnchantedItemsOnDeath();
}

void MC::Mob::SendInventory(bool _0)
{
    NativePtr->sendInventory(_0);
}

bool MC::Mob::CreateAIGoals()
{
    auto __ret = NativePtr->createAIGoals();
    return __ret;
}

void MC::Mob::OnBorn(MC::Actor^ _0, MC::Actor^ _1)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Actor*)_0->NativePtr;
    if (ReferenceEquals(_1, nullptr))
        throw gcnew ::System::ArgumentNullException("_1", "Cannot be null because it is a C++ reference (&).");
    auto& __arg1 = *(class ::Actor*)_1->NativePtr;
    NativePtr->onBorn(__arg0, __arg1);
}

void MC::Mob::AttackAnimation(MC::Actor^ _0, float _1)
{
    auto __arg0 = (class ::Actor*)_0->NativePtr;
    NativePtr->attackAnimation(__arg0, _1);
}

float MC::Mob::GetWalkTargetValue(MC::BlockPos _0)
{
    return NativePtr->_getWalkTargetValue(_0);
}

bool MC::Mob::CanExistWhenDisallowMob()
{
    auto __ret = NativePtr->canExistWhenDisallowMob();
    return __ret;
}

//void MC::Mob::UnkVfn345()
//{
//    NativePtr->__unk_vfn_345();
//}

void MC::Mob::AscendLadder()
{
    NativePtr->ascendLadder();
}

void MC::Mob::AscendBlockByJumping()
{
    NativePtr->ascendBlockByJumping();
}

void MC::Mob::DescendBlockByCrouching()
{
    NativePtr->descendBlockByCrouching();
}

void MC::Mob::DropContainer()
{
    NativePtr->dropContainer();
}

void MC::Mob::JumpFromGround()
{
    NativePtr->jumpFromGround();
}

void MC::Mob::UpdateAi()
{
    NativePtr->updateAi();
}

void MC::Mob::NewServerAiStep()
{
    NativePtr->newServerAiStep();
}

void MC::Mob::ServerAiMobStep()
{
    NativePtr->_serverAiMobStep();
}

void MC::Mob::DropBags()
{
    NativePtr->dropBags();
}

void MC::Mob::TickDeath()
{
    NativePtr->tickDeath();
}

void MC::Mob::UpdateGliding()
{
    NativePtr->updateGliding();
}

//void MC::Mob::UnkVfn359()
//{
//    NativePtr->__unk_vfn_359();
//}

MC::AABB MC::Mob::GetAdjustedAABBForSpawnCheck(MC::AABB _0, MC::Vec3 _1)
{
    return NativePtr->_getAdjustedAABBForSpawnCheck(_0, _1);
}

void MC::Mob::EndJump()
{
    NativePtr->_endJump();
}

void MC::Mob::AddSpeedModifier(MC::Mce::UUID _0, ::System::String^ _1, float _2)
{
    auto __arg1 = clix::marshalString<clix::E_UTF8>(_1);
    NativePtr->addSpeedModifier(_0, __arg1, _2);
}

//void MC::Mob::CreateAI(::System::Collections::Generic::List<MC::GoalDefinition^>^ _0)
//{
//    auto _tmp_0 = std::vector<::GoalDefinition>();
//    for each (MC::GoalDefinition ^ _element in _0)
//    {
//        if (ReferenceEquals(_element, nullptr))
//            throw gcnew ::System::ArgumentNullException("_element", "Cannot be null because it is passed by value.");
//        auto _marshalElement = *(struct ::GoalDefinition*)_element->NativePtr;
//        _tmp_0.push_back(_marshalElement);
//    }
//    auto __arg0 = _tmp_0;
//    NativePtr->createAI(__arg0);
//}

void MC::Mob::EmitJumpPreventedEvent(MC::BlockPos _0)
{
    NativePtr->emitJumpPreventedEvent(_0);
}

void MC::Mob::FrostWalk()
{
    NativePtr->frostWalk();
}

void MC::Mob::OnPlayerJump(int _0)
{
    NativePtr->onPlayerJump(_0);
}

void MC::Mob::RemoveSpeedModifier(MC::Mce::UUID _0)
{
    NativePtr->removeSpeedModifier(_0);
}

void MC::Mob::ResetAttributes()
{
    NativePtr->resetAttributes();
}

void MC::Mob::ResetNoActionTime()
{
    NativePtr->resetNoActionTime();
}

void MC::Mob::SetJumpVelRedux(bool _0)
{
    NativePtr->setJumpVelRedux(_0);
}

void MC::Mob::SetJumping(bool _0)
{
    NativePtr->setJumping(_0);
}

void MC::Mob::SetNaturallySpawned(bool _0)
{
    NativePtr->setNaturallySpawned(_0);
}

void MC::Mob::SetSpeedModifier(float _0)
{
    NativePtr->setSpeedModifier(_0);
}

void MC::Mob::SetSurfaceMob(bool _0)
{
    NativePtr->setSurfaceMob(_0);
}

void MC::Mob::SetXxa(float _0)
{
    NativePtr->setXxa(_0);
}

void MC::Mob::SetYya(float _0)
{
    NativePtr->setYya(_0);
}

void MC::Mob::SnapToYBodyRot(float _0)
{
    NativePtr->snapToYBodyRot(_0);
}

void MC::Mob::SnapToYHeadRot(float _0)
{
    NativePtr->snapToYHeadRot(_0);
}

bool MC::Mob::IsRuntimePredictedMovementEnabled::get()
{
    auto __ret = NativePtr->isRuntimePredictedMovementEnabled();
    return __ret;
}

float MC::Mob::YawSpeedInDegreesPerSecond::get()
{
    auto __ret = NativePtr->getYawSpeedInDegreesPerSecond();
    return __ret;
}

float MC::Mob::CameraOffset::get()
{
    auto __ret = NativePtr->getCameraOffset();
    return __ret;
}

bool MC::Mob::IsImmobile::get()
{
    auto __ret = NativePtr->isImmobile();
    return __ret;
}

bool MC::Mob::IsPickable::get()
{
    auto __ret = NativePtr->isPickable();
    return __ret;
}

bool MC::Mob::Sleeping::get()
{
    auto __ret = NativePtr->isSleeping();
    return __ret;
}

void MC::Mob::Sleeping::set(bool _0)
{
    NativePtr->setSleeping(_0);
}

bool MC::Mob::IsBlocking::get()
{
    auto __ret = NativePtr->isBlocking();
    return __ret;
}

bool MC::Mob::IsAlive::get()
{
    auto __ret = NativePtr->isAlive();
    return __ret;
}

bool MC::Mob::SurfaceMob::get()
{
    auto __ret = NativePtr->isSurfaceMob();
    return __ret;
}

MC::Actor^ MC::Mob::Target::get()
{
    auto __ret = NativePtr->getTarget();
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
}

void MC::Mob::Target::set(MC::Actor^ _0)
{
    auto __arg0 = (class ::Actor*)_0->NativePtr;
    NativePtr->setTarget(__arg0);
}

//MC::Actor^ MC::Mob::FindAttackTarget::get()
//{
//    auto __ret = NativePtr->findAttackTarget();
//    if (__ret == nullptr) return nullptr;
//    return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
//}

bool MC::Mob::Jumping::get()
{
    auto __ret = NativePtr->isJumping();
    return __ret;
}

MC::ActorUniqueID MC::Mob::SourceUniqueID::get()
{
    return NativePtr->getSourceUniqueID();
}

int MC::Mob::PortalWaitTime::get()
{
    auto __ret = NativePtr->getPortalWaitTime();
    return __ret;
}

MC::ActorUniqueID MC::Mob::ControllingPlayer::get()
{
    return NativePtr->getControllingPlayer();
}

bool MC::Mob::InCaravan::get()
{
    auto __ret = NativePtr->inCaravan();
    return __ret;
}

int MC::Mob::DeathTime::get()
{
    auto __ret = NativePtr->getDeathTime();
    return __ret;
}

float MC::Mob::YHeadRot::get()
{
    auto __ret = NativePtr->getYHeadRot();
    return __ret;
}

void MC::Mob::YHeadRot::set(float _0)
{
    NativePtr->setYHeadRot(_0);
}

/*float MC::Mob::YHeadRotO::get()
{
    auto __ret = NativePtr->getYHeadRotO();
    return __ret;
}*/

bool MC::Mob::IsWorldBuilder::get()
{
    auto __ret = NativePtr->isWorldBuilder();
    return __ret;
}

bool MC::Mob::IsCreative::get()
{
    auto __ret = NativePtr->isCreative();
    return __ret;
}

bool MC::Mob::IsAdventure::get()
{
    auto __ret = NativePtr->isAdventure();
    return __ret;
}

bool MC::Mob::IsSurvival::get()
{
    auto __ret = NativePtr->isSurvival();
    return __ret;
}

bool MC::Mob::IsSpectator::get()
{
    auto __ret = NativePtr->isSpectator();
    return __ret;
}

bool MC::Mob::Sprinting::get()
{
    auto __ret = NativePtr->isSprinting();
    return __ret;
}

void MC::Mob::Sprinting::set(bool _0)
{
    NativePtr->setSprinting(_0);
}

float MC::Mob::Speed::get()
{
    auto __ret = NativePtr->getSpeed();
    return __ret;
}

void MC::Mob::Speed::set(float _0)
{
    NativePtr->setSpeed(_0);
}

float MC::Mob::JumpPower::get()
{
    auto __ret = NativePtr->getJumpPower();
    return __ret;
}

int MC::Mob::MeleeKnockbackBonus::get()
{
    auto __ret = NativePtr->getMeleeKnockbackBonus();
    return __ret;
}

bool MC::Mob::IsLookingAtAnEntity::get()
{
    auto __ret = NativePtr->isLookingAtAnEntity();
    return __ret;
}

int MC::Mob::ItemUseDuration::get()
{
    auto __ret = NativePtr->getItemUseDuration();
    return __ret;
}

float MC::Mob::ItemUseStartupProgress::get()
{
    auto __ret = NativePtr->getItemUseStartupProgress();
    return __ret;
}

float MC::Mob::ItemUseIntervalProgress::get()
{
    auto __ret = NativePtr->getItemUseIntervalProgress();
    return __ret;
}

int MC::Mob::ItemUseIntervalAxis::get()
{
    auto __ret = NativePtr->getItemUseIntervalAxis();
    return __ret;
}

int MC::Mob::TimeAlongSwing::get()
{
    auto __ret = NativePtr->getTimeAlongSwing();
    return __ret;
}

float MC::Mob::MaxHeadXRot::get()
{
    auto __ret = NativePtr->getMaxHeadXRot();
    return __ret;
}

bool MC::Mob::HasCaravanTail::get()
{
    auto __ret = NativePtr->hasCaravanTail();
    return __ret;
}

MC::ActorUniqueID MC::Mob::CaravanHead::get()
{
    return NativePtr->getCaravanHead();
}

int MC::Mob::ArmorValue::get()
{
    auto __ret = NativePtr->getArmorValue();
    return __ret;
}

float MC::Mob::ArmorCoverPercentage::get()
{
    auto __ret = NativePtr->getArmorCoverPercentage();
    return __ret;
}

int MC::Mob::ToughnessValue::get()
{
    auto __ret = NativePtr->getToughnessValue();
    return __ret;
}

int MC::Mob::ClearEquipment::get()
{
    auto __ret = NativePtr->clearEquipment();
    return __ret;
}

array<int>^ MC::Mob::AllArmorID::get()
{
    auto __ret = NativePtr->getAllArmorID();
    auto _tmp__ret = gcnew array<int>(static_cast<int>(__ret.size()));
    auto __list0 = __ret;
    for (int i = 0; i < __list0.size(); ++i)
    {
        auto _marshalElement = __list0[i];
        _tmp__ret[i] = _marshalElement;
    }
    return _tmp__ret;
}

int MC::Mob::ArmorTypeHash::get()
{
    auto __ret = NativePtr->getArmorTypeHash();
    return __ret;
}

bool MC::Mob::TransitioningSitting::get()
{
    auto __ret = NativePtr->isTransitioningSitting();
    return __ret;
}

void MC::Mob::TransitioningSitting::set(bool _0)
{
    NativePtr->setTransitioningSitting(_0);
}

int MC::Mob::AttackTime::get()
{
    auto __ret = NativePtr->getAttackTime();
    return __ret;
}

bool MC::Mob::DiscardFriction::get()
{
    auto __ret = NativePtr->discardFriction();
    return __ret;
}

MC::BlockPos MC::Mob::BoundOrigin::get()
{
    return NativePtr->getBoundOrigin();
}

int MC::Mob::CaravanSize::get()
{
    auto __ret = NativePtr->getCaravanSize();
    return __ret;
}

int MC::Mob::EatCounter::get()
{
    auto __ret = NativePtr->getEatCounter();
    return __ret;
}

void MC::Mob::EatCounter::set(int _0)
{
    NativePtr->setEatCounter(_0);
}

MC::Mob^ MC::Mob::FirstCaravanHead::get()
{
    auto __ret = NativePtr->getFirstCaravanHead();
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Mob((class ::Mob*)__ret);
}

float MC::Mob::FlightSpeed::get()
{
    auto __ret = NativePtr->getFlightSpeed();
    return __ret;
}

void MC::Mob::FlightSpeed::set(float _0)
{
    NativePtr->setFlightSpeed(_0);
}

float MC::Mob::FrictionModifier::get()
{
    auto __ret = NativePtr->getFrictionModifier();
    return __ret;
}

void MC::Mob::FrictionModifier::set(float _0)
{
    NativePtr->setFrictionModifier(_0);
}

int MC::Mob::GlidingTicks::get()
{
    auto __ret = NativePtr->getGlidingTicks();
    return __ret;
}

float MC::Mob::JumpEffectAmplifierValue::get()
{
    auto __ret = NativePtr->getJumpEffectAmplifierValue();
    return __ret;
}

float MC::Mob::JumpMultiplier::get()
{
    auto __ret = NativePtr->getJumpMultiplier();
    return __ret;
}

//MC::Mob::JumpPreventionResult^ MC::Mob::JumpPrevention::get()
//{
//    auto __ret = NativePtr->getJumpPrevention();
//    auto ____ret = new struct ::Mob::JumpPreventionResult(__ret);
//    return (____ret == nullptr) ? nullptr : gcnew ::MC::Mob::JumpPreventionResult((struct ::Mob::JumpPreventionResult*)____ret, true);
//}

float MC::Mob::MovementComponentCurrentSpeed::get()
{
    auto __ret = NativePtr->getMovementComponentCurrentSpeed();
    return __ret;
}

void MC::Mob::MovementComponentCurrentSpeed::set(float _0)
{
    NativePtr->setMovementComponentCurrentSpeed(_0);
}

int MC::Mob::NoActionTime::get()
{
    auto __ret = NativePtr->getNoActionTime();
    return __ret;
}

float MC::Mob::PassengerLockedBodyRot::get()
{
    auto __ret = NativePtr->getPassengerLockedBodyRot();
    return __ret;
}

void MC::Mob::PassengerLockedBodyRot::set(float _0)
{
    NativePtr->setPassengerLockedBodyRot(_0);
}

float MC::Mob::PassengerRotLimit::get()
{
    auto __ret = NativePtr->getPassengerRotLimit();
    return __ret;
}

void MC::Mob::PassengerRotLimit::set(float _0)
{
    NativePtr->setPassengerRotLimit(_0);
}

int MC::Mob::RollCounter::get()
{
    auto __ret = NativePtr->getRollCounter();
    return __ret;
}

float MC::Mob::SwimSpeedMultiplier::get()
{
    auto __ret = NativePtr->getSwimSpeedMultiplier();
    return __ret;
}

void MC::Mob::SwimSpeedMultiplier::set(float _0)
{
    NativePtr->setSwimSpeedMultiplier(_0);
}

MC::ActorUniqueID MC::Mob::TargetCaptain::get()
{
    return NativePtr->getTargetCaptain();
}

void MC::Mob::TargetCaptain::set(MC::ActorUniqueID _0)
{
    NativePtr->setTargetCaptain(_0);
}

float MC::Mob::YRotA::get()
{
    auto __ret = NativePtr->getYRotA();
    return __ret;
}

void MC::Mob::YRotA::set(float _0)
{
    NativePtr->setYRotA(_0);
}

float MC::Mob::Zza::get()
{
    auto __ret = NativePtr->getZza();
    return __ret;
}

void MC::Mob::Zza::set(float _0)
{
    NativePtr->setZza(_0);
}

bool MC::Mob::HasBoundOrigin::get()
{
    auto __ret = NativePtr->hasBoundOrigin();
    return __ret;
}

bool MC::Mob::IsAbleToMove::get()
{
    auto __ret = NativePtr->isAbleToMove();
    return __ret;
}

bool MC::Mob::Eating::get()
{
    auto __ret = NativePtr->isEating();
    return __ret;
}

void MC::Mob::Eating::set(bool _0)
{
    NativePtr->setEating(_0);
}

bool MC::Mob::IsFrostWalking::get()
{
    auto __ret = NativePtr->isFrostWalking();
    return __ret;
}

bool MC::Mob::IsGliding::get()
{
    auto __ret = NativePtr->isGliding();
    return __ret;
}

bool MC::Mob::IsLayingEgg::get()
{
    auto __ret = NativePtr->isLayingEgg();
    return __ret;
}

void MC::Mob::IsLayingEgg::set(bool _0)
{
    NativePtr->setIsLayingEgg(_0);
}

bool MC::Mob::IsPregnant::get()
{
    auto __ret = NativePtr->isPregnant();
    return __ret;
}

void MC::Mob::IsPregnant::set(bool _0)
{
    NativePtr->setIsPregnant(_0);
}

bool MC::Mob::Rolling::get()
{
    auto __ret = NativePtr->isRolling();
    return __ret;
}

void MC::Mob::Rolling::set(bool _0)
{
    NativePtr->setRolling(_0);
}

int MC::Mob::ARMOR_DAMAGE_DIVISOR::get()
{
    return ::Mob::ARMOR_DAMAGE_DIVISOR;
}

float MC::Mob::ARMOR_PROTECTION_DIVIDER::get()
{
    return ::Mob::ARMOR_PROTECTION_DIVIDER;
}

float MC::Mob::ASCEND_BLOCK_BY_JUMPING_SPEED::get()
{
    return ::Mob::ASCEND_BLOCK_BY_JUMPING_SPEED;
}

float MC::Mob::BASE_ARMOR_TOUGHNESS::get()
{
    return ::Mob::BASE_ARMOR_TOUGHNESS;
}

float MC::Mob::DEFAULT_GRAVITY::get()
{
    return ::Mob::DEFAULT_GRAVITY;
}

float MC::Mob::FRICTION_CONSTANT::get()
{
    return ::Mob::FRICTION_CONSTANT;
}

float MC::Mob::FRICTION_CONSTANT_MODIFIED::get()
{
    return ::Mob::FRICTION_CONSTANT_MODIFIED;
}

float MC::Mob::FRICTION_MODIFIER::get()
{
    return ::Mob::FRICTION_MODIFIER;
}

float MC::Mob::GLIDING_FALL_RESET_DELTA::get()
{
    return ::Mob::GLIDING_FALL_RESET_DELTA;
}

float MC::Mob::LADDER_CLIMB_SPEED::get()
{
    return ::Mob::LADDER_CLIMB_SPEED;
}

float MC::Mob::MAX_ARMOR::get()
{
    return ::Mob::MAX_ARMOR;
}

float MC::Mob::MIN_ARMOR_RATIO::get()
{
    return ::Mob::MIN_ARMOR_RATIO;
}

float MC::Mob::NUM_ARMOR_ITEMS::get()
{
    return ::Mob::NUM_ARMOR_ITEMS;
}

float MC::Mob::PLAYER_SWIMMING_SURFACE_OFFSET::get()
{
    return ::Mob::PLAYER_SWIMMING_SURFACE_OFFSET;
}

int MC::Mob::REMOVE_PASSENGERS_DELAY::get()
{
    return ::Mob::REMOVE_PASSENGERS_DELAY;
}

float MC::Mob::SLOW_FALL_GRAVITY::get()
{
    return ::Mob::SLOW_FALL_GRAVITY;
}

int MC::Mob::SPAWN_XP_DELAY::get()
{
    return ::Mob::SPAWN_XP_DELAY;
}

int MC::Mob::TOTAL_ROLL_STEPS::get()
{
    return ::Mob::TOTAL_ROLL_STEPS;
}
#endif // INCLUDE_MCAPI
