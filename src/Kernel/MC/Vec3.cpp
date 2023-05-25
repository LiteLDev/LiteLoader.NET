#include <src/Header/MC/Vec2.hpp>
#include <src/Header/MC/Vec3.hpp>
#include <src/Header/MC/BlockPos.hpp>

inline MC::Vec3::Vec3(BlockPos pos)
{
    auto& vec = ::Vec3(::BlockPos(pos));
    X = vec.x;
    Y = vec.y;
    Z = vec.z;
}

inline MC::Vec3::Vec3(System::Numerics::Vector3 vec3)
{
    X = vec3.X;
    Y = vec3.Y;
    Z = vec3.Z;
}

MC::BlockPos MC::Vec3::ToBlockPos()
{
    return BlockPos(::BlockPos(::Vec3{ X,Y,Z }));
}

MC::Vec3::operator MC::BlockPos(Vec3 vec)
{
    return vec.ToBlockPos();
}

MC::Vec3::operator System::Numerics::Vector3(Vec3 vec)
{
    return System::Numerics::Vector3(vec.X, vec.Y, vec.Z);
}
