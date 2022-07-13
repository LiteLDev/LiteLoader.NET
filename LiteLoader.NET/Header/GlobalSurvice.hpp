#pragma once

using System::IntPtr;

namespace MC
{
	ref class Level;
	ref class CommandRegistry;
}

namespace LLNET
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

		static property IntPtr Level_Native
		{
			IntPtr get();
		}
		static property IntPtr CommandRegistry_Native
		{
			IntPtr get();
		}
		static property IntPtr Minecraft_Native
		{
			IntPtr get();
		}
		static property IntPtr MinecraftCommands_Native
		{
			IntPtr get();
		}
		static property IntPtr RakNetServerLocator_Native
		{
			IntPtr get();
		}
		static property IntPtr ServerLevel_Native
		{
			IntPtr get();
		}
		static property IntPtr ServerNetworkHandler_Native
		{
			IntPtr get();
		}
		static property IntPtr DBStorage_Native
		{
			IntPtr get();
		}
		static property IntPtr Scoreboard_Native
		{
			IntPtr get();
		}
		static property IntPtr AllowListFile_Native
		{
			IntPtr get();
		}
		static property IntPtr PropertiesSettings_Native
		{
			IntPtr get();
		}
		static property IntPtr LevelStorage_Native
		{
			IntPtr get();
		}

	};
}