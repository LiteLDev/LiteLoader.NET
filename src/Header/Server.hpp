#pragma once
#include <ServerAPI.h>
#include <src/Main/DotNETGlobal.hpp>
namespace LiteLoader
{
public
ref class ServerAPI __static
{
public:
    property static String^ BdsVersion
    {
        String^ get();
    }
    property static int ServerProtocolVersion
    {
        int get();
    }
    inline static bool SetServerMotd(String^ d);
};
} // namespace LiteLoader
