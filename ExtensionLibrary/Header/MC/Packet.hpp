#pragma once
#include "../../Tools/.NETGlobal.hpp"
#include  <MC/Packet.hpp>

#include "../../Tools/ClassAdapter.hpp"

namespace MC::Extensions
{
	public ref class Packet
		:public MC::Packet
	{
	public:
		__ctor_ex(Packet, MC::Packet, ::Packet)
	public:

		property unsigned Unk2 { unsigned get(); void set(unsigned value); };
		property MC::PacketReliability ReliableOrdered {MC::PacketReliability get(); void set(MC::PacketReliability value); };
		property uint64_t Unk24 { uint64_t get(); void set(uint64_t value); };
		property uint64_t Unk40 { uint64_t get(); void set(uint64_t value); };
		property uint32_t Incompressible { uint32_t get(); void set(uint32_t value); };
	};
}
