#pragma once

#include <LiteLoader.NET/Module/RemoteCall/Types/ValueType.hpp>

namespace LiteLoader::RemoteCall::Helper
{
    public ref class TypeHelper 
    {
    public:

        enum class ValidType
        {
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

        value struct FunctionInfo
        {
            value struct TypeInfo
            {
                System::Type^ _type;
                ValidType type;
                array<TypeInfo>^ genericArgs;
            };
            TypeInfo returnType;
            array<TypeInfo>^ parameters;
        };

        static PAIR<bool, ValidType> TryGetValidType(System::Type^ t);

        static FunctionInfo::TypeInfo GenerateTypeInfo(System::Type^ t);

        /// <exception cref="LiteLoader::NET::InvalidRemoteCallTypeException"></exception>
        static FunctionInfo GenerateFunctionInfo(Delegate^ func);
    };
}



