#pragma once
#include <src/Module/Interop/OriginalData/Enums/AccessType.hpp>

namespace LiteLoader::NET::Interop::OrignalData
{
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

