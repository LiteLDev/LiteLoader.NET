#pragma once
#include <mc/Tick.hpp>
#include "Types.hpp"

namespace MC
{

public
ref struct Tick : ClassTemplate<Tick, ::Tick>
{

    __ctor(Tick, ::Tick);
    __ctor_default(Tick, ::Tick);

    property unsigned long long T
    {
        unsigned long long get()
        {
            return NativePtr->t;
        }
    }
};

} // namespace MC
