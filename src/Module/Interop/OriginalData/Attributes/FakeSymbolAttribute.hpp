#pragma once
namespace LiteLoader::NET::Interop::OrignalData
{
    using System::AttributeUsageAttribute;
    using System::AttributeTargets;

    [AttributeUsage(AttributeTargets::Method | AttributeTargets::Field | AttributeTargets::Property)]
    public ref class FakeSymbolAttribute :System::Attribute
    {
    public:
        System::String^ fakeSymbol;

        FakeSymbolAttribute(System::String^ fakeSymbol)
            :fakeSymbol(fakeSymbol)
        {
        }
    };
}

