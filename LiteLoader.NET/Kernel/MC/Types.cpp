#include <LiteLoader.NET/Header/MC/Types.hpp>

#include <LiteLoader.NET/Header/MC/BlockPos.hpp>
#include <LiteLoader.NET/Header/MC/AABB.hpp>
#include <LiteLoader.NET/Header/MC/Vec3.hpp>

namespace MC
{
	ActorRuntimeID::ActorRuntimeID()
		: ClassTemplate(::ActorRuntimeID())
	{
	}
	ActorRuntimeID::ActorRuntimeID(unsigned long long id)
		: ClassTemplate(::ActorRuntimeID())
	{
		NativePtr->id = id;
	}
	inline unsigned long long ActorRuntimeID::Id::get()
	{
		return NativePtr->id;
	}
	inline void ActorRuntimeID::Id::set(unsigned long long value)
	{
		NativePtr->id = value;
	}
	inline ActorRuntimeID::operator unsigned long long(ActorRuntimeID^ id)
	{
		return *id->NativePtr;
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
