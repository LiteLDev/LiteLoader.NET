#include "../Header/GlobalSurvice.hpp"

#include <MC/CommandParameterData.hpp>

#include "../Header/MC/Level.hpp"
#include "../Header/Command/CommandRegistry.hpp"


#include <MC/RakNet.hpp>
#include <MC/Minecraft.hpp>
#include <MC/MinecraftCommands.hpp>
#include <MC/RakNetServerLocator.hpp>
#include <MC/ServerLevel.hpp>
#include <MC/ServerNetworkHandler.hpp>
#include <MC/DBStorage.hpp>
#include <MC/Scoreboard.hpp>
#include <MC/AllowListFile.hpp>
#include <MC/PropertiesSettings.hpp>
#include <MC/LevelStorage.hpp>
#include <GlobalServiceAPI.h>

namespace LLNET
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


	IntPtr GlobalService::Level_Native::get()
	{
		if (Global<::Level> != nullptr)
		{
			return IntPtr(Global<::Level>);
		}
		return IntPtr::Zero;
	}
	IntPtr GlobalService::CommandRegistry_Native::get()
	{
		if (Global<::CommandRegistry> != nullptr)
		{
			return IntPtr(Global<::CommandRegistry>);
		}
		return IntPtr::Zero;
	}
	IntPtr GlobalService::Minecraft_Native::get()
	{
		if (Global<::Minecraft> != nullptr)
		{
			return IntPtr(Global<::Minecraft>);
		}
		return IntPtr::Zero;
	}
	IntPtr GlobalService::MinecraftCommands_Native::get()
	{
		if (Global<::MinecraftCommands> != nullptr)
		{
			return IntPtr(Global<::MinecraftCommands>);
		}
		return IntPtr::Zero;
	}
	IntPtr GlobalService::RakNetServerLocator_Native::get()
	{
		if (Global<::RakNetServerLocator> != nullptr)
		{
			return IntPtr(Global<::RakNetServerLocator>);
		}
		return IntPtr::Zero;
	}
	IntPtr GlobalService::ServerLevel_Native::get()
	{
		if (Global<::ServerLevel> != nullptr)
		{
			return IntPtr(Global<::ServerLevel>);
		}
		return IntPtr::Zero;
	}
	IntPtr GlobalService::ServerNetworkHandler_Native::get()
	{
		if (Global<::ServerNetworkHandler> != nullptr)
		{
			return IntPtr(Global<::ServerNetworkHandler>);
		}
		return IntPtr::Zero;
	}
	IntPtr GlobalService::DBStorage_Native::get()
	{
		if (Global<::DBStorage> != nullptr)
		{
			return IntPtr(Global<::DBStorage>);
		}
		return IntPtr::Zero;
	}
	IntPtr GlobalService::Scoreboard_Native::get()
	{
		if (Global<::Scoreboard> != nullptr)
		{
			return IntPtr(Global<::Scoreboard>);
		}
		return IntPtr::Zero;
	}
	IntPtr GlobalService::AllowListFile_Native::get()
	{
		if (Global<::AllowListFile> != nullptr)
		{
			return IntPtr(Global<::AllowListFile>);
		}
		return IntPtr::Zero;
	}
	IntPtr GlobalService::PropertiesSettings_Native::get()
	{
		if (Global<::PropertiesSettings> != nullptr)
		{
			return IntPtr(Global<::PropertiesSettings>);
		}
		return IntPtr::Zero;
	}
	IntPtr GlobalService::LevelStorage_Native::get()
	{
		if (Global<::LevelStorage> != nullptr)
		{
			return IntPtr(Global<::LevelStorage>);
		}
		return IntPtr::Zero;
	}
}