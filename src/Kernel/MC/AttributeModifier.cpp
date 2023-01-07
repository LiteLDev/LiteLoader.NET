#include "src/Header/MC/AttributeModifier.hpp"

namespace MC
{
    AttributeModifier::AttributeModifier()
    {
        NativePtr = new ::AttributeModifier();
        OwnsNativeInstance = true;
    }

    AttributeModifier::AttributeModifier(AttributeModifier^ other)
    {
        NativePtr = new ::AttributeModifier(*other->NativePtr);
        OwnsNativeInstance = true;
    }

    AttributeModifier::AttributeModifier(Mce::UUID id, String^ name, float amount, AttributeModifierOperation operation,
                                         AttributeOperands operand, bool isSerializable)
    {
        NativePtr = new ::AttributeModifier(id, marshalString(name), amount,
                                            static_cast<::AttributeModifierOperation>(operation),
                                            static_cast<::AttributeOperands>(operand), isSerializable);
        OwnsNativeInstance = true;
    }

    Mce::UUID AttributeModifier::Id::get()
    {
        return NativePtr->mId;
    }

    void AttributeModifier::Id::set(Mce::UUID value)
    {
        NativePtr->mId = value;
    }

    String^ AttributeModifier::Name::get()
    {
        return marshalString(NativePtr->mName);
    }

    void AttributeModifier::Name::set(String^ value)
    {
        NativePtr->mName = marshalString(value);
    }

    float AttributeModifier::Amount::get()
    {
        return NativePtr->mAmount;
    }

    void AttributeModifier::Amount::set(float value)
    {
        NativePtr->mAmount = value;
    }

    AttributeModifierOperation AttributeModifier::Operation::get()
    {
        return static_cast<AttributeModifierOperation>(NativePtr->mOperation);
    }

    void AttributeModifier::Operation::set(AttributeModifierOperation value)
    {
        NativePtr->mOperation = static_cast<::AttributeModifierOperation>(value);
    }

    AttributeOperands AttributeModifier::Operand::get()
    {
        return static_cast<AttributeOperands>(NativePtr->mOperation);
    }

    void AttributeModifier::Operand::set(AttributeOperands value)
    {
        NativePtr->mOperand = static_cast<::AttributeOperands>(value);
    }

    bool AttributeModifier::IsSerializable::get()
    {
        return NativePtr->mSerialize;
    }

    void AttributeModifier::IsSerializable::set(bool value)
    {
        NativePtr->mSerialize = value;
    }

    bool AttributeModifier::Equals(AttributeModifier^ other)
    {
        return NativePtr == other->NativePtr;
    }

    bool AttributeModifier::Equals(Object^ other)
    {
        AttributeModifier^ otherModifier = dynamic_cast<AttributeModifier^>(other);
        return otherModifier != nullptr && Equals(otherModifier);
    }
}
