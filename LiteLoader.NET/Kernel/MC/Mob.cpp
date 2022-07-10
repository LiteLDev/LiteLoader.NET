#include "../../Header/MC/Mob.hpp"
namespace MC
{
	inline bool Mob::RefreshInventory()
	{
		return NativePtr->refreshInventory();
	}
} // namespace MC

#ifdef MANUAL_MAINTENANCE

#include "../../Header/MC/Vec3.hpp"
#include "../../Header/MC/BlockPos.hpp"
#include "../../Header/MC/AABB.hpp"
#include "../../Header/MC/ItemStack.hpp"
#include "../../Header/MC/Player.hpp"

void MC::Mob::OutOfWorld()
{
	((class ::Mob*)NativePtr)->outOfWorld();
}

void MC::Mob::DoInitialMove()
{
	((class ::Mob*)NativePtr)->_doInitialMove();
}

void MC::Mob::ResetUserPos(bool _0)
{
	((class ::Mob*)NativePtr)->resetUserPos(_0);
}

float MC::Mob::GetInterpolatedBodyRot(float _0)
{
	auto __ret = ((class ::Mob*)NativePtr)->getInterpolatedBodyRot(_0);
	return __ret;
}

float MC::Mob::GetInterpolatedHeadRot(float _0)
{
	auto __ret = ((class ::Mob*)NativePtr)->getInterpolatedHeadRot(_0);
	return __ret;
}

float MC::Mob::GetInterpolatedBodyYaw(float _0)
{
	auto __ret = ((class ::Mob*)NativePtr)->getInterpolatedBodyYaw(_0);
	return __ret;
}

//void MC::Mob::UnkVfn40()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_40();
//}

void MC::Mob::TeleportTo(MC::Vec3 _0, bool _1, int _2, int _3)
{
	((class ::Mob*)NativePtr)->teleportTo(_0, _1, _2, _3);
}

void MC::Mob::NormalTick()
{
	((class ::Mob*)NativePtr)->normalTick();
}

void MC::Mob::BaseTick()
{
	((class ::Mob*)NativePtr)->baseTick();
}

//void MC::Mob::VehicleTick()
//{
//	((class ::Mob*)NativePtr)->vehicleTick();
//}

bool MC::Mob::StartRiding(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Mob*)NativePtr)->startRiding(__arg0);
	return __ret;
}

void MC::Mob::AddPassenger(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	((class ::Mob*)NativePtr)->addPassenger(__arg0);
}

//void MC::Mob::UnkVfn61()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_61();
//}
//
//void MC::Mob::UnkVfn68()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_68();
//}
//
//void MC::Mob::UnkVfn82()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_82();
//}

bool MC::Mob::CanInteractWithOtherEntitiesInGame()
{
	auto __ret = ((class ::Mob*)NativePtr)->canInteractWithOtherEntitiesInGame();
	return __ret;
}

//void MC::Mob::UnkVfn88()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_88();
//}

void MC::Mob::PlayerTouch(MC::Player^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Player*)_0->NativePtr;
	((class ::Mob*)NativePtr)->playerTouch(__arg0);
}

//void MC::Mob::UnkVfn95()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_95();
//}
//
//void MC::Mob::UnkVfn98()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_98();
//}
//
//void MC::Mob::UnkVfn105()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_105();
//}
//
//void MC::Mob::UnkVfn107()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_107();
//}
//
//void MC::Mob::UnkVfn108()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_108();
//}
//
//void MC::Mob::UnkVfn109()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_109();
//}

bool MC::Mob::IsValidTarget(MC::Actor^ _0)
{
	auto __arg0 = (class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Mob*)NativePtr)->isValidTarget(__arg0);
	return __ret;
}

bool MC::Mob::Attack(MC::Actor^ _0, MC::ActorDamageCause _1)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	auto __arg1 = (::ActorDamageCause)_1;
	auto __ret = ((class ::Mob*)NativePtr)->attack(__arg0, __arg1);
	return __ret;
}

void MC::Mob::OnTame()
{
	((class ::Mob*)NativePtr)->onTame();
}

void MC::Mob::OnFailedTame()
{
	((class ::Mob*)NativePtr)->onFailedTame();
}

bool MC::Mob::canPowerJump()
{
	auto __ret = ((class ::Mob*)NativePtr)->canPowerJump();
	return __ret;
}

void MC::Mob::VehicleLanded(MC::Vec3 _0, MC::Vec3 _1)
{
	((class ::Mob*)NativePtr)->vehicleLanded(_0, _1);
}

void MC::Mob::AnimateHurt()
{
	((class ::Mob*)NativePtr)->animateHurt();
}

bool MC::Mob::DoFireHurt(int _0)
{
	auto __ret = ((class ::Mob*)NativePtr)->doFireHurt(_0);
	return __ret;
}

void MC::Mob::AwardKillScore(MC::Actor^ _0, int _1)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	((class ::Mob*)NativePtr)->awardKillScore(__arg0, _1);
}

bool MC::Mob::CanFreeze()
{
	auto __ret = ((class ::Mob*)NativePtr)->canFreeze();
	return __ret;
}

bool MC::Mob::CanChangeDimensions()
{
	auto __ret = ((class ::Mob*)NativePtr)->canChangeDimensions();
	return __ret;
}

//void MC::Mob::UnkVfn181()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_181();
//}

bool MC::Mob::CanBePulledIntoVehicle()
{
	auto __ret = ((class ::Mob*)NativePtr)->canBePulledIntoVehicle();
	return __ret;
}

//void MC::Mob::UnkVfn195()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_195();
//}

bool MC::Mob::CanSynchronizeNewEntity()
{
	auto __ret = ((class ::Mob*)NativePtr)->canSynchronizeNewEntity();
	return __ret;
}

void MC::Mob::StopRiding(bool _0, bool _1, bool _2)
{
	((class ::Mob*)NativePtr)->stopRiding(_0, _1, _2);
}

void MC::Mob::BuildDebugInfo(::System::String^ _0)
{
	auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
	((class ::Mob*)NativePtr)->buildDebugInfo(__arg0);
}

void MC::Mob::Swing()
{
	((class ::Mob*)NativePtr)->swing();
}

//void MC::Mob::UnkVfn220()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_220();
//}
//
//void MC::Mob::UnkVfn221()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_221();
//}

void MC::Mob::SetAuxValue(int _0)
{
	((class ::Mob*)NativePtr)->setAuxValue(_0);
}

void MC::Mob::StopSpinAttack()
{
	((class ::Mob*)NativePtr)->stopSpinAttack();
}

//void MC::Mob::UnkVfn246()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_246();
//}
//
//void MC::Mob::UnkVfn249()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_249();
//}

void MC::Mob::Kill()
{
	((class ::Mob*)NativePtr)->kill();
}

bool MC::Mob::ShouldDropDeathLoot()
{
	auto __ret = ((class ::Mob*)NativePtr)->shouldDropDeathLoot();
	return __ret;
}

//void MC::Mob::UnkVfn261()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_261();
//}

void MC::Mob::AddAdditionalSaveData(MC::CompoundTag^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::CompoundTag*)_0->NativePtr;
	((class ::Mob*)NativePtr)->addAdditionalSaveData(__arg0);
}

//void MC::Mob::UnkVfn269()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_269();
//}

void MC::Mob::RemovePassenger(MC::ActorUniqueID^ _0, bool _1, bool _2, bool _3)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(struct ::ActorUniqueID*)_0->NativePtr;
	((class ::Mob*)NativePtr)->_removePassenger(__arg0, _1, _2, _3);
}

void MC::Mob::OnSizeUpdated()
{
	((class ::Mob*)NativePtr)->_onSizeUpdated();
}

//void MC::Mob::UnkVfn278()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_278();
//}

void MC::Mob::Knockback(MC::Actor^ _0, int _1, float _2, float _3, float _4, float _5, float _6)
{
	auto __arg0 = (class ::Actor*)_0->NativePtr;
	((class ::Mob*)NativePtr)->knockback(__arg0, _1, _2, _3, _4, _5, _6);
}

void MC::Mob::SpawnAnim()
{
	((class ::Mob*)NativePtr)->spawnAnim();
}

float MC::Mob::GetMeleeWeaponDamageBonus(MC::Mob^ _0)
{
	auto __arg0 = (class ::Mob*)_0->NativePtr;
	auto __ret = ((class ::Mob*)NativePtr)->getMeleeWeaponDamageBonus(__arg0);
	return __ret;
}

void MC::Mob::Travel(float _0, float _1, float _2)
{
	((class ::Mob*)NativePtr)->travel(_0, _1, _2);
}

void MC::Mob::ApplyFinalFriction(float _0, bool _1)
{
	((class ::Mob*)NativePtr)->applyFinalFriction(_0, _1);
}

void MC::Mob::AiStep()
{
	((class ::Mob*)NativePtr)->aiStep();
}

void MC::Mob::PushActors()
{
	((class ::Mob*)NativePtr)->pushActors();
}

void MC::Mob::LookAt(MC::Actor^ _0, float _1, float _2)
{
	auto __arg0 = (class ::Actor*)_0->NativePtr;
	((class ::Mob*)NativePtr)->lookAt(__arg0, _1, _2);
}

bool MC::Mob::CheckSpawnRules(bool _0)
{
	auto __ret = ((class ::Mob*)NativePtr)->checkSpawnRules(_0);
	return __ret;
}

bool MC::Mob::CheckSpawnObstruction()
{
	auto __ret = ((class ::Mob*)NativePtr)->checkSpawnObstruction();
	return __ret;
}

float MC::Mob::GetAttackAnim(float _0)
{
	auto __ret = ((class ::Mob*)NativePtr)->getAttackAnim(_0);
	return __ret;
}

//void MC::Mob::UnkVfn307()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_307();
//}

bool MC::Mob::IsAlliedTo(MC::Mob^ _0)
{
	auto __arg0 = (class ::Mob*)_0->NativePtr;
	auto __ret = ((class ::Mob*)NativePtr)->isAlliedTo(__arg0);
	return __ret;
}

bool MC::Mob::DoHurtTarget(MC::Actor^ _0, MC::ActorDamageCause _1)
{
	auto __arg0 = (class ::Actor*)_0->NativePtr;
	auto __arg1 = (::ActorDamageCause)_1;
	auto __ret = ((class ::Mob*)NativePtr)->doHurtTarget(__arg0, __arg1);
	return __ret;
}

//void MC::Mob::UnkVfn311()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_311();
//}

void MC::Mob::LeaveCaravan()
{
	((class ::Mob*)NativePtr)->leaveCaravan();
}

void MC::Mob::JoinCaravan(MC::Mob^ _0)
{
	auto __arg0 = (class ::Mob*)_0->NativePtr;
	((class ::Mob*)NativePtr)->joinCaravan(__arg0);
}

void MC::Mob::ContainerChanged(int _0)
{
	((class ::Mob*)NativePtr)->containerChanged(_0);
}

void MC::Mob::UpdateEquipment()
{
	((class ::Mob*)NativePtr)->updateEquipment();
}

void MC::Mob::DropEquipmentOnDeath()
{
	((class ::Mob*)NativePtr)->dropEquipmentOnDeath();
}

void MC::Mob::ClearVanishEnchantedItemsOnDeath()
{
	((class ::Mob*)NativePtr)->clearVanishEnchantedItemsOnDeath();
}

void MC::Mob::SendInventory(bool _0)
{
	((class ::Mob*)NativePtr)->sendInventory(_0);
}

bool MC::Mob::CreateAIGoals()
{
	auto __ret = ((class ::Mob*)NativePtr)->createAIGoals();
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
	((class ::Mob*)NativePtr)->onBorn(__arg0, __arg1);
}

void MC::Mob::AttackAnimation(MC::Actor^ _0, float _1)
{
	auto __arg0 = (class ::Actor*)_0->NativePtr;
	((class ::Mob*)NativePtr)->attackAnimation(__arg0, _1);
}

float MC::Mob::GetWalkTargetValue(MC::BlockPos _0)
{
	return ((class ::Mob*)NativePtr)->_getWalkTargetValue(_0);
}

bool MC::Mob::CanExistWhenDisallowMob()
{
	auto __ret = ((class ::Mob*)NativePtr)->canExistWhenDisallowMob();
	return __ret;
}

//void MC::Mob::UnkVfn345()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_345();
//}

void MC::Mob::AscendLadder()
{
	((class ::Mob*)NativePtr)->ascendLadder();
}

void MC::Mob::AscendBlockByJumping()
{
	((class ::Mob*)NativePtr)->ascendBlockByJumping();
}

void MC::Mob::DescendBlockByCrouching()
{
	((class ::Mob*)NativePtr)->descendBlockByCrouching();
}

void MC::Mob::DropContainer()
{
	((class ::Mob*)NativePtr)->dropContainer();
}

void MC::Mob::JumpFromGround()
{
	((class ::Mob*)NativePtr)->jumpFromGround();
}

void MC::Mob::UpdateAi()
{
	((class ::Mob*)NativePtr)->updateAi();
}

void MC::Mob::NewServerAiStep()
{
	((class ::Mob*)NativePtr)->newServerAiStep();
}

void MC::Mob::ServerAiMobStep()
{
	((class ::Mob*)NativePtr)->_serverAiMobStep();
}

void MC::Mob::DropBags()
{
	((class ::Mob*)NativePtr)->dropBags();
}

void MC::Mob::TickDeath()
{
	((class ::Mob*)NativePtr)->tickDeath();
}

void MC::Mob::UpdateGliding()
{
	((class ::Mob*)NativePtr)->updateGliding();
}

//void MC::Mob::UnkVfn359()
//{
//    ((class ::Mob*)NativePtr)->__unk_vfn_359();
//}

MC::AABB MC::Mob::GetAdjustedAABBForSpawnCheck(MC::AABB _0, MC::Vec3 _1)
{
	return ((class ::Mob*)NativePtr)->_getAdjustedAABBForSpawnCheck(_0, _1);
}

void MC::Mob::EndJump()
{
	((class ::Mob*)NativePtr)->_endJump();
}

void MC::Mob::AddSpeedModifier(MC::Mce::UUID _0, ::System::String^ _1, float _2)
{
	auto __arg1 = clix::marshalString<clix::E_UTF8>(_1);
	((class ::Mob*)NativePtr)->addSpeedModifier(_0, __arg1, _2);
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
//    ((class ::Mob*)NativePtr)->createAI(__arg0);
//}

void MC::Mob::EmitJumpPreventedEvent(MC::BlockPos _0)
{
	((class ::Mob*)NativePtr)->emitJumpPreventedEvent(_0);
}

void MC::Mob::FrostWalk()
{
	((class ::Mob*)NativePtr)->frostWalk();
}

void MC::Mob::OnPlayerJump(int _0)
{
	((class ::Mob*)NativePtr)->onPlayerJump(_0);
}

void MC::Mob::RemoveSpeedModifier(MC::Mce::UUID _0)
{
	((class ::Mob*)NativePtr)->removeSpeedModifier(_0);
}

void MC::Mob::ResetAttributes()
{
	((class ::Mob*)NativePtr)->resetAttributes();
}

void MC::Mob::ResetNoActionTime()
{
	((class ::Mob*)NativePtr)->resetNoActionTime();
}

void MC::Mob::SetJumpVelRedux(bool _0)
{
	((class ::Mob*)NativePtr)->setJumpVelRedux(_0);
}

void MC::Mob::SetJumping(bool _0)
{
	((class ::Mob*)NativePtr)->setJumping(_0);
}

void MC::Mob::SetNaturallySpawned(bool _0)
{
	((class ::Mob*)NativePtr)->setNaturallySpawned(_0);
}

void MC::Mob::SetSpeedModifier(float _0)
{
	((class ::Mob*)NativePtr)->setSpeedModifier(_0);
}

void MC::Mob::SetSurfaceMob(bool _0)
{
	((class ::Mob*)NativePtr)->setSurfaceMob(_0);
}

void MC::Mob::SetXxa(float _0)
{
	((class ::Mob*)NativePtr)->setXxa(_0);
}

void MC::Mob::SetYya(float _0)
{
	((class ::Mob*)NativePtr)->setYya(_0);
}

void MC::Mob::SnapToYBodyRot(float _0)
{
	((class ::Mob*)NativePtr)->snapToYBodyRot(_0);
}

void MC::Mob::SnapToYHeadRot(float _0)
{
	((class ::Mob*)NativePtr)->snapToYHeadRot(_0);
}

bool MC::Mob::IsRuntimePredictedMovementEnabled::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isRuntimePredictedMovementEnabled();
	return __ret;
}

float MC::Mob::YawSpeedInDegreesPerSecond::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getYawSpeedInDegreesPerSecond();
	return __ret;
}

float MC::Mob::CameraOffset::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getCameraOffset();
	return __ret;
}

bool MC::Mob::IsImmobile::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isImmobile();
	return __ret;
}

bool MC::Mob::IsPickable::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isPickable();
	return __ret;
}

bool MC::Mob::Sleeping::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isSleeping();
	return __ret;
}

void MC::Mob::Sleeping::set(bool _0)
{
	((class ::Mob*)NativePtr)->setSleeping(_0);
}

bool MC::Mob::IsBlocking::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isBlocking();
	return __ret;
}

bool MC::Mob::IsAlive::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isAlive();
	return __ret;
}

bool MC::Mob::SurfaceMob::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isSurfaceMob();
	return __ret;
}

MC::Actor^ MC::Mob::Target::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getTarget();
	if (__ret == nullptr) return nullptr;
	return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
}

void MC::Mob::Target::set(MC::Actor^ _0)
{
	auto __arg0 = (class ::Actor*)_0->NativePtr;
	((class ::Mob*)NativePtr)->setTarget(__arg0);
}

MC::Actor^ MC::Mob::FindAttackTarget::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->findAttackTarget();
	if (__ret == nullptr) return nullptr;
	return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
}

bool MC::Mob::Jumping::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isJumping();
	return __ret;
}

MC::ActorUniqueID^ MC::Mob::SourceUniqueID::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getSourceUniqueID();
	auto ____ret = new struct ::ActorUniqueID(__ret);
	return (____ret == nullptr) ? nullptr : gcnew ::MC::ActorUniqueID((struct ::ActorUniqueID*)____ret, true);
}

int MC::Mob::PortalWaitTime::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getPortalWaitTime();
	return __ret;
}

MC::ActorUniqueID^ MC::Mob::ControllingPlayer::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getControllingPlayer();
	auto ____ret = new struct ::ActorUniqueID(__ret);
	return (____ret == nullptr) ? nullptr : gcnew ::MC::ActorUniqueID((struct ::ActorUniqueID*)____ret, true);
}

bool MC::Mob::InCaravan::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->inCaravan();
	return __ret;
}

int MC::Mob::DeathTime::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getDeathTime();
	return __ret;
}

float MC::Mob::YHeadRot::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getYHeadRot();
	return __ret;
}

void MC::Mob::YHeadRot::set(float _0)
{
	((class ::Mob*)NativePtr)->setYHeadRot(_0);
}

float MC::Mob::YHeadRotO::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getYHeadRotO();
	return __ret;
}

bool MC::Mob::IsWorldBuilder::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isWorldBuilder();
	return __ret;
}

bool MC::Mob::IsCreative::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isCreative();
	return __ret;
}

bool MC::Mob::IsAdventure::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isAdventure();
	return __ret;
}

bool MC::Mob::IsSurvival::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isSurvival();
	return __ret;
}

bool MC::Mob::IsSpectator::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isSpectator();
	return __ret;
}

bool MC::Mob::Sprinting::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isSprinting();
	return __ret;
}

void MC::Mob::Sprinting::set(bool _0)
{
	((class ::Mob*)NativePtr)->setSprinting(_0);
}

float MC::Mob::Speed::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getSpeed();
	return __ret;
}

void MC::Mob::Speed::set(float _0)
{
	((class ::Mob*)NativePtr)->setSpeed(_0);
}

float MC::Mob::JumpPower::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getJumpPower();
	return __ret;
}

int MC::Mob::MeleeKnockbackBonus::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getMeleeKnockbackBonus();
	return __ret;
}

bool MC::Mob::IsLookingAtAnEntity::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isLookingAtAnEntity();
	return __ret;
}

int MC::Mob::ItemUseDuration::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getItemUseDuration();
	return __ret;
}

float MC::Mob::ItemUseStartupProgress::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getItemUseStartupProgress();
	return __ret;
}

float MC::Mob::ItemUseIntervalProgress::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getItemUseIntervalProgress();
	return __ret;
}

int MC::Mob::ItemUseIntervalAxis::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getItemUseIntervalAxis();
	return __ret;
}

int MC::Mob::TimeAlongSwing::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getTimeAlongSwing();
	return __ret;
}

float MC::Mob::MaxHeadXRot::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getMaxHeadXRot();
	return __ret;
}

bool MC::Mob::HasCaravanTail::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->hasCaravanTail();
	return __ret;
}

MC::ActorUniqueID^ MC::Mob::CaravanHead::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getCaravanHead();
	auto ____ret = new struct ::ActorUniqueID(__ret);
	return (____ret == nullptr) ? nullptr : gcnew ::MC::ActorUniqueID((struct ::ActorUniqueID*)____ret, true);
}

int MC::Mob::ArmorValue::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getArmorValue();
	return __ret;
}

float MC::Mob::ArmorCoverPercentage::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getArmorCoverPercentage();
	return __ret;
}

int MC::Mob::ToughnessValue::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getToughnessValue();
	return __ret;
}

int MC::Mob::ClearEquipment::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->clearEquipment();
	return __ret;
}

::System::Collections::Generic::List<int>^ MC::Mob::AllArmorID::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getAllArmorID();
	auto _tmp__ret = gcnew ::System::Collections::Generic::List<int>();
	auto __list0 = __ret;
	for (auto _element : __list0)
	{
		auto _marshalElement = _element;
		_tmp__ret->Add(_marshalElement);
	}
	return _tmp__ret;
}

int MC::Mob::ArmorTypeHash::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getArmorTypeHash();
	return __ret;
}

bool MC::Mob::TransitioningSitting::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isTransitioningSitting();
	return __ret;
}

void MC::Mob::TransitioningSitting::set(bool _0)
{
	((class ::Mob*)NativePtr)->setTransitioningSitting(_0);
}

int MC::Mob::AttackTime::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getAttackTime();
	return __ret;
}

bool MC::Mob::DiscardFriction::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->discardFriction();
	return __ret;
}

MC::BlockPos MC::Mob::BoundOrigin::get()
{
	return ((class ::Mob*)NativePtr)->getBoundOrigin();
}

int MC::Mob::CaravanSize::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getCaravanSize();
	return __ret;
}

int MC::Mob::EatCounter::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getEatCounter();
	return __ret;
}

void MC::Mob::EatCounter::set(int _0)
{
	((class ::Mob*)NativePtr)->setEatCounter(_0);
}

MC::Mob^ MC::Mob::FirstCaravanHead::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getFirstCaravanHead();
	if (__ret == nullptr) return nullptr;
	return (__ret == nullptr) ? nullptr : gcnew ::MC::Mob((class ::Mob*)__ret);
}

float MC::Mob::FlightSpeed::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getFlightSpeed();
	return __ret;
}

void MC::Mob::FlightSpeed::set(float _0)
{
	((class ::Mob*)NativePtr)->setFlightSpeed(_0);
}

float MC::Mob::FrictionModifier::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getFrictionModifier();
	return __ret;
}

void MC::Mob::FrictionModifier::set(float _0)
{
	((class ::Mob*)NativePtr)->setFrictionModifier(_0);
}

int MC::Mob::GlidingTicks::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getGlidingTicks();
	return __ret;
}

float MC::Mob::JumpEffectAmplifierValue::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getJumpEffectAmplifierValue();
	return __ret;
}

float MC::Mob::JumpMultiplier::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getJumpMultiplier();
	return __ret;
}

//MC::Mob::JumpPreventionResult^ MC::Mob::JumpPrevention::get()
//{
//    auto __ret = ((class ::Mob*)NativePtr)->getJumpPrevention();
//    auto ____ret = new struct ::Mob::JumpPreventionResult(__ret);
//    return (____ret == nullptr) ? nullptr : gcnew ::MC::Mob::JumpPreventionResult((struct ::Mob::JumpPreventionResult*)____ret, true);
//}

float MC::Mob::MovementComponentCurrentSpeed::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getMovementComponentCurrentSpeed();
	return __ret;
}

void MC::Mob::MovementComponentCurrentSpeed::set(float _0)
{
	((class ::Mob*)NativePtr)->setMovementComponentCurrentSpeed(_0);
}

int MC::Mob::NoActionTime::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getNoActionTime();
	return __ret;
}

float MC::Mob::PassengerLockedBodyRot::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getPassengerLockedBodyRot();
	return __ret;
}

void MC::Mob::PassengerLockedBodyRot::set(float _0)
{
	((class ::Mob*)NativePtr)->setPassengerLockedBodyRot(_0);
}

float MC::Mob::PassengerRotLimit::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getPassengerRotLimit();
	return __ret;
}

void MC::Mob::PassengerRotLimit::set(float _0)
{
	((class ::Mob*)NativePtr)->setPassengerRotLimit(_0);
}

int MC::Mob::RollCounter::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getRollCounter();
	return __ret;
}

float MC::Mob::SwimSpeedMultiplier::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getSwimSpeedMultiplier();
	return __ret;
}

void MC::Mob::SwimSpeedMultiplier::set(float _0)
{
	((class ::Mob*)NativePtr)->setSwimSpeedMultiplier(_0);
}

MC::ActorUniqueID^ MC::Mob::TargetCaptain::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getTargetCaptain();
	auto ____ret = new struct ::ActorUniqueID(__ret);
	return (____ret == nullptr) ? nullptr : gcnew ::MC::ActorUniqueID((struct ::ActorUniqueID*)____ret, true);
}

void MC::Mob::TargetCaptain::set(MC::ActorUniqueID^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is passed by value.");
	auto __arg0 = *(struct ::ActorUniqueID*)_0->NativePtr;
	((class ::Mob*)NativePtr)->setTargetCaptain(__arg0);
}

float MC::Mob::YRotA::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getYRotA();
	return __ret;
}

void MC::Mob::YRotA::set(float _0)
{
	((class ::Mob*)NativePtr)->setYRotA(_0);
}

float MC::Mob::Zza::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->getZza();
	return __ret;
}

void MC::Mob::Zza::set(float _0)
{
	((class ::Mob*)NativePtr)->setZza(_0);
}

bool MC::Mob::HasBoundOrigin::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->hasBoundOrigin();
	return __ret;
}

bool MC::Mob::IsAbleToMove::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isAbleToMove();
	return __ret;
}

bool MC::Mob::Eating::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isEating();
	return __ret;
}

void MC::Mob::Eating::set(bool _0)
{
	((class ::Mob*)NativePtr)->setEating(_0);
}

bool MC::Mob::IsFrostWalking::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isFrostWalking();
	return __ret;
}

bool MC::Mob::IsGliding::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isGliding();
	return __ret;
}

bool MC::Mob::IsLayingEgg::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isLayingEgg();
	return __ret;
}

void MC::Mob::IsLayingEgg::set(bool _0)
{
	((class ::Mob*)NativePtr)->setIsLayingEgg(_0);
}

bool MC::Mob::IsPregnant::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isPregnant();
	return __ret;
}

void MC::Mob::IsPregnant::set(bool _0)
{
	((class ::Mob*)NativePtr)->setIsPregnant(_0);
}

bool MC::Mob::Rolling::get()
{
	auto __ret = ((class ::Mob*)NativePtr)->isRolling();
	return __ret;
}

void MC::Mob::Rolling::set(bool _0)
{
	((class ::Mob*)NativePtr)->setRolling(_0);
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
