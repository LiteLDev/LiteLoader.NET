#include "../../Header/MC/MinecraftPackets.hpp"
#include "MC/MinecraftPackets.hpp"

MC::Packet^ MC::MinecraftPackets::CreatePacket(MinecraftPacketId packetId)
{
	return static_cast<MC::Packet^>(gcnew __Packet(::MinecraftPackets::createPacket(static_cast<MinecraftPacketIds>(packetId))));
}
