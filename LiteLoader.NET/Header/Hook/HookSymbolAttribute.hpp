#pragma once

#include <LiteLoader.NET/Main/DotNETGlobal.hpp>

namespace LLNET::Hook
{
	[System::AttributeUsageAttribute(System::AttributeTargets::Class)]
	public ref class HookSymbolAttribute :public System::Attribute
	{
	public:

		property String^ Sym;

		HookSymbolAttribute(String^ sym);
	};
}