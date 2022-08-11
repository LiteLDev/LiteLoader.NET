#pragma once
#include "../../Extra/mutex.h"
#include <RemoteCallAPI.h>
#include "../../Main/.NETGlobal.hpp"
#include "../../Tools/NativeCallbackConverter.hpp"
#include "../../Main/ClassTemplate.h"

#include "../../Header/MC/CompoundTag.hpp"
#include "../../Header/MC/ItemStack.hpp"
#include "../../Header/MC/BlockInstance.hpp"
#include "../../Header/MC/Player.hpp"
#include "../../Header/MC/Actor.hpp"
#include "../../Header/MC/BlockActor.hpp"
#include "../../Header/MC/Container.hpp"
#include "../../Header/MC/Vec3.hpp"
#include "../../Header/MC/BlockPos.hpp"

#include "../../Header/Logger/Logger.hpp"

//#define REMOTECALL_DEBUG

#define REMOTECALL_DEBUG_INFO(info)							\
auto _color = Console::ForegroundColor;						\
Console::ForegroundColor = System::ConsoleColor::Yellow;	\
Console::WriteLine(info);									\
Console::ForegroundColor = _color