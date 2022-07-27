#pragma once
#include <MC/Packet.hpp>
#include "Types.hpp"
#include "BinaryStream.hpp"

namespace MC
{
    public enum class PacketReliability
    {
        Relible,
        RelibleOrdered
    };

    public ref class Packet : ClassTemplate<Packet, ::Packet>
    {
    public:
        __ctor(Packet, ::Packet);

#ifdef MANUAL_MAINTENANCE

        property unsigned int Unk2
        {
            unsigned int get();
            void set(unsigned int);
        }

        property PacketReliability ReliableOrdered
        {
            PacketReliability get();
            void set(PacketReliability);
        }

        property unsigned char ClientSubId
        {
            unsigned char get();
            void set(unsigned char);
        }

        property unsigned long long Unk24
        {
            unsigned long long get();
            void set(unsigned long long);
        }

        property unsigned long long Unk40
        {
            unsigned long long get();
            void set(unsigned long long);
        }

        property unsigned int Incompressible
        {
            unsigned int get();
            void set(unsigned int);
        }

        property MinecraftPacketId Id
        {
            MinecraftPacketId get();
        }

        property String^ Name
        {
            String^ get();
        };

        void Write([Out]BinaryStream^ resultStream);
        StreamReadResult Read(ReadOnlyBinaryStream^ stream);
        bool DisallowBatching();

#endif // INCLUDE_MCAPI
    };
} // namespace MC
