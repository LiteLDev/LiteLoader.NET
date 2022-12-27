#pragma once
#include <LiteLoader.NET/Main/ClassTemplate.hpp>

#include <RemoteCallAPI.h>

#include <LiteLoader.NET/Header/MC/Vec3.hpp>
#include <LiteLoader.NET/Header/MC/BlockPos.hpp>

namespace RemoteCall
{
    struct BlockPosType;
}

namespace LiteLoader::RemoteCall
{
    public ref class BlockPosType : ClassTemplate<BlockPosType, ::RemoteCall::BlockPosType>/*, IValue*/
    {
    internal:
        __ctor_copy(BlockPosType, ::RemoteCall::BlockPosType);
        __ctor_move(BlockPosType, ::RemoteCall::BlockPosType);
    public:
        BlockPosType(MC::BlockPos pos, int dimId);
        BlockPosType(MC::BlockPos pos);
        BlockPosType(PAIR<MC::BlockPos, int> pos);

        MC::BlockPos Get();

        property MC::BlockPos% Pos
        {
            MC::BlockPos% get();
        }

        property MC::Vec3 Vec3
        {
            MC::Vec3 get();
        }

        property PAIR<MC::Vec3, int> Vec3Pair
        {
            PAIR<MC::Vec3, int> get();
        }

        property PAIR<MC::BlockPos, int> BlockPosPair
        {
            PAIR<MC::BlockPos, int> get();
        }

        property int DimId
        {
            int get();
            void set(int value);
        }

    public:
        static operator BlockPosType ^ (MC::BlockPos v);
        static operator MC::BlockPos(BlockPosType^ v);
    internal:
        BlockPosType(::RemoteCall::BlockPosType const& v);
    public:
        virtual String^ ToString() override;
    };
}