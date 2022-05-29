#pragma once
#include <MC/CommandItem.hpp>
#include "../MC/Types.hpp"

namespace MC {
	ref class CommandOutput;
	ref class ItemInstance;
}

namespace MC {
	public ref class CommandItem
		:ClassTemplate<CommandItem, ::CommandItem>
	{
	public:
		__ctor(CommandItem, ::CommandItem);
	public:
		CommandItem(unsigned __int64 uint64);
		CommandItem(int a1, short a2, bool a3);
		CommandItem();

		property int Id {int get(); };

		ItemInstance^ CreateInstance(int a1, int a2, MC::CommandOutput^ output, bool a4);
		
		static operator bool(CommandItem^ obj);
		static operator unsigned __int64(CommandItem^ obj);
	};
}
