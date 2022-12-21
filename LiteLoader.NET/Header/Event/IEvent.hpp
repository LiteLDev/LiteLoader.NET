#pragma once
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>

namespace LiteLoader::Event
{

    public interface class ICancellable
    {
        property bool IsCancelled { void set(bool); };
    };

    public interface class IEvent
    {
        property bool IsCancelled { bool get(); };
    };

    public ref class EventBase abstract : IEvent
    {
        bool isCancelled;

    public:
        virtual property bool IsCancelled
        {
            bool get() { return isCancelled; }

            void set(const bool value)
            {
                if (dynamic_cast<ICancellable^>(this) == nullptr)
                    throw gcnew LiteLoader::NET::CancelEventException;

                isCancelled = value;
            }
        }

        void Call();
    };
}
