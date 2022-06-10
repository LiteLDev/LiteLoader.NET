#pragma once
#include <MC/BoundingBox.hpp>
#include "Types.hpp"
namespace MC {
    public
    ref class BoundingBox : ClassTemplate<BoundingBox, ::BoundingBox>
    {
    public:
        __ctor(BoundingBox, ::BoundingBox);
    public:
        property BlockPos^ Min {inline BlockPos^ get(); inline void set(BlockPos^ bpos); };
        property BlockPos^ Max {inline BlockPos^ get(); inline void set(BlockPos^ bpos); };
        inline BlockPos^ GetCenter();
        inline AABB^ ToAABB();
    };
}
