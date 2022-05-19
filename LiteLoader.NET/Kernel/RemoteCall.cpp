#include "../Header/RemoteCall.h"

#ifdef REMOTECALL_FIXED

namespace LLNET::RemoteCall
{
NativeCallbackConvertHelper(ExportFuncCallback, RemoteCallAPI::CallbackFn, RemoteCallAPI::ValueType, std::vector<RemoteCallAPI::ValueType> vec)
{
    auto size = (int)vec.size();
    List<String ^> ^ arg = gcnew List<String ^>(size);
    for each (auto& item in vec)
    {
        throw gcnew System::NotImplementedException;
    }
    try
    {
        auto ret = delfunc(arg);
        return marshalString(ret);
    }
    catch (System::Exception ^ ex)
    {
        System::Console::WriteLine(LLNET_DEFAULT_EXCEPTION_MESSAGE, ex->GetType()->ToString());
        System::Console::WriteLine(ex->Message);
        return "";
    }
}

bool RemoteCallAPI::ExportFunc(String^ nameSpace, String^ funcName, CallbackFn ^ callback)
{
    NULL_ARG_CHEEK(nameSpace);
    NULL_ARG_CHEEK(funcName);
    NULL_ARG_CHEEK(callback);

    auto pair = ExportFuncCallback::Create(callback);
    CallbackData->Add(do_Hash(nameSpace) ^ do_Hash(funcName), (NativeCallbackHandler ^) pair.converter);
    return ::RemoteCall::exportFunc(marshalString(nameSpace), marshalString(funcName), pair.pCallbackFn, MODULE);
}

bool RemoteCallAPI::ExportFunc(String^ nameSpace, String^ funcName, CallbackFn ^ callback, System::IntPtr handler)
{
    NULL_ARG_CHEEK(nameSpace);
    NULL_ARG_CHEEK(funcName);
    NULL_ARG_CHEEK(callback);

    auto pair = ExportFuncCallback::Create(callback);
    CallbackData->Add(do_Hash(nameSpace) ^ do_Hash(funcName), (NativeCallbackHandler ^) pair.converter);
    return ::RemoteCall::exportFunc(marshalString(nameSpace), marshalString(funcName), pair.pCallbackFn, (HMODULE)(void*)handler);
}

NativeCallbackConvertHelper(RemoteCallHelper, RemoteCallAPI::CallbackFn, ::RemoteCall::ValueType, std::vector<::RemoteCall::ValueType> vec)
{
    throw gcnew System::NotImplementedException;
}

RemoteCallAPI::CallbackFn ^ RemoteCallAPI::ImportFunc(String^ nameSpace, String^ funcName)
{
    NULL_ARG_CHEEK(nameSpace);
    NULL_ARG_CHEEK(funcName);

    throw gcnew System::NotImplementedException;

    auto pfunc = (::RemoteCall::CallbackFn)::RemoteCall::importFunc(marshalString(nameSpace), marshalString(funcName));
}

bool RemoteCallAPI::HasFunc(String ^ nameSpace, String ^ funcName)
{
    return ::RemoteCall::hasFunc(marshalString(nameSpace), marshalString(funcName));
}

bool RemoteCallAPI::RemoveFunc(String ^ nameSpace, String ^ funcName)
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

bool RemoteCallAPI::RemoveNameSpace(String ^ nameSpace)
{
    return ::RemoteCall::removeNameSpace(marshalString(nameSpace));
}

bool RemoteCallAPI::RemoveFuncs(List<Pair<String ^, String ^>> ^ funcs)
{
    auto count = (size_t)funcs->Count;
    std::vector<std::pair<std::string, std::string>> stdvector;
    stdvector.resize(count);
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

#endif
