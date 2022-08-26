#pragma once
#include <MC/AttributeInstance.hpp>
#include <LiteLoader.NET/Header/MC/Attribute.hpp>
#include <LiteLoader.NET/Header/MC/AttributeModifier.hpp>
#include "Types.hpp"

namespace MC
{
    enum class AttributeValueType
    {
        Min,
        Max,
        Current
    };

    public ref class AttributeInstance : ClassTemplate<AttributeInstance, ::AttributeInstance>
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
        List<AttributeModifier^>^ GetModifiers();
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
        void SerializationSetValue(float value, AttributeValueType type, float defaultValue);
        void SetDefaultValue(float value, AttributeValueType type);
        void SetDefaultValueOnly(float value);
        //void SetDelegate(AttributeInstanceDelegate^);
        void SetRange(float min, float current, float max);
        void UpdateModifier(AttributeModifier^ modifier);
        static bool operator ==(AttributeInstance^ obj1, AttributeInstance^ obj2);
    };
} // namespace MC
