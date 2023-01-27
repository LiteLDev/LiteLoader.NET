#pragma once
namespace LiteLoader::NET::Interop
{
    using System::AttributeUsageAttribute;
    using System::AttributeTargets;

    [AttributeUsage(AttributeTargets::Class | AttributeTargets::Struct)]
    public ref class VirtualCppClassAttribute :System::Attribute
    {
    public:
        int vtableLength;

        VirtualCppClassAttribute(int vtableLength)
            : vtableLength(vtableLength)
        {
        }
    };
}

