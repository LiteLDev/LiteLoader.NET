#include <src/Header/MC/SerializedSkin.hpp>

namespace MC
{
    SerializedSkin::SerializedSkin()
        : ClassTemplate(::SerializedSkin())
    {
    }

    SerializedSkin::SerializedSkin(SerializedSkin^ skin)
        : ClassTemplate(::SerializedSkin(skin))
    {
    }

    String^ SerializedSkin::Name::get()
    {
        return marshalString(NativePtr->getName());
    }

    bool SerializedSkin::IsTrustedSkin::get()
    {
        return NativePtr->isTrustedSkin();
    }

    void SerializedSkin::IsTrustedSkin::set(bool value)
    {
        NativePtr->setIsTrustedSkin(value);
    }

    void SerializedSkin::UpdateGeometryName()
    {
        NativePtr->updateGeometryName();
    }

    void SerializedSkin::Read(ReadOnlyBinaryStream^ stream)
    {
        NativePtr->read(stream);
    }

    void SerializedSkin::Write(BinaryStream^ stream)
    {
        NativePtr->write(*stream->NativePtr);
    }
}
