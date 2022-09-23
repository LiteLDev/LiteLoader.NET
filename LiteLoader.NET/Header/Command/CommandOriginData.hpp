#pragma once
#include <mc/CommandOriginData.hpp>
#include <LiteLoader.NET/Header/MC/Types.hpp>
namespace MC
{
public
ref struct CommandOriginData : ClassTemplate<CommandOriginData, ::CommandOriginData>
{
public:
    __ctor_all(CommandOriginData, ::CommandOriginData);

    static CommandOriginData ^ Create(CommandOriginData ^ val);
    static CommandOriginData ^ Create();
    CommandOriginData ^ operator=(CommandOriginData ^ b);
};
} // namespace MC
