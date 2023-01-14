#include <src/Header/Hook/HookAPI.hpp>

inline int LiteLoader::Hook::HookAPI::HookFunction(void* oldfunc, void** poutold, void* newfunc)
{
    return ::HookFunction(oldfunc, poutold, newfunc);
}

inline int LiteLoader::Hook::HookAPI::HookFunction(nint_t oldfunc, LiteLoader::NET::SecondaryRankPtr poutold, nint_t newfunc)
{
    return ::HookFunction(oldfunc.ToPointer(), poutold.ToSecPointer(), newfunc.ToPointer());
}

inline void* LiteLoader::Hook::HookAPI::dlsym_real(char const* name)
{
    return ::dlsym_real(name);
}

inline nint_t LiteLoader::Hook::HookAPI::dlsym_real(System::String^ name)
{
    return nint_t(::dlsym_real(marshalString(name).c_str()));
}

inline uintptr_t LiteLoader::Hook::HookAPI::findSig(String^ szSignature)
{
    return ll::hook::findSig(marshalString(szSignature).c_str());
}
