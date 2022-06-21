#include "DynamicExportFunctionRegister.hpp"
namespace LLNET::RemoteCall::Internal {
	::RemoteCall::ValueType DynamicExportFunctionRegister::ExportedFunc::_Invoke(std::vector<::RemoteCall::ValueType> vec)
	{
		try
		{
			return *(::RemoteCall::ValueType*)this->dynamicMethod(&vec);
		}
		CATCH
			return ::RemoteCall::pack(nullptr);
	}
}