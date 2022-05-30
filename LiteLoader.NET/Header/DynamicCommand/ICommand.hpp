#pragma once
#include "DynamicCommandAttributes.hpp"

namespace LLNET::DynamicCommand {
	using namespace LLNET::DynamicCommand::Internal;

	public interface class ICommand {
		void Execute(MC::CommandOrigin^ origin, MC::CommandOutput^ output);
	};

	public interface class ICommandEvent {
		void BeforeCommandSetup(DynamicCommandInstance^ cmd);
		void AfterCommandSetup(DynamicCommandInstance^ cmd);
	};

	public interface class ICommandData {
		void BeforeCommandSetup(CommandManager::CommandData^ cmdData, DynamicCommandInstance^ cmd);
		void AfterCommandSetup(CommandManager::CommandData^ cmdData, DynamicCommandInstance^ cmd);
	};
}
