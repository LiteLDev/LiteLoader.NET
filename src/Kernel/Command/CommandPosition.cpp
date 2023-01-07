#include <src/Header/Command/CommandPosition.hpp>
#include <src/Header/Command/CommandOrigin.hpp>
#include <src/Header/MC/BlockPos.hpp>
#include <src/Header/MC/Vec3.hpp>
#include <src/Header/MC/CompoundTag.hpp>
namespace MC
{

    CommandPosition^ CommandPosition::Create(Vec3 vec)
    {
        return gcnew CommandPosition(::CommandPosition(vec));
    }

    CommandPosition^ CommandPosition::Create()
    {
        return gcnew CommandPosition(::CommandPosition());
    }

    BlockPos MC::CommandPosition::GetBlockPos(int v1, CommandOrigin ^ co, Vec3 vec)
    {
        return BlockPos(NativePtr->getBlockPos(v1, (::CommandOrigin&)co, (::Vec3&)vec));
    }

    BlockPos CommandPosition::GetBlockPos(Vec3 vec0, Vec3 vec1)
    {
        return BlockPos(NativePtr->getBlockPos((::Vec3&)vec0, (::Vec3&)vec1));
    }
    Vec3  CommandPosition::GetPosition(Vec3 vec0, Vec3 vec1)
    {
        return NativePtr->getPosition((::Vec3)vec0, (::Vec3)vec1);
    }
    Vec3  CommandPosition::GetPosition(int v1,CommandOrigin^ co, Vec3 vec0)
    {
        return NativePtr->getPosition(v1,(::CommandOrigin&) co, vec0);
    }
    void CommandPosition::Load(CompoundTag^ ct)
    {
        NativePtr->load(*(ct->NativePtr));
    }
    CompoundTag^ CommandPosition::Serialize()
    {
        return gcnew CompoundTag(&NativePtr->serialize());
    }
} // namespace MC