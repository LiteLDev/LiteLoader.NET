#pragma once
#include <mc/AttributeInstance.hpp>
#include <src/Header/MC/Attribute.hpp>
#include <src/Header/MC/AttributeModifier.hpp>
#include "Types.hpp"

namespace MC
{
    public enum class AttributeValueType
    {
        Min,
        Max,
        Current
    };

    public ref class AttributeInstance : ClassTemplate<AttributeInstance, ::AttributeInstance>,
                                         System::IEquatable<AttributeInstance^>
    {
    public:
        __ctor(AttributeInstance, ::AttributeInstance);

        AttributeInstance(AttributeInstance^ attr);
        AttributeInstance();

        property Attribute^ Attribute { MC::Attribute^ get(); }
        property float CurrentValue { float get(); void set(float value); }
        property float MaxValue { float get(); void set(float value); }
        property float MinValue { float get(); }
        property bool IsValid { bool get(); }
        property bool HasModifiers { bool get(); }
        property bool HasTemporalBuffs { bool get(); }

        //void AddBuff(AttributeBuff^);
        void AddModifier(AttributeModifier^ modifier);
        //List<TemporalAttributeBuff^>^ GetBuffs();
        float GetDefaultValue(AttributeValueType type);
        //AttributeInstanceHandle^ GetHandle();
        //List<AttributeInstanceHandle>^ GetListeners();
        AttributeModifier^ GetModifier(Mce::UUID id);
        array<AttributeModifier^>^ GetModifiers();
        bool HasModifier(AttributeModifier^ modifier);
        bool HasModifier(Mce::UUID id);
        //void InheritFrom(AttributeInstance^, BaseAttributeMap^);
        void Notify(long long _0);
        void RecalculateModifiers();
        void RegisterListener(AttributeInstance^ attr);
        //void RemoveBuff(AttributeBuff^);
        //void RemoveBuff(AttributeBuff^);
        void RemoveBuffs();
        void RemoveModifier(AttributeModifier^ modifier);
        bool RemoveModifier(Mce::UUID id);
        void RemoveModifiers();
        void ResetToDefaultValue();
        void ResetToMaxValue();
        void ResetToMinValue();
        void SerializationSetRange(float min, float defaultCurrent, float max);
        void SerializationSetValue(float value, AttributeValueType type, float limit);
        void SetDefaultValue(float value, AttributeValueType type);
        void SetDefaultValueOnly(float value);
        //void SetDelegate(AttributeInstanceDelegate^);
        void SetRange(float min, float current, float max);
        void UpdateModifier(AttributeModifier^ modifier);
        virtual bool Equals(AttributeInstance^ other);
        bool Equals(Object^ other) override;
    };
} // namespace MC
