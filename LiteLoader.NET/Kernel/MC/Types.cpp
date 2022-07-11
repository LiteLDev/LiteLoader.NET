#include "../../Header/MC/Types.hpp"

#include "../../Header/MC/BlockPos.hpp"
#include "../../Header/MC/AABB.hpp"
#include "../../Header/MC/Vec3.hpp"

namespace MC
{
	ActorRuntimeID::ActorRuntimeID()
		: ClassTemplate(::ActorRuntimeID())
	{
	}
	inline long long ActorRuntimeID::get()
	{
		return NativePtr->get();
	}
	inline ActorRuntimeID::operator long long()
	{
		return ((long long)*NativePtr);
	}
} // namespace MC\

namespace MC::Mce
{
	inline  MC::Vec3 Color::ToVec3() {
		return Vec3{ r, g, b };
	}

	inline Color Color::FromVec3(MC::Vec3% k)
	{
		return Color{ k.x, k.y, k.z, 1.0f };
	}

	inline  MC::BlockPos Color::ToBlockPos() {
		return BlockPos{ int(r * 255.0f), int(g * 255.0f), int(b * 255.0f) };
	}

	inline Color Color::fromBlockPos(MC::BlockPos% k) {
		return  Color{ k.x / 255.0f, k.y / 255.0f, k.z / 255.0f, 1.0f };
	}
}
