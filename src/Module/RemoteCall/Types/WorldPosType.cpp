#include "WorldPosType.hpp"

#include<src/Header/MC/Vec3.hpp>
#include<src/Header/MC/BlockPos.hpp>

namespace LiteLoader::RemoteCall
{
    inline WorldPosType::WorldPosType(MC::Vec3 pos, int dimId)
        : ClassTemplate(new ::RemoteCall::WorldPosType(pos, dimId), true)
    {
    }

    inline WorldPosType::WorldPosType(MC::Vec3 pos)
        : ClassTemplate(new ::RemoteCall::WorldPosType(pos), true)
    {
    }

    inline WorldPosType::WorldPosType(PAIR<MC::Vec3, int> pos)
        : ClassTemplate(new ::RemoteCall::WorldPosType(pos.Key, pos.Value), true)
    {
    }

    inline WorldPosType::WorldPosType(::RemoteCall::WorldPosType const& v)
        : ClassTemplate(new ::RemoteCall::WorldPosType(v), true)
    {
    }

    inline MC::Vec3 WorldPosType::Get()
    {
        return NativePtr->pos;
    }

    MC::Vec3% WorldPosType::Pos::get()
    {
        return *(MC::Vec3*)&NativePtr->pos;
    }

    MC::BlockPos WorldPosType::BlockPos::get()
    {
        return MC::BlockPos(MC::Vec3(NativePtr->pos));
    }

    PAIR<MC::Vec3, int> WorldPosType::PosPair::get()
    {
        return PAIR<MC::Vec3, int>(*(MC::Vec3*)&NativePtr->pos, NativePtr->dimId);
    }

    PAIR<MC::BlockPos, int> WorldPosType::BlockPosPair::get()
    {
        return PAIR<MC::BlockPos, int>(BlockPos, NativePtr->dimId);
    }

    int WorldPosType::DimId::get()
    {
        return NativePtr->dimId;
    }

    void WorldPosType::DimId::set(int value)
    {
        NativePtr->dimId = value;
    }

    inline WorldPosType::operator WorldPosType ^ (MC::Vec3 v)
    {
        return gcnew WorldPosType(v);
    }

    inline WorldPosType::operator MC::Vec3(WorldPosType^ v)
    {
        return v->Get();
    }

    String^ WorldPosType::ToString()
    {
        return String::Format("{0},{1}", Pos.ToString(), DimId);
    }
}