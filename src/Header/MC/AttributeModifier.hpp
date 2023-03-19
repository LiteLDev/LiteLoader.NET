#pragma once
#include <mc/AttributeModifier.hpp>
#include "Types.hpp"

namespace MC
{
    public enum class AttributeModifierOperation
    {
        Add,
        MultiplyBase,
        MultiplyTotal,
        Cap,
        Invalid
    };

    public enum class AttributeOperands
    {
        Min,
        Max,
        Current,
        Invalid
    };

    public ref class AttributeModifier : ClassTemplate<AttributeModifier, ::AttributeModifier>,
                                         System::IEquatable<AttributeModifier^>
    {
    public:
        __ctor(AttributeModifier, ::AttributeModifier);

        AttributeModifier();
        AttributeModifier(Mce::UUID id, String^ name, float amount, AttributeModifierOperation operation,
                          AttributeOperands operand, bool isSerializable);

        property Mce::UUID Id { Mce::UUID get(); void set(Mce::UUID value); }
        property String^ Name { String^ get(); void set(String^ value); }
        property float Amount { float get(); void set(float value); }
        property AttributeModifierOperation Operation
        {
            AttributeModifierOperation get(); void set(AttributeModifierOperation value);
        }
        property AttributeOperands Operand { AttributeOperands get(); void set(AttributeOperands value); }
        property bool IsSerializable { bool get(); void set(bool value); }

        virtual bool Equals(AttributeModifier^ other);
        bool Equals(Object^ other) override;
    };
} // namespace MC
