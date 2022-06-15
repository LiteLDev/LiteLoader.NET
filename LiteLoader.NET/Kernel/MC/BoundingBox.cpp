#include "../../Header/MC/BoundingBox.hpp"
#include "../../Header/MC/BlockPos.hpp"
#include "../../Header/MC/AABB.hpp"

#include "../../Tools/NativeCallbackConverter.hpp"


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

	inline void BoundingBox::ForEachBlockInBox(ForEachBlockInBoxHandler^ todo) {
		pin_ptr<BoundingBox> p = this;
		auto pair = ForEachBlockInBoxHelper::Create(todo);
		((::BoundingBox*)p)->forEachBlockInBox(pair.pCallbackFn);
		delete pair.converter;
	}
}