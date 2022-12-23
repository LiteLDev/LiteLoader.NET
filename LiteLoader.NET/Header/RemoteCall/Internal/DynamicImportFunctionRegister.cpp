#include "DynamicImportFunctionRegister.hpp"

namespace LiteLoader::RemoteCall::Internal
{
    inline void* DynamicImportFunctionRegister::ImportedFunc::_Invoke(void* vec) {
        try 
        {
            return new ::RemoteCall::ValueType((*pfunc)(std::move(*(std::vector<::RemoteCall::ValueType>*)vec)));
        }
        CATCH
            return new ::RemoteCall::ValueType(::RemoteCall::pack(nullptr));
    }
    inline DynamicImportFunctionRegister::ImportedFunc::~ImportedFunc() {
        delete pfunc;
    }
}