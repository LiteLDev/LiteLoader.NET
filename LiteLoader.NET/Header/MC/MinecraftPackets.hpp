#pragma once
#include "Packet.hpp"
#include "Types.hpp"

namespace MC
{
    public ref class MinecraftPackets abstract sealed
    {
    public:
        static Packet^ CreatePacket(MinecraftPacketId packetId);
    };
}
