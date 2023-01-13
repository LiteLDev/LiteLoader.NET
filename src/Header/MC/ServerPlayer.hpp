#pragma once
#include <mc/ServerPlayer.hpp>
#include "Player.hpp"

namespace MC
{
    public ref class ServerPlayer : Player
    {
    public:
        __ctor_base(ServerPlayer, ::ServerPlayer, Player);
        __ctor_default_base(ServerPlayer, ::ServerPlayer, Player);
    };
} // namespace MC