#pragma once
#include <src/Main/DotNETGlobal.hpp>

#include <src/Module/RemoteCall/Interfaces/IValueType.hpp>
#include <src/Module/RemoteCall/Enums/InstanceType.hpp>
#include <src/Module/RemoteCall/Attributes/RemoteCallValueTypeAttribute.hpp>

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

