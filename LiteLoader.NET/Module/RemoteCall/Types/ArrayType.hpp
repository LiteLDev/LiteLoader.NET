#pragma once
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>

#include <LiteLoader.NET/Module/RemoteCall/Interfaces/IValueType.hpp>

namespace LiteLoader::RemoteCall
{
    ref class Valuetype;
}

namespace LiteLoader::RemoteCall
{
    public ref class ArrayType :IValueType
    {
    public:
        ArrayType(List<Valuetype^>^ v);
        List<Valuetype^>^ value;
    public:
        virtual String^ ToString() override;
    };
}

