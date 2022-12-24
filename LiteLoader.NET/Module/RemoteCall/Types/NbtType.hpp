#pragma once
//#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <LiteLoader.NET/Header/Core/INativeCastable.hpp>
#include <LiteLoader.NET/Main/ClassTemplate.hpp>

using namespace LiteLoader::NET;

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
    public
    ref class NbtType : ClassTemplate<NbtType, ::RemoteCall::NbtType>/*, IValue*/
    {
    internal:
        __ctor_copy(NbtType, ::RemoteCall::NbtType);
        __ctor_move(NbtType, ::RemoteCall::NbtType);
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

