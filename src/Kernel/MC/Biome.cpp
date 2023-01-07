#include <src/Header/MC/Biome.hpp>

namespace MC
{
    inline Biome^ Biome::FromId(int id) { return gcnew Biome(::Biome::fromId(id)); }
    inline Biome^ Biome::FromName(String^ name) { return gcnew Biome(::Biome::fromName(marshalString(name))); }
    inline List<Biome^>^ Biome::GetBiomesByType(VanillaBiomeTypes type) {
        auto& vec = ::Biome::getBiomesByType(::VanillaBiomeTypes(type));
        auto ret = gcnew List<Biome^>((int)vec.size());
        for (auto pBiome : vec) {
            ret->Add(gcnew Biome(pBiome));
        }
        return ret;
    }
}