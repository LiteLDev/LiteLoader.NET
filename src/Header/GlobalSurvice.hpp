#pragma once

#include <src/Main/DotNETGlobal.hpp>

namespace MC
{
    ref class Level;
    ref class CommandRegistry;
}

namespace LiteLoader
{
    public ref class GlobalService sealed
    {
    public:
        static property MC::Level^ Level
        {
            MC::Level^ get();
        }
        
        static property MC::CommandRegistry^ CommandRegistry
        {
            MC::CommandRegistry^ get();
        }

        ////////////////Ptr////////////////

        static property nint_t Level_Native
        {
            nint_t get();
        }
        static property nint_t CommandRegistry_Native
        {
            nint_t get();
        }
        static property nint_t Minecraft_Native
        {
            nint_t get();
        }
        static property nint_t MinecraftCommands_Native
        {
            nint_t get();
        }
        static property nint_t RakNetServerLocator_Native
        {
            nint_t get();
        }
        static property nint_t ServerLevel_Native
        {
            nint_t get();
        }
        static property nint_t ServerNetworkHandler_Native
        {
            nint_t get();
        }
        static property nint_t DBStorage_Native
        {
            nint_t get();
        }
        static property nint_t Scoreboard_Native
        {
            nint_t get();
        }
        static property nint_t AllowListFile_Native
        {
            nint_t get();
        }
        static property nint_t PropertiesSettings_Native
        {
            nint_t get();
        }
        static property nint_t LevelStorage_Native
        {
            nint_t get();
        }

    };
}