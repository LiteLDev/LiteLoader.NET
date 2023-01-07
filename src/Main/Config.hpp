#pragma once
#include "Info.hpp"

#define LLNET_LOADER_NAME_WITH_EXTENSION "src.dll"



#define LLNET_PLUGIN_ENTRY_CLASS "PluginMain.Plugin"

#define LLNET_PLUGIN_ENTRY_METHOD "OnPostInit"

#define LLNET_MANAGED_ENTRY_CLASS "LLNET.__Entry, src"

#define LLNET_MANAGED_ENTRY_DELEGATE_TYPE "LLNET.__Entry+EntryPropotype, src"

#define LLNET_MANAGED_ENTRY_METHOD "InitAndLoadPlugins"



#define LLNET_PLUGINS_LOAD_DIR "plugins"

#define LLNET_LIBRARY_DIR_DOTNETONLY "plugins/lib/managed"

#define LLNET_RUNTIME_CONFIG_JSON_PATH "plugins/LiteLoader/src.runtimeconfig.json"

#define LLNET_LOADER_PATH "plugins/LiteLoader/src.dll"



#define LITELOADER_LIBRARY_DIR "plugins/lib"



#define DOTNET_RUNTIME_DIR "plugins/lib/managed/dotnet"



//#define INCLUDE_MCAPI

#define MANUAL_MAINTENANCE
