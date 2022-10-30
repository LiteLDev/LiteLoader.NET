#include <LiteLoader.NET/Header/RemoteCall/RemoteCall.hpp>
namespace LLNET::RemoteCall
{

	::RemoteCall::ValueType _invoke_managed_func(Object^ del, std::vector<::RemoteCall::ValueType> vec)
	{
		auto size = (int)vec.size();
		auto arg = gcnew List<Valuetype^>(size);
		for (auto& item : vec)
		{
			arg->Add(gcnew Valuetype(item));
		}
		try
		{
			auto ret = static_cast<RemoteCallAPI::CallbackFn^>(del)(arg);
			return *ret->NativePtr;
		}
		catch (System::Exception^ ex)
		{
			GlobalClass::logger->error->WriteLine(LLNET_DEFAULT_EXCEPTION_MESSAGE, ex->GetType()->ToString());
			GlobalClass::logger->error->WriteLine(ex->Message);
			return ::RemoteCall::ValueType();
		}
	}

	Valuetype^ _invoke_native_func(void* pfunc, List<Valuetype^>^ list)
	{
		auto count = (size_t)list->Count;
		std::vector<::RemoteCall::ValueType> stdvector;
		for (auto i = 0; i < count; ++i)
		{
			stdvector.emplace_back(*list[i]->NativePtr);
		}
		auto& ret = static_cast<::RemoteCall::ValueType(*)(std::vector<::RemoteCall::ValueType>)>(pfunc)(stdvector);

		return gcnew Valuetype(ret);
	}

	using _callback_converter = llnet::callback::converter<
		::RemoteCall::ValueType(std::vector<::RemoteCall::ValueType>), Valuetype ^ (List<Valuetype^>^), RemoteCallAPI::CallbackFn>;



	bool RemoteCallAPI::ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ callback)
	{
		NULL_ARG_CHECK(nameSpace);
		NULL_ARG_CHECK(funcName);
		NULL_ARG_CHECK(callback);

		auto pair = _callback_converter::create<_invoke_managed_func>(callback);

		CallbackData->Add(do_Hash(nameSpace) ^ do_Hash(funcName), pair.second);
		return ::RemoteCall::exportFunc(marshalString(nameSpace), marshalString(funcName), pair.first, CALLING_MODULE);
	}

	bool RemoteCallAPI::ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ callback, System::IntPtr handle)
	{
		NULL_ARG_CHECK(nameSpace);
		NULL_ARG_CHECK(funcName);
		NULL_ARG_CHECK(callback);

		auto pair = _callback_converter::create<_invoke_managed_func>(callback);

		CallbackData->Add(do_Hash(nameSpace) ^ do_Hash(funcName), pair.second);
		return ::RemoteCall::exportFunc(marshalString(nameSpace), marshalString(funcName), pair.first, (HMODULE)(void*)handle);
	}

	RemoteCallAPI::CallbackFn^ RemoteCallAPI::ImportFunc(String^ nameSpace, String^ funcName)
	{
		NULL_ARG_CHECK(nameSpace);
		NULL_ARG_CHECK(funcName);

		auto& pfunc = ::RemoteCall::importFunc(marshalString(nameSpace), marshalString(funcName));
		auto pair = _callback_converter::create<_invoke_native_func>(
			pfunc.target<::RemoteCall::ValueType(std::vector<::RemoteCall::ValueType>)>());

		GC::KeepAlive(pair.second);
		return pair.first;
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
			p->Release();
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
				p->Release();
			}
		}
		return ::RemoteCall::removeFuncs(std::move(stdvector));
	}


} // namespace LLNET::RemoteCall
