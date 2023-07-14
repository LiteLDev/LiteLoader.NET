#pragma once
#include <mc/Block.hpp>
#include "Types.hpp"
#include <src/Header/MC/HashedString.hpp>

namespace MC
{
ref class CompoundTag;
value class Vec3;
}

namespace MC
{
public
ref class Block : ClassTemplate<Block, ::Block>
{
public:
    __ctor(Block, ::Block);
    __ctor_default(Block, ::Block);

    inline static Block ^ Create(const String ^ str, unsigned short tileData);
    inline static Block ^ Create(CompoundTag ^ nbt);

    property HashedString^ Name { HashedString ^ get(); };
    property CompoundTag ^ Nbt { CompoundTag ^ get(); };

    property int Id
    {
        int get();
    }
    property unsigned short TileData
    {
        unsigned short get();
    }

#ifdef MANUAL_MAINTENANCE

    property bool CausesFreezeEffect
    {
        bool get();
    }

    property bool AllowsRunes
    {
        bool get();
    }

    property int BurnOdds
    {
        int get();
    }

    property int Color
    {
        int get();
    }

    /*property MC::Block ^ DefaultState {
        MC::Block ^ get();
    }*/

        property ::String^
        DescriptionId {
            ::String^ get();
        }

        property float DestroySpeed
    {
        float get();
    }

    property int FlameOdds
    {
        int get();
    }

    property float Friction
    {
        float get();
    }

    property unsigned int RuntimeId
    {
        unsigned int get();
    }

    property MC::CompoundTag ^ SerializationId {
        MC::CompoundTag ^ get();
    }

        property float Thickness
    {
        float get();
    }

    property float Translucency
    {
        float get();
    }

    property int Variant
    {
        int get();
    }

    property bool HasBlockEntity
    {
        bool get();
    }

    property bool HasComparatorSignal
    {
        bool get();
    }

    //property bool HasRuntimeId
    //{
    //    bool get();
    //}

    property bool IsBounceBlock
    {
        bool get();
    }

    property bool IsButtonBlock
    {
        bool get();
    }

    property bool IsContainerBlock
    {
        bool get();
    }

    property bool IsCropBlock
    {
        bool get();
    }

    property bool IsDoorBlock
    {
        bool get();
    }

    property bool IsFenceBlock
    {
        bool get();
    }

    property bool IsFenceGateBlock
    {
        bool get();
    }

    //property bool IsHeavy
    //{
    //    bool get();
    //}

    property bool IsInteractiveBlock
    {
        bool get();
    }

    property bool IsLeverBlock
    {
        bool get();
    }

    property bool IsMotionBlockingBlock
    {
        bool get();
    }

    property bool IsRailBlock
    {
        bool get();
    }

    property bool IsSignalSource
    {
        bool get();
    }

    property bool IsSlabBlock
    {
        bool get();
    }

    property bool IsSolid
    {
        bool get();
    }

    property bool IsSolidBlockingBlock
    {
        bool get();
    }

    property bool IsSolidBlockingBlockAndNotSignalSource
    {
        bool get();
    }

    property bool IsStairBlock
    {
        bool get();
    }

    //property bool IsStandingSign
    //{
    //    bool get();
    //}

    property bool IsStemBlock
    {
        bool get();
    }

    property bool IsThinFenceBlock
    {
        bool get();
    }

    property bool IsUnbreakable
    {
        bool get();
    }

    property bool IsWallBlock
    {
        bool get();
    }

    property bool IsWaterBlocking
    {
        bool get();
    }

    property bool MayPick
    {
        bool get();
    }

    property bool PushesOutItems
    {
        bool get();
    }

    property bool PushesUpFallingBlocks
    {
        bool get();
    }

    ::String^ BuildDescriptionId();

    ::String^ BuildDescriptionName();

    void CacheComponentData();

    bool CanBeBrokenFromFalling();

    bool CanBeOriginalSurface();

    bool CanConnect(MC::Block ^ _0, unsigned char _1, MC::Block ^ _2);

    bool CanHaveExtraData();

    bool CanHurtAndBreakItem();

    bool CanInstatick();

    void GetDebugText(::System::Collections::Generic::IList<::String^> ^ _0, MC::BlockPos _1);

    bool HasTag(unsigned long long _0);

    bool IgnoreEntitiesOnPistonMove();

    bool IsPreservingMediumWhenPlaced(MC::Block ^ _0);

    static bool operator!=(MC::Block ^ __op, MC::Block ^ _0);

    static bool operator==(MC::Block ^ __op, MC::Block ^ _0);

    virtual bool Equals(::System::Object ^ obj) override;

    MC::Vec3 RandomlyModifyPosition(MC::BlockPos _0);

    bool ShouldRandomTick();

    bool ShouldRandomTickExtraLayer();

    ::String^ ToDebugString();

    MC::Block ^ TryGetInfested();

    MC::Block ^ TryGetUninfested();

    static property ::String^ BLOCK_DESCRIPTION_PREFIX {
        ::String^ get();
    }

        static property float SIZE_OFFSET
    {
        float get();
    }
#endif // INCLUDE_MCAPI
};
} // namespace MC
