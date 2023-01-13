#pragma once
#include <mc/CommandPositionFloat.hpp>
#include <src/Header/MC/Types.hpp>
#include "CommandPosition.hpp"
namespace MC
{
public
ref class CommandPositionFloat : public CommandPosition
{
public:
    __ctor_all_base(CommandPositionFloat, ::CommandPositionFloat, CommandPosition);
    __ctor_default_base(CommandPositionFloat, ::CommandPositionFloat, CommandPosition);
};
} // namespace MC
