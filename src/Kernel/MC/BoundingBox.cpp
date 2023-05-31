#include <src/Header/MC/BoundingBox.hpp>
#include <src/Header/MC/BlockPos.hpp>
#include <src/Header/MC/AABB.hpp>

#include <src/Tools/NativeCallbackConverter.hpp>

#include <src/Header/Logger/Logger.hpp>


namespace MC {
    DelegateToNativeHelper(ForEachBlockInBoxHelper, BoundingBox::ForEachBlockInBoxHandler, void, ::BlockPos const& pos) {
        delfunc(*((BlockPos*)&pos));
    }

    inline AABB BoundingBox::ToAABB()
    {
        pin_ptr<BoundingBox> p = this;
        return ((::BoundingBox*)p)->toAABB();
    }

    //inline BoundingBox BoundingBox::Merge(BoundingBox% a) {
    //    pin_ptr<BoundingBox> pthis = this;
    //    pin_ptr<BoundingBox> pa = &a;
    //    return ((::BoundingBox*)pthis)->merge(*(::BoundingBox*)pa);
    //}

    //inline BoundingBox BoundingBox::Merge(BlockPos% a) {
    //    pin_ptr<BoundingBox> pthis = this;
    //    pin_ptr<BlockPos> pa = &a;
    //    return ((::BoundingBox*)pthis)->merge(*(::BlockPos*)pa);
    //}

    inline void BoundingBox::ForEachBlockInBox(ForEachBlockInBoxHandler^ todo) {
        pin_ptr<BoundingBox> p = this;
        auto pair = ForEachBlockInBoxHelper::Create(todo);
        ((::BoundingBox*)p)->forEachBlockInBox(pair.pCallbackFn);
        delete pair.converter;
    }
}