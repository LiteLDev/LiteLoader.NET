#include <mutex>

#include "TypeHelper.hpp"

#include <stdint.h>

namespace LiteLoader::RemoteCall::Helper
{
    VALUE_TUPLE<bool, TypeHelper::ValidType> TypeHelper::TryGetValidType(System::Type^ t)
    {
        using RTN = VALUE_TUPLE<bool, ValidType>;

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
        if (!type.Item1)
            throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;

        auto ret = FunctionInfo::TypeInfo();
        ret._type = t;
        ret.type = type.Item2;

        switch (type.Item2)
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

    TypeHelper::FunctionInfo TypeHelper::GenerateFunctionInfo(System::Reflection::MethodInfo^ info)
    {
        auto params = info->GetParameters();

        auto funcInfo = FunctionInfo();

        funcInfo.returnType = GenerateTypeInfo(info->ReturnType);
        funcInfo.parameters = gcnew array<FunctionInfo::TypeInfo>(params->Length);

        for (int i = 0; i < params->Length; ++i)
        {
            funcInfo.parameters[i] = GenerateTypeInfo(params[i]->ParameterType);
        }

        return funcInfo;
    }
}