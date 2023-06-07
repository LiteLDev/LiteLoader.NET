#include <src/Header/MC/ItemStackBase.hpp>
namespace MC
{
int ItemStackBase::Count::get()
{
    return NativePtr->getCount();
}
#ifndef INCLUDE_MCAPI
short MC::ItemStackBase::Id::get()
{
    auto __ret = NativePtr->getId();
    return __ret;
}
#endif // INCLUDE_MCAPI


} // namespace MC


#ifdef MANUAL_MAINTENANCE

#include <src/Header/MC/HashedString.hpp>

void MC::ItemStackBase::SetNull()
{
    NativePtr->setNull({});
}

::String^ MC::ItemStackBase::ToString()
{
    auto __ret = NativePtr->toString();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

::String^ MC::ItemStackBase::ToDebugString()
{
    auto __ret = NativePtr->toDebugString();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

void MC::ItemStackBase::Add(int _0)
{
    NativePtr->add(_0);
}

bool MC::ItemStackBase::CanBeCharged()
{
    auto __ret = NativePtr->canBeCharged();
    return __ret;
}

void MC::ItemStackBase::ClearChargedItem()
{
    NativePtr->clearChargedItem();
}

bool MC::ItemStackBase::ComponentsMatch(MC::ItemStackBase ^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::ItemStackBase*)_0->NativePtr;
    auto __ret = NativePtr->componentsMatch(__arg0);
    return __ret;
}

bool MC::ItemStackBase::HasSameAuxValue(MC::ItemStackBase ^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::ItemStackBase*)_0->NativePtr;
    auto __ret = NativePtr->hasSameAuxValue(__arg0);
    return __ret;
}

bool MC::ItemStackBase::HasSameUserData(MC::ItemStackBase ^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::ItemStackBase*)_0->NativePtr;
    auto __ret = NativePtr->hasSameUserData(__arg0);
    return __ret;
}

bool MC::ItemStackBase::HasTag(unsigned long long _0)
{
    auto __arg0 = (const unsigned long long&)_0;
    auto __ret = NativePtr->hasTag(__arg0);
    return __ret;
}

/*bool MC::ItemStackBase::IsOneOfInstances(::System::Collections::Generic::List<MC::HashedString^>^ _0, bool _1)
{
    auto _tmp_0 = std::vector<::HashedString>();
    for each (MC::HashedString ^ _element in _0)
    {
        if (ReferenceEquals(_element, nullptr))
            throw gcnew ::System::ArgumentNullException("_element", "Cannot be null because it is passed by value.");
        auto _marshalElement = *(class ::HashedString*)_element->NativePtr;
        _tmp_0.push_back(_marshalElement);
    }
    auto __arg0 = _tmp_0;
    auto __ret = NativePtr->isOneOfInstances(__arg0, _1);
    return __ret;
}*/

bool MC::ItemStackBase::IsStackable(MC::ItemStackBase ^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::ItemStackBase*)_0->NativePtr;
    auto __ret = NativePtr->isStackable(__arg0);
    return __ret;
}

bool MC::ItemStackBase::IsValidAuxValue(int _0)
{
    auto __ret = NativePtr->isValidAuxValue(_0);
    return __ret;
}

bool MC::ItemStackBase::Matches(MC::ItemStackBase ^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::ItemStackBase*)_0->NativePtr;
    auto __ret = NativePtr->matches(__arg0);
    return __ret;
}

bool MC::ItemStackBase::MatchesItem(MC::ItemStackBase ^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::ItemStackBase*)_0->NativePtr;
    auto __ret = NativePtr->matchesItem(__arg0);
    return __ret;
}

MC::ItemStackBase::operator bool(MC::ItemStackBase ^ __op)
{
    if (ReferenceEquals(__op, nullptr))
        throw gcnew ::System::ArgumentNullException("__op", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::ItemStackBase*)__op->NativePtr;
    auto __ret = (bool)__arg0;
    return __ret;
}

bool MC::ItemStackBase::operator!=(MC::ItemStackBase ^ __op, MC::ItemStackBase ^ _0)
{
    bool __opNull = ReferenceEquals(__op, nullptr);
    bool _0Null = ReferenceEquals(_0, nullptr);
    if (__opNull || _0Null)
        return !(__opNull && _0Null);
    auto& __arg0 = *(class ::ItemStackBase*)__op->NativePtr;
    auto& __arg1 = *(class ::ItemStackBase*)_0->NativePtr;
    auto __ret = __arg0 != __arg1;
    return __ret;
}

bool MC::ItemStackBase::operator==(MC::ItemStackBase ^ __op, MC::ItemStackBase ^ _0)
{
    bool __opNull = ReferenceEquals(__op, nullptr);
    bool _0Null = ReferenceEquals(_0, nullptr);
    if (__opNull || _0Null)
        return __opNull && _0Null;
    auto& __arg0 = *(class ::ItemStackBase*)__op->NativePtr;
    auto& __arg1 = *(class ::ItemStackBase*)_0->NativePtr;
    auto __ret = __arg0 == __arg1;
    return __ret;
}

bool MC::ItemStackBase::Equals(::System::Object ^ obj)
{
    return this == safe_cast<MC::ItemStackBase ^>(obj);
}

void MC::ItemStackBase::Remove(int _0)
{
    NativePtr->remove(_0);
}

void MC::ItemStackBase::ResetHoverName()
{
    NativePtr->resetHoverName();
}

bool MC::ItemStackBase::SameItem(int _0, int _1)
{
    auto __ret = NativePtr->sameItem(_0, _1);
    return __ret;
}

//bool MC::ItemStackBase::SameItem(MC::ItemStackBase ^ _0)
//{
//    if (ReferenceEquals(_0, nullptr))
//        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
//    auto& __arg0 = *(class ::ItemStackBase*)_0->NativePtr;
//    auto __ret = NativePtr->sameItem(__arg0);
//    return __ret;
//}

bool MC::ItemStackBase::SameItemAndAux(MC::ItemStackBase ^ _0)
{
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::ItemStackBase*)_0->NativePtr;
    auto __ret = NativePtr->sameItemAndAux(__arg0);
    return __ret;
}

void MC::ItemStackBase::Set(int _0)
{
    NativePtr->set(_0);
}

void MC::ItemStackBase::SetCustomLore(::System::Collections::Generic::IList<::String^> ^ _0)
{
    auto _tmp_0 = std::vector<::std::string>();
    for each (::String^ _element in _0)
    {
        auto _marshalElement = clix::marshalString<clix::E_UTF8>(_element);
        _tmp_0.push_back(_marshalElement);
    }
    auto __arg0 = _tmp_0;
    NativePtr->setCustomLore(__arg0);
}

void MC::ItemStackBase::SetJustBrewed(bool _0)
{
    NativePtr->setJustBrewed(_0);
}

void MC::ItemStackBase::SetPickupTime()
{
    NativePtr->setPickupTime();
}

void MC::ItemStackBase::SetRepairCost(int _0)
{
    NativePtr->setRepairCost(_0);
}

bool MC::ItemStackBase::ShouldVanish()
{
    auto __ret = NativePtr->shouldVanish();
    return __ret;
}

//bool MC::ItemStackBase::IsValidComponent(::String^ _0)
//{
//    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
//    auto __ret = ::ItemStackBase::isValidComponent(__arg0);
//    return __ret;
//}

int MC::ItemStackBase::AttackDamage::get()
{
    auto __ret = NativePtr->getAttackDamage();
    return __ret;
}

short MC::ItemStackBase::AuxValue::get()
{
    auto __ret = NativePtr->getAuxValue();
    return __ret;
}

void MC::ItemStackBase::AuxValue::set(short _0)
{
    NativePtr->setAuxValue(_0);
}

int MC::ItemStackBase::BaseRepairCost::get()
{
    auto __ret = NativePtr->getBaseRepairCost();
    return __ret;
}

MC::Mce::Color MC::ItemStackBase::Color::get()
{
    return NativePtr->getColor();
}

::String^ MC::ItemStackBase::CustomName::get()
{
    auto __ret = NativePtr->getCustomName();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

void MC::ItemStackBase::CustomName::set(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    NativePtr->setCustomName(__arg0);
}

short MC::ItemStackBase::DamageValue::get()
{
    auto __ret = NativePtr->getDamageValue();
    return __ret;
}

void MC::ItemStackBase::DamageValue::set(short _0)
{
    NativePtr->setDamageValue(_0);
}

::String^ MC::ItemStackBase::DescriptionId::get()
{
    auto __ret = NativePtr->getDescriptionId();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

::String^ MC::ItemStackBase::EffectName::get()
{
    auto __ret = NativePtr->getEffectName();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

int MC::ItemStackBase::EnchantValue::get()
{
    auto __ret = NativePtr->getEnchantValue();
    return __ret;
}

::String^ MC::ItemStackBase::HoverName::get()
{
    auto __ret = NativePtr->getHoverName();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

int MC::ItemStackBase::IdAux::get()
{
    auto __ret = NativePtr->getIdAux();
    return __ret;
}

short MC::ItemStackBase::MaxDamage::get()
{
    auto __ret = NativePtr->getMaxDamage();
    return __ret;
}

unsigned char MC::ItemStackBase::MaxStackSize::get()
{
    auto __ret = NativePtr->getMaxStackSize();
    return __ret;
}

::String^ MC::ItemStackBase::Name::get()
{
    auto __ret = NativePtr->getName();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

::String^ MC::ItemStackBase::RawNameId::get()
{
    auto __ret = NativePtr->getRawNameId();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

bool MC::ItemStackBase::WasPickedUp::get()
{
    auto __ret = NativePtr->getWasPickedUp();
    return __ret;
}

void MC::ItemStackBase::WasPickedUp::set(bool _0)
{
    NativePtr->setWasPickedUp(_0);
}

bool MC::ItemStackBase::HasChargedItem::get()
{
    auto __ret = NativePtr->hasChargedItem();
    return __ret;
}

bool MC::ItemStackBase::HasCompoundTextUserData::get()
{
    auto __ret = NativePtr->hasCompoundTextUserData();
    return __ret;
}

bool MC::ItemStackBase::HasCustomHoverName::get()
{
    auto __ret = NativePtr->hasCustomHoverName();
    return __ret;
}

bool MC::ItemStackBase::HasUserData::get()
{
    auto __ret = NativePtr->hasUserData();
    return __ret;
}

bool MC::ItemStackBase::IsArmorItem::get()
{
    auto __ret = NativePtr->isArmorItem();
    return __ret;
}

bool MC::ItemStackBase::IsBlock::get()
{
    auto __ret = NativePtr->isBlock();
    return __ret;
}

bool MC::ItemStackBase::IsDamageableItem::get()
{
    auto __ret = NativePtr->isDamageableItem();
    return __ret;
}

bool MC::ItemStackBase::IsDamaged::get()
{
    auto __ret = NativePtr->isDamaged();
    return __ret;
}

bool MC::ItemStackBase::IsEnchanted::get()
{
    auto __ret = NativePtr->isEnchanted();
    return __ret;
}

bool MC::ItemStackBase::IsEnchantingBook::get()
{
    auto __ret = NativePtr->isEnchantingBook();
    return __ret;
}

bool MC::ItemStackBase::IsExplodable::get()
{
    auto __ret = NativePtr->isExplodable();
    return __ret;
}

bool MC::ItemStackBase::IsFireResistant::get()
{
    auto __ret = NativePtr->isFireResistant();
    return __ret;
}

bool MC::ItemStackBase::IsFullStack::get()
{
    auto __ret = NativePtr->isFullStack();
    return __ret;
}

bool MC::ItemStackBase::IsGlint::get()
{
    auto __ret = NativePtr->isGlint();
    return __ret;
}

bool MC::ItemStackBase::IsHorseArmorItem::get()
{
    auto __ret = NativePtr->isHorseArmorItem();
    return __ret;
}

bool MC::ItemStackBase::IsLiquidClipItem::get()
{
    auto __ret = NativePtr->isLiquidClipItem();
    return __ret;
}

bool MC::ItemStackBase::IsNull::get()
{
    auto __ret = NativePtr->isNull();
    return __ret;
}

bool MC::ItemStackBase::IsOffhandItem::get()
{
    auto __ret = NativePtr->isOffhandItem();
    return __ret;
}

bool MC::ItemStackBase::IsPattern::get()
{
    auto __ret = NativePtr->isPattern();
    return __ret;
}

bool MC::ItemStackBase::IsPotionItem::get()
{
    auto __ret = NativePtr->isPotionItem();
    return __ret;
}

bool MC::ItemStackBase::IsStackedByData::get()
{
    auto __ret = NativePtr->isStackedByData();
    return __ret;
}

bool MC::ItemStackBase::IsWearableItem::get()
{
    auto __ret = NativePtr->isWearableItem();
    return __ret;
}

::String^ MC::ItemStackBase::TAG_CAN_DESTROY::get()
{
    return clix::marshalString<clix::E_UTF8>(::ItemStackBase::TAG_CAN_DESTROY);
}

::String^ MC::ItemStackBase::TAG_CAN_PLACE_ON::get()
{
    return clix::marshalString<clix::E_UTF8>(::ItemStackBase::TAG_CAN_PLACE_ON);
}

::String^ MC::ItemStackBase::TAG_DISPLAY::get()
{
    return clix::marshalString<clix::E_UTF8>(::ItemStackBase::TAG_DISPLAY);
}

::String^ MC::ItemStackBase::TAG_DISPLAY_NAME::get()
{
    return clix::marshalString<clix::E_UTF8>(::ItemStackBase::TAG_DISPLAY_NAME);
}

::String^ MC::ItemStackBase::TAG_ENCHANTS::get()
{
    return clix::marshalString<clix::E_UTF8>(::ItemStackBase::TAG_ENCHANTS);
}

::String^ MC::ItemStackBase::TAG_LORE::get()
{
    return clix::marshalString<clix::E_UTF8>(::ItemStackBase::TAG_LORE);
}

::String^ MC::ItemStackBase::TAG_REPAIR_COST::get()
{
    return clix::marshalString<clix::E_UTF8>(::ItemStackBase::TAG_REPAIR_COST);
}

#endif // INCLUDE_MCAPI
