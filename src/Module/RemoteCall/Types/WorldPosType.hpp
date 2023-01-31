#pragma once
#include <src/Main/ClassTemplate.hpp>

#include <RemoteCallAPI.h>

#include <src/Header/MC/Vec3.hpp>
#include <src/Header/MC/BlockPos.hpp>

namespace RemoteCall
{
    struct WorldPosType;
}

namespace LiteLoader::RemoteCall
{
    public ref class WorldPosType : ClassTemplate<WorldPosType, ::RemoteCall::WorldPosType>/*, IValue*/
    {
    public:
        __ctor_all(WorldPosType, ::RemoteCall::WorldPosType);
        __ctor_default(WorldPosType, ::RemoteCall::WorldPosType);
    public:
        WorldPosType(MC::Vec3 pos, int dimId);
        WorldPosType(MC::Vec3 pos);
        WorldPosType(VALUE_TUPLE<MC::Vec3, int> pos);

        MC::Vec3 Get();

        property MC::Vec3% Pos 
        {
            MC::Vec3% get();
        }

        property MC::BlockPos BlockPos 
        {
            MC::BlockPos get();
        }

        property VALUE_TUPLE<MC::Vec3, int> PosPair
        {
            VALUE_TUPLE<MC::Vec3, int> get();
        }

        property VALUE_TUPLE<MC::BlockPos, int> BlockPosPair
        {
            VALUE_TUPLE<MC::BlockPos, int> get();
        }

        property int DimId 
        {
            int get();
            void set(int value);
        }

    public:
        static operator WorldPosType ^ (MC::Vec3 v);
        static operator MC::Vec3(WorldPosType^ v);
    internal:
        WorldPosType(::RemoteCall::WorldPosType const& v);
    public:
        virtual String^ ToString() override;
    };
}