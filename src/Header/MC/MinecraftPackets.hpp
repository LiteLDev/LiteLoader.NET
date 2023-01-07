#pragma once
#include "Packet.hpp"
#include "Types.hpp"

ref class __Packet :MC::Packet
{
internal:
    std::shared_ptr<::Packet>* s_ptr;

    !__Packet()
    {
        delete s_ptr;
        delete static_cast<MC::Packet^>(this);
    }

    virtual ~__Packet()
    {
        this->!__Packet();
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
        static Packet^ CreatePacket(MinecraftPacketId packetId);
    };
}
