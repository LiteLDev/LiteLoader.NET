#include "RemoteCallAPI.hpp"

#include "Helpers/EmitHelper.hpp"
#include <src/Header/Logger/Logger.hpp>
#include <src/Main/PluginOwnData.hpp>

#include <src/Tools/NativeCallbackConverter.hpp>

namespace LiteLoader::RemoteCall
{
    using namespace LiteLoader::RemoteCall::Helper;

    value_type _invoke_managed_func(RemoteCallAPI::CallbackFn^ del, array_type vec)
    {
        auto size = (int)vec.size();
        auto arg = gcnew List<Valuetype^>(size);
        for (auto& item : vec)
        {
            arg->Add(gcnew Valuetype(item));
        }
        try
        {
            auto ret = del(arg);
            return *ret->NativePtr;
        }
        catch (System::Exception^ ex)
        {
            GlobalClass::logger->error->WriteLine(LLNET_DEFAULT_EXCEPTION_MESSAGE, ex->GetType()->ToString());
            GlobalClass::logger->error->WriteLine(ex->Message);
            return value_type();
        }
    }
    Valuetype^ _invoke_native_func(void* pfunc, List<Valuetype^>^ list)
    {
        auto count = (size_t)list->Count;
        array_type stdvector;
        for (auto i = 0; i < count; ++i)
        {
            stdvector.emplace_back(*list[i]->NativePtr);
        }
        auto& ret = static_cast<value_type(*)(array_type)>(pfunc)(stdvector);

        return gcnew Valuetype(ret);
    }

    Valuetype^ _invoke_native_func_by_std_function(call_back_func* pstdfunc, List<Valuetype^>^ list)
    {
        auto count = (size_t)list->Count;
        array_type stdvector;
        for (auto i = 0; i < count; ++i)
        {
            stdvector.emplace_back(*list[i]->NativePtr);
        }
        auto& ret = (*pstdfunc)(stdvector);

        return gcnew Valuetype(ret);
    }

    using basic_api_converter = LiteLoader::NET::callback::converter<
        value_type(array_type), Valuetype ^ (List<Valuetype^>^), RemoteCallAPI::CallbackFn>;

    bool RemoteCallAPI::ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ callback)
    {
        NULL_ARG_CHECK(nameSpace);
        NULL_ARG_CHECK(funcName);
        NULL_ARG_CHECK(callback);

        auto pair = basic_api_converter::create<_invoke_managed_func>(callback);

        auto handle = CALLING_MODULE;

        LiteLoader::NET::PluginOwnData::AddRemoteCallData(do_Hash(nameSpace) ^ do_Hash(funcName), nint_t(handle), pair.second);

        return ::RemoteCall::exportFunc(marshalString(nameSpace), marshalString(funcName), pair.first, handle);
    }

    bool RemoteCallAPI::ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ callback, nint_t handle)
    {
        NULL_ARG_CHECK(nameSpace);
        NULL_ARG_CHECK(funcName);
        NULL_ARG_CHECK(callback);

        auto pair = basic_api_converter::create<_invoke_managed_func>(callback);

        LiteLoader::NET::PluginOwnData::AddRemoteCallData(do_Hash(nameSpace) ^ do_Hash(funcName), nint_t(handle), pair.second);
        return ::RemoteCall::exportFunc(marshalString(nameSpace), marshalString(funcName), pair.first, (HMODULE)handle.ToPointer());
    }

    RemoteCallAPI::CallbackFn^ RemoteCallAPI::ImportFunc(String^ nameSpace, String^ funcName)
    {

        NULL_ARG_CHECK(nameSpace);
        NULL_ARG_CHECK(funcName);


        auto& stdfunc = ::RemoteCall::importFunc(marshalString(nameSpace), marshalString(funcName));
        auto pair = basic_api_converter::create<_invoke_native_func_by_std_function>(stdfunc);

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
        if (LiteLoader::NET::PluginOwnData::RemoteCallData->ContainsKey(hashval))
        {
            auto p = LiteLoader::NET::PluginOwnData::RemoteCallData[hashval];
            LiteLoader::NET::PluginOwnData::RemoteCallData->Remove(hashval);
            p.Item2->Release();
        }
        return ret;
    }

    bool RemoteCallAPI::RemoveNameSpace(String^ nameSpace)
    {
        return ::RemoteCall::removeNameSpace(marshalString(nameSpace));
    }

    bool RemoteCallAPI::RemoveFuncs(List<VALUE_TUPLE<String^, String^>>^ funcs)
    {
        auto count = (size_t)funcs->Count;
        std::vector<std::pair<std::string, std::string>> stdvector;
        for each (auto % item in funcs)
        {
            stdvector.emplace_back(marshalString(item.Item1), marshalString(item.Item2));
            auto hashval = do_Hash(item.Item1) ^ do_Hash(item.Item2);
            if (LiteLoader::NET::PluginOwnData::RemoteCallData->ContainsKey(hashval))
            {
                auto p = LiteLoader::NET::PluginOwnData::RemoteCallData[hashval];
                LiteLoader::NET::PluginOwnData::RemoteCallData->Remove(hashval);
                p.Item2->Release();
            }
        }
        return ::RemoteCall::removeFuncs(std::move(stdvector));
    }
}