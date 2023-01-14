#include <src/Header/GlobalSurvice.hpp>

#include <mc/CommandParameterData.hpp>

#include <src/Header/MC/Level.hpp>
#include <src/Header/Command/CommandRegistry.hpp>


#include <mc/RakNet.hpp>
#include <mc/Minecraft.hpp>
#include <mc/MinecraftCommands.hpp>
#include <mc/RakNetServerLocator.hpp>
#include <mc/ServerLevel.hpp>
#include <mc/ServerNetworkHandler.hpp>
#include <mc/DBStorage.hpp>
#include <mc/Scoreboard.hpp>
#include <mc/AllowListFile.hpp>
#include <mc/PropertiesSettings.hpp>
#include <mc/LevelStorage.hpp>
#include <GlobalServiceAPI.h>

namespace LiteLoader
{
    MC::Level^ GlobalService::Level::get()
    {
        if (Global<::Level> != nullptr)
        {
            return gcnew MC::Level(Global<::Level>);
        }
        return nullptr;
    }
    
    MC::CommandRegistry^ GlobalService::CommandRegistry::get()
    {
        if (Global<::CommandRegistry> != nullptr)
        {
            return gcnew MC::CommandRegistry(Global<::CommandRegistry>);
        }
        return nullptr;
    }


    nint_t GlobalService::Level_Native::get()
    {
        if (Global<::Level> != nullptr)
        {
            return nint_t(Global<::Level>);
        }
        return nint_t::Zero;
    }
    nint_t GlobalService::CommandRegistry_Native::get()
    {
        if (Global<::CommandRegistry> != nullptr)
        {
            return nint_t(Global<::CommandRegistry>);
        }
        return nint_t::Zero;
    }
    nint_t GlobalService::Minecraft_Native::get()
    {
        if (Global<::Minecraft> != nullptr)
        {
            return nint_t(Global<::Minecraft>);
        }
        return nint_t::Zero;
    }
    nint_t GlobalService::MinecraftCommands_Native::get()
    {
        if (Global<::MinecraftCommands> != nullptr)
        {
            return nint_t(Global<::MinecraftCommands>);
        }
        return nint_t::Zero;
    }
    nint_t GlobalService::RakNetServerLocator_Native::get()
    {
        if (Global<::RakNetServerLocator> != nullptr)
        {
            return nint_t(Global<::RakNetServerLocator>);
        }
        return nint_t::Zero;
    }
    nint_t GlobalService::ServerLevel_Native::get()
    {
        if (Global<::ServerLevel> != nullptr)
        {
            return nint_t(Global<::ServerLevel>);
        }
        return nint_t::Zero;
    }
    nint_t GlobalService::ServerNetworkHandler_Native::get()
    {
        if (Global<::ServerNetworkHandler> != nullptr)
        {
            return nint_t(Global<::ServerNetworkHandler>);
        }
        return nint_t::Zero;
    }
    nint_t GlobalService::DBStorage_Native::get()
    {
        if (Global<::DBStorage> != nullptr)
        {
            return nint_t(Global<::DBStorage>);
        }
        return nint_t::Zero;
    }
    nint_t GlobalService::Scoreboard_Native::get()
    {
        if (Global<::Scoreboard> != nullptr)
        {
            return nint_t(Global<::Scoreboard>);
        }
        return nint_t::Zero;
    }
    nint_t GlobalService::AllowListFile_Native::get()
    {
        if (Global<::AllowListFile> != nullptr)
        {
            return nint_t(Global<::AllowListFile>);
        }
        return nint_t::Zero;
    }
    nint_t GlobalService::PropertiesSettings_Native::get()
    {
        if (Global<::PropertiesSettings> != nullptr)
        {
            return nint_t(Global<::PropertiesSettings>);
        }
        return nint_t::Zero;
    }
    nint_t GlobalService::LevelStorage_Native::get()
    {
        if (Global<::LevelStorage> != nullptr)
        {
            return nint_t(Global<::LevelStorage>);
        }
        return nint_t::Zero;
    }
}