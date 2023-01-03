#include <LiteLoader.NET/Extra/mutex.hpp>

#include "TypeHelper.hpp"

#include <stdint.h>

namespace LiteLoader::RemoteCall::Helper
{
    PAIR<bool, TypeHelper::ValidType> TypeHelper::TryGetValidType(System::Type^ t)
    {
        using RTN = PAIR<bool, ValidType>;

        if (t == double::typeid)
            return RTN(true, ValidType::Double);
        if (t == float::typeid)
            return RTN(true, ValidType::Float);
        if (t == int64_t::typeid)
            return RTN(true, ValidType::Int64);
        if (t == int32_t::typeid)
            return RTN(true, ValidType::Int32);
        if (t == int16_t::typeid)
            return RTN(true, ValidType::Int16);
        if (t == int8_t::typeid)
            return RTN(true, ValidType::Int8);
        if (t == uint64_t::typeid)
            return RTN(true, ValidType::UInt64);
        if (t == uint32_t::typeid)
            return RTN(true, ValidType::UInt32);
        if (t == uint16_t::typeid)
            return RTN(true, ValidType::UInt16);
        if (t == uint8_t::typeid)
            return RTN(true, ValidType::UInt8);

        if (t == bool::typeid)
            return RTN(true, ValidType::Bool);
        if (t == String::typeid)
            return RTN(true, ValidType::String);
        if (t == NumberType::typeid)
            return RTN(true, ValidType::NumberType);
        if (t == MC::Player::typeid)
            return RTN(true, ValidType::Player);
        if (t == MC::Actor::typeid)
            return RTN(true, ValidType::Actor);
        if (t == MC::BlockActor::typeid)
            return RTN(true, ValidType::BlockActor);
        if (t == MC::Container::typeid)
            return RTN(true, ValidType::Container);
        if (t == MC::Vec3::typeid)
            return RTN(true, ValidType::Vec3);
        if (t == MC::BlockPos::typeid)
            return RTN(true, ValidType::BlockPos);


        if (t == WorldPosType::typeid)
            return RTN(true, ValidType::WorldPosType);
        if (t == BlockPosType::typeid)
            return RTN(true, ValidType::BlockPosType);
        if (t == ItemType::typeid)
            return RTN(true, ValidType::ItemType);
        if (t == BlockType::typeid)
            return RTN(true, ValidType::BlockType);
        if (t == NbtType::typeid)
            return RTN(true, ValidType::NbtType);
        if (t == void::typeid)
            return RTN(true, ValidType::Void);

        if (t->Namespace == "System.Collections.Generic" && t->Name == "List`1")
            return RTN(true, ValidType::List);

        if (t->Namespace == "System.Collections.Generic" && t->Name == "Dictionary`2") {
            auto genericTypes = t->GenericTypeArguments;
            if (genericTypes[0] != String::typeid) {
                return RTN(false, ValidType::Invalid);
            }
            return RTN(true, ValidType::Dictionary);

        }
        return RTN(false, ValidType::Invalid);
    }
    TypeHelper::FunctionInfo::TypeInfo TypeHelper::GenerateTypeInfo(System::Type^ t)
    {

        auto type = TryGetValidType(t);
        if (!type.Key)
            throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;

        auto ret = FunctionInfo::TypeInfo();
        ret._type = t;
        ret.type = type.Value;

        switch (type.Value)
        {
        case TypeHelper::ValidType::List:
        {
            ret.genericArgs = gcnew array<FunctionInfo::TypeInfo>(1);

            ret.genericArgs[0] = GenerateTypeInfo(t->GenericTypeArguments[0]);
        }
        break;

        case TypeHelper::ValidType::Dictionary:
        {
            ret.genericArgs = gcnew array<FunctionInfo::TypeInfo>(2);

            ret.genericArgs[0] = GenerateTypeInfo(t->GenericTypeArguments[0]);
            ret.genericArgs[1] = GenerateTypeInfo(t->GenericTypeArguments[1]);
        }
        break;

        default:
            break;
        case TypeHelper::ValidType::Invalid:
            throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
        }

        return ret;
    }

    TypeHelper::FunctionInfo TypeHelper::GenerateFunctionInfo(Delegate^ func)
    {
        auto methodInfo = func->Method;
        auto params = methodInfo->GetParameters();

        auto funcInfo = FunctionInfo();

        funcInfo.returnType = GenerateTypeInfo(methodInfo->ReturnType);
        funcInfo.parameters = gcnew array<FunctionInfo::TypeInfo>(params->Length);

        for (int i = 0; i < params->Length; ++i)
        {
            funcInfo.parameters[i] = GenerateTypeInfo(params[i]->ParameterType);
        }

        return funcInfo;
    }
    //    inline System::Object^ ExportFunctionRegister::_parseParameter(FunctionInfo::TypeInfo const% info, ::RemoteCall::ValueType& val)
    //    {
    //
    //#define _VALUE std::get<::RemoteCall::Value>(val.value)
    //#define _NUMBERTYPE std::get<::RemoteCall::NumberType>(_VALUE)
    //
    //        switch (info.type)
    //        {
    //        case ValidType::Invalid:
    //            throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
    //        case ValidType::Double:
    //        {
    //            return _NUMBERTYPE.get<double>();
    //        }
    //        break;
    //        case ValidType::Float:
    //        {
    //            return _NUMBERTYPE.get<float>();
    //        }
    //        break;
    //        case ValidType::Int64:
    //        {
    //            return _NUMBERTYPE.get<int64_t>();
    //        }
    //        break;
    //        case ValidType::Int32:
    //        {
    //            return _NUMBERTYPE.get<int32_t>();
    //        }
    //        break;
    //        case ValidType::Int16:
    //        {
    //            return _NUMBERTYPE.get<int16_t>();
    //        }
    //        break;
    //        case ValidType::Int8:
    //        {
    //            return _NUMBERTYPE.get<int8_t>();
    //        }
    //        break;
    //        case ValidType::UInt64:
    //        {
    //            return _NUMBERTYPE.get<uint64_t>();
    //        }
    //        break;
    //        case ValidType::UInt32:
    //        {
    //            return _NUMBERTYPE.get<uint32_t>();
    //        }
    //        break;
    //        case ValidType::UInt16:
    //        {
    //            return _NUMBERTYPE.get<uint16_t>();
    //        }
    //        break;
    //        case ValidType::UInt8:
    //        {
    //            return _NUMBERTYPE.get<uint8_t>();
    //        }
    //        break;
    //        case ValidType::Bool:
    //        {
    //            return std::get<bool>(_VALUE);
    //        }
    //        break;
    //        case ValidType::String:
    //        {
    //            return marshalString(std::get<std::string>(_VALUE));
    //        }
    //        break;
    //        case ValidType::NumberType:
    //            return NumberType(_NUMBERTYPE);
    //            break;
    //        case ValidType::Player:
    //            return gcnew MC::Player(std::get<::Player*>(_VALUE));
    //            break;
    //        case ValidType::Actor:
    //            return gcnew MC::Actor(std::get<::Actor*>(_VALUE));
    //            break;
    //        case ValidType::BlockActor:
    //            return gcnew MC::BlockActor(std::get<::BlockActor*>(_VALUE));
    //            break;
    //        case ValidType::Container:
    //            return gcnew MC::Container(std::get<::Container*>(_VALUE));
    //            break;
    //        case ValidType::Vec3:
    //            return MC::Vec3(std::get<::RemoteCall::WorldPosType>(_VALUE).pos);
    //            break;
    //        case ValidType::BlockPos:
    //            return MC::BlockPos(std::get<::RemoteCall::BlockPosType>(_VALUE).pos);
    //            break;
    //        case ValidType::ItemType:
    //            return gcnew ItemType(std::get<::RemoteCall::ItemType>(_VALUE));
    //            break;
    //        case ValidType::BlockType:
    //            return gcnew BlockType(std::get<::RemoteCall::BlockType>(_VALUE));
    //            break;
    //        case ValidType::NbtType:
    //            return gcnew NbtType(std::get<::RemoteCall::NbtType>(_VALUE));
    //            break;
    //        case ValidType::List:
    //        {
    //            auto& vec = std::get<::RemoteCall::ValueType::ArrayType>(val.value);
    //            auto ret = System::Activator::CreateInstance(info._type, gcnew array<Object^>{(int)vec.size()});
    //
    //            auto AddMethod = info._type->GetMethod("Add");
    //
    //            for (auto& val : vec) {
    //                AddMethod->Invoke(ret, gcnew array<Object^>{_parseParameter(info.genericArgs[0], val)});
    //            }
    //            return ret;
    //        }
    //        break;
    //        case ValidType::Dictionary:
    //        {
    //            auto& umap = std::get<::RemoteCall::ValueType::ObjectType>(val.value);
    //
    //            auto ret = System::Activator::CreateInstance(info._type, gcnew array<System::Object^>{(int)umap.size()});
    //            auto AddMethod = info._type->GetMethod("Add");
    //
    //            for (auto& val : umap) {
    //                AddMethod->Invoke(ret, gcnew array<Object^>{marshalString(val.first), _parseParameter(info.genericArgs[1], val.second)});
    //            }
    //            return ret;
    //        }
    //        break;
    //        case ValidType::Void:
    //        default:
    //            return nullptr;
    //            break;
    //        }
    //    }
    //    inline ::RemoteCall::ValueType ExportFunctionRegister::_parseReturnVal(FunctionInfo::TypeInfo const% info, Object^ val)
    //    {
    //        switch (info.type)
    //        {
    //        case ValidType::Invalid:
    //            throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
    //            break;
    //        case ValidType::Double:
    //            return ::RemoteCall::NumberType(static_cast<double>(val));
    //            break;
    //        case ValidType::Float:
    //            return ::RemoteCall::NumberType(static_cast<float>(val));
    //            break;
    //        case ValidType::Int64:
    //            return ::RemoteCall::NumberType(static_cast<int64_t>(val));
    //            break;
    //        case ValidType::Int32:
    //            return ::RemoteCall::NumberType(static_cast<int32_t>(val));
    //            break;
    //        case ValidType::Int16:
    //            return ::RemoteCall::NumberType(static_cast<int16_t>(val));
    //            break;
    //        case ValidType::Int8:
    //            return ::RemoteCall::NumberType(static_cast<int8_t>(val));
    //            break;
    //        case ValidType::UInt64:
    //            return ::RemoteCall::NumberType(static_cast<uint64_t>(val));
    //            break;
    //        case ValidType::UInt32:
    //            return ::RemoteCall::NumberType(static_cast<uint32_t>(val));
    //            break;
    //        case ValidType::UInt16:
    //            return ::RemoteCall::NumberType(static_cast<uint16_t>(val));
    //            break;
    //        case ValidType::UInt8:
    //            return ::RemoteCall::NumberType(static_cast<uint8_t>(val));
    //            break;
    //        case ValidType::Bool:
    //            return ::RemoteCall::packValue(static_cast<bool>(val));
    //            break;
    //        case ValidType::String:
    //            return marshalString(static_cast<String^>(val));
    //            break;
    //        case ValidType::NumberType:
    //            return static_cast<NumberType>(val)._toNative();
    //            break;
    //        case ValidType::Player:
    //            return static_cast<MC::Player^>(val)->NativePtr;
    //            break;
    //        case ValidType::Actor:
    //            return static_cast<MC::Actor^>(val)->NativePtr;
    //            break;
    //        case ValidType::BlockActor:
    //            return static_cast<MC::BlockActor^>(val)->NativePtr;
    //            break;
    //        case ValidType::Container:
    //            return static_cast<MC::Container^>(val)->NativePtr;
    //            break;
    //        case ValidType::Vec3:
    //            return ::RemoteCall::pack(std::make_pair(static_cast<MC::Vec3>(val).operator ::Vec3(), 3));
    //            break;
    //        case ValidType::BlockPos:
    //            return ::RemoteCall::pack(std::make_pair(static_cast<MC::BlockPos>(val).operator ::BlockPos(), 0));
    //            break;
    //        case ValidType::ItemType:
    //            return *static_cast<ItemType^>(val)->NativePtr;
    //            break;
    //        case ValidType::BlockType:
    //            return *static_cast<BlockType^>(val)->NativePtr;
    //            break;
    //        case ValidType::NbtType:
    //            return *static_cast<NbtType^>(val)->NativePtr;
    //            break;
    //        case ValidType::List:
    //        {
    //            auto ret = ::RemoteCall::ValueType::ArrayType();
    //
    //            auto EMPTY_ARGS = System::Array::Empty<System::Object^>();
    //
    //            auto GetEnumeratorMethod = info._type->GetMethod("GetEnumerator");
    //
    //            auto enumeratorType = GetEnumeratorMethod->ReturnType;
    //            auto MoveNextMethod = enumeratorType->GetMethod("MoveNext");
    //            auto get_CurrentMethod = enumeratorType->GetMethod("get_Current");
    //
    //            auto enumerator = GetEnumeratorMethod->Invoke(val, EMPTY_ARGS);
    //
    //            while ((bool)MoveNextMethod->Invoke(enumerator, EMPTY_ARGS))
    //            {
    //                ret.emplace_back(std::move(_parseReturnVal(info.genericArgs[0], get_CurrentMethod->Invoke(enumerator, EMPTY_ARGS))));
    //            }
    //            return ret;
    //        }
    //        break;
    //        case ValidType::Dictionary:
    //        {
    //            auto ret = ::RemoteCall::ValueType::ObjectType();
    //            auto EMPTY_ARGS = System::Array::Empty<System::Object^>();
    //
    //            auto GetEnumeratorMethod = info._type->GetMethod("GetEnumerator");
    //
    //            auto enumeratorType = GetEnumeratorMethod->ReturnType;
    //            auto MoveNextMethod = enumeratorType->GetMethod("MoveNext");
    //            auto get_CurrentMethod = enumeratorType->GetMethod("get_Current");
    //
    //            auto kvPairType = get_CurrentMethod->ReturnType;
    //            auto get_KeyMethod = kvPairType->GetMethod("get_Key");
    //            auto get_ValueMethod = kvPairType->GetMethod("get_Value");
    //
    //            auto enumerator = GetEnumeratorMethod->Invoke(val, EMPTY_ARGS);
    //
    //            while ((bool)MoveNextMethod->Invoke(enumerator, EMPTY_ARGS))
    //            {
    //                auto kvPair = get_CurrentMethod->Invoke(enumerator, EMPTY_ARGS);
    //                auto key = get_KeyMethod->Invoke(kvPair, EMPTY_ARGS);
    //                auto value = get_ValueMethod->Invoke(kvPair, EMPTY_ARGS);
    //
    //                ret.emplace(marshalString(static_cast<String^>(key)), _parseReturnVal(info.genericArgs[1], value));
    //            }
    //
    //            return ret;
    //        }
    //        break;
    //        case ValidType::Void:
    //        default:
    //            return ::RemoteCall::ValueType();
    //            break;
    //        }
    //    }
        //inline ExportFunctionRegister::ExportFunc::ExportFunc(String^ nameSpace, String^ funcName, FunctionInfo^ info, System::Delegate^ del)
        //    :nameSpace(nameSpace), funcName(funcName), info(info), func(del)
        //{
        //}
        //inline Pair<ExportFunctionRegister::ExportFunc^, ExportFunctionRegister::delNative^> ExportFunctionRegister::ExportFunc::Create(String^ nameSpace, String^ funcName, FunctionInfo^ info, System::Delegate^ del) {
        //    auto instance = gcnew ExportFunc(nameSpace, funcName, info, del);
        //    auto delnative = gcnew delNative(instance, &ExportFunc::_nativeFunc);
        //    instance->gch = GCHandle::Alloc(delnative);
        //    return Pair<ExportFunc^, delNative^>(instance, delnative);
        //}
        //inline NATIVECALLBACK::RemoteCall::ValueType ExportFunctionRegister::ExportFunc::_nativeFunc(std::vector<::RemoteCall::ValueType> vec) {
        //    auto args = gcnew array<Object^>(info->parameters->Length);
        //    for (int i = 0; i < info->parameters->Length; ++i)
        //    {
        //        args[i] = _parseParameter(info->parameters[i], vec[i]);
        //    }

        //    auto ret = func->DynamicInvoke(args);

        //    return std::move(_parseReturnVal(info->returnType, ret));
        //}
}