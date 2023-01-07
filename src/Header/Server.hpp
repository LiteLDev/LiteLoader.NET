#pragma once
#include <ServerAPI.h>
#include <src/Main/DotNETGlobal.hpp>
namespace LiteLoader
{
public
ref class ServerAPI __static
{
public:
    inline static String^ GetBdsVersion();
    inline static int GetServerProtocolVersion();
    inline static bool SetServerMotd(String^ d);
};
} // namespace LiteLoader
