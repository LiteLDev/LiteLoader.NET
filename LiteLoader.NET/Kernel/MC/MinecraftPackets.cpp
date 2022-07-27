#include "../../Header/MC/MinecraftPackets.hpp"
#include "MC/MinecraftPackets.hpp"

MC::Packet^ MC::MinecraftPackets::CreatePacket(MinecraftPacketId packetId)
{
    return gcnew Packet(::MinecraftPackets::createPacket(static_cast<MinecraftPacketIds>(packetId)).get());
}
