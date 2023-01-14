#pragma once
#include <src/Main/DotNETGlobal.hpp>
#include <variant>

namespace LiteLoader::Hook
{
    private ref class HookHelper __static
    {
    internal:
        generic<typename TDelegate>
        where TDelegate : Delegate
        static TDelegate _hookFunction(nint_t hmodule, std::variant<void*, gcroot<String^>> addressOrSymbol, TDelegate newFunc);
    };
}