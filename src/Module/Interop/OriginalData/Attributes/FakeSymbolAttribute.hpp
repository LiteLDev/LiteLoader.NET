#pragma once
namespace LiteLoader::NET::Interop::OrignalData
{
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

