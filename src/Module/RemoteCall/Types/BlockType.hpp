#pragma once
#include <src/Main/ClassTemplate.hpp>

#include <RemoteCallAPI.h>

namespace RemoteCall
{
    struct BlockType;
}

namespace MC
{
    ref class BlockInstance;
}

namespace LiteLoader::RemoteCall
{
    public ref class BlockType : ClassTemplate<BlockType, ::RemoteCall::BlockType>/*, IValue*/
    {
    internal:
        __ctor_copy(BlockType, ::RemoteCall::BlockType);
        __ctor_move(BlockType, ::RemoteCall::BlockType);
    public:
        BlockType(MC::BlockInstance^ item);

        MC::BlockInstance^ Get();

    public:
        static operator BlockType ^ (MC::BlockInstance^ v);
        static operator MC::BlockInstance ^ (BlockType^ v);
    internal:
        BlockType(::RemoteCall::BlockType const& v);
    public:
        virtual String^ ToString() override;
    };
}