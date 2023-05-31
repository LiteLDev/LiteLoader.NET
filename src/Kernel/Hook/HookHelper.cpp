#include <src/Header/Hook/HookHelper.hpp>

#include <src/Main/PluginOwnData.hpp>
#include <HookAPI.h>

namespace LiteLoader::Hook
{
    generic<typename TDelegate>
    where TDelegate : Delegate
    TDelegate HookHelper::_hookFunction(nint_t hmodule, std::variant<void*, gcroot<String^>> addressOrSymbol, TDelegate newFunc)
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


        LiteLoader::NET::PluginOwnData::AddHookedFunction(hmodule, newFunc, nint_t(address), nint_t(pHook), nint_t(pOriginal));

        GCHandle::Alloc(newFunc);

        return (TDelegate)Marshal::GetDelegateForFunctionPointer<TDelegate>(nint_t(pOriginal));
    }
}