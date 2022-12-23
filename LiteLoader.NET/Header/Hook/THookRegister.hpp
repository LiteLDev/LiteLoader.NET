#pragma once
#include <HookAPI.h>
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <LiteLoader.NET/Header/Core/SecondaryRankPtr.hpp>

namespace LiteLoader::Hook
{
	using LiteLoader::NET::SecondaryRankPtr;

	public ref class THookRegister
	{
		THookRegister(System::IntPtr address, System::IntPtr hook, SecondaryRankPtr org);

		THookRegister(void* address, void* hook, void** org);

		THookRegister(System::String^ sym, System::IntPtr hook, SecondaryRankPtr org);

		THookRegister(char const* sym, void* hook, void** org);
	};

}
