#pragma unmanaged
#include <Utils/WinHelper.h>
#include <LLAPI.h>

#include "Config.h"

using namespace std;

#pragma unmanaged
extern void LoadMain();


#pragma unmanaged
void LoadConfigFile()
{
    auto content = ReadAllFile(LITELOADER_CONFIG_FILE);
}

#pragma unmanaged
void entry()
{
    _set_se_translator(seh_exception::TranslateSEHtoCE);

    LL::registerPlugin(LLNET_LOADER_NAME, LLNET_LOADER_DESCRIPTION, LITELOADER_VERSION, {{"GitHub","github.com/LiteLDev/LiteLoader.Net"}});

    LoadMain();
}