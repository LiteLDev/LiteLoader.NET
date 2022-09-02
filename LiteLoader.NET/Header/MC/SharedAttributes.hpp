#pragma once
#include "Attribute.hpp"
#include "MC/SharedAttributes.hpp"

namespace MC
{
public
ref class SharedAttributes abstract sealed
{
public:
    static initonly Attribute^ Absorption = gcnew Attribute(const_cast<::Attribute*>(&::SharedAttributes::ABSORPTION));
    static initonly Attribute^ AttackDamage = gcnew Attribute(const_cast<::Attribute*>(&::SharedAttributes::ATTACK_DAMAGE));
    static initonly Attribute^ FollowRange = gcnew Attribute(const_cast<::Attribute*>(&::SharedAttributes::FOLLOW_RANGE));
    static initonly Attribute^ Health = gcnew Attribute(const_cast<::Attribute*>(&::SharedAttributes::HEALTH));
    static initonly Attribute^ JumpStrength = gcnew Attribute(const_cast<::Attribute*>(&::SharedAttributes::JUMP_STRENGTH));
    static initonly Attribute^ KnockbackResistance = gcnew Attribute(const_cast<::Attribute*>(&::SharedAttributes::KNOCKBACK_RESISTANCE));
    static initonly Attribute^ LavaMovementSpeed = gcnew Attribute(const_cast<::Attribute*>(&::SharedAttributes::LAVA_MOVEMENT_SPEED));
    static initonly Attribute^ Luck = gcnew Attribute(const_cast<::Attribute*>(&::SharedAttributes::LUCK));
    static initonly Attribute^ MovementSpeed = gcnew Attribute(const_cast<::Attribute*>(&::SharedAttributes::MOVEMENT_SPEED));
    static initonly Attribute^ UnderwaterMovementSpeed = gcnew Attribute(const_cast<::Attribute*>(&::SharedAttributes::UNDERWATER_MOVEMENT_SPEED));
};
}
