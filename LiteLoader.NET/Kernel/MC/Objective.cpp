#include "../../Header/MC/Objective.hpp"
#include "../../Header/MC/ScoreboardId.hpp"
namespace MC
{

inline bool Objective::SetDisplay(String^ slotName, ObjectiveSortOrder sort)
{
    return NativePtr->setDisplay(marshalString<Encoding::E_UTF8>(slotName), ::ObjectiveSortOrder(sort));
}
} // namespace MC

#ifdef INCLUDE_MCAPI
::String^ MC::Objective::DisplayName::get()
{
    auto& __ret = ((class ::Objective*)NativePtr)->getDisplayName();
    return (::String^)(clix::marshalString<clix::E_UTF8>(__ret));
}

::String^ MC::Objective::Name::get()
{
    auto& __ret = ((class ::Objective*)NativePtr)->getName();
    return (::String^)(clix::marshalString<clix::E_UTF8>(__ret));
}

::System::Collections::Generic::List<MC::ScoreboardId ^> ^ MC::Objective::Players::get()
{
    auto __ret = ((class ::Objective*)NativePtr)->getPlayers();
    auto _tmp__ret = gcnew ::System::Collections::Generic::List<MC::ScoreboardId ^>();
    auto& __list0 = __ret;
    for (auto& _element : __list0)
    {
        auto ___element = new struct ::ScoreboardId(_element);
        auto _marshalElement = (___element == nullptr) ? nullptr : gcnew ::MC::ScoreboardId((struct ::ScoreboardId*)___element, true);
        _tmp__ret->Add(_marshalElement);
    }
    return _tmp__ret;
}
#endif // INCLUDE_MCAPI
