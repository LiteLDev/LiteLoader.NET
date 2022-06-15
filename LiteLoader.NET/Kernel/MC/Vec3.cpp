#include "../../Header/MC/Vec2.hpp"
#include "../../Header/MC/Vec3.hpp"
#include "../../Header/MC/BlockPos.hpp"

inline MC::Vec3::Vec3(BlockPos pos)
{
	auto& vec = ::Vec3(::BlockPos(pos));
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

MC::BlockPos MC::Vec3::ToBlockPos()
{
	return BlockPos(::BlockPos(::Vec3{ x,y,z }));
}
