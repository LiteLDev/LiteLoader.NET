#include "ImportFunctionRegister.hpp"

namespace LLNET::RemoteCall::Internal
{
	inline void* ImportFunctionRegister::ImportedFunc::_Invoke(void* vec) {
		try 
		{
			return new ::RemoteCall::ValueType((*pfunc)(std::move(*(std::vector<::RemoteCall::ValueType>*)vec)));
		}
		CATCH
			return new ::RemoteCall::ValueType(::RemoteCall::pack(nullptr));
	}
}