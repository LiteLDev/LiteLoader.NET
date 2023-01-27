#pragma once
namespace LiteLoader::NET::Interop::OrignalData
{
    using System::AttributeUsageAttribute;
    using System::AttributeTargets;

    [AttributeUsage(AttributeTargets::Method | AttributeTargets::Field | AttributeTargets::Property)]
    public ref class SymbolAttribute :System::Attribute
    {
    public:
        System::String^ symbol;

        SymbolAttribute(System::String^ symbol)
            :symbol(symbol)
        {
        }
    };
}

