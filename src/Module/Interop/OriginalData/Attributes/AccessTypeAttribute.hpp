#pragma once
#include <src/Module/Interop/OriginalData/Enums/AccessType.hpp>

namespace LiteLoader::NET::Interop::OrignalData
{
    using System::AttributeUsageAttribute;
    using System::AttributeTargets;

    [AttributeUsage(AttributeTargets::Method | AttributeTargets::Field | AttributeTargets::Property)]
    public ref class AccessTypeAttribute :System::Attribute
    {
    public:
        AccessType accessType;

        AccessTypeAttribute(AccessType accessType)
            :accessType(accessType)
        {
        }
    };
}

