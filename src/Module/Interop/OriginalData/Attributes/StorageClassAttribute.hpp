#pragma once
#include <src/Module/Interop/OriginalData/Enums/StorageType.hpp>

namespace LiteLoader::NET::Interop::OrignalData
{
    public ref class StorageClassAttribute :System::Attribute
    {
    public:
        StorageType storageType;

        StorageClassAttribute(StorageType storageType)
            :storageType(storageType)
        {
        }
    };
}
