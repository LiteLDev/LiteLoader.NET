#include "../Header/RemoteCall/RemoteCall.h"
namespace LLNET::RemoteCall
{
	DelegateToNativeHelper(ExportFuncCallback, RemoteCallAPI::CallbackFn, ::RemoteCall::ValueType, std::vector<::RemoteCall::ValueType> vec)
	{
		auto size = (int)vec.size();
		auto arg = gcnew List<Valuetype^>(size);
		for (auto& item : vec)
		{
			arg->Add(gcnew Valuetype(item));
		}
		try
		{
			auto ret = delfunc(arg);
			return *ret->NativePtr;
		}
		catch (System::Exception^ ex)
		{
			System::Console::WriteLine(LLNET_DEFAULT_EXCEPTION_MESSAGE, ex->GetType()->ToString());
			System::Console::WriteLine(ex->Message);
			return ::RemoteCall::ValueType();
		}
	}

	bool RemoteCallAPI::ExportedFunc(String^ nameSpace, String^ funcName, CallbackFn^ callback)
	{
		NULL_ARG_CHEEK(nameSpace);
		NULL_ARG_CHEEK(funcName);
		NULL_ARG_CHEEK(callback);

		auto pair = ExportFuncCallback::Create(callback);
		CallbackData->Add(do_Hash(nameSpace) ^ do_Hash(funcName), (NativeCallbackHandler^)pair.converter);
		return ::RemoteCall::exportFunc(marshalString(nameSpace), marshalString(funcName), pair.pCallbackFn, Global::__GetCurrentModule(Assembly::GetCallingAssembly()));
	}

	bool RemoteCallAPI::ExportedFunc(String^ nameSpace, String^ funcName, CallbackFn^ callback, System::IntPtr handler)
	{
		NULL_ARG_CHEEK(nameSpace);
		NULL_ARG_CHEEK(funcName);
		NULL_ARG_CHEEK(callback);

		auto pair = ExportFuncCallback::Create(callback);
		CallbackData->Add(do_Hash(nameSpace) ^ do_Hash(funcName), (NativeCallbackHandler^)pair.converter);
		return ::RemoteCall::exportFunc(marshalString(nameSpace), marshalString(funcName), pair.pCallbackFn, (HMODULE)(void*)handler);
	}

	RemoteCallAPI::CallbackFn^ RemoteCallAPI::ImportFunc(String^ nameSpace, String^ funcName)
	{
		NULL_ARG_CHEEK(nameSpace);
		NULL_ARG_CHEEK(funcName);

		auto& pfunc = ::RemoteCall::importFunc(marshalString(nameSpace), marshalString(funcName));
		auto pair = RemoteCallHelper::Create(pfunc);
		GC::KeepAlive(pair.Key);
		return pair.Value;
	}

	bool RemoteCallAPI::HasFunc(String^ nameSpace, String^ funcName)
	{
		return ::RemoteCall::hasFunc(marshalString(nameSpace), marshalString(funcName));
	}

	bool RemoteCallAPI::RemoveFunc(String^ nameSpace, String^ funcName)
	{
		auto ret = ::RemoteCall::removeFunc(marshalString(nameSpace), marshalString(funcName));
		auto hashval = do_Hash(nameSpace) ^ do_Hash(funcName);
		if (CallbackData->ContainsKey(hashval))
		{
			auto p = CallbackData[hashval];
			CallbackData->Remove(hashval);
			delete p;
		}
		return ret;
	}

	bool RemoteCallAPI::RemoveNameSpace(String^ nameSpace)
	{
		return ::RemoteCall::removeNameSpace(marshalString(nameSpace));
	}

	bool RemoteCallAPI::RemoveFuncs(List<Pair<String^, String^>>^ funcs)
	{
		auto count = (size_t)funcs->Count;
		std::vector<std::pair<std::string, std::string>> stdvector;
		for each (auto % item in funcs)
		{
			stdvector.emplace_back(marshalString(item.Key), marshalString(item.Value));
			auto hashval = do_Hash(item.Key) ^ do_Hash(item.Value);
			if (CallbackData->ContainsKey(hashval))
			{
				auto p = CallbackData[hashval];
				CallbackData->Remove(hashval);
				delete p;
			}
		}
		return ::RemoteCall::removeFuncs(std::move(stdvector));
	}


} // namespace LLNET::RemoteCall
