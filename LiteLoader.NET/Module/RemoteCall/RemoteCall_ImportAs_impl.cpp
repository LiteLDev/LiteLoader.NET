#include "RemoteCallAPI.hpp"

//#include <LiteLoader.NET/Main/PluginOwnData.hpp>
//#include "Helpers/EmitHelper.hpp"

namespace LiteLoader::RemoteCall
{

    generic<typename TDelegate> where TDelegate: Delegate
        TDelegate RemoteCallAPI::ImportAs(String^ nameSpace, String^ funcName)
    {
        throw gcnew System::NotImplementedException;
    }
}