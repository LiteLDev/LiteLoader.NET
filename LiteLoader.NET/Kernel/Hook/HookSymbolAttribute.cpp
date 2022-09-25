#include <LiteLoader.NET/Header/Hook/HookSymbolAttribute.hpp>

namespace LLNET::Hook
{
	inline HookSymbolAttribute::HookSymbolAttribute(String^ sym)
	{
		Sym = sym;
	}

	HookSymbolAttribute::HookSymbolAttribute(intptr_t add)
	{
		Add = (void*)add;
	}
}