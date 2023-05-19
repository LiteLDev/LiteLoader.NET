#include <src/Header/MC/Packet.hpp>
namespace MC
{
} // namespace MC

#ifdef MANUAL_MAINTENANCE
unsigned int MC::Packet::Unk2::get()
{
    return NativePtr->unk2;
}

void MC::Packet::Unk2::set(unsigned int value)
{
    NativePtr->unk2 = value;
}

MC::PacketReliability MC::Packet::ReliableOrdered::get()
{
    return static_cast<PacketReliability>(NativePtr->reliableOrdered);
}

void MC::Packet::ReliableOrdered::set(MC::PacketReliability value)
{
    NativePtr->reliableOrdered = static_cast<::PacketReliability>(value);
}

unsigned char MC::Packet::ClientSubId::get()
{
    return NativePtr->clientSubId;
}

void MC::Packet::ClientSubId::set(unsigned char value)
{
    NativePtr->clientSubId = value;
}

unsigned long long MC::Packet::Unk24::get()
{
    return NativePtr->unk24;
}

void MC::Packet::Unk24::set(unsigned long long value)
{
    NativePtr->unk24 = value;
}

unsigned long long MC::Packet::Unk40::get()
{
    return NativePtr->unk40;
}

void MC::Packet::Unk40::set(unsigned long long value)
{
    NativePtr->unk40 = value;
}

unsigned int MC::Packet::Incompressible::get()
{
    return NativePtr->incompressible;
}

void MC::Packet::Incompressible::set(unsigned int value)
{
    NativePtr->incompressible = value;
}

MC::MinecraftPacketIds MC::Packet::Id::get()
{
    return static_cast<MinecraftPacketIds>(NativePtr->getId());
}

String^ MC::Packet::Name::get()
{
    return marshalString(NativePtr->getName());
}

bool MC::Packet::DisallowBatching()
{
    return NativePtr->disallowBatching();
}

void MC::Packet::Write([Out]BinaryStream^ resultStream)
{
    ::BinaryStream stream = ::BinaryStream();
    NativePtr->write(stream);
    resultStream = gcnew BinaryStream(&stream);
}

MC::StreamReadResult MC::Packet::Read(ReadOnlyBinaryStream^ stream)
{
    return static_cast<StreamReadResult>(NativePtr->read(*stream->NativePtr));
}

#endif // INCLUDE_MCAPI
