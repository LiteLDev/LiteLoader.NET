#include "BlockPosType.hpp"

#include<src/Header/MC/Vec3.hpp>
#include<src/Header/MC/BlockPos.hpp>

namespace LiteLoader::RemoteCall
{
    inline BlockPosType::BlockPosType(MC::BlockPos pos, int dimId)
        : ClassTemplate(new ::RemoteCall::BlockPosType(pos, dimId), true)
    {
    }

    inline BlockPosType::BlockPosType(MC::BlockPos pos)
        : ClassTemplate(new ::RemoteCall::BlockPosType(pos), true)
    {
    }

    inline BlockPosType::BlockPosType(PAIR<MC::BlockPos, int> pos)
        : ClassTemplate(new ::RemoteCall::BlockPosType(pos.Key, pos.Value), true)
    {
    }

    inline BlockPosType::BlockPosType(::RemoteCall::BlockPosType const& v)
        : ClassTemplate(new ::RemoteCall::BlockPosType(v), true)
    {
    }

    inline MC::BlockPos BlockPosType::Get()
    {
        return NativePtr->pos;
    }

    MC::BlockPos% BlockPosType::Pos::get()
    {
        return *(MC::BlockPos*)&NativePtr->pos;
    }

    MC::Vec3 BlockPosType::Vec3::get()
    {
        return MC::Vec3(MC::Vec3(NativePtr->pos));
    }

    PAIR<MC::Vec3, int> BlockPosType::Vec3Pair::get()
    {
        return PAIR<MC::Vec3, int>(Vec3, NativePtr->dimId);
    }

    PAIR<MC::BlockPos, int> BlockPosType::BlockPosPair::get()
    {
        return PAIR<MC::BlockPos, int>(MC::BlockPos(NativePtr->pos), NativePtr->dimId);
    }

    int BlockPosType::DimId::get()
    {
        return NativePtr->dimId;
    }

    void BlockPosType::DimId::set(int value)
    {
        NativePtr->dimId = value;
    }

    inline BlockPosType::operator BlockPosType ^ (MC::BlockPos v)
    {
        return gcnew BlockPosType(v);
    }

    inline BlockPosType::operator MC::BlockPos(BlockPosType^ v)
    {
        return v->Get();
    }

    String^ BlockPosType::ToString()
    {
        return String::Format("{0},{1}", Pos.ToString(), DimId);
    }
}