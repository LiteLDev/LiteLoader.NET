#pragma once
#include <HookAPI.h>
#include <src/Main/DotNETGlobal.hpp>
#include <src/Header/Core/SecondaryRankPtr.hpp>

namespace LiteLoader::Hook
{
    using LiteLoader::NET::SecondaryRankPtr;

    public ref class THookRegister
    {
        THookRegister(nint_t address, nint_t hook, SecondaryRankPtr org);

        THookRegister(void* address, void* hook, void** org);

        THookRegister(System::String^ sym, nint_t hook, SecondaryRankPtr org);

        THookRegister(char const* sym, void* hook, void** org);
    };

}
