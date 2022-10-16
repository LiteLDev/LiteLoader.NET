#include <LiteLoader.NET/Header/MC/BoundingBox.hpp>
#include <LiteLoader.NET/Header/MC/BlockPos.hpp>
#include <LiteLoader.NET/Header/MC/AABB.hpp>

#include <LiteLoader.NET/Tools/NativeCallbackConverter_old.hpp>

#include <LiteLoader.NET/Header/Logger/Logger.hpp>


namespace MC {
	DelegateToNativeHelper(ForEachBlockInBoxHelper, BoundingBox::ForEachBlockInBoxHandler, void, ::BlockPos const& pos) {
		try
		{
			delfunc(*((BlockPos*)&pos));
		}
		CATCH
	}

	inline AABB BoundingBox::ToAABB()
	{
		pin_ptr<BoundingBox> p = this;
		return ((::BoundingBox*)p)->toAABB();
	}

	//inline BoundingBox BoundingBox::Merge(BoundingBox% a) {
	//	pin_ptr<BoundingBox> pthis = this;
	//	pin_ptr<BoundingBox> pa = &a;
	//	return ((::BoundingBox*)pthis)->merge(*(::BoundingBox*)pa);
	//}

	//inline BoundingBox BoundingBox::Merge(BlockPos% a) {
	//	pin_ptr<BoundingBox> pthis = this;
	//	pin_ptr<BlockPos> pa = &a;
	//	return ((::BoundingBox*)pthis)->merge(*(::BlockPos*)pa);
	//}

	inline void BoundingBox::ForEachBlockInBox(ForEachBlockInBoxHandler^ todo) {
		pin_ptr<BoundingBox> p = this;
		auto pair = ForEachBlockInBoxHelper::Create(todo);
		((::BoundingBox*)p)->forEachBlockInBox(pair.pCallbackFn);
		delete pair.converter;
	}
}