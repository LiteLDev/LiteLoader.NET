#pragma once
#include "Packet.hpp"
#include "Types.hpp"

ref class __Packet :MC::Packet
{
internal:
    std::shared_ptr<::Packet>* s_ptr;

public:
    virtual bool ReleaseHandle() override
    {
        delete s_ptr;
        MC::Packet::ReleaseHandle();

        return true;
    }

    __Packet(std::shared_ptr<::Packet> sharedPtr)
        :Packet(sharedPtr.get())
    {
        s_ptr = new std::shared_ptr<::Packet>(std::move(sharedPtr));
    }
};

namespace MC
{
    public ref class MinecraftPackets __static
    {
    public:
        static Packet^ CreatePacket(MinecraftPacketIds packetId);
    };
}
