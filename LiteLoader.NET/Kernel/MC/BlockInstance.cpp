#include <LiteLoader.NET/Header/MC/BlockInstance.hpp>

#include <LiteLoader.NET/Header/MC/Block.hpp>
#include <LiteLoader.NET/Header/MC/BlockSource.hpp>
#include <LiteLoader.NET/Header/MC/BlockActor.hpp>
#include <LiteLoader.NET/Header/MC/Container.hpp>
#include <LiteLoader.NET/Header/MC/BlockPos.hpp>
#include <LiteLoader.NET/Header/MC/ItemStack.hpp>

namespace MC
{

inline BlockInstance ^ BlockInstance::CreateBlockinstance(MC::Block ^ block, BlockPos pos, int dimId)
{
    return gcnew BlockInstance(
        ::BlockInstance::createBlockInstance(block, pos, dimId));
}

BlockInstance^ BlockInstance::Create(MC::Block^ block, MC::BlockPos pos, int dimid)
{
    return gcnew MC::BlockInstance(::BlockInstance::createBlockInstance(block->NativePtr, pos, dimid));
}

BlockInstance^ BlockInstance::Create(MC::Block^ block, MC::BlockPos pos)
{
    return gcnew MC::BlockInstance(::BlockInstance::createBlockInstance(block->NativePtr, pos, 0));
}

BlockInstance^ BlockInstance::Create()
{
    return gcnew BlockInstance(::BlockInstance());
}

inline Block ^ BlockInstance::Block::get()
{
    return gcnew MC::Block(NativePtr->getBlock());
}

inline BlockPos BlockInstance::Position::get()
{
    return BlockPos(NativePtr->getPosition());
}

inline BlockSource ^ BlockInstance::BlockSource::get()
{
    return gcnew MC::BlockSource(NativePtr->getBlockSource());
}

inline int BlockInstance::DimensionId::get()
{
    return NativePtr->getDimensionId();
}

inline bool BlockInstance::HasBlockEntity::get()
{
    return NativePtr->hasBlockEntity();
}

inline BlockActor ^ BlockInstance::BlockEntity::get()
{
    if (!HasBlockEntity)
        return nullptr;
    return gcnew BlockActor(NativePtr->getBlockEntity());
}

inline bool BlockInstance::HasContainer::get()
{
    return NativePtr->hasContainer();
}

inline Container ^ BlockInstance::Container::get()
{
    if (!HasContainer)
        return nullptr;
    return gcnew MC::Container(NativePtr->getContainer());
}

inline bool BlockInstance::BreakNaturally(bool isCreativeMode)
{
    return NativePtr->breakNaturally(isCreativeMode);
}

inline bool BlockInstance::BreakNaturally()
{
    return NativePtr->breakNaturally(false);
}

inline bool BlockInstance::BreakNaturally(ItemStack ^ tool, bool isCreativeMode)
{
    return NativePtr->breakNaturally(tool->NativePtr, isCreativeMode);
}

inline bool BlockInstance::BreakNaturally(ItemStack ^ tool)
{
    return NativePtr->breakNaturally(tool->NativePtr, false);
}

inline ItemStack ^ BlockInstance::BlockDrops::get()
{
    return gcnew ItemStack(new ::ItemStack(NativePtr->getBlockDrops()), true);
}

inline bool BlockInstance::IsNull::get()
{
    return NativePtr->isNull();
}

inline short BlockInstance::BlockId::get() {
    return NativePtr->getBlock()->getId();
}

inline bool BlockInstance::operator==(BlockInstance ^ a, BlockInstance ^ b)
{
    return *a->NativePtr == *b->NativePtr;
}
} // namespace MC