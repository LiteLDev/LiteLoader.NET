#include "../../Header/MC/Packet.hpp"

namespace MC::Extensions
{
	unsigned PacketEX::Unk2::get() {
		return NativePtr->unk2;
	}
	void PacketEX::Unk2::set(unsigned value) {
		NativePtr->unk2 = value;
	}
	MC::PacketReliability PacketEX::ReliableOrdered::get() {
		return (MC::PacketReliability)NativePtr->reliableOrdered;
	}
	void PacketEX::ReliableOrdered::set(MC::PacketReliability value) {
		NativePtr->reliableOrdered = (::PacketReliability)value;
	}
	uint32_t PacketEX::Unk24::get() {
		return NativePtr->unk2;
	}
	void PacketEX::Unk24::set(uint32_t value) {
		NativePtr->unk2 = value;
	}
	uint32_t PacketEX::Unk40::get() {
		return NativePtr->unk2;
	}
	void PacketEX::Unk40::set(uint32_t value) {
		NativePtr->unk2 = value;
	}
	uint32_t PacketEX::Incompressible::get() {
		return NativePtr->unk2;
	}
	void PacketEX::Incompressible::set(uint32_t value) {
		NativePtr->unk2 = value;
	}
}