#include "RemoteCallAPI.hpp"

#include "Helpers/TypeHelper.hpp"

namespace LiteLoader::RemoteCall
{
    using namespace LiteLoader::RemoteCall::Helper;

    generic<typename TDelegate> where TDelegate: Delegate
        static bool RemoteCallAPI::ExportAs(String^ nameSpace, String^ funcName, TDelegate func)
    {
        auto funcInfo = TypeHelper::GenerateFunctionInfo(func);
    }
}