#include <src/Header/MC/Vec2.hpp>
#include <src/Header/MC/Vec3.hpp>
#include <src/Header/MC/BlockPos.hpp>

inline MC::Vec3::Vec3(BlockPos pos)
{
    auto& vec = ::Vec3(::BlockPos(pos));
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

inline MC::Vec3::Vec3(System::Numerics::Vector3 vec3)
{
    x = vec3.X;
    y = vec3.Y;
    z = vec3.Z;
}

MC::BlockPos MC::Vec3::ToBlockPos()
{
    return BlockPos(::BlockPos(::Vec3{ x,y,z }));
}
