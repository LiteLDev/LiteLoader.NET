#pragma once
namespace LiteLoader::NET::Interop::OrignalData
{
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

