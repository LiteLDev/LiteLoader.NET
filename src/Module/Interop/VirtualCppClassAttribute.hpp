#pragma once
namespace LiteLoader::NET::Interop
{
    public ref class VirtualCppClassAttribute :System::Attribute
    {
        int vtableLength;

        VirtualCppClassAttribute(int vtableLength)
            : vtableLength(vtableLength)
        {
        }
    };
}

