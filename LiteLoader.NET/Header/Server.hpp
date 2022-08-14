#pragma once
#include <ServerAPI.h>
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
namespace LLNET::LL
{
public
ref class ServerAPI abstract
{
public:
    inline static String^ GetBdsVersion();
    inline static int GetServerProtocolVersion();
    inline static bool SetServerMotd(String^ d);
};
} // namespace LLNET::LL
