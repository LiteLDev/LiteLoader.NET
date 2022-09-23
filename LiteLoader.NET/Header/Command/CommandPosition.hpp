#pragma once
#include <mc/CommandPosition.hpp>
#include <LiteLoader.NET/Header/MC/Types.hpp>

namespace MC
{
ref class CommandOrigin;
value class Vec3;
value class BlockPos;
ref class CompoundTag;
}

namespace MC
{
public
ref class CommandPosition : ClassTemplate<CommandPosition, ::CommandPosition>
{
public:
    __ctor_all(CommandPosition, ::CommandPosition);

    static CommandPosition ^ Create(Vec3 vec);
    static CommandPosition ^ Create();
    BlockPos GetBlockPos(int v1, CommandOrigin ^ co, Vec3 vec);
    BlockPos GetBlockPos(Vec3 vec0, Vec3 vec1);
    Vec3 GetPosition(Vec3 vec0, Vec3 vec1);
    Vec3 GetPosition(int v1,CommandOrigin ^ co, Vec3 vec0);
    void Load(CompoundTag ^ ct);
    CompoundTag ^ Serialize();
};
} // namespace MC
