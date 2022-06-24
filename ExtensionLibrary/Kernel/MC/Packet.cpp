#include "../../Header/MC/Packet.hpp"

namespace MC::Extensions
{
	unsigned Packet::Unk2::get() {
		return NativePtr->unk2;
	}
	void Packet::Unk2::set(unsigned value) {
		NativePtr->unk2 = value;
	}
	MC::PacketReliability Packet::ReliableOrdered::get() {
		return (MC::PacketReliability)NativePtr->reliableOrdered;
	}
	void Packet::ReliableOrdered::set(MC::PacketReliability value) {
		NativePtr->reliableOrdered = (::PacketReliability)value;
	}
	uint64_t Packet::Unk24::get() {
		return NativePtr->unk2;
	}
	void Packet::Unk24::set(uint64_t value) {
		NativePtr->unk2 = value;
	}
	uint64_t Packet::Unk40::get() {
		return NativePtr->unk2;
	}
	void Packet::Unk40::set(uint64_t value) {
		NativePtr->unk2 = value;
	}
	uint32_t Packet::Incompressible::get() {
		return NativePtr->unk2;
	}
	void Packet::Incompressible::set(uint32_t value) {
		NativePtr->unk2 = value;
	}
}