#pragma once
namespace LiteLoader::NET::Interop::OrignalData
{
    public enum class SymbolType
    {
        Constructor = 1,
        Destructor = 2,
        Operator = 3,
        StaticField = 4,
        Function = 5
    };
}