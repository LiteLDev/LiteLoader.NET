#pragma once
#include <src/Module/Interop/OriginalData/Enums/StorageType.hpp>

namespace LiteLoader::NET::Interop::OrignalData
{
    using System::AttributeUsageAttribute;
    using System::AttributeTargets;

    [AttributeUsage(AttributeTargets::Method | AttributeTargets::Field | AttributeTargets::Property)]
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
