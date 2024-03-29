#pragma once
#include <mc/CommandArea.hpp>
#include <src/Header/MC/Types.hpp>
namespace MC
{
public
ref class CommandArea : ClassTemplate<CommandArea, ::CommandArea>
{
public:
    __ctor(CommandArea, ::CommandArea);
    __ctor_default(CommandArea, ::CommandArea);
};
} // namespace MC
