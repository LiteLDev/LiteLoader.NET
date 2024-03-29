#pragma once
#include <mc/Attribute.hpp>
#include "Types.hpp"
namespace MC
{
public
ref class Attribute : ClassTemplate<Attribute, ::Attribute>
{
public:
    __ctor(Attribute, ::Attribute);
    __ctor_default(Attribute, ::Attribute);

#ifdef INCLUDE_MCAPI
    property unsigned int IDValue
    {
        unsigned int get();
    }

    property bool IsClientSyncable
    {
        bool get();
    }

#endif // INCLUDE_MCAPI
};
} // namespace MC