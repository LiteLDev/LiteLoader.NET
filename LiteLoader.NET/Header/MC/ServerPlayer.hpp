#pragma once
#include <MC/ServerPlayer.hpp>
#include "Player.hpp"

namespace MC
{
    public ref class ServerPlayer : Player
    {
    public:
        __ctor_base(ServerPlayer, ::ServerPlayer, Player);
    };
} // namespace MC