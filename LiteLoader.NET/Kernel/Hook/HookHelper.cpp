#include <LiteLoader.NET/Header/Hook/HookHelper.hpp>

#include <LiteLoader.NET/Main/PluginOwnData.hpp>
#include <HookAPI.h>

namespace LiteLoader::Hook
{
    generic<typename TDelegate>
    where TDelegate : Delegate
    TDelegate HookHelper::_hookFunction(IntPtr hmodule, std::variant<void*, gcroot<String^>> addressOrSymbol, TDelegate newFunc)
    {
        NULL_ARG_CHECK(newFunc);

        void* address = nullptr;
        String^ symbol = nullptr;
        bool isAddress = false;

        if (std::holds_alternative<void*>(addressOrSymbol))
        {
            address = std::get<void*>(addressOrSymbol);

            if (address == nullptr)
                throw gcnew System::ArgumentNullException("address", "Cannot be null");

            isAddress = true;
        }
        else
        {
            symbol = static_cast<String^>(std::get<gcroot<String^>>(addressOrSymbol));

            if (symbol == nullptr)
                throw gcnew System::ArgumentNullException("symbol", "Cannot be null");
        }

        GC::KeepAlive(newFunc);
        GCHandle::Alloc(newFunc);

        auto pHook = Marshal::GetFunctionPointerForDelegate(newFunc).ToPointer();

        void* pOriginal = nullptr;

        if (isAddress)
        {
            ::THookRegister(address, pHook, (void**)&pOriginal);
        }
        else
        {
            ::THookRegister(marshalString(symbol).c_str(), pHook, (void**)&pOriginal);
        }

        if (pOriginal == nullptr)
            throw gcnew LiteLoader::NET::HookFailedException;


        LiteLoader::NET::PluginOwnData::AddHookedFunction(hmodule, newFunc, IntPtr(address), IntPtr(pHook), IntPtr(pOriginal));

        return (TDelegate)Marshal::GetDelegateForFunctionPointer<TDelegate>(IntPtr(pOriginal));
    }
}