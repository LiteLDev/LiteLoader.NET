#pragma once
//#include "DotNETGlobal.hpp"


namespace LiteLoader::Logger
{
    ref class Logger;
}

ref class GlobalClass __static
{
internal:
    static const String^ RUNTIME_SHARED_LIB_DIR;
    static const LiteLoader::Logger::Logger^ logger;
    static void Init();
    static GlobalClass() { Init(); }
    static HMODULE GetCurrentModule(Assembly^ asm_);
};
