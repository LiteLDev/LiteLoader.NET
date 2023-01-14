#include "RemoteCallAPI.hpp"

#include <src/Main/PluginOwnData.hpp>
#include "Helpers/EmitHelper.hpp"

namespace LiteLoader::RemoteCall
{
    using namespace LiteLoader::RemoteCall::Helper;

    generic<typename TDelegate> where TDelegate: Delegate
        TDelegate RemoteCallAPI::ImportAs(String^ nameSpace, String^ funcName)
    {
        auto funcInfo = TypeHelper::GenerateFunctionInfo(typeof(TDelegate)->GetMethod("Invoke"));

        auto ilBulider = gcnew EmitHelper::ILCodeBulider(
            nameSpace, funcName, funcInfo, EmitHelper::ILCodeBulider::BuliderType::Import, typeof(TDelegate));

        Object^ temp = nullptr;

        if (ilBulider->Build(nullptr, temp))
        {
            auto funcInstance = As<ImportedFuncInstance^>(temp);
            auto module = CALLING_MODULE;

            LiteLoader::NET::PluginOwnData::AddImportedRemoteCallFunctions(nint_t(module), funcInstance);

            return (TDelegate)(funcInstance->intertopManagedFuncDelegate);
        }

        return TDelegate();
    }
}