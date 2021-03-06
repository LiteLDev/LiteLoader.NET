#include "../../Header/MC/Actor.hpp"

#include "../../Header/MC/BlockSource.hpp"
#include "../../Header/MC/Tick.hpp"
#include "../../Header/MC/BlockInstance.hpp"
#include "../../Header/MC/UserEntityIdentifierComponent.hpp"
#include "../../Header/MC/MobEffect.hpp"
#include "../../Header/MC/Vec2.hpp"
#include "../../Header/MC/Vec3.hpp"
#include "../../Header/MC/ItemStack.hpp"
#include "../../Header/MC/CompoundTag.hpp"
#include "../../Header/MC/MobEffectInstance.hpp"
#include "../../Header/MC/AABB.hpp"
#include "../../Header/MC/Level.hpp"
#include "../../Header/MC/Player.hpp"

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
	return ((class ::Actor*)NativePtr)->teleport(to, dimID, x, y);
}

void MC::Actor::OutOfWorld()
{
	((class ::Actor*)NativePtr)->outOfWorld();
}

void MC::Actor::DoInitialMove()
{
	((class ::Actor*)NativePtr)->_doInitialMove();
}

void MC::Actor::ResetUserPos(bool _0)
{
	((class ::Actor*)NativePtr)->resetUserPos(_0);
}

float MC::Actor::GetInterpolatedBodyRot(float _0)
{
	auto __ret = ((class ::Actor*)NativePtr)->getInterpolatedBodyRot(_0);
	return __ret;
}

float MC::Actor::GetInterpolatedHeadRot(float _0)
{
	auto __ret = ((class ::Actor*)NativePtr)->getInterpolatedHeadRot(_0);
	return __ret;
}

float MC::Actor::GetInterpolatedBodyYaw(float _0)
{
	auto __ret = ((class ::Actor*)NativePtr)->getInterpolatedBodyYaw(_0);
	return __ret;
}

//void MC::Actor::UnkVfn40()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_40();
//}

void MC::Actor::TeleportTo(MC::Vec3 _0, bool _1, int _2, int _3, bool _4)
{
	((class ::Actor*)NativePtr)->teleportTo(_0, _1, _2, _3, _4);
}

void MC::Actor::NormalTick()
{
	((class ::Actor*)NativePtr)->normalTick();
}

void MC::Actor::BaseTick()
{
	((class ::Actor*)NativePtr)->baseTick();
}

//void MC::Actor::VehicleTick()
//{
//	((class ::Actor*)NativePtr)->vehicleTick();
//}

bool MC::Actor::StartRiding(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->startRiding(__arg0);
	return __ret;
}

void MC::Actor::AddPassenger(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	((class ::Actor*)NativePtr)->addPassenger(__arg0);
}

//void MC::Actor::UnkVfn61()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_61();
//}
//
//void MC::Actor::UnkVfn68()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_68();
//}
//
//void MC::Actor::UnkVfn82()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_82();
//}

bool MC::Actor::CanInteractWithOtherEntitiesInGame()
{
	auto __ret = ((class ::Actor*)NativePtr)->canInteractWithOtherEntitiesInGame();
	return __ret;
}

//void MC::Actor::UnkVfn88()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_88();
//}

void MC::Actor::PlayerTouch(MC::Player^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Player*)_0->NativePtr;
	((class ::Actor*)NativePtr)->playerTouch(__arg0);
}

//void MC::Actor::UnkVfn95()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_95();
//}
//
//void MC::Actor::UnkVfn98()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_98();
//}
//
//void MC::Actor::UnkVfn105()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_105();
//}
//
//void MC::Actor::UnkVfn107()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_107();
//}
//
//void MC::Actor::UnkVfn108()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_108();
//}
//
//void MC::Actor::UnkVfn109()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_109();
//}

bool MC::Actor::IsValidTarget(MC::Actor^ _0)
{
	auto __arg0 = (class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->isValidTarget(__arg0);
	return __ret;
}

bool MC::Actor::Attack(MC::Actor^ _0, MC::ActorDamageCause _1)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto __arg0 = _0->NativePtr;
	auto __arg1 = (::ActorDamageCause)_1;
	auto __ret = ((class ::Actor*)NativePtr)->attack(*__arg0, __arg1);
	return __ret;
}

void MC::Actor::OnTame()
{
	((class ::Actor*)NativePtr)->onTame();
}

void MC::Actor::OnFailedTame()
{
	((class ::Actor*)NativePtr)->onFailedTame();
}

void MC::Actor::VehicleLanded(MC::Vec3 _0, MC::Vec3 _1)
{
	((class ::Actor*)NativePtr)->vehicleLanded(_0, _1);
}

void MC::Actor::AnimateHurt()
{
	((class ::Actor*)NativePtr)->animateHurt();
}

bool MC::Actor::DoFireHurt(int _0)
{
	auto __ret = ((class ::Actor*)NativePtr)->doFireHurt(_0);
	return __ret;
}

void MC::Actor::AwardKillScore(MC::Actor^ _0, int _1)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	((class ::Actor*)NativePtr)->awardKillScore(__arg0, _1);
}

bool MC::Actor::CanFreeze()
{
	auto __ret = ((class ::Actor*)NativePtr)->canFreeze();
	return __ret;
}

bool MC::Actor::CanChangeDimensions()
{
	auto __ret = ((class ::Actor*)NativePtr)->canChangeDimensions();
	return __ret;
}

//void MC::Actor::UnkVfn181()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_181();
//}

bool MC::Actor::CanBePulledIntoVehicle()
{
	auto __ret = ((class ::Actor*)NativePtr)->canBePulledIntoVehicle();
	return __ret;
}

//void MC::Actor::UnkVfn195()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_195();
//}

bool MC::Actor::CanSynchronizeNewEntity()
{
	auto __ret = ((class ::Actor*)NativePtr)->canSynchronizeNewEntity();
	return __ret;
}

void MC::Actor::StopRiding(bool _0, bool _1, bool _2)
{
	((class ::Actor*)NativePtr)->stopRiding(_0, _1, _2);
}

void MC::Actor::BuildDebugInfo(::System::String^ _0)
{
	auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
	((class ::Actor*)NativePtr)->buildDebugInfo(__arg0);
}

void MC::Actor::Swing()
{
	((class ::Actor*)NativePtr)->swing();
}

//void MC::Actor::UnkVfn220()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_220();
//}
//
//void MC::Actor::UnkVfn221()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_221();
//}

void MC::Actor::SetAuxValue(int _0)
{
	((class ::Actor*)NativePtr)->setAuxValue(_0);
}

void MC::Actor::StopSpinAttack()
{
	((class ::Actor*)NativePtr)->stopSpinAttack();
}

//void MC::Actor::UnkVfn246()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_246();
//}
//
//void MC::Actor::UnkVfn249()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_249();
//}

void MC::Actor::Kill()
{
	((class ::Actor*)NativePtr)->kill();
}

bool MC::Actor::ShouldDropDeathLoot()
{
	auto __ret = ((class ::Actor*)NativePtr)->shouldDropDeathLoot();
	return __ret;
}

//void MC::Actor::UnkVfn261()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_261();
//}

void MC::Actor::AddAdditionalSaveData(MC::CompoundTag^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::CompoundTag*)_0->NativePtr;
	((class ::Actor*)NativePtr)->addAdditionalSaveData(__arg0);
}

//void MC::Actor::UnkVfn269()
//{
//    ((class ::Actor*)NativePtr)->__unk_vfn_269();
//}

void MC::Actor::RemovePassenger(MC::ActorUniqueID _0, bool _1, bool _2, bool _3)
{
	((class ::Actor*)NativePtr)->_removePassenger(_0, _1, _2, _3);
}

void MC::Actor::OnSizeUpdated()
{
	((class ::Actor*)NativePtr)->_onSizeUpdated();
}

void MC::Actor::SetLastHurtMob(MC::Actor^ _0)
{
	auto __arg0 = (class ::Actor*)_0->NativePtr;
	((class ::Actor*)NativePtr)->setLastHurtMob(__arg0);
}

void MC::Actor::ServerInitItemStackIds()
{
	((class ::Actor*)NativePtr)->_serverInitItemStackIds();
}

void MC::Actor::Reset()
{
	((class ::Actor*)NativePtr)->reset();
}

void MC::Actor::Remove()
{
	((class ::Actor*)NativePtr)->remove();
}

MC::Vec3 MC::Actor::GetPosExtrapolated(float _0)
{
	return NativePtr->getPosExtrapolated(_0);
}

void MC::Actor::SetRot(MC::Vec2% _0)
{
	pin_ptr<Vec2> p = &_0;
	((class ::Actor*)NativePtr)->setRot(*(::Vec2*)p);
}

void MC::Actor::Move(MC::Vec3 _0)
{
	((class ::Actor*)NativePtr)->move(_0);
}

MC::Vec3 MC::Actor::GetInterpolatedRidingPosition(float _0)
{
	return ((class ::Actor*)NativePtr)->getInterpolatedRidingPosition(_0);
}

float MC::Actor::GetInterpolatedWalkAnimSpeed(float _0)
{
	return ((class ::Actor*)NativePtr)->getInterpolatedWalkAnimSpeed(_0);
}

MC::Vec3 MC::Actor::GetInterpolatedRidingOffset(float _0)
{
	return ((class ::Actor*)NativePtr)->getInterpolatedRidingOffset(_0);
}

void MC::Actor::UpdateEntityInside()
{
	((class ::Actor*)NativePtr)->updateEntityInside();
}

void MC::Actor::UpdateEntityInside(MC::AABB _0)
{
	((class ::Actor*)NativePtr)->updateEntityInside(_0);
}

bool MC::Actor::CanDisableShield()
{
	auto __ret = ((class ::Actor*)NativePtr)->canDisableShield();
	return __ret;
}

bool MC::Actor::TryTeleportTo(MC::Vec3 _0, bool _1, bool _2, int _3, int _4)
{
	return ((class ::Actor*)NativePtr)->tryTeleportTo(_0, _1, _2, _3, _4);
}

void MC::Actor::ChorusFruitTeleport(MC::Vec3 _0)
{
	((class ::Actor*)NativePtr)->chorusFruitTeleport(_0);
}

void MC::Actor::LerpMotion(MC::Vec3 _0)
{
	((class ::Actor*)NativePtr)->lerpMotion(_0);
}

void MC::Actor::PositionPassenger(MC::Actor^ _0, float _1)
{
	((class ::Actor*)NativePtr)->positionPassenger(_0, _1);
}

void MC::Actor::FlagPassengerToRemove(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	((class ::Actor*)NativePtr)->flagPassengerToRemove(__arg0);
}

bool MC::Actor::Intersects(MC::Vec3 _0, MC::Vec3 _1)
{
	return ((class ::Actor*)NativePtr)->intersects(_0, _1);
}

bool MC::Actor::CanShowNameTag()
{
	auto __ret = ((class ::Actor*)NativePtr)->canShowNameTag();
	return __ret;
}

void MC::Actor::SetNameTagVisible(bool _0)
{
	((class ::Actor*)NativePtr)->setNameTagVisible(_0);
}

void MC::Actor::ResetBlockMovementSlowdownMultiplier()
{
	((class ::Actor*)NativePtr)->resetBlockMovementSlowdownMultiplier();
}

MC::Vec3 MC::Actor::GetHeadLookVector(float _0)
{
	return ((class ::Actor*)NativePtr)->getHeadLookVector(_0);
}

bool MC::Actor::CanSee(MC::Vec3 _0)
{
	return ((class ::Actor*)NativePtr)->canSee(_0);
}

bool MC::Actor::CanSee(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->canSee(__arg0);
	return __ret;
}

bool MC::Actor::IsSkyLit(float _0)
{
	auto __ret = ((class ::Actor*)NativePtr)->isSkyLit(_0);
	return __ret;
}

float MC::Actor::GetBrightness(float _0)
{
	auto __ret = ((class ::Actor*)NativePtr)->getBrightness(_0);
	return __ret;
}

void MC::Actor::OnAboveBubbleColumn(bool _0)
{
	((class ::Actor*)NativePtr)->onAboveBubbleColumn(_0);
}

void MC::Actor::OnInsideBubbleColumn(bool _0)
{
	((class ::Actor*)NativePtr)->onInsideBubbleColumn(_0);
}

bool MC::Actor::CanAttack(MC::Actor^ _0, bool _1)
{
	auto __arg0 = (class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->canAttack(__arg0, _1);
	return __ret;
}

void MC::Actor::PerformRangedAttack(MC::Actor^ _0, float _1)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	((class ::Actor*)NativePtr)->performRangedAttack(__arg0, _1);
}

void MC::Actor::SetOwner(MC::ActorUniqueID _0)
{
	((class ::Actor*)NativePtr)->setOwner(_0);
}

bool MC::Actor::ShouldRender()
{
	auto __ret = ((class ::Actor*)NativePtr)->shouldRender();
	return __ret;
}

void MC::Actor::PlayAmbientSound()
{
	((class ::Actor*)NativePtr)->playAmbientSound();
}

void MC::Actor::OnLightningHit()
{
	((class ::Actor*)NativePtr)->onLightningHit();
}

void MC::Actor::Feed(int _0)
{
	((class ::Actor*)NativePtr)->feed(_0);
}

void MC::Actor::Despawn()
{
	((class ::Actor*)NativePtr)->despawn();
}

void MC::Actor::Killed(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	((class ::Actor*)NativePtr)->killed(__arg0);
}

bool MC::Actor::ConsumeTotem()
{
	auto __ret = ((class ::Actor*)NativePtr)->consumeTotem();
	return __ret;
}

bool MC::Actor::Save(MC::CompoundTag^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::CompoundTag*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->save(__arg0);
	return __ret;
}

void MC::Actor::SaveWithoutId(MC::CompoundTag^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::CompoundTag*)_0->NativePtr;
	((class ::Actor*)NativePtr)->saveWithoutId(__arg0);
}

void MC::Actor::ThawFreezeEffect()
{
	((class ::Actor*)NativePtr)->thawFreezeEffect();
}

void MC::Actor::HandleInsidePortal(MC::BlockPos _0)
{
	((class ::Actor*)NativePtr)->handleInsidePortal(_0);
}

void MC::Actor::CheckFallDamage(float _0, bool _1)
{
	((class ::Actor*)NativePtr)->checkFallDamage(_0, _1);
}

void MC::Actor::HandleFallDistanceOnServer(float _0, float _1, bool _2)
{
	((class ::Actor*)NativePtr)->handleFallDistanceOnServer(_0, _1, _2);
}

void MC::Actor::OnSynchedFlagUpdate(int _0, long long _1, long long _2)
{
	((class ::Actor*)NativePtr)->onSynchedFlagUpdate(_0, _1, _2);
}

void MC::Actor::OnSynchedDataUpdate(int _0)
{
	((class ::Actor*)NativePtr)->onSynchedDataUpdate(_0);
}

bool MC::Actor::CanAddPassenger(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->canAddPassenger(__arg0);
	return __ret;
}

void MC::Actor::TickLeash()
{
	((class ::Actor*)NativePtr)->tickLeash();
}

void MC::Actor::SendMotionPacketIfNeeded()
{
	((class ::Actor*)NativePtr)->sendMotionPacketIfNeeded();
}

void MC::Actor::StartSwimming()
{
	((class ::Actor*)NativePtr)->startSwimming();
}

void MC::Actor::StopSwimming()
{
	((class ::Actor*)NativePtr)->stopSwimming();
}

void MC::Actor::Heal(int _0)
{
	((class ::Actor*)NativePtr)->heal(_0);
}

bool MC::Actor::CanBeAffected(MC::MobEffectInstance^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::MobEffectInstance*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->canBeAffected(__arg0);
	return __ret;
}

bool MC::Actor::CanBeAffected(int _0)
{
	auto __ret = ((class ::Actor*)NativePtr)->canBeAffected(_0);
	return __ret;
}

bool MC::Actor::CanBeAffectedByArrow(MC::MobEffectInstance^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::MobEffectInstance*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->canBeAffectedByArrow(__arg0);
	return __ret;
}

void MC::Actor::OnEffectAdded(MC::MobEffectInstance^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::MobEffectInstance*)_0->NativePtr;
	((class ::Actor*)NativePtr)->onEffectAdded(__arg0);
}

void MC::Actor::OnEffectUpdated(MC::MobEffectInstance^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::MobEffectInstance*)_0->NativePtr;
	((class ::Actor*)NativePtr)->onEffectUpdated(__arg0);
}

void MC::Actor::OnEffectRemoved(MC::MobEffectInstance^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::MobEffectInstance*)_0->NativePtr;
	((class ::Actor*)NativePtr)->onEffectRemoved(__arg0);
}

void MC::Actor::OpenContainerComponent(MC::Player^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Player*)_0->NativePtr;
	((class ::Actor*)NativePtr)->openContainerComponent(__arg0);
}

void MC::Actor::GetDebugText(::System::Collections::Generic::List<::System::String^>^ _0)
{
	auto _tmp_0 = std::vector<::std::string>();
	for each (::System::String ^ _element in _0)
	{
		auto _marshalElement = clix::marshalString<clix::E_UTF8>(_element);
		_tmp_0.push_back(_marshalElement);
	}
	auto __arg0 = _tmp_0;
	((class ::Actor*)NativePtr)->getDebugText(__arg0);
}

float MC::Actor::GetPassengerYRotation(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->getPassengerYRotation(__arg0);
	return __ret;
}

void MC::Actor::SetSize(float _0, float _1)
{
	((class ::Actor*)NativePtr)->setSize(_0, _1);
}

void MC::Actor::OnOrphan()
{
	((class ::Actor*)NativePtr)->onOrphan();
}

void MC::Actor::Wobble()
{
	((class ::Actor*)NativePtr)->wobble();
}

bool MC::Actor::WasHurt()
{
	auto __ret = ((class ::Actor*)NativePtr)->wasHurt();
	return __ret;
}

void MC::Actor::StartSpinAttack()
{
	((class ::Actor*)NativePtr)->startSpinAttack();
}

void MC::Actor::ReloadLootTable()
{
	((class ::Actor*)NativePtr)->reloadLootTable();
}

bool MC::Actor::ShouldTick()
{
	auto __ret = ((class ::Actor*)NativePtr)->shouldTick();
	return __ret;
}

float MC::Actor::GetNextStep(float _0)
{
	auto __ret = ((class ::Actor*)NativePtr)->getNextStep(_0);
	return __ret;
}

void MC::Actor::InterpolatorTick()
{
	((class ::Actor*)NativePtr)->interpolatorTick();
}

bool MC::Actor::ShouldTryMakeStepSound()
{
	auto __ret = ((class ::Actor*)NativePtr)->shouldTryMakeStepSound();
	return __ret;
}

void MC::Actor::MarkHurt()
{
	((class ::Actor*)NativePtr)->markHurt();
}

void MC::Actor::CheckInsideBlocks(float _0)
{
	((class ::Actor*)NativePtr)->checkInsideBlocks(_0);
}

void MC::Actor::PushOutOfBlocks(MC::Vec3 _0)
{
	((class ::Actor*)NativePtr)->pushOutOfBlocks(_0);
}

void MC::Actor::DoWaterSplashEffect()
{
	((class ::Actor*)NativePtr)->doWaterSplashEffect();
}

void MC::Actor::SpawnTrailBubbles()
{
	((class ::Actor*)NativePtr)->spawnTrailBubbles();
}

void MC::Actor::UpdateInsideBlock()
{
	((class ::Actor*)NativePtr)->updateInsideBlock();
}

bool MC::Actor::SetNbt(MC::CompoundTag^ nbt)
{
	auto __arg0 = (class ::CompoundTag*)nbt->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->setNbt(__arg0);
	return __ret;
}

void MC::Actor::SendDirtyActorData()
{
	((class ::Actor*)NativePtr)->_sendDirtyActorData();
}

void MC::Actor::AddDefinitionGroup(::System::String^ _0)
{
	auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
	((class ::Actor*)NativePtr)->addDefinitionGroup(__arg0);
}

void MC::Actor::AddEffect(MC::MobEffectInstance^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::MobEffectInstance*)_0->NativePtr;
	((class ::Actor*)NativePtr)->addEffect(__arg0);
}

bool MC::Actor::AddTag(::System::String^ _0)
{
	auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
	auto __ret = ((class ::Actor*)NativePtr)->addTag(__arg0);
	return __ret;
}

void MC::Actor::BuildDebugGroupInfo(::System::String^ _0)
{
	auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
	((class ::Actor*)NativePtr)->buildDebugGroupInfo(__arg0);
}

MC::Vec3 MC::Actor::BuildForward()
{
	return ((class ::Actor*)NativePtr)->buildForward();
}

void MC::Actor::Burn(int _0, bool _1)
{
	((class ::Actor*)NativePtr)->burn(_0, _1);
}

void MC::Actor::CacheComponentData()
{
	((class ::Actor*)NativePtr)->cacheComponentData();
}

float MC::Actor::CalculateAttackDamage(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->calculateAttackDamage(__arg0);
	return __ret;
}

bool MC::Actor::CanAscendCurrentBlockByJumping()
{
	auto __ret = ((class ::Actor*)NativePtr)->canAscendCurrentBlockByJumping();
	return __ret;
}

bool MC::Actor::CanBeginOrContinueClimbingLadder()
{
	auto __ret = ((class ::Actor*)NativePtr)->canBeginOrContinueClimbingLadder();
	return __ret;
}

bool MC::Actor::CanCurrentlySwim()
{
	auto __ret = ((class ::Actor*)NativePtr)->canCurrentlySwim();
	return __ret;
}

bool MC::Actor::CanDescendBlockBelowByCrouching()
{
	auto __ret = ((class ::Actor*)NativePtr)->canDescendBlockBelowByCrouching();
	return __ret;
}

bool MC::Actor::CanMate(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->canMate(__arg0);
	return __ret;
}

bool MC::Actor::CanSeeDaylight()
{
	auto __ret = ((class ::Actor*)NativePtr)->canSeeDaylight();
	return __ret;
}

void MC::Actor::CelebrateHunt(int _0, bool _1)
{
	((class ::Actor*)NativePtr)->celebrateHunt(_0, _1);
}

//void MC::Actor::CheckForPropertyUpdate()
//{
//	((class ::Actor*)NativePtr)->checkForPropertyUpdate();
//}

void MC::Actor::ClearFishingHookID()
{
	((class ::Actor*)NativePtr)->clearFishingHookID();
}

bool MC::Actor::CloserThan(MC::Actor^ _0, float _1)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->closerThan(__arg0, _1);
	return __ret;
}

void MC::Actor::DeregisterTagsFromLevelCache()
{
	((class ::Actor*)NativePtr)->deregisterTagsFromLevelCache();
}

float MC::Actor::DistanceSqrToBlockPosCenter(MC::BlockPos _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto __ret = ((class ::Actor*)NativePtr)->distanceSqrToBlockPosCenter(_0);
	return __ret;
}

float MC::Actor::DistanceTo(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->distanceTo(__arg0);
	return __ret;
}

float MC::Actor::DistanceTo(MC::Vec3 _0)
{
	return ((class ::Actor*)NativePtr)->distanceTo(_0);
}

float MC::Actor::DistanceToSqr(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->distanceToSqr(__arg0);
	return __ret;
}

float MC::Actor::DistanceToSqr(MC::Vec3 _0)
{
	return ((class ::Actor*)NativePtr)->distanceToSqr(_0);
}

void MC::Actor::DropLeash(bool _0, bool _1)
{
	((class ::Actor*)NativePtr)->dropLeash(_0, _1);
}

MC::BlockPos MC::Actor::GetBlockPosCurrentlyStandingOn(MC::Actor^ _0)
{
	auto __arg0 = (class ::Actor*)_0->NativePtr;
	return ((class ::Actor*)NativePtr)->getBlockPosCurrentlyStandingOn(__arg0);
}

MC::MobEffectInstance^ MC::Actor::GetEffect(MC::MobEffect^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::MobEffect*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->getEffect(__arg0);
	if (__ret == nullptr) return nullptr;
	return (__ret == nullptr) ? nullptr : gcnew ::MC::MobEffectInstance((class ::MobEffectInstance*)__ret);
}

bool MC::Actor::GetFirstAvailableSeatPos(MC::Actor^ _0, MC::Vec3 _1)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	return ((class ::Actor*)NativePtr)->getFirstAvailableSeatPos(__arg0, ::Vec3(_1));
}

MC::Vec3 MC::Actor::GetInterpolatedPosition(float _0)
{
	return ((class ::Actor*)NativePtr)->getInterpolatedPosition(_0);
}

MC::Vec2 MC::Actor::GetInterpolatedRotation(float _0)
{
	return ((class ::Actor*)NativePtr)->getInterpolatedRotation(_0);
}

int MC::Actor::GetPassengerIndex(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->getPassengerIndex(__arg0);
	return __ret;
}

float MC::Actor::GetSwimAmount(float _0)
{
	auto __ret = ((class ::Actor*)NativePtr)->getSwimAmount(_0);
	return __ret;
}

MC::Vec3 MC::Actor::GetViewVector(float _0)
{
	return ((class ::Actor*)NativePtr)->getViewVector(_0);
}

bool MC::Actor::HasBeenHurtByMobInLastTicks(int _0)
{
	auto __ret = ((class ::Actor*)NativePtr)->hasBeenHurtByMobInLastTicks(_0);
	return __ret;
}

bool MC::Actor::HasDefinitionGroup(::System::String^ _0)
{
	auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
	auto __ret = ((class ::Actor*)NativePtr)->hasDefinitionGroup(__arg0);
	return __ret;
}

bool MC::Actor::HasEffect(MC::MobEffect^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::MobEffect*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->hasEffect(__arg0);
	return __ret;
}

void MC::Actor::HealEffects(int _0)
{
	((class ::Actor*)NativePtr)->healEffects(_0);
}

void MC::Actor::InitActorProperties()
{
	((class ::Actor*)NativePtr)->initActorProperties();
}

bool MC::Actor::IsInsideBorderBlock(float _0)
{
	auto __ret = ((class ::Actor*)NativePtr)->isInsideBorderBlock(_0);
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
	auto __ret = ((class ::Actor*)NativePtr)->isPassenger(__arg0);
	return __ret;
}

bool MC::Actor::IsRiding(MC::Actor^ _0)
{
	auto __arg0 = (class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->isRiding(__arg0);
	return __ret;
}

bool MC::Actor::IsRiding()
{
	auto __ret = ((class ::Actor*)NativePtr)->isRiding();
	return __ret;
}

void MC::Actor::LerpTo(MC::Vec3 _0, MC::Vec2 _1, int _2)
{
	((class ::Actor*)NativePtr)->lerpTo(_0, _1, _2);
}

void MC::Actor::LerpTo(MC::Vec3 _0, MC::Vec2 _1, float _2, int _3)
{
	((class ::Actor*)NativePtr)->lerpTo(_0, _1, _2, _3);
}

void MC::Actor::LerpToRotation(MC::Vec2 _0, int _1)
{
	((class ::Actor*)NativePtr)->lerpToRotation(_0, _1);
}

void MC::Actor::MigrateUniqueID(MC::ActorUniqueID _0)
{
	((class ::Actor*)NativePtr)->migrateUniqueID(_0);
}

void MC::Actor::MoveBBs(MC::Vec3 _0)
{
	((class ::Actor*)NativePtr)->moveBBs(_0);
}

void MC::Actor::MoveRelative(float _0, float _1, float _2, float _3)
{
	((class ::Actor*)NativePtr)->moveRelative(_0, _1, _2, _3);
}

void MC::Actor::MoveTo(MC::Vec3 _0, MC::Vec2 _1)
{
	((class ::Actor*)NativePtr)->moveTo(_0, _1);
}

void MC::Actor::OnAffectedByWaterBottle()
{
	((class ::Actor*)NativePtr)->onAffectedByWaterBottle();
}

bool MC::Actor::OnClimbableBlock()
{
	auto __ret = ((class ::Actor*)NativePtr)->onClimbableBlock();
	return __ret;
}

bool MC::Actor::OnHoverableBlock()
{
	auto __ret = ((class ::Actor*)NativePtr)->onHoverableBlock();
	return __ret;
}

void MC::Actor::OnOnewayCollision(MC::AABB _0)
{
	((class ::Actor*)NativePtr)->onOnewayCollision(_0);
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
	((class ::Actor*)NativePtr)->positionAllPassengers(a1);
}

bool MC::Actor::PullInEntity(MC::Actor^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::Actor*)_0->NativePtr;
	auto __ret = ((class ::Actor*)NativePtr)->pullInEntity(__arg0);
	return __ret;
}

void MC::Actor::RefreshComponents()
{
	((class ::Actor*)NativePtr)->refreshComponents();
}

void MC::Actor::Reload()
{
	((class ::Actor*)NativePtr)->reload();
}

void MC::Actor::RemoveAllEffects()
{
	((class ::Actor*)NativePtr)->removeAllEffects();
}

void MC::Actor::RemoveAllPassengers(bool _0, bool _1)
{
	((class ::Actor*)NativePtr)->removeAllPassengers(_0, _1);
}

void MC::Actor::RemoveDefinitionGroup(::System::String^ _0)
{
	auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
	((class ::Actor*)NativePtr)->removeDefinitionGroup(__arg0);
}

void MC::Actor::RemoveEffect(int _0)
{
	((class ::Actor*)NativePtr)->removeEffect(_0);
}

void MC::Actor::RemoveEffectParticles()
{
	((class ::Actor*)NativePtr)->removeEffectParticles();
}

void MC::Actor::RemovePersistingTrade()
{
	((class ::Actor*)NativePtr)->removePersistingTrade();
}

bool MC::Actor::RemoveTag(::System::String^ _0)
{
	auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
	auto __ret = ((class ::Actor*)NativePtr)->removeTag(__arg0);
	return __ret;
}

void MC::Actor::ResetClientAnimations()
{
	((class ::Actor*)NativePtr)->resetClientAnimations();
}

void MC::Actor::ResetRegion()
{
	((class ::Actor*)NativePtr)->resetRegion();
}

void MC::Actor::SaveEntityFlags(MC::CompoundTag^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	auto& __arg0 = *(class ::CompoundTag*)_0->NativePtr;
	((class ::Actor*)NativePtr)->saveEntityFlags(__arg0);
}

void MC::Actor::SendActorDefinitionEventTriggered(::System::String^ _0)
{
	auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
	((class ::Actor*)NativePtr)->sendActorDefinitionEventTriggered(__arg0);
}

void MC::Actor::SendMotionToServer()
{
	((class ::Actor*)NativePtr)->sendMotionToServer();
}

void MC::Actor::SerializationSetHealth(int _0)
{
	((class ::Actor*)NativePtr)->serializationSetHealth(_0);
}

void MC::Actor::SetCanClimb(bool _0)
{
	((class ::Actor*)NativePtr)->setCanClimb(_0);
}

void MC::Actor::SetCollidableMob(bool _0)
{
	((class ::Actor*)NativePtr)->setCollidableMob(_0);
}

void MC::Actor::SetDancing(bool _0)
{
	((class ::Actor*)NativePtr)->setDancing(_0);
}

void MC::Actor::SetFishingHookID(MC::ActorUniqueID _0)
{
	((class ::Actor*)NativePtr)->setFishingHookID(_0);
}

void MC::Actor::SetInLove(MC::Actor^ _0)
{
	auto __arg0 = (class ::Actor*)_0->NativePtr;
	((class ::Actor*)NativePtr)->setInLove(__arg0);
}

void MC::Actor::SetInterpolation(bool _0)
{
	((class ::Actor*)NativePtr)->setInterpolation(_0);
}

void MC::Actor::SetLastHitBB(MC::Vec3 _0, MC::Vec3 _1)
{
	((class ::Actor*)NativePtr)->setLastHitBB(_0, _1);
}

void MC::Actor::SetPersistent()
{
	((class ::Actor*)NativePtr)->setPersistent();
}

void MC::Actor::SetPosDirectLegacy(MC::Vec3 _0)
{
	((class ::Actor*)NativePtr)->setPosDirectLegacy(_0);
}

void MC::Actor::SetPreviousPosRot(MC::Vec3 _0, MC::Vec2 _1)
{
	((class ::Actor*)NativePtr)->setPreviousPosRot(_0, _1);
}

void MC::Actor::SetSaddle(bool _0)
{
	((class ::Actor*)NativePtr)->setSaddle(_0);
}

void MC::Actor::SetScared(bool _0)
{
	((class ::Actor*)NativePtr)->setScared(_0);
}

void MC::Actor::SetStunned(bool _0)
{
	((class ::Actor*)NativePtr)->setStunned(_0);
}

void MC::Actor::SetTempted(bool _0)
{
	((class ::Actor*)NativePtr)->setTempted(_0);
}

void MC::Actor::SetVelocity(MC::Vec3 _0)
{
	((class ::Actor*)NativePtr)->setVelocity(_0);
}

bool MC::Actor::ShouldUpdateEffects()
{
	auto __ret = ((class ::Actor*)NativePtr)->shouldUpdateEffects();
	return __ret;
}

void MC::Actor::SpawnBalloonPopParticles()
{
	((class ::Actor*)NativePtr)->spawnBalloonPopParticles();
}

void MC::Actor::SpawnDeathParticles()
{
	((class ::Actor*)NativePtr)->spawnDeathParticles();
}

void MC::Actor::SpawnDustParticles(int _0)
{
	((class ::Actor*)NativePtr)->spawnDustParticles(_0);
}

void MC::Actor::SpawnTamingParticles(bool _0)
{
	((class ::Actor*)NativePtr)->spawnTamingParticles(_0);
}

void MC::Actor::TeleportPassengersTo(MC::Vec3 _0, int _1, int _2)
{
	((class ::Actor*)NativePtr)->teleportPassengersTo(_0, _1, _2);
}

//::System::Collections::Generic::List<MC::ItemDescriptor^>^ MC::Actor::TryGetEquippableSlotAllowedItems(int _0)
//{
//    auto __ret = ((class ::Actor*)NativePtr)->tryGetEquippableSlotAllowedItems(_0);
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

bool MC::Actor::TryMoveChunks()
{
	auto __ret = ((class ::Actor*)NativePtr)->tryMoveChunks();
	return __ret;
}

void MC::Actor::UpdateAnimationComponentOnServer()
{
	((class ::Actor*)NativePtr)->updateAnimationComponentOnServer();
}

void MC::Actor::UpdateBBFromDefinition()
{
	((class ::Actor*)NativePtr)->updateBBFromDefinition();
}

void MC::Actor::UpdateDescription()
{
	((class ::Actor*)NativePtr)->updateDescription();
}

void MC::Actor::UpdateInvisibilityStatus()
{
	((class ::Actor*)NativePtr)->updateInvisibilityStatus();
}

void MC::Actor::UpdateTickingData()
{
	((class ::Actor*)NativePtr)->updateTickingData();
}

bool MC::Actor::WasLastHitByPlayer()
{
	auto __ret = ((class ::Actor*)NativePtr)->wasLastHitByPlayer();
	return __ret;
}

bool MC::Actor::WasLoadedFromNBTThisFrame()
{
	auto __ret = ((class ::Actor*)NativePtr)->wasLoadedFromNBTThisFrame();
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

MC::Vec3 MC::Actor::FeetPosition::get()
{
	return ((class ::Actor*)NativePtr)->getFeetPosition();
}

::System::Collections::Generic::List<::System::String^>^ MC::Actor::AllTags::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getAllTags();
	auto _tmp__ret = gcnew ::System::Collections::Generic::List<::System::String^>();
	auto __list0 = __ret;
	for (auto& _element : __list0)
	{
		auto _marshalElement = clix::marshalString<clix::E_UTF8>(_element);
		_tmp__ret->Add(_marshalElement);
	}
	return _tmp__ret;
}

bool MC::Actor::IsRuntimePredictedMovementEnabled::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isRuntimePredictedMovementEnabled();
	return __ret;
}

float MC::Actor::YawSpeedInDegreesPerSecond::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getYawSpeedInDegreesPerSecond();
	return __ret;
}

float MC::Actor::CameraOffset::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getCameraOffset();
	return __ret;
}

bool MC::Actor::IsImmobile::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isImmobile();
	return __ret;
}

bool MC::Actor::IsPickable::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isPickable();
	return __ret;
}

bool MC::Actor::Sleeping::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isSleeping();
	return __ret;
}

void MC::Actor::Sleeping::set(bool _0)
{
	((class ::Actor*)NativePtr)->setSleeping(_0);
}

bool MC::Actor::IsBlocking::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isBlocking();
	return __ret;
}

bool MC::Actor::IsAlive::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isAlive();
	return __ret;
}

bool MC::Actor::IsSurfaceMob::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isSurfaceMob();
	return __ret;
}

MC::Actor^ MC::Actor::Target::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getTarget();
	if (__ret == nullptr) return nullptr;
	return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
}

void MC::Actor::Target::set(MC::Actor^ _0)
{
	auto __arg0 = (class ::Actor*)_0->NativePtr;
	((class ::Actor*)NativePtr)->setTarget(__arg0);
}

//MC::Actor^ MC::Actor::FindAttackTarget::get()
//{
//	auto __ret = ((class ::Actor*)NativePtr)->findAttackTarget();
//	if (__ret == nullptr) return nullptr;
//	return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
//}

bool MC::Actor::CanPowerJump::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->canPowerJump();
	return __ret;
}

void MC::Actor::CanPowerJump::set(bool _0)
{
	((class ::Actor*)NativePtr)->setCanPowerJump(_0);
}

bool MC::Actor::IsJumping::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isJumping();
	return __ret;
}

MC::ActorUniqueID MC::Actor::SourceUniqueID::get()
{
	return ((class ::Actor*)NativePtr)->getSourceUniqueID();

}

int MC::Actor::PortalWaitTime::get()
{
	return ((class ::Actor*)NativePtr)->getPortalWaitTime();
}

MC::ActorUniqueID MC::Actor::ControllingPlayer::get()
{
	return ((class ::Actor*)NativePtr)->getControllingPlayer();
}

bool MC::Actor::InCaravan::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->inCaravan();
	return __ret;
}

int MC::Actor::DeathTime::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getDeathTime();
	return __ret;
}

float MC::Actor::YHeadRot::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getYHeadRot();
	return __ret;
}

void MC::Actor::YHeadRot::set(float _0)
{
	((class ::Actor*)NativePtr)->setYHeadRot(_0);
}

float MC::Actor::YHeadRotO::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getYHeadRotO();
	return __ret;
}

bool MC::Actor::IsWorldBuilder::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isWorldBuilder();
	return __ret;
}

bool MC::Actor::IsCreative::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isCreative();
	return __ret;
}

bool MC::Actor::IsAdventure::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isAdventure();
	return __ret;
}

bool MC::Actor::IsSurvival::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isSurvival();
	return __ret;
}

bool MC::Actor::IsSpectator::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isSpectator();
	return __ret;
}

MC::Mob^ MC::Actor::LastHurtByMob::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getLastHurtByMob();
	if (__ret == nullptr) return nullptr;
	return (__ret == nullptr) ? nullptr : gcnew ::MC::Mob((class ::Mob*)__ret);
}

void MC::Actor::LastHurtByMob::set(MC::Mob^ _0)
{
	auto __arg0 = (class ::Mob*)_0->NativePtr;
	((class ::Actor*)NativePtr)->setLastHurtByMob(__arg0);
}

MC::Player^ MC::Actor::LastHurtByPlayer::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getLastHurtByPlayer();
	if (__ret == nullptr) return nullptr;
	return (__ret == nullptr) ? nullptr : gcnew ::MC::Player((class ::Player*)__ret);
}

void MC::Actor::LastHurtByPlayer::set(MC::Player^ _0)
{
	auto __arg0 = (class ::Player*)_0->NativePtr;
	((class ::Actor*)NativePtr)->setLastHurtByPlayer(__arg0);
}

MC::Mob^ MC::Actor::LastHurtMob::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getLastHurtMob();
	if (__ret == nullptr) return nullptr;
	return (__ret == nullptr) ? nullptr : gcnew ::MC::Mob((class ::Mob*)__ret);
}

MC::Vec3 MC::Actor::Pos::get()
{
	return ((class ::Actor*)NativePtr)->getPos();
}

void MC::Actor::Pos::set(MC::Vec3 _0)
{
	((class ::Actor*)NativePtr)->setPos(_0);
}

MC::Vec3% MC::Actor::PosPrev::get()
{
	return *(Vec3*)(const_cast<::Vec3*>(&((class ::Actor*)NativePtr)->getPosPrev()));
}

void MC::Actor::PosPrev::set(MC::Vec3% _0)
{
	pin_ptr<Vec3> p = &_0;
	((class ::Actor*)NativePtr)->setPosPrev(*(::Vec3*)p);
}

MC::Vec3 MC::Actor::FiringPos::get()
{
	return ((class ::Actor*)NativePtr)->getFiringPos();
}

bool MC::Actor::IsFireImmune::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isFireImmune();
	return __ret;
}

float MC::Actor::RidingHeight::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getRidingHeight();
	return __ret;
}

bool MC::Actor::IsInWall::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInWall();
	return __ret;
}

bool MC::Actor::Invisible::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInvisible();
	return __ret;
}

void MC::Actor::Invisible::set(bool _0)
{
	((class ::Actor*)NativePtr)->setInvisible(_0);
}

::System::String^ MC::Actor::NameTag::get()
{
	auto& __ret = ((class ::Actor*)NativePtr)->getNameTag();
	return (::System::String^)(clix::marshalString<clix::E_UTF8>(__ret));
}

void MC::Actor::NameTag::set(::System::String^ _0)
{
	auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
	((class ::Actor*)NativePtr)->setNameTag(__arg0);
}

unsigned long long MC::Actor::NameTagAsHash::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getNameTagAsHash();
	return __ret;
}

::System::String^ MC::Actor::FormattedNameTag::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getFormattedNameTag();
	return clix::marshalString<clix::E_UTF8>(__ret);
}

::System::String^ MC::Actor::ScoreTag::get()
{
	auto& __ret = ((class ::Actor*)NativePtr)->getScoreTag();
	return (::System::String^)(clix::marshalString<clix::E_UTF8>(__ret));
}

void MC::Actor::ScoreTag::set(::System::String^ _0)
{
	auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
	((class ::Actor*)NativePtr)->setScoreTag(__arg0);
}

bool MC::Actor::IsInWater::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInWater();
	return __ret;
}

bool MC::Actor::HasEnteredWater::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasEnteredWater();
	return __ret;
}

bool MC::Actor::IsInLava::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInLava();
	return __ret;
}

bool MC::Actor::IsOverWater::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isOverWater();
	return __ret;
}

float MC::Actor::ShadowHeightOffs::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getShadowHeightOffs();
	return __ret;
}

float MC::Actor::ShadowRadius::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getShadowRadius();
	return __ret;
}

bool MC::Actor::IsSilent::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isSilent();
	return __ret;
}

bool MC::Actor::Sneaking::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isSneaking();
	return __ret;
}

void MC::Actor::Sneaking::set(bool _0)
{
	((class ::Actor*)NativePtr)->setSneaking(_0);
}

bool MC::Actor::IsOnFire::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isOnFire();
	return __ret;
}

bool MC::Actor::IsOnHotBlock::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isOnHotBlock();
	return __ret;
}

bool MC::Actor::IsAffectedByWaterBottle::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isAffectedByWaterBottle();
	return __ret;
}

int MC::Actor::EquipmentCount::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getEquipmentCount();
	return __ret;
}

bool MC::Actor::Sitting::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isSitting();
	return __ret;
}

void MC::Actor::Sitting::set(bool _0)
{
	((class ::Actor*)NativePtr)->setSitting(_0);
}

int MC::Actor::InventorySize::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getInventorySize();
	return __ret;
}

int MC::Actor::EquipSlots::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getEquipSlots();
	return __ret;
}

int MC::Actor::ChestSlots::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getChestSlots();
	return __ret;
}

bool MC::Actor::Standing::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isStanding();
	return __ret;
}

void MC::Actor::Standing::set(bool _0)
{
	((class ::Actor*)NativePtr)->setStanding(_0);
}

bool MC::Actor::Enchanted::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isEnchanted();
	return __ret;
}

void MC::Actor::Enchanted::set(bool _0)
{
	((class ::Actor*)NativePtr)->setEnchanted(_0);
}

float MC::Actor::PickRadius::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getPickRadius();
	return __ret;
}

bool MC::Actor::IsWearingLeatherArmor::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isWearingLeatherArmor();
	return __ret;
}

int MC::Actor::PortalCooldown::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getPortalCooldown();
	return __ret;
}

bool MC::Actor::IsClientSide::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isClientSide();
	return __ret;
}

bool MC::Actor::IsInvertedHealAndHarm::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInvertedHealAndHarm();
	return __ret;
}

float MC::Actor::MapDecorationRotation::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getMapDecorationRotation();
	return __ret;
}

bool MC::Actor::IsAttackableGamemode::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isAttackableGamemode();
	return __ret;
}

bool MC::Actor::DamageNearbyMobs::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getDamageNearbyMobs();
	return __ret;
}

void MC::Actor::DamageNearbyMobs::set(bool _0)
{
	((class ::Actor*)NativePtr)->setDamageNearbyMobs(_0);
}

bool MC::Actor::UpdateWaterState::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->updateWaterState();
	return __ret;
}

MC::Vec3 MC::Actor::PosOld::get()
{
	return ((class ::Actor*)NativePtr)->getPosOld();
}

MC::Vec3 MC::Actor::RandomHeartPos::get()
{
	return ((class ::Actor*)NativePtr)->_randomHeartPos();
}

MC::Vec3 MC::Actor::CalcCenterPos::get()
{
	return ((class ::Actor*)NativePtr)->calcCenterPos();
}

bool MC::Actor::CanFly::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->canFly();
	return __ret;
}

void MC::Actor::CanFly::set(bool _0)
{
	((class ::Actor*)NativePtr)->setCanFly(_0);
}

MC::AABB MC::Actor::AABB::get()
{
	return ((class ::Actor*)NativePtr)->getAABB();
}

void MC::Actor::AABB::set(MC::AABB _0)
{
	((class ::Actor*)NativePtr)->setAABB(_0);
}

MC::Vec2 MC::Actor::AABBDim::get()
{
	return ((class ::Actor*)NativePtr)->getAABBDim();
}

void MC::Actor::AABBDim::set(MC::Vec2 _0)
{
	((class ::Actor*)NativePtr)->setAABBDim(_0);
}

int MC::Actor::ActiveEffectCount::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getActiveEffectCount();
	return __ret;
}

::System::Collections::Generic::List<MC::MobEffectInstance^>^ MC::Actor::AllEffects::get()
{
	auto& __ret = ((class ::Actor*)NativePtr)->getAllEffects();
	auto _tmp__ret = gcnew ::System::Collections::Generic::List<MC::MobEffectInstance^>();
	auto __list0 = __ret;
	for (auto _element : __list0)
	{
		auto ___element = new class ::MobEffectInstance(_element);
		auto _marshalElement = (___element == nullptr) ? nullptr : gcnew ::MC::MobEffectInstance((class ::MobEffectInstance*)___element, true);
		_tmp__ret->Add(_marshalElement);
	}
	return (::System::Collections::Generic::List<MC::MobEffectInstance^>^)(_tmp__ret);
}

MC::BlockPos MC::Actor::BlockTarget::get()
{
	return ((class ::Actor*)NativePtr)->getBlockTarget();
}

void MC::Actor::BlockTarget::set(MC::BlockPos _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
	((class ::Actor*)NativePtr)->setBlockTarget(_0);
}

bool MC::Actor::CanPickupItems::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getCanPickupItems();
	return __ret;
}

bool MC::Actor::ChainedDamageEffects::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getChainedDamageEffects();
	return __ret;
}

void MC::Actor::ChainedDamageEffects::set(bool _0)
{
	((class ::Actor*)NativePtr)->setChainedDamageEffects(_0);
}

//bool MC::Actor::CollidableMobNear::get()
//{
//	auto __ret = ((class ::Actor*)NativePtr)->getCollidableMobNear();
//	return __ret;
//}
//
//void MC::Actor::CollidableMobNear::set(bool _0)
//{
//	((class ::Actor*)NativePtr)->setCollidableMobNear(_0);
//}

int MC::Actor::ControllingSeat::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getControllingSeat();
	return __ret;
}

void MC::Actor::ControllingSeat::set(int _0)
{
	((class ::Actor*)NativePtr)->setControllingSeat(_0);
}

float MC::Actor::CurrentSwimAmount::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getCurrentSwimAmount();
	return __ret;
}

MC::Actor^ MC::Actor::FirstPassenger::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getFirstPassenger();
	if (__ret == nullptr) return nullptr;
	return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
}

int MC::Actor::Health::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getHealth();
	return __ret;
}

int MC::Actor::HurtDir::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getHurtDir();
	return __ret;
}

void MC::Actor::HurtDir::set(int _0)
{
	((class ::Actor*)NativePtr)->setHurtDir(_0);
}

int MC::Actor::HurtTime::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getHurtTime();
	return __ret;
}

void MC::Actor::HurtTime::set(int _0)
{
	((class ::Actor*)NativePtr)->setHurtTime(_0);
}

bool MC::Actor::IsExperienceDropEnabled::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getIsExperienceDropEnabled();
	return __ret;
}

void MC::Actor::IsExperienceDropEnabled::set(bool _0)
{
	((class ::Actor*)NativePtr)->setIsExperienceDropEnabled(_0);
}

int MC::Actor::JumpDuration::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getJumpDuration();
	return __ret;
}

void MC::Actor::JumpDuration::set(int _0)
{
	((class ::Actor*)NativePtr)->setJumpDuration(_0);
}

int MC::Actor::LastHurtByMobTime::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getLastHurtByMobTime();
	return __ret;
}

int MC::Actor::LastHurtByMobTimestamp::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getLastHurtByMobTimestamp();
	return __ret;
}

MC::ActorDamageCause MC::Actor::LastHurtCause::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getLastHurtCause();
	return (MC::ActorDamageCause)__ret;
}

float MC::Actor::LastHurtDamage::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getLastHurtDamage();
	return __ret;
}

int MC::Actor::LastHurtMobTimestamp::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getLastHurtMobTimestamp();
	return __ret;
}

unsigned long long MC::Actor::LastHurtTimestamp::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getLastHurtTimestamp();
	return __ret;
}

MC::ActorUniqueID MC::Actor::LeashHolder::get()
{
	return ((class ::Actor*)NativePtr)->getLeashHolder();
}

void MC::Actor::LeashHolder::set(MC::ActorUniqueID _0)
{
	((class ::Actor*)NativePtr)->setLeashHolder(_0);
}

int MC::Actor::LimitedLifetimeTicks::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getLimitedLifetimeTicks();
	return __ret;
}

void MC::Actor::LimitedLifetimeTicks::set(int _0)
{
	((class ::Actor*)NativePtr)->setLimitedLifetimeTicks(_0);
}

//::System::Collections::Generic::List<MC::ActorLink^>^ MC::Actor::Links::get()
//{
//    auto __ret = ((class ::Actor*)NativePtr)->getLinks();
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
	auto __ret = ((class ::Actor*)NativePtr)->getMarkVariant();
	return __ret;
}

void MC::Actor::MarkVariant::set(int _0)
{
	((class ::Actor*)NativePtr)->setMarkVariant(_0);
}

int MC::Actor::MaxHealth::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getMaxHealth();
	return __ret;
}

int MC::Actor::OnDeathExperience::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getOnDeathExperience();
	return __ret;
}

MC::Mob^ MC::Actor::Owner::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getOwner();
	if (__ret == nullptr) return nullptr;
	return (__ret == nullptr) ? nullptr : gcnew ::MC::Mob((class ::Mob*)__ret);
}

MC::ActorUniqueID MC::Actor::OwnerId::get()
{
	return ((class ::Actor*)NativePtr)->getOwnerId();
}

int MC::Actor::PersistingTradeRiches::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getPersistingTradeRiches();
	return __ret;
}

MC::Player^ MC::Actor::PlayerOwner::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getPlayerOwner();
	if (__ret == nullptr) return nullptr;
	return (__ret == nullptr) ? nullptr : gcnew ::MC::Player((class ::Player*)__ret);
}

//MC::Vec3% MC::Actor::PosDelta::get()
//{
//	return *(Vec3*)const_cast<::Vec3*>(&((class ::Actor*)NativePtr)->getPosDelta());
//}
//
//void MC::Actor::PosDelta::set(MC::Vec3% _0)
//{
//	pin_ptr<Vec3> p = &_0;
//	((class ::Actor*)NativePtr)->setPosDelta(*(::Vec3*)p);
//}

MC::Vec3% MC::Actor::PosDeltaNonConst::get()
{
	return *(Vec3*)const_cast<::Vec3*>(&((class ::Actor*)NativePtr)->getPosDeltaNonConst());
}

float MC::Actor::Radius::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getRadius();
	return __ret;
}

MC::Vec2 MC::Actor::Rotation::get()
{
	return ((class ::Actor*)NativePtr)->getRotation();
}

MC::ActorRuntimeID^ MC::Actor::RuntimeID::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getRuntimeID();
	auto ____ret = new class ::ActorRuntimeID(__ret);
	return (____ret == nullptr) ? nullptr : gcnew ::MC::ActorRuntimeID((class ::ActorRuntimeID*)____ret, true);
}

void MC::Actor::RuntimeID::set(MC::ActorRuntimeID^ _0)
{
	if (ReferenceEquals(_0, nullptr))
		throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is passed by value.");
	auto __arg0 = *(class ::ActorRuntimeID*)_0->NativePtr;
	((class ::Actor*)NativePtr)->setRuntimeID(__arg0);
}

int MC::Actor::ShakeTime::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getShakeTime();
	return __ret;
}

void MC::Actor::ShakeTime::set(int _0)
{
	((class ::Actor*)NativePtr)->setShakeTime(_0);
}

int MC::Actor::SkinID::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getSkinID();
	return __ret;
}

void MC::Actor::SkinID::set(int _0)
{
	((class ::Actor*)NativePtr)->setSkinID(_0);
}

float MC::Actor::SpeedInMetersPerSecond::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getSpeedInMetersPerSecond();
	return __ret;
}

int MC::Actor::Strength::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getStrength();
	return __ret;
}

void MC::Actor::Strength::set(int _0)
{
	((class ::Actor*)NativePtr)->setStrength(_0);
}

int MC::Actor::StrengthMax::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getStrengthMax();
	return __ret;
}

void MC::Actor::StrengthMax::set(int _0)
{
	((class ::Actor*)NativePtr)->setStrengthMax(_0);
}

int MC::Actor::StructuralIntegrity::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getStructuralIntegrity();
	return __ret;
}

void MC::Actor::StructuralIntegrity::set(int _0)
{
	((class ::Actor*)NativePtr)->setStructuralIntegrity(_0);
}

MC::ActorUniqueID MC::Actor::TargetId::get()
{
	return ((class ::Actor*)NativePtr)->getTargetId();
}

bool MC::Actor::TradeInterest::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getTradeInterest();
	return __ret;
}

void MC::Actor::TradeInterest::set(bool _0)
{
	((class ::Actor*)NativePtr)->setTradeInterest(_0);
}

MC::Player^ MC::Actor::TradingPlayer::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getTradingPlayer();
	if (__ret == nullptr) return nullptr;
	return (__ret == nullptr) ? nullptr : gcnew ::MC::Player((class ::Player*)__ret);
}

void MC::Actor::TradingPlayer::set(MC::Player^ _0)
{
	auto __arg0 = (class ::Player*)_0->NativePtr;
	((class ::Actor*)NativePtr)->setTradingPlayer(__arg0);
}

MC::ActorUniqueID MC::Actor::UniqueID::get()
{
	return ((class ::Actor*)NativePtr)->getUniqueID();
}

void MC::Actor::UniqueID::set(MC::ActorUniqueID _0)
{
	((class ::Actor*)NativePtr)->setUniqueID(_0);
}

int MC::Actor::Variant::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getVariant();
	return __ret;
}

void MC::Actor::Variant::set(int _0)
{
	((class ::Actor*)NativePtr)->setVariant(_0);
}

MC::Actor^ MC::Actor::Vehicle::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getVehicle();
	if (__ret == nullptr) return nullptr;
	return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
}

MC::Actor^ MC::Actor::VehicleRoot::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getVehicleRoot();
	if (__ret == nullptr) return nullptr;
	return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
}

MC::ActorRuntimeID^ MC::Actor::VehicleRuntimeID::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getVehicleRuntimeID();
	auto ____ret = new class ::ActorRuntimeID(__ret);
	return (____ret == nullptr) ? nullptr : gcnew ::MC::ActorRuntimeID((class ::ActorRuntimeID*)____ret, true);
}

float MC::Actor::VerticalSpeedInMetersPerSecond::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->getVerticalSpeedInMetersPerSecond();
	return __ret;
}

bool MC::Actor::HasAnyEffects::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasAnyEffects();
	return __ret;
}

bool MC::Actor::HasAnyVisibleEffects::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasAnyVisibleEffects();
	return __ret;
}

bool MC::Actor::HasDimension::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasDimension();
	return __ret;
}

bool MC::Actor::HasFishingHook::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasFishingHook();
	return __ret;
}

bool MC::Actor::HasLevel::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasLevel();
	return __ret;
}

bool MC::Actor::HasPassenger::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasPassenger();
	return __ret;
}

bool MC::Actor::HasPersistingTrade::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasPersistingTrade();
	return __ret;
}

bool MC::Actor::HasPlayerPassenger::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasPlayerPassenger();
	return __ret;
}

bool MC::Actor::HasPriorityAmmunition::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasPriorityAmmunition();
	return __ret;
}

bool MC::Actor::HasRuntimeID::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasRuntimeID();
	return __ret;
}

bool MC::Actor::HasSaddle::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasSaddle();
	return __ret;
}

bool MC::Actor::HasTags::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasTags();
	return __ret;
}

bool MC::Actor::HasTeleported::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasTeleported();
	return __ret;
}

bool MC::Actor::HasTickingArea::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasTickingArea();
	return __ret;
}

bool MC::Actor::HasTotemEquipped::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasTotemEquipped();
	return __ret;
}

bool MC::Actor::HasUniqueID::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->hasUniqueID();
	return __ret;
}

bool MC::Actor::InDownwardFlowingLiquid::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->inDownwardFlowingLiquid();
	return __ret;
}

bool MC::Actor::IsAngry::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isAngry();
	return __ret;
}

bool MC::Actor::Autonomous::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isAutonomous();
	return __ret;
}

void MC::Actor::Autonomous::set(bool _0)
{
	((class ::Actor*)NativePtr)->setAutonomous(_0);
}

bool MC::Actor::IsBaby::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isBaby();
	return __ret;
}

bool MC::Actor::BreakingObstruction::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isBreakingObstruction();
	return __ret;
}

void MC::Actor::BreakingObstruction::set(bool _0)
{
	((class ::Actor*)NativePtr)->setBreakingObstruction(_0);
}

bool MC::Actor::IsBribed::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isBribed();
	return __ret;
}

bool MC::Actor::Charged::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isCharged();
	return __ret;
}

void MC::Actor::Charged::set(bool _0)
{
	((class ::Actor*)NativePtr)->setCharged(_0);
}

bool MC::Actor::IsChested::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isChested();
	return __ret;
}

bool MC::Actor::Climbing::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isClimbing();
	return __ret;
}

void MC::Actor::Climbing::set(bool _0)
{
	((class ::Actor*)NativePtr)->setClimbing(_0);
}

bool MC::Actor::IsControlledByLocalInstance::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isControlledByLocalInstance();
	return __ret;
}

bool MC::Actor::DoorBreaker::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isDoorBreaker();
	return __ret;
}

void MC::Actor::DoorBreaker::set(bool _0)
{
	((class ::Actor*)NativePtr)->setDoorBreaker(_0);
}

bool MC::Actor::DoorOpener::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isDoorOpener();
	return __ret;
}

void MC::Actor::DoorOpener::set(bool _0)
{
	((class ::Actor*)NativePtr)->setDoorOpener(_0);
}

bool MC::Actor::Global::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isGlobal();
	return __ret;
}

void MC::Actor::Global::set(bool _0)
{
	((class ::Actor*)NativePtr)->setGlobal(_0);
}

bool MC::Actor::IsIgnited::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isIgnited();
	return __ret;
}

bool MC::Actor::IsImmersedInWater::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isImmersedInWater();
	return __ret;
}

bool MC::Actor::IsInClouds::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInClouds();
	return __ret;
}

bool MC::Actor::IsInContactWithWater::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInContactWithWater();
	return __ret;
}

bool MC::Actor::IsInLove::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInLove();
	return __ret;
}

bool MC::Actor::IsInPrecipitation::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInPrecipitation();
	return __ret;
}

bool MC::Actor::IsInRain::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInRain();
	return __ret;
}

bool MC::Actor::IsInScaffolding::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInScaffolding();
	return __ret;
}

bool MC::Actor::IsInSnow::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInSnow();
	return __ret;
}

bool MC::Actor::IsInThunderstorm::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInThunderstorm();
	return __ret;
}

bool MC::Actor::IsInWaterOrRain::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInWaterOrRain();
	return __ret;
}

bool MC::Actor::IsInWorld::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInWorld();
	return __ret;
}

bool MC::Actor::IsInsidePortal::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isInsidePortal();
	return __ret;
}

bool MC::Actor::LayingDown::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isLayingDown();
	return __ret;
}

void MC::Actor::LayingDown::set(bool _0)
{
	((class ::Actor*)NativePtr)->setLayingDown(_0);
}

bool MC::Actor::IsLeashed::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isLeashed();
	return __ret;
}

bool MC::Actor::MovedToLimbo::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isMovedToLimbo();
	return __ret;
}

void MC::Actor::MovedToLimbo::set(bool _0)
{
	((class ::Actor*)NativePtr)->setMovedToLimbo(_0);
}

bool MC::Actor::MovedToUnloadedChunk::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isMovedToUnloadedChunk();
	return __ret;
}

void MC::Actor::MovedToUnloadedChunk::set(bool _0)
{
	((class ::Actor*)NativePtr)->setMovedToUnloadedChunk(_0);
}

bool MC::Actor::Moving::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isMoving();
	return __ret;
}

void MC::Actor::Moving::set(bool _0)
{
	((class ::Actor*)NativePtr)->setMoving(_0);
}

bool MC::Actor::IsOrphan::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isOrphan();
	return __ret;
}

bool MC::Actor::IsOutOfControl::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isOutOfControl();
	return __ret;
}

bool MC::Actor::IsOverScaffolding::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isOverScaffolding();
	return __ret;
}

bool MC::Actor::IsPacified::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isPacified();
	return __ret;
}

bool MC::Actor::IsPersistent::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isPersistent();
	return __ret;
}

bool MC::Actor::IsPlayingDead::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isPlayingDead();
	return __ret;
}

bool MC::Actor::IsPowered::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isPowered();
	return __ret;
}

bool MC::Actor::IsRegionValid::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isRegionValid();
	return __ret;
}

bool MC::Actor::IsRemoved::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isRemoved();
	return __ret;
}

bool MC::Actor::Resting::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isResting();
	return __ret;
}

void MC::Actor::Resting::set(bool _0)
{
	((class ::Actor*)NativePtr)->setResting(_0);
}

bool MC::Actor::IsSafeToSleepNear::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isSafeToSleepNear();
	return __ret;
}

bool MC::Actor::IsSheared::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isSheared();
	return __ret;
}

bool MC::Actor::IsSoulSpeedEnchantActive::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isSoulSpeedEnchantActive();
	return __ret;
}

bool MC::Actor::IsStackable::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isStackable();
	return __ret;
}

bool MC::Actor::Swimmer::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isSwimmer();
	return __ret;
}

void MC::Actor::Swimmer::set(bool _0)
{
	((class ::Actor*)NativePtr)->setSwimmer(_0);
}

bool MC::Actor::IsSwimming::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isSwimming();
	return __ret;
}

bool MC::Actor::IsTame::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isTame();
	return __ret;
}

bool MC::Actor::IsTickingEntity::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isTickingEntity();
	return __ret;
}

bool MC::Actor::IsTouchingDamageBlock::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isTouchingDamageBlock();
	return __ret;
}

bool MC::Actor::IsTrading::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isTrading();
	return __ret;
}

bool MC::Actor::IsTrusting::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isTrusting();
	return __ret;
}

bool MC::Actor::IsUseNewTradeScreen::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isUseNewTradeScreen();
	return __ret;
}

bool MC::Actor::WASDControlled::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isWASDControlled();
	return __ret;
}

void MC::Actor::WASDControlled::set(bool _0)
{
	((class ::Actor*)NativePtr)->setWASDControlled(_0);
}

bool MC::Actor::Walker::get()
{
	auto __ret = ((class ::Actor*)NativePtr)->isWalker();
	return __ret;
}

void MC::Actor::Walker::set(bool _0)
{
	((class ::Actor*)NativePtr)->setWalker(_0);
}

MC::ActorUniqueID MC::Actor::LovePartnerId::get()
{
	return ((class ::Actor*)NativePtr)->lovePartnerId();
}

float MC::Actor::DEFAULT_AMBIENT_SOUND_INTERVAL::get()
{
	return ::Actor::DEFAULT_AMBIENT_SOUND_INTERVAL;
}

float MC::Actor::DEFAULT_AMBIENT_SOUND_INTERVAL_RANGE::get()
{
	return ::Actor::DEFAULT_AMBIENT_SOUND_INTERVAL_RANGE;
}

float MC::Actor::DEFAULT_MOVEMENT_SOUND_DISTANCE_OFFSET::get()
{
	return ::Actor::DEFAULT_MOVEMENT_SOUND_DISTANCE_OFFSET;
}

MC::Vec3 MC::Actor::LAVA_AABB_SHRINK_AMOUNT::get()
{
	return ::Actor::LAVA_AABB_SHRINK_AMOUNT;
}

float MC::Actor::LAVA_FLOW_STRENGTH_MULTIPLIER::get()
{
	return ::Actor::LAVA_FLOW_STRENGTH_MULTIPLIER;
}

int MC::Actor::MAX_BYTE_CHARGE_AMOUNT::get()
{
	return ::Actor::MAX_BYTE_CHARGE_AMOUNT;
}

int MC::Actor::PLAYER_HURT_EXPERIENCE_TIME::get()
{
	return ::Actor::PLAYER_HURT_EXPERIENCE_TIME;
}

::System::String^ MC::Actor::RIDING_TAG::get()
{
	return clix::marshalString<clix::E_UTF8>(::Actor::RIDING_TAG);
}

int MC::Actor::TOTAL_AIR_SUPPLY::get()
{
	return ::Actor::TOTAL_AIR_SUPPLY;
}

MC::Vec3 MC::Actor::WATER_AABB_SHRINK_AMOUNT::get()
{
	return ::Actor::WATER_AABB_SHRINK_AMOUNT;
}

float MC::Actor::WATER_FLOW_STRENGTH_MULTIPLIER::get()
{
	return ::Actor::WATER_FLOW_STRENGTH_MULTIPLIER;
}
#endif // MANUAL_MAINTENANCE
