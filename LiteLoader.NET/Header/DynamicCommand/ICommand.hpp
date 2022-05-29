#pragma once
#include "../Command/CommandOrigin.hpp"
#include "../Command/CommandOutput.hpp"

namespace LLNET::DynamicCommand {
	public interface class ICommand {
		void Execute(MC::CommandOrigin^ origin, MC::CommandOutput^ output);
	};
}
