#pragma once
#include <src/Module/Interop/OriginalData/Enums/SymbolType.hpp>

namespace LiteLoader::NET::Interop::OrignalData
{
    ref class SymbolTypeAttribute :System::Attribute
    {
    public:
        SymbolType symbolType;

        SymbolTypeAttribute(SymbolType symbolType)
            :symbolType(symbolType)
        {
        }
    };
}

