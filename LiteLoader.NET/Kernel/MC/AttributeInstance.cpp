#include <LiteLoader.NET/Header/MC/AttributeInstance.hpp>

namespace MC
{
    AttributeInstance::AttributeInstance(AttributeInstance^ attr)
    {
        OwnsNativeInstance = true;
        NativePtr = new ::AttributeInstance(*attr->NativePtr);
    }

    AttributeInstance::AttributeInstance()
    {
        OwnsNativeInstance = true;
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

    void AttributeInstance::AddModifier(AttributeModifier^ modifier)
    {
        NativePtr->addModifier(modifier);
    }

    float AttributeInstance::GetDefaultValue(AttributeValueType type)
    {
        return NativePtr->getDefaultValue(static_cast<int>(type));
    }

    AttributeModifier^ AttributeInstance::GetModifier(Mce::UUID id)
    {
        return gcnew AttributeModifier(&NativePtr->getModifier(id));
    }

    List<AttributeModifier^>^ AttributeInstance::GetModifiers()
    {
        auto modifiers = NativePtr->getModifiers();
        auto result = gcnew List<AttributeModifier^>();

        for (auto modifier : modifiers)
        {
            result->Add(gcnew AttributeModifier(&modifier));
        }

        return result;
    }

    bool AttributeInstance::HasModifier(AttributeModifier^ modifier)
    {
        for (auto temp :NativePtr->getModifiers())
        {
            if (temp == *modifier->NativePtr)
                return true;
        }

        return false;
    }

    bool AttributeInstance::HasModifier(Mce::UUID id)
    {
        return NativePtr->hasModifier(id);
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

    void AttributeInstance::RemoveModifier(AttributeModifier^ modifier)
    {
        NativePtr->removeModifier(modifier);
    }

    bool AttributeInstance::RemoveModifier(Mce::UUID id)
    {
        return NativePtr->removeModifier(id);
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

    void AttributeInstance::SerializationSetRange(float min, float defaultCurrent, float max)
    {
        NativePtr->serializationSetRange(min, defaultCurrent, max);
    }

    void AttributeInstance::SerializationSetValue(float value, AttributeValueType type, float limit)
    {
        NativePtr->serializationSetValue(value, static_cast<int>(type), limit);
    }

    void AttributeInstance::SetDefaultValue(float value, AttributeValueType type)
    {
        NativePtr->setDefaultValue(value, static_cast<int>(type));
    }

    void AttributeInstance::SetDefaultValueOnly(float value)
    {
        NativePtr->setDefaultValueOnly(value);
    }

    void AttributeInstance::SetRange(float min, float current, float max)
    {
        NativePtr->setRange(min, current, max);
    }

    void AttributeInstance::UpdateModifier(AttributeModifier^ modifier)
    {
        NativePtr->updateModifier(modifier);
    }

    bool AttributeInstance::Equals(AttributeInstance^ other)
    {
        return NativePtr == other->NativePtr;
    }

    bool AttributeInstance::Equals(Object^ other)
    {
        AttributeInstance^ otherModifier = dynamic_cast<AttributeInstance^>(other);
        return otherModifier != nullptr && Equals(otherModifier);
    }
}
