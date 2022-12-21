#include <LiteLoader.NET/Header/Hook/HookAPI.hpp>

inline int LiteLoader::Hook::HookAPI::HookFunction(void* oldfunc, void** poutold, void* newfunc)
{
    return ::HookFunction(oldfunc, poutold, newfunc);
}

inline int LiteLoader::Hook::HookAPI::HookFunction(System::IntPtr oldfunc, LiteLoader::NET::SecondaryRankPtr poutold, System::IntPtr newfunc)
{
    return ::HookFunction(oldfunc.ToPointer(), poutold.ToSecPointer(), newfunc.ToPointer());
}

inline void* LiteLoader::Hook::HookAPI::dlsym_real(char const* name)
{
    return ::dlsym_real(name);
}

inline System::IntPtr LiteLoader::Hook::HookAPI::dlsym_real(System::String^ name)
{
    return System::IntPtr(::dlsym_real(marshalString(name).c_str()));
}

inline uintptr_t LiteLoader::Hook::HookAPI::findSig(String^ szSignature)
{
    return ll::hook::findSig(marshalString(szSignature).c_str());
}
