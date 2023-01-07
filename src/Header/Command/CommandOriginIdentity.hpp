#pragma once
#include <mc/CommandOriginIdentity.hpp>
#include <src/Header/MC/Types.hpp>
namespace MC
{
public
ref struct CommandOriginIdentity : ClassTemplate<CommandOriginIdentity, ::CommandOriginIdentity>
{
public:
    __ctor(CommandOriginIdentity, ::CommandOriginIdentity);
};
} // namespace MC
