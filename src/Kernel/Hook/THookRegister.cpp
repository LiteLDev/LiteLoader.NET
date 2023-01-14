#pragma once
#include <src/Header/Hook/THookRegister.hpp>

namespace LiteLoader::Hook
{
    inline THookRegister::THookRegister(nint_t address, nint_t hook, SecondaryRankPtr org)
    {
        ::THookRegister(address.ToPointer(), hook.ToPointer(), (void**)org);
    }

    inline THookRegister::THookRegister(void* address, void* hook, void** org)
    {
        ::THookRegister(address, hook, org);
    }

    inline THookRegister::THookRegister(System::String^ sym, nint_t hook, SecondaryRankPtr org)
    {
        ::THookRegister(marshalString(sym).c_str(), hook.ToPointer(), (void**)org);
    }

    inline THookRegister::THookRegister(char const* sym, void* hook, void** org)
    {
        ::THookRegister(sym, hook, org);
    }
}