#pragma once
#include <mc/MobEffect.hpp>
#include "Types.hpp"

#pragma make_public(::MobEffect)


namespace MC
{
    public
    ref class MobEffect : ClassTemplate<MobEffect, ::MobEffect>
    {
    public:
        __ctor(MobEffect, ::MobEffect);
        __ctor_default(MobEffect, ::MobEffect);
        enum class EffectType : short
        {
            Empty = 0,
            Speed = 1,
            Slowness = 2,
            Haste = 3,
            MiningFatigue = 4,
            Strength = 5,
            InstantHealth = 6,
            InstantDamage = 7,
            JumpBoost = 8,
            Nausea = 9,
            Regeneration = 10,
            Resistance = 11,
            FireResistance = 12,
            WaterBreathing = 13,
            Invisibility = 14,
            Blindness = 15,
            NightVision = 16,
            Hunger = 17,
            Weakness = 18,
            Poison = 19,
            Wither = 20,
            HealthBoost = 21,
            Absorption = 22,
            Saturation = 23,
            Levitation = 24,
            FatalPoison = 25,
            ConduitPower = 26,
            SlowFalling = 27,
            BadOmen = 28,
            VillageHero = 29,
        };

        ref class FactorCalculationData : ClassTemplate<FactorCalculationData, ::MobEffect::FactorCalculationData>
        {
        public:
            __ctor(FactorCalculationData, ::MobEffect::FactorCalculationData);
            __ctor_default(FactorCalculationData, ::MobEffect::FactorCalculationData);
        };
    };
} // namespace MC
