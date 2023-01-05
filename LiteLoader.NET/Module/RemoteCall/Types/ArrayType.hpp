#pragma once
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>

#include <LiteLoader.NET/Module/RemoteCall/Interfaces/IValueType.hpp>
#include <LiteLoader.NET/Module/RemoteCall/Enums/InstanceType.hpp>
#include <LiteLoader.NET/Module/RemoteCall/Attributes/RemoteCallValueTypeAttribute.hpp>

namespace LiteLoader::RemoteCall
{
    ref class Valuetype;
}

namespace LiteLoader::RemoteCall
{
    [RemoteCallValueType(InstanceType::ArrayType)]
    public ref class ArrayType :IValueType
    {
    public:
        ArrayType(List<Valuetype^>^ v);
        List<Valuetype^>^ value;
    public:
        virtual String^ ToString() override;
    };
}

