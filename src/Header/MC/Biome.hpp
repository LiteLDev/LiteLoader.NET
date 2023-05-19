#pragma once

#include "Types.hpp"
#include <mc/Biome.hpp>
namespace MC
{
    public enum class VanillaBiomeTypes
    {
        Beach = 0x0,
        Desert = 0x1,
        ExtremeHills = 0x2,
        FlatWorld = 0x3,
        Forest = 0x4,
        Hell = 0x5,
        //TODO: confirm IcePlainsSpikes
        IcePlainsSpikes = 0x6, // The Ice Plains Spikes Biome is a rare variant of the ice plains biome, containing unique ice structures. It is quite cold, with most water frozen as ice. 
        Jungle = 0x7,
        Mesa = 0x8, // Mesa is a very rare biome which is made up from red sand, cacti, dead bushes and plateaus. The red sand is only one layer thick. Red sand is found in the Mesa itself, not its variants. Water patches are found but are not a variant. 
        MushroomIsland = 0x9,
        Ocean = 0xA,
        Plain = 0xB,
        River = 0xC,
        Savanna = 0xD, // A savanna is a dry biome with scattered acacia trees. It typically generates bordering a desert, forest or plains biome and has three variations total. 
        RockyBeach = 0xE,
        Swamp = 0xF, // The Minecraft Swamp biome is a waterlogged area, consisting of many small islands separated by vast canals of water. In the Bedrock Edition, this water is a murky brown color, and this version also allows for Huge Mushrooms to appear on the islands.
        TaigaForest = 0x10,
        TheEnd = 0x11,
        Custom = 0x12, // Dirve by bahavior pack?
    };

    public ref class Biome
        :ClassTemplate<Biome, ::Biome>
    {
    public:
        __ctor(Biome, ::Biome);
        __ctor_default(Biome, ::Biome);
    public:
        enum class BiomeTempCategory {};
        property int Id {int get() { return NativePtr->getId(); }};
        property String^ Name {String^ get() { return marshalString(NativePtr->getName()); }};

        static Biome^ FromId(int id);;
        static Biome^ FromName(String^ name);;
        static array<Biome^>^ GetBiomesByType(VanillaBiomeTypes type);
    };
}