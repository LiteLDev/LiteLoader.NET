#include "../../Header/MC/BoundingBox.hpp"
#include "../../Header/MC/BlockPos.hpp"
#include "../../Header/MC/AABB.hpp"

namespace MC {
    inline BlockPos^ BoundingBox::Bpos1::get()
    {
        return gcnew BlockPos(NativePtr->bpos1);
    }
    inline void BoundingBox::Bpos1::set(BlockPos^ bpos)
    {
        NativePtr->bpos1 = bpos;
    }
    inline BlockPos^ BoundingBox::Bpos2::get()
    {
        return gcnew BlockPos(NativePtr->bpos2);
    }
    inline void BoundingBox::Bpos2::set(BlockPos^ bpos)
    {
        NativePtr->bpos2 = bpos;
    }
    inline BlockPos^ BoundingBox::GetCenter()
    {
        return gcnew BlockPos(NativePtr->getCenter());
    }
    inline AABB^ BoundingBox::ToAABB()
    {
        ::Vec3 vec1 = { (float)Bpos1->X, (float)Bpos1->Y, (float)Bpos1->Z };
        ::Vec3 vec2 = { (float)Bpos1->X, (float)Bpos1->Y, (float)Bpos1->Z };
        return gcnew AABB({ vec1, vec2 + ::Vec3{1, 1, 1} });
    }
}