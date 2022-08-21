#include <LiteLoader.NET/Header/MC/AttributeInstance.hpp>

namespace MC
{
    AttributeInstance::AttributeInstance(AttributeInstance^ attr)
    {
        NativePtr = new ::AttributeInstance(*attr->NativePtr);
    }

    AttributeInstance::AttributeInstance()
    {
        NativePtr = new ::AttributeInstance();
    }

    Attribute^ AttributeInstance::Attribute::get()
    {
        return gcnew MC::Attribute(const_cast<::Attribute*>(NativePtr->getAttribute()));
    }

    float AttributeInstance::CurrentValue::get()
    {
        return NativePtr->getCurrentValue();
    }

    void AttributeInstance::CurrentValue::set(float value)
    {
        NativePtr->setCurrentValue(value);
    }

    float AttributeInstance::MaxValue::get()
    {
        return NativePtr->getMaxValue();
    }

    void AttributeInstance::MaxValue::set(float value)
    {
        NativePtr->setMaxValue(value);
    }

    float AttributeInstance::MinValue::get()
    {
        return NativePtr->getMinValue();
    }

    bool AttributeInstance::IsValid::get()
    {
        return NativePtr->isValid();
    }

    bool AttributeInstance::HasModifiers::get()
    {
        return NativePtr->hasModifiers();
    }

    bool AttributeInstance::HasTemporalBuffs::get()
    {
        return NativePtr->hasTemporalBuffs();
    }

    float AttributeInstance::GetDefaultValue(ValueType type)
    {
        return NativePtr->getDefaultValue(static_cast<int>(type));
    }

    bool AttributeInstance::HasModifier(Mce::UUID^ uuid)
    {
        return NativePtr->hasModifier(uuid);
    }

    void AttributeInstance::Notify(long long _0)
    {
        NativePtr->notify(_0);
    }

    void AttributeInstance::RecalculateModifiers()
    {
        NativePtr->recalculateModifiers();
    }

    void AttributeInstance::RegisterListener(AttributeInstance^ attr)
    {
        NativePtr->registerListener(attr);
    }

    void AttributeInstance::RemoveBuffs()
    {
        NativePtr->removeBuffs();
    }

    bool AttributeInstance::RemoveModifier(Mce::UUID^ uuid)
    {
        return NativePtr->removeModifier(uuid);
    }

    void AttributeInstance::RemoveModifiers()
    {
        NativePtr->removeModifiers();
    }

    void AttributeInstance::ResetToDefaultValue()
    {
        NativePtr->resetToDefaultValue();
    }

    void AttributeInstance::ResetToMaxValue()
    {
        NativePtr->resetToMaxValue();
    }

    void AttributeInstance::ResetToMinValue()
    {
        NativePtr->resetToMinValue();
    }

    void AttributeInstance::SerializationSetRange(float _0, float _1, float _2)
    {
        NativePtr->serializationSetRange(_0, _1, _2);
    }

    void AttributeInstance::SerializationSetValue(float _0, ValueType type, float _2)
    {
        NativePtr->serializationSetValue(_0, static_cast<int>(type), _2);
    }

    void AttributeInstance::SetDefaultValue(float value, ValueType type)
    {
        NativePtr->setDefaultValue(value, static_cast<int>(type));
    }

    void AttributeInstance::SetDefaultValueOnly(float value)
    {
        NativePtr->setDefaultValueOnly(value);
    }

    void AttributeInstance::SetRange(float _0, float _1, float _2)
    {
        NativePtr->setRange(_0, _1, _2);
    }
}
