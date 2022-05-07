#pragma once
#include <ServerAPI.h>
#include "../Main/.NETGlobal.hpp"
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
