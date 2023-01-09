#include <src/Header/MC/Biome.hpp>

namespace MC
{
    inline Biome^ Biome::FromId(int id) { return gcnew Biome(::Biome::fromId(id)); }
    inline Biome^ Biome::FromName(String^ name) { return gcnew Biome(::Biome::fromName(marshalString(name))); }
    inline array<Biome^>^ Biome::GetBiomesByType(VanillaBiomeTypes type) {
        auto& vec = ::Biome::getBiomesByType(::VanillaBiomeTypes(type));
        auto ret = gcnew array<Biome^>((int)vec.size());
        for (int i = 0; i < vec.size(); ++i) {
            ret[i] = gcnew Biome(vec[i]);
        }
        return ret;
    }
}