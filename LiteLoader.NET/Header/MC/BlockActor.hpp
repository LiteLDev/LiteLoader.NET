#pragma once
#include <MC/BlockActor.hpp>
#include "Types.hpp"

namespace MC
{
ref class Block;
ref class CompoundTag;
}

namespace MC
{
public
ref class BlockActor : ClassTemplate<BlockActor, ::BlockActor>
{
public:
    __ctor(BlockActor, ::BlockActor);

    inline static unsigned int getBlockEntityType(Block ^ block);

    inline bool RefreshData();
    inline CompoundTag ^ GetNbt();
    inline bool SetNbt(CompoundTag ^ nbt);

#ifdef INCLUDE_MCAPI
    property bool CustomNameSaved
    {
        bool get();
        void set(bool);
    }

    property bool HasAlphaLayer
    {
        bool get();
    }

    property ::String^ CustomName {
        ::String^ get();
        void set(::String^);
    }

        property ::String^
        Name {
            ::String^ get();
        }

        property int RepairCost
    {
        int get();
    }

    property float DeletionDelayTimeSeconds
    {
        float get();
    }

    property MC::AABB ^ AABB {
        MC::AABB ^ get();
    }

        property MC::BlockPos ^
        Position {
            MC::BlockPos ^ get();
        }

        property bool IgnoreLighting
    {
        bool get();
        void set(bool);
    }

    virtual void UnkVfn12();

    virtual void TriggerEvent(int _0, int _1);

    virtual void ClearCache();

    virtual void UnkVfn16();

    virtual void GetDebugText(::System::Collections::Generic::List<::String^> ^ _0, MC::BlockPos ^ _1);

    virtual void UnkVfn28();

    virtual void UnkVfn29();

    virtual void UnkVfn31();

    virtual void UnkVfn32();

    virtual void UnkVfn33();

    void MoveTo(MC::BlockPos ^ _0);

    void SetChanged();

    void SetMovable(bool _0);
#endif // INCLUDE_MCAPI
};
} // namespace MC