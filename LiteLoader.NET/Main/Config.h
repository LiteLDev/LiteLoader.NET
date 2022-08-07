#pragma once
#include "Info.h"

#define LLNET_LOADER_NAME_WITH_EXTENSION "LiteLoader.NET.dll"



#define LLNET_PLUGIN_ENTRY_CLASS "PluginMain.Plugin"

#define LLNET_PLUGIN_ENTRY_METHOD "OnPostInit"

#define LLNET_MANAGED_ENTRY_CLASS "LLNET.__Entry, LiteLoader.NET"

#define LLNET_MANAGED_ENTRY_DELEGATE_TYPE "LLNET.__Entry+EntryPropotype, LiteLoader.NET"

#define LLNET_MANAGED_ENTRY_METHOD "InitAndLoadPlugins"



#define LLNET_PLUGINS_LOAD_DIR "plugins"

#define LLNET_LIBRARY_DIR_DOTNETONLY "plugins/lib/managed"

#define LLNET_RUNTIME_CONFIG_JSON_PATH "plugins/LiteLoader/LiteLoader.NET.runtimeconfig.json"

#define LLNET_LOADER_PATH "plugins/LiteLoader/LiteLoader.NET.dll"



#define LITELOADER_CONFIG_FILE "plugins/LiteLoader/LiteLoader.json"

#define LITELOADER_LIBRARY_DIR "plugins/lib"

#define LITELOADER_VERSION LL::getLoaderVersion()



#define DOTNET_RUNTIME_DIR "plugins/lib/managed/dotnet"


//#define DOTNET_NETHOST_DLL_PATH "plugins/lib/managed/nethost.dll"


//#define INCLUDE_MCAPI

#define MANUAL_MAINTENANCE