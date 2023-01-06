#include "RemoteCallAPI.hpp"

#include <LiteLoader.NET/Main/PluginOwnData.hpp>
#include "Helpers/EmitHelper.hpp"

namespace LiteLoader::RemoteCall
{
    using namespace LiteLoader::RemoteCall::Helper;

    generic<typename TDelegate> where TDelegate: Delegate
        bool RemoteCallAPI::ExportAs(String^ nameSpace, String^ funcName, TDelegate func)
    {
        auto funcInfo = TypeHelper::GenerateFunctionInfo(func->Method);

        auto ilBulider = gcnew EmitHelper::ILCodeBulider(
            nameSpace, funcName, funcInfo, EmitHelper::ILCodeBulider::BuliderType::Export, typeof(TDelegate));

        Object^ temp = nullptr;

        if (ilBulider->Build(func, temp))
        {
            auto funcInstance = As<ExportedFuncInstance^>(temp);
            auto module = CALLING_MODULE;

            auto succeed = ::RemoteCall::exportFunc(marshalString(nameSpace), marshalString(funcName),
                static_cast<value_type(*)(array_type)>(funcInstance->exportedNativeFunc), module);

            if (succeed)
            {
                LiteLoader::NET::PluginOwnData::AddExportedRemoteCallFunctions(IntPtr(module), funcInstance);
                return true;
            }
        }

        return false;
    }
}