#pragma once
#include <LiteLoader.NET/Extra/mutex.hpp>
#include <RemoteCallAPI.h>
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <LiteLoader.NET/Tools/NativeCallbackConverter.hpp>
#include <LiteLoader.NET/Main/ClassTemplate.hpp>

#include <LiteLoader.NET/Header/MC/CompoundTag.hpp>
#include <LiteLoader.NET/Header/MC/ItemStack.hpp>
#include <LiteLoader.NET/Header/MC/BlockInstance.hpp>
#include <LiteLoader.NET/Header/MC/Player.hpp>
#include <LiteLoader.NET/Header/MC/Actor.hpp>
#include <LiteLoader.NET/Header/MC/BlockActor.hpp>
#include <LiteLoader.NET/Header/MC/Container.hpp>
#include <LiteLoader.NET/Header/MC/Vec3.hpp>
#include <LiteLoader.NET/Header/MC/BlockPos.hpp>

#include <LiteLoader.NET/Header/Logger/Logger.hpp>

//#define REMOTECALL_DEBUG

#define REMOTECALL_DEBUG_INFO(info)							\
auto _color = Console::ForegroundColor;						\
Console::ForegroundColor = System::ConsoleColor::Yellow;	\
Console::WriteLine(info);									\
Console::ForegroundColor = _color