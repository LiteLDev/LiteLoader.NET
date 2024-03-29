#pragma once
#include <mc/Objective.hpp>
#include "Types.hpp"

namespace MC
{
ref class ScoreboardId;
}

namespace MC
{
public
ref class Objective : ClassTemplate<Objective, ::Objective>
{
public:
    __ctor(Objective, ::Objective);
    __ctor_default(Objective, ::Objective);
    inline bool SetDisplay(String^ slotName, ObjectiveSortOrder sort);

#ifdef INCLUDE_MCAPI
    property ::String^ DisplayName {
        ::String^ get();
    }

        property ::String^
        Name {
            ::String^ get();
        }

        property ::System::Collections::Generic::List<MC::ScoreboardId ^> ^
        Players {
            ::System::Collections::Generic::List<MC::ScoreboardId ^> ^ get();
        }
#endif // INCLUDE_MCAPI
};
} // namespace MC
