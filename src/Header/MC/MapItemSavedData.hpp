#pragma once
#include <mc/MapItemSavedData.hpp>
#include "Types.hpp"
namespace MC
{
public
ref class MapItemSavedData : ClassTemplate<MapItemSavedData, ::MapItemSavedData>
{
public:
    __ctor(MapItemSavedData, ::MapItemSavedData);
    __ctor_default(MapItemSavedData, ::MapItemSavedData);
};
} // namespace MC
