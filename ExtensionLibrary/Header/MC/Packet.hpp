#pragma once
#include "../../Tools/.NETGlobal.hpp"
#include  <MC/Packet.hpp>

#include "../../Tools/ClassAdapter.hpp"

namespace MC::Extensions
{
	public ref class PacketEX
		:public MC::Packet
	{
	public:
		__ctor_ex(PacketEX, MC::Packet, ::Packet)
	public:

		property unsigned Unk2 { unsigned get(); void set(unsigned value); };
		property MC::PacketReliability ReliableOrdered {MC::PacketReliability get(); void set(MC::PacketReliability value); };
		property uint32_t Unk24 { uint32_t get(); void set(uint32_t value); };
		property uint32_t Unk40 { uint32_t get(); void set(uint32_t value); };
		property uint32_t Incompressible { uint32_t get(); void set(uint32_t value); };
	};
}
