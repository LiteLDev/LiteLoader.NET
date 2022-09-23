#pragma once
#include <mc/CommandPositionFloat.hpp>
#include <LiteLoader.NET/Header/MC/Types.hpp>
#include "CommandPosition.hpp"
namespace MC
{
public
ref class CommandPositionFloat : public CommandPosition
{
public:
    __ctor_all_base(CommandPositionFloat, ::CommandPositionFloat, CommandPosition);
};
} // namespace MC
