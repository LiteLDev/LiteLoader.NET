#include "DynamicExportFunctionRegister.hpp"
namespace LiteLoader::RemoteCall::Internal {
	::RemoteCall::ValueType DynamicExportFunctionRegister::ExportedFunc::_Invoke(std::vector<::RemoteCall::ValueType> vec)
	{
		try
		{
			auto p = this->dynamicMethod(&vec);
			::RemoteCall::ValueType ret = std::move(*(::RemoteCall::ValueType*)p);
			delete (::RemoteCall::ValueType*)p;
			return ret;
		}
		CATCH
			return ::RemoteCall::pack(nullptr);
	}
}