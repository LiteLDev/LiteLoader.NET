#pragma once
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <variant>

namespace LiteLoader::Hook
{
    private ref class HookHelper __static
    {
    internal:
        generic<typename TDelegate>
        where TDelegate : Delegate
        static TDelegate _hookFunction(IntPtr hmodule, std::variant<void*, gcroot<String^>> addressOrSymbol, TDelegate newFunc);
    };
}