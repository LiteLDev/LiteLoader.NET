#include <src/Header/MC/Block.hpp>

#include <src/Header/MC/CompoundTag.hpp>
#include <src/Header/MC/BlockPos.hpp>
#include <src/Header/MC/AABB.hpp>
#include <src/Header/MC/Vec3.hpp>

namespace MC
{
inline Block ^ Block::Create(const String ^ str, unsigned short tileData)
{
    return gcnew Block((::Block*)::Block::create(marshalString((String ^) str), tileData));
}

inline Block ^ Block::Create(CompoundTag ^ nbt)
{
    return gcnew Block((::Block*)::Block::create(nbt->NativePtr));
}

inline HashedString ^ Block::Name::get()
{
    return gcnew HashedString((::HashedString &)NativePtr->getName());
}

inline int Block::Id::get()
{
    return NativePtr->getId();
}

inline unsigned short Block::TileData::get()
{
    return NativePtr->getTileData();
}

inline CompoundTag ^ Block::Nbt::get()
{
    return gcnew CompoundTag(NativePtr->getNbt().release(), true);
}

inline void Block::Nbt::set(CompoundTag ^ nbt)
{
    NativePtr->setNbt(nbt->NativePtr);
}
} // namespace MC


#ifdef MANUAL_MAINTENANCE

::String^ MC::Block::BuildDescriptionId()
{
    auto __ret = NativePtr->buildDescriptionId();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

::String^ MC::Block::BuildDescriptionName()
{
    auto __ret = NativePtr->buildDescriptionName();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

void MC::Block::CacheComponentData()
{
    NativePtr->cacheComponentData();
}

bool MC::Block::CanBeBrokenFromFalling()
{
    auto __ret = NativePtr->canBeBrokenFromFalling();
    return __ret;
}

bool MC::Block::CanBeOriginalSurface()
{
    auto __ret = NativePtr->canBeOriginalSurface();
    return __ret;
}

bool MC::Block::CanConnect(MC::Block ^ _0, unsigned char _1, MC::Block ^ _2)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Block*)_0->NativePtr;
    if (ReferenceEquals(_2, nullptr))
        throw gcnew ::System::ArgumentNullException("_2", "Cannot be null because it is a C++ reference (&).");
    auto& __arg2 = *(class ::Block*)_2->NativePtr;
    auto __ret = NativePtr->canConnect(__arg0, _1, __arg2);
    return __ret;
}

bool MC::Block::CanHaveExtraData()
{
    auto __ret = NativePtr->canHaveExtraData();
    return __ret;
}

bool MC::Block::CanHurtAndBreakItem()
{
    auto __ret = NativePtr->canHurtAndBreakItem();
    return __ret;
}

bool MC::Block::CanInstatick()
{
    auto __ret = NativePtr->canInstatick();
    return __ret;
}

void MC::Block::GetDebugText(::System::Collections::Generic::IList<::String^> ^ _0, MC::BlockPos _1)
{
    auto _tmp_0 = std::vector<::std::string>();
    for each (::String^ _element in _0)
    {
        auto _marshalElement = clix::marshalString<clix::E_UTF8>(_element);
        _tmp_0.push_back(_marshalElement);
    }
    auto __arg0 = _tmp_0;
    NativePtr->getDebugText(__arg0, _1);
}

bool MC::Block::HasTag(unsigned long long _0)
{
    auto __arg0 = (const unsigned long long&)_0;
    auto __ret = NativePtr->hasTag(__arg0);
    return __ret;
}

bool MC::Block::IgnoreEntitiesOnPistonMove()
{
    auto __ret = NativePtr->ignoreEntitiesOnPistonMove();
    return __ret;
}

bool MC::Block::IsPreservingMediumWhenPlaced(MC::Block ^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::Block*)_0->NativePtr;
    auto __ret = NativePtr->isPreservingMediumWhenPlaced(__arg0);
    return __ret;
}

bool MC::Block::operator!=(MC::Block ^ __op, MC::Block ^ _0)
{
    bool __opNull = ReferenceEquals(__op, nullptr);
    bool _0Null = ReferenceEquals(_0, nullptr);
    if (__opNull || _0Null)
        return !(__opNull && _0Null);
    auto& __arg0 = *(class ::Block*)__op->NativePtr;
    auto& __arg1 = *(class ::Block*)_0->NativePtr;
    auto __ret = __arg0 != __arg1;
    return __ret;
}

bool MC::Block::operator==(MC::Block ^ __op, MC::Block ^ _0)
{
    bool __opNull = ReferenceEquals(__op, nullptr);
    bool _0Null = ReferenceEquals(_0, nullptr);
    if (__opNull || _0Null)
        return __opNull && _0Null;
    auto& __arg0 = *(class ::Block*)__op->NativePtr;
    auto& __arg1 = *(class ::Block*)_0->NativePtr;
    auto __ret = __arg0 == __arg1;
    return __ret;
}

bool MC::Block::Equals(::System::Object ^ obj)
{
    return this == safe_cast<MC::Block ^>(obj);
}

MC::Vec3 MC::Block::RandomlyModifyPosition(MC::BlockPos _0)
{
    return NativePtr->randomlyModifyPosition(_0);
}

bool MC::Block::ShouldRandomTick()
{
    auto __ret = NativePtr->shouldRandomTick();
    return __ret;
}

bool MC::Block::ShouldRandomTickExtraLayer()
{
    auto __ret = NativePtr->shouldRandomTickExtraLayer();
    return __ret;
}

::String^ MC::Block::ToDebugString()
{
    auto __ret = NativePtr->toDebugString();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

MC::Block ^ MC::Block::TryGetInfested()
{
    auto __ret = NativePtr->tryGetInfested();
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Block((class ::Block*)__ret);
}

MC::Block ^ MC::Block::TryGetUninfested()
{
    auto __ret = NativePtr->tryGetUninfested();
    if (__ret == nullptr) return nullptr;
    return (__ret == nullptr) ? nullptr : gcnew ::MC::Block((class ::Block*)__ret);
}

bool MC::Block::CausesFreezeEffect::get()
{
    auto __ret = NativePtr->causesFreezeEffect();
    return __ret;
}

bool MC::Block::AllowsRunes::get()
{
    auto __ret = NativePtr->getAllowsRunes();
    return __ret;
}

int MC::Block::BurnOdds::get()
{
    auto __ret = NativePtr->getBurnOdds();
    return __ret;
}

int MC::Block::Color::get()
{
    auto __ret = NativePtr->getColor();
    return __ret;
}

/*MC::Block ^ MC::Block::DefaultState::get()
{
    auto& __ret = NativePtr->getDefaultState();
    return (MC::Block ^)((&__ret == nullptr) ? nullptr : gcnew ::MC::Block((class ::Block*)&__ret));
}*/

::String^ MC::Block::DescriptionId::get()
{
    auto __ret = NativePtr->getDescriptionId();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

float MC::Block::DestroySpeed::get()
{
    auto __ret = NativePtr->getDestroySpeed();
    return __ret;
}

int MC::Block::FlameOdds::get()
{
    auto __ret = NativePtr->getFlameOdds();
    return __ret;
}

float MC::Block::Friction::get()
{
    auto __ret = NativePtr->getFriction();
    return __ret;
}

unsigned int MC::Block::RuntimeId::get()
{
    auto& __ret = NativePtr->getRuntimeId();
    return (unsigned int)(const_cast<unsigned int&>(__ret));
}

MC::CompoundTag ^ MC::Block::SerializationId::get()
{
    auto& __ret = NativePtr->getSerializationId();
    return (MC::CompoundTag ^)((&__ret == nullptr) ? nullptr : gcnew ::MC::CompoundTag((class ::CompoundTag*)&__ret));
}

float MC::Block::Thickness::get()
{
    auto __ret = NativePtr->getThickness();
    return __ret;
}

float MC::Block::Translucency::get()
{
    auto __ret = NativePtr->getTranslucency();
    return __ret;
}

int MC::Block::Variant::get()
{
    auto __ret = NativePtr->getVariant();
    return __ret;
}

bool MC::Block::HasBlockEntity::get()
{
    auto __ret = NativePtr->hasBlockEntity();
    return __ret;
}

bool MC::Block::HasComparatorSignal::get()
{
    auto __ret = NativePtr->hasComparatorSignal();
    return __ret;
}

//bool MC::Block::HasRuntimeId::get()
//{
//    auto __ret = NativePtr->hasRuntimeId();
//    return __ret;
//}

bool MC::Block::IsBounceBlock::get()
{
    return NativePtr->isBounceBlock();
}

bool MC::Block::IsButtonBlock::get()
{
    return NativePtr->isButtonBlock();
}

bool MC::Block::IsContainerBlock::get()
{
    return NativePtr->isContainerBlock();
}

bool MC::Block::IsCropBlock::get()
{
    return NativePtr->isCropBlock();
}

bool MC::Block::IsDoorBlock::get()
{
    return NativePtr->isDoorBlock();
}

bool MC::Block::IsFenceBlock::get()
{
    return NativePtr->isFenceBlock();
}

bool MC::Block::IsFenceGateBlock::get()
{
    return NativePtr->isFenceGateBlock();
}

//bool MC::Block::IsHeavy::get()
//{
//    auto __ret = NativePtr->isHeavy();
//    return __ret;
//}

bool MC::Block::IsInteractiveBlock::get()
{
    return NativePtr->isInteractiveBlock();
}

bool MC::Block::IsLeverBlock::get()
{
    return NativePtr->isLeverBlock();
}

bool MC::Block::IsMotionBlockingBlock::get()
{
    return NativePtr->isMotionBlockingBlock();
}

bool MC::Block::IsRailBlock::get()
{
    return NativePtr->isRailBlock();
}

bool MC::Block::IsSignalSource::get()
{
    auto __ret = NativePtr->isSignalSource();
    return __ret;
}

bool MC::Block::IsSlabBlock::get()
{
    return NativePtr->isSlabBlock();
}

bool MC::Block::IsSolid::get()
{
    auto __ret = NativePtr->isSolid();
    return __ret;
}

bool MC::Block::IsSolidBlockingBlock::get()
{
    return NativePtr->isSolidBlockingBlock();
}

bool MC::Block::IsSolidBlockingBlockAndNotSignalSource::get()
{
    auto __ret = NativePtr->isSolidBlockingBlockAndNotSignalSource();
    return __ret;
}

bool MC::Block::IsStairBlock::get()
{
    return NativePtr->isStairBlock();
}

/*bool MC::Block::IsStandingSign::get()
{
    auto __ret = NativePtr->isStandingSign();
    return __ret;
}*/

bool MC::Block::IsStemBlock::get()
{
    return NativePtr->isStemBlock();
}

bool MC::Block::IsThinFenceBlock::get()
{
    return NativePtr->isThinFenceBlock();
}

bool MC::Block::IsUnbreakable::get()
{
    auto __ret = NativePtr->isUnbreakable();
    return __ret;
}

bool MC::Block::IsWallBlock::get()
{
    return NativePtr->isWallBlock();
}

bool MC::Block::IsWaterBlocking::get()
{
    auto __ret = NativePtr->isWaterBlocking();
    return __ret;
}

bool MC::Block::MayPick::get()
{
    auto __ret = NativePtr->mayPick();
    return __ret;
}

bool MC::Block::PushesOutItems::get()
{
    auto __ret = NativePtr->pushesOutItems();
    return __ret;
}

bool MC::Block::PushesUpFallingBlocks::get()
{
    auto __ret = NativePtr->pushesUpFallingBlocks();
    return __ret;
}

::String^ MC::Block::BLOCK_DESCRIPTION_PREFIX::get()
{
    return clix::marshalString<clix::E_UTF8>(::Block::BLOCK_DESCRIPTION_PREFIX);
}

float MC::Block::SIZE_OFFSET::get()
{
    return ::Block::SIZE_OFFSET;
}

#endif // INCLUDE_MCAPI
