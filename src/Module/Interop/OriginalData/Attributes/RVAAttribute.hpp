#pragma once
namespace LiteLoader::NET::Interop::OrignalData
{
    using System::AttributeUsageAttribute;
    using System::AttributeTargets;

    [AttributeUsage(AttributeTargets::Method | AttributeTargets::Field | AttributeTargets::Property)]
    public ref class RVAAttribute :System::Attribute
    {
    public:
        long long rva;

        RVAAttribute(long long rva)
            :rva(rva)
        {
        }
    };
}

