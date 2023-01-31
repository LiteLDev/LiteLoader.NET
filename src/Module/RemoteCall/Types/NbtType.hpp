#pragma once
#include <src/Main/ClassTemplate.hpp>

#include <RemoteCallAPI.h>

namespace RemoteCall
{
    struct NbtType;
}

namespace MC
{
    ref class CompoundTag;
}

namespace LiteLoader::RemoteCall
{
    public ref class NbtType : ClassTemplate<NbtType, ::RemoteCall::NbtType>/*, IValue*/
    {
    public:
        __ctor_all(NbtType, ::RemoteCall::NbtType);
        __ctor_default(NbtType, ::RemoteCall::NbtType);
    public:
        NbtType(MC::CompoundTag^ tag);

        MC::CompoundTag^ Get();

    public:
        static operator NbtType ^ (MC::CompoundTag^ v);
        static operator MC::CompoundTag ^ (NbtType^ v);
    internal:
        NbtType(::RemoteCall::NbtType const& v);
    public:
        virtual String^ ToString() override;
    };
}

