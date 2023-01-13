#pragma once
#include <mc/BlockPalette.hpp>
#include "Types.hpp"
namespace MC
{
public
ref class BlockPalette : ClassTemplate<BlockPalette, ::BlockPalette>
{
public:
    __ctor(BlockPalette, ::BlockPalette);
    __ctor_default(BlockPalette, ::BlockPalette);
};
} // namespace MC