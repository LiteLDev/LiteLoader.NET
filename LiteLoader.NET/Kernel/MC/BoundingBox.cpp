#include "../../Header/MC/BoundingBox.hpp"
#include "../../Header/MC/BlockPos.hpp"
#include "../../Header/MC/AABB.hpp"

namespace MC {
    inline BlockPos^ BoundingBox::Min::get()
    {
        return gcnew BlockPos(NativePtr->min);
    }
    inline void BoundingBox::Min::set(BlockPos^ bpos)
    {
        NativePtr->min = bpos;
    }
    inline BlockPos^ BoundingBox::Max::get()
    {
        return gcnew BlockPos(NativePtr->max);
    }
    inline void BoundingBox::Max::set(BlockPos^ bpos)
    {
        NativePtr->max = bpos;
    }
    inline BlockPos^ BoundingBox::GetCenter()
    {
        return gcnew BlockPos(NativePtr->getCenter());
    }
    inline AABB^ BoundingBox::ToAABB()
    {
        ::Vec3 vec1 = { (float)Min->X, (float)Min->Y, (float)Min->Z };
        ::Vec3 vec2 = { (float)Min->X, (float)Min->Y, (float)Min->Z };
        return gcnew AABB({ vec1, vec2 + ::Vec3{1, 1, 1} });
    }
}