#pragma once
#include "IRemoteCallHelper.hpp"

using namespace System::Reflection::Emit;

#define oc OpCodes

namespace LiteLoader::RemoteCall::Internal {
    public ref class DynamicRemoteCallFunctionRegisterBase
    {
    public:
        enum class ValidType {
            Invalid,

            Double,
            Float,
            Int64,
            Int32,
            Int16,
            Int8,
            UInt64,
            UInt32,
            UInt16,
            UInt8,

            Bool,
            String,
            NumberType,
            Player,
            Actor,
            BlockActor,
            Container,
            Vec3,
            BlockPos,

            WorldPosType,
            BlockPosType,
            ItemType,
            BlockType,
            NbtType,

            List,
            Dictionary,

            Void
        };
        ref struct FunctionInfo {
            value struct TypeInfo {
                System::Type^ _type;
                ValidType type;
                array<TypeInfo>^ genericArgs;
            };
            TypeInfo returnType;
            array<TypeInfo>^ parameters;
        };
        static VALUE_TUPLE<bool, ValidType> _tryGetValidType(System::Type^ t);
        static FunctionInfo::TypeInfo _generateTypeInfo(System::Type^ t);

        static void IL_ManagedObjectToValueType(ILGenerator^ il, FunctionInfo::TypeInfo% info, Dictionary<int, LocalBuilder^>% locals);
        static void IL_ValueTypeToManagedObject(ILGenerator^ il, FunctionInfo::TypeInfo% info, Dictionary<int, LocalBuilder^>% locals);
    };
}

