#include <LiteLoader.NET/Header/MC/SimulatedPlayer.hpp>

#include "LiteLoader.NET/Header/MC/ItemStack.hpp"


namespace MC
{
    SimulatedPlayer^ SimulatedPlayer::Create(String^ name)
    {
        return gcnew SimulatedPlayer(::SimulatedPlayer::create(marshalString(name)));
    }

    SimulatedPlayer^ SimulatedPlayer::Create(String^ name, AutomaticID<Dimension^, int>^ dimensionId)
    {
	    return gcnew SimulatedPlayer(::SimulatedPlayer::create(marshalString(name), ::AutomaticID<::Dimension, int>(dimensionId)));
    }

    SimulatedPlayer^ SimulatedPlayer::Create(String^ name, MC::BlockPos blockPos)
    {
	    return gcnew SimulatedPlayer(::SimulatedPlayer::create(marshalString(name), blockPos));
    }

    SimulatedPlayer^ SimulatedPlayer::Create(String^ name, MC::BlockPos blockPos, AutomaticID<Dimension^, int>^ dimensionId)
    {
	    return gcnew SimulatedPlayer(::SimulatedPlayer::create(marshalString(name), blockPos, ::AutomaticID<::Dimension, int>(dimensionId)));
    }

    inline bool SimulatedPlayer::SimulateDestroy()
    {
        return NativePtr->simulateDestroy();
    }

    inline bool SimulatedPlayer::SimulateUseItem()
    {
        return NativePtr->simulateUseItem();
    }

    inline bool SimulatedPlayer::SimulateSneak()
    {
        return NativePtr->simulateSneak();
    }

    inline bool SimulatedPlayer::SimulateStopSneaking()
    {
        return NativePtr->simulateStopSneaking();
    }

    inline bool SimulatedPlayer::SimulateAttack()
    {
	    return NativePtr->simulateAttack();
    }

    inline bool SimulatedPlayer::SimulateAttack(Actor^ actor)
    {
	    return NativePtr->simulateAttack(actor);
    }

    /*inline bool SimulatedPlayer::SimulateDestroyBlock(MC::BlockPos blockPos, ScriptModuleMinecraft::ScriptFacing facing)
    {
	    return NativePtr->simulateDestroyBlock(blockPos, facing);
    }*/

    inline void SimulatedPlayer::SimulateDisconnect()
    {
	    return NativePtr->simulateDisconnect();
    }

    inline bool SimulatedPlayer::SimulateGiveItem(ItemStack^ item, bool _0)
    {
	    return NativePtr->simulateGiveItem(*item->NativePtr, _0);
    }

    inline bool SimulatedPlayer::SimulateInteract()
    {
	    return NativePtr->simulateInteract();
    }

    inline bool SimulatedPlayer::SimulateInteract(Actor^ actor)
    {
	    return NativePtr->simulateInteract(actor);
    }

    /*inline bool SimulatedPlayer::SimulateInteract(MC::BlockPos blockPos, ScriptModuleMinecraft::ScriptFacing facing)
    {
	    return NativePtr->simulateInteract(blockPos, facing);
    }*/

    inline bool SimulatedPlayer::SimulateJump()
    {
	    return NativePtr->simulateJump();
    }

    inline void SimulatedPlayer::SimulateLocalMove(MC::Vec3 target, float speed)
    {
	    return NativePtr->simulateLocalMove(target, speed);
    }

    inline void SimulatedPlayer::SimulateLookAt(Actor^ actor)
    {
	    return NativePtr->simulateLookAt(actor);
    }

    inline void SimulatedPlayer::SimulateLookAt(MC::BlockPos blockPos)
    {
	    return NativePtr->simulateLookAt(blockPos);
    }

    inline void SimulatedPlayer::SimulateLookAt(MC::Vec3 target)
    {
	    return NativePtr->simulateLookAt(target);
    }

    inline void SimulatedPlayer::SimulateMoveToLocation(MC::Vec3 target, float speed)
    {
	    return NativePtr->simulateMoveToLocation(target, speed);
    }

    inline ScriptModuleMinecraft::ScriptNavigationResult SimulatedPlayer::SimulateNavigateToEntity(Actor^ actor, float speed)
    {
	    return NativePtr->simulateNavigateToEntity(actor, speed);
    }

    inline ScriptModuleMinecraft::ScriptNavigationResult SimulatedPlayer::SimulateNavigateToLocation(MC::Vec3 target, float speed)
    {
	    return NativePtr->simulateNavigateToLocation(target, speed);
    }

    inline void SimulatedPlayer::SimulateNavigateToLocations(List<Vec3>^ locations, float speed)
    {
        auto count = locations->Count;
		std::vector<::Vec3> stdvector(count);
		for (int i = 0; i < count; ++i)
			stdvector.emplace_back(::Vec3(locations[i]));
	    return NativePtr->simulateNavigateToLocations(std::move(stdvector), speed);
    }

    inline void SimulatedPlayer::SimulateSetBodyRotation(float _0)
    {
	    return NativePtr->simulateSetBodyRotation(_0);
    }

    inline bool SimulatedPlayer::SimulateSetItem(ItemStack^ item, bool _0, int _1)
    {
	    return NativePtr->simulateSetItem(*item->NativePtr, _0, _1);
    }

    inline void SimulatedPlayer::SimulateStopDestroyingBlock()
    {
	    return NativePtr->simulateStopDestroyingBlock();
    }

    inline void SimulatedPlayer::SimulateStopInteracting()
    {
	    return NativePtr->simulateStopInteracting();
    }

    inline void SimulatedPlayer::SimulateStopMoving()
    {
	    return NativePtr->simulateStopMoving();
    }

    inline void SimulatedPlayer::SimulateStopUsingItem()
    {
	    return NativePtr->simulateStopUsingItem();
    }

    inline bool SimulatedPlayer::SimulateUseItem(ItemStack^ item)
    {
	    return NativePtr->simulateUseItem(*item->NativePtr);
    }

    inline bool SimulatedPlayer::SimulateUseItemInSlot(int slot)
    {
	    return NativePtr->simulateUseItemInSlot(slot);
    }

    /*inline bool SimulatedPlayer::SimulateUseItemInSlotOnBlock(int slot, MC::BlockPos blockPos, ScriptModuleMinecraft::ScriptFacing facing, MC::Vec3 target)
    {
	    return NativePtr->simulateUseItemInSlotOnBlock(slot, blockPos, facing, target);
    }*/

    /*inline bool SimulatedPlayer::SimulateUseItemOnBlock(ItemStack^ item, MC::BlockPos blockPos, ScriptModuleMinecraft::ScriptFacing facing, MC::Vec3 target)
    {
	    return NativePtr->simulateUseItemOnBlock(*item->NativePtr, blockPos, facing, target);
    }*/

    inline void SimulatedPlayer::SimulateWorldMove(MC::Vec3 target, float speed)
    {
	    return NativePtr->simulateWorldMove(target, speed);
    }
}
