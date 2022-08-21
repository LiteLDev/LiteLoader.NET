#pragma once
#include <MC/AttributeInstance.hpp>
#include <LiteLoader.NET/Header/MC/Attribute.hpp>
#include "Types.hpp"

namespace MC
{
    public ref class AttributeInstance : ClassTemplate<AttributeInstance, ::AttributeInstance>
    {
    public:
        __ctor(AttributeInstance, ::AttributeInstance);

        AttributeInstance(AttributeInstance^ attr);
        AttributeInstance();

        enum class ValueType
        {
            Min,
            Max,
            Current
        };

        property Attribute^ Attribute { MC::Attribute^ get(); }
        property float CurrentValue { float get(); void set(float value); }
        property float MaxValue { float get(); void set(float value); }
        property float MinValue { float get(); }
        property bool IsValid { bool get(); }
        property bool HasModifiers { bool get(); }
        property bool HasTemporalBuffs { bool get(); }

        //void AddBuff(AttributeBuff^);
        //void AddModifier(AttributeModifier^);
        //List<TemporalAttributeBuff^>^ GetBuffs();
        float GetDefaultValue(ValueType type);
        //AttributeInstanceHandle^ GetHandle();
        //List<AttributeInstanceHandle>^ GetListeners();
        //AttributeModifier^ GetModifier(Mce::UUID^);
        //List<AttributeModifier^>^ GetModifiers();
        bool HasModifier(Mce::UUID^ uuid);
        //bool HasModifier(AttributeModifier^);
        //void InheritFrom(AttributeInstance^, BaseAttributeMap^);
        void Notify(long long _0);
        void RecalculateModifiers();
        void RegisterListener(AttributeInstance^ attr);
        //void RemoveBuff(AttributeBuff^);
        //void RemoveBuff(AttributeBuff^);
        void RemoveBuffs();
        //void RemoveModifier(AttributeModifier^);
        //void RemoveModifier(AttributeModifier^);
        bool RemoveModifier(Mce::UUID^ uuid);
        void RemoveModifiers();
        void ResetToDefaultValue();
        void ResetToMaxValue();
        void ResetToMinValue();
        void SerializationSetRange(float _0, float _1, float _2);
        void SerializationSetValue(float _0, ValueType type, float _2);
        void SetDefaultValue(float value, ValueType type);
        void SetDefaultValueOnly(float value);
        //void SetDelegate(AttributeInstanceDelegate^);
        void SetRange(float _0, float _1, float _2);
        //void UpdateModifier(AttributeModifier^);
    };
} // namespace MC
