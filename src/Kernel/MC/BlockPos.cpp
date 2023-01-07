#include <src/Header/MC/BlockPos.hpp>
#include <src/Header/MC/Vec3.hpp>
#include <src/Header/MC/BoundingBox.hpp>

namespace MC {
    inline Vec3 BlockPos::ToVec3()
    {
        pin_ptr<BlockPos> p = this;
        return ((::BlockPos*)p)->toVec3();
    }

    inline Vec3 BlockPos::BottomCenter()
    {
        pin_ptr<BlockPos> p = this;
        return ((::BlockPos*)p)->bottomCenter();
    }

    inline Vec3 BlockPos::Center()
    {
        pin_ptr<BlockPos> p = this;
        return ((::BlockPos*)p)->center();
    }
    inline bool BlockPos::ContainedWithin(BoundingBox% obj)
    {
        pin_ptr<BlockPos> p = this;
        pin_ptr<BoundingBox> pobj = &obj;

        return ((::BlockPos*)p)->containedWithin(*(::BoundingBox*)pobj);
    }
}