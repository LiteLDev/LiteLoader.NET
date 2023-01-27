#pragma once
namespace LiteLoader::NET::Interop::OrignalData
{
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

