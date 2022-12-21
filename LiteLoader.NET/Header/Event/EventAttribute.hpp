#pragma once

namespace LiteLoader::Event
{
    using System::AttributeUsageAttribute;
    using System::AttributeTargets;
    using System::Attribute;

    [AttributeUsage(AttributeTargets::Method)]
    public ref class EventHandlerAttribute : Attribute
    {
    public:
        property EventPriority Priority;
        property bool IgnoreCancelled;

        EventHandlerAttribute()
        {
            Priority = EventPriority::NORMAL;
            IgnoreCancelled = false;
        }
    };
}
