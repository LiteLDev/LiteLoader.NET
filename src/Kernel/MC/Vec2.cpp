#include <src/Header/MC/Vec2.hpp>

inline MC::Vec2::Vec2(System::Numerics::Vector2 vec2)
{
    X = vec2.X;
    Y = vec2.Y;
}

MC::Vec2::operator System::Numerics::Vector2(Vec2 vec)
{
    return System::Numerics::Vector2(vec.X, vec.Y);
}
