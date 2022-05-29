#pragma once
#include "DynamicCommand.h"
namespace LLNET::DynamicCommand {
	ref class CommandManager {
		ref struct CommandData 
		{
			ICommand^ cmd;
			::DynamicCommandInstance* instance;
		};
	};
}
