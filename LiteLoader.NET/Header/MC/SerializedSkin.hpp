#pragma once
#include <MC/SerializedSkin.hpp>
#include "Types.hpp"
#include "ReadOnlyBinaryStream.hpp"
#include "BinaryStream.hpp"

namespace MC
{
    public ref class SerializedSkin : ClassTemplate<SerializedSkin, ::SerializedSkin>
    {
    public:
        __ctor(SerializedSkin, ::SerializedSkin);

        SerializedSkin();
        SerializedSkin(SerializedSkin^ skin);

        property String^ Name { String^ get(); }
        property bool IsTrustedSkin { bool get(); void set(bool value); }
        property bool UseBlinkingAnimation { bool get(); }

        void UpdateGeometryName();
        bool Read(ReadOnlyBinaryStream^ stream);
        void Write(BinaryStream^ stream);
    };
}
