#include <LiteLoader.NET/Header/Hook/HookAPI.hpp>

inline int LLNET::Hook::HookAPI::HookFunction(void* oldfunc, void** poutold, void* newfunc)
{
    return ::HookFunction(oldfunc, poutold, newfunc);
}

inline int LLNET::Hook::HookAPI::HookFunction(System::IntPtr oldfunc, SecondaryRankPtr poutold, System::IntPtr newfunc)
{
    return ::HookFunction(oldfunc.ToPointer(), poutold.ToSecPointer(), newfunc.ToPointer());
}

inline void* LLNET::Hook::HookAPI::dlsym_real(char const* name)
{
    return ::dlsym_real(name);
}

inline System::IntPtr LLNET::Hook::HookAPI::dlsym_real(System::String^ name)
{
    return System::IntPtr(::dlsym_real(marshalString(name).c_str()));
}
