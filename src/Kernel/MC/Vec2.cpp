#include <src/Header/MC/Vec2.hpp>

inline MC::Vec2::Vec2(System::Numerics::Vector2 vec2)
{
    x = vec2.X;
    y = vec2.Y;
}
