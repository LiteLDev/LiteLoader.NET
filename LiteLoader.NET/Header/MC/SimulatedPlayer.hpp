#pragma once
#include <MC/SimulatedPlayer.hpp>
#include "BlockPos.hpp"
#include "ServerPlayer.hpp"

namespace MC
{
	ref class Dimension;
    ref class EntityContext;
} // namespace MC

namespace MC
{
    public
    ref class SimulatedPlayer : ServerPlayer
    {
    public:
        __ctor_base(SimulatedPlayer, ::SimulatedPlayer, ServerPlayer);
        
        //property gametest::BaseGameTestHelper^ GameTestHelper;

        static SimulatedPlayer^ Create(String^ name);
        static SimulatedPlayer^ Create(String^ name, AutomaticID<Dimension^, int>^ dimensionId);
        static SimulatedPlayer^ Create(String^ name, MC::BlockPos blockPos);
        static SimulatedPlayer^ Create(String^ name, MC::BlockPos blockPos, AutomaticID<Dimension^, int>^ dimensionId);
        //static SimulatedPlayer^ TryGetFromEntity(EntityContext^ entity, bool _0);
        
        inline bool SimulateDestroy();
        inline bool SimulateUseItem();
        inline bool SimulateSneak();
        inline bool SimulateStopSneaking();
        inline bool SimulateAttack();
        inline bool SimulateAttack(Actor^ actor);
        //inline bool SimulateDestroyBlock(MC::BlockPos blockPos, ScriptModuleMinecraft::ScriptFacing facing);
        inline void SimulateDisconnect();
        inline bool SimulateGiveItem(ItemStack^ item, bool _0);
        inline bool SimulateInteract();
        inline bool SimulateInteract(Actor^ actor);
        //inline bool SimulateInteract(MC::BlockPos blockPos, ScriptModuleMinecraft::ScriptFacing facing);
        inline bool SimulateJump();
        inline void SimulateLocalMove(Vec3 target, float speed);
	    inline void SimulateLookAt(Actor^ actor);
	    inline void SimulateLookAt(MC::BlockPos blockPos);
	    inline void SimulateLookAt(Vec3 target);
	    inline void SimulateMoveToLocation(Vec3 target, float speed);
	    inline ScriptModuleMinecraft::ScriptNavigationResult SimulateNavigateToEntity(Actor^ actor, float speed);
	    inline ScriptModuleMinecraft::ScriptNavigationResult SimulateNavigateToLocation(Vec3 target, float speed);
	    inline void SimulateNavigateToLocations(List<Vec3>^ locations, float speed);
	    inline void SimulateSetBodyRotation(float _0);
	    inline bool SimulateSetItem(ItemStack^ item, bool _0, int _1);
	    inline void SimulateStopDestroyingBlock();
	    inline void SimulateStopInteracting();
	    inline void SimulateStopMoving();
	    inline void SimulateStopUsingItem();
	    inline bool SimulateUseItem(ItemStack^ item);
	    inline bool SimulateUseItemInSlot(int slot);
	    //inline bool SimulateUseItemInSlotOnBlock(int slot, MC::BlockPos blockPos, ScriptModuleMinecraft::ScriptFacing facing, Vec3 target);
	    //inline bool SimulateUseItemOnBlock(ItemStack^ item, MC::BlockPos blockPos, ScriptModuleMinecraft::ScriptFacing facing, Vec3 target);
	    inline void SimulateWorldMove(Vec3 target, float speed);
    };
}
