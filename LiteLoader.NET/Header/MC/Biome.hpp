#pragma once

#include "Types.hpp"
#include <MC/Biome.hpp>
namespace MC
{
	public enum class VanillaBiomeTypes {};

	public ref class Biome
		:ClassTemplate<Biome, ::Biome>
	{
	public:
		__ctor(Biome, ::Biome);
	public:
		enum class BiomeTempCategory {};
		property int Id {int get() { return NativePtr->getId(); }};
		property String^ Name {String^ get() { return marshalString(NativePtr->getName()); }};

		static Biome^ FromId(int id);;
		static Biome^ FromName(String^ name);;
		static List<Biome^>^ GetBiomesByType(VanillaBiomeTypes type);
	};
}