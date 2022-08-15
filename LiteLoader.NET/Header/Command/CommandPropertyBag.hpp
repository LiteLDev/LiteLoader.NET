#pragma once
#include <MC/CommandPropertyBag.hpp>
#include <LiteLoader.NET/Header/MC/Types.hpp>

namespace MC
{
value class Vec3;
}

namespace MC
{
public
ref class CommandPropertyBag : ClassTemplate<CommandPropertyBag, ::CommandPropertyBag>
{
public:
    __ctor(CommandPropertyBag, ::CommandPropertyBag);

    inline void AddToResultList(String^ str0, String^ str1);
    inline void Set(String^ str, BlockPos bp);
    inline void Set(String^ str, Vec3 bp);
};
} // namespace MC
