#pragma once

#include <LiteLoader.NET/Main/DotNETGlobal.hpp>

namespace LiteLoader::Hook
{
    [System::AttributeUsageAttribute(System::AttributeTargets::Class)]
    public ref class HookSymbolAttribute :public System::Attribute
    {
    public:
                              
        property String^ Sym;

        property String^ Sig;

        property void* Add;

        HookSymbolAttribute(String^ symbol_or_signature);
        HookSymbolAttribute(intptr_t add);
    };
}