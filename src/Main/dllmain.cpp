#pragma comment(lib, "../SDK/lib/bedrock_server_api.lib")
#pragma comment(lib, "../SDK/lib/bedrock_server_var.lib")
#pragma comment(lib, "../SDK/lib/SymDBHelper.lib")
#pragma comment(lib, "../SDK/lib/LiteLoader.lib")

#pragma unmanaged
#include <windows.h>
#include <iostream>
#include "Global.hpp"
#include <Utils/WinHelper.h>

#pragma unmanaged
extern void entry();

#pragma unmanaged
extern "C" _declspec(dllexport) void onPostInit()
{
    std::ios::sync_with_stdio(false);
    MODULE = GetCurrentModule();
    entry();
}
