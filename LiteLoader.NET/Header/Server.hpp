#pragma once
#include <ServerAPI.h>
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
namespace LiteLoader
{
public
ref class ServerAPI abstract
{
public:
    inline static String^ GetBdsVersion();
    inline static int GetServerProtocolVersion();
    inline static bool SetServerMotd(String^ d);
};
} // namespace LiteLoader
