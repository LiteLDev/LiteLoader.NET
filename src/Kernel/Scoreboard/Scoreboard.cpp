#include <src/Header/Scoreboard/Scoreboard.hpp>
#include <src/Header/MC/Player.hpp>
#include <src/Header/MC/Objective.hpp>

namespace MC
{
Objective ^ ScoreInfo::Objective::get()
{
    return gcnew MC::Objective(NativePtr->getObjective());
}

int ScoreInfo::Count::get()
{
    return NativePtr->getCount();
}

ScoreboardId ^ Scoreboard::CreateScoreboardId(String ^ a0)
{
    return gcnew ScoreboardId((::ScoreboardId&)NativePtr->createScoreboardId(marshalString(a0)));
}
ScoreboardId ^ Scoreboard::CreateScoreboardId(Player ^ player)
{
    return gcnew ScoreboardId((::ScoreboardId&)NativePtr->createScoreboardId(*player->NativePtr));
}
Objective ^ Scoreboard::NewObjective(String ^ objname, String ^ displayName)
{
    return gcnew Objective(::Scoreboard::newObjective(marshalString(objname), marshalString(displayName)));
}
bool Scoreboard::RemoveFromObjective(String ^ objname, String ^ displayName)
{
    return ::Scoreboard::removeFromObjective(marshalString(objname), marshalString(displayName));
}
bool Scoreboard::RemoveFromObjective(String ^ objname, Player ^ player)
{
    return ::Scoreboard::removeFromObjective(marshalString(objname), player->NativePtr);
}
ScoreboardId ^ Scoreboard::GetOrCreateScoreboardId(String ^ id)
{
    return gcnew ScoreboardId(::Scoreboard::getOrCreateScoreboardId(marshalString(id)));
}
int Scoreboard::GetScore(String ^ objname, String ^ id)
{
    return ::Scoreboard::getScore(marshalString(objname), marshalString(id));
}

int Scoreboard::SetScore(String ^ objname, String ^ id, int score)
{
    return ::Scoreboard::setScore(marshalString(objname), marshalString(id), score).value_or(0);
}

int Scoreboard::AddScore(String ^ objname, String ^ id, int score)
{
    return ::Scoreboard::addScore(marshalString(objname), marshalString(id), score).value_or(0);
}

int Scoreboard::ReduceScore(String ^ objname, String ^ id, int score)
{
    return ::Scoreboard::reduceScore(marshalString(objname), marshalString(id), score).value_or(0);
}

int Scoreboard::GetScore(Player ^ player, String ^ key)
{
    return ::Scoreboard::getScore(player->NativePtr, marshalString(key));
}

bool Scoreboard::SetScore(Player ^ player, String ^ key, int value)
{
    return ::Scoreboard::setScore(player->NativePtr, marshalString(key), value);
}

bool Scoreboard::AddScore(Player ^ player, String ^ key, int value)
{
    return ::Scoreboard::addScore(player->NativePtr, marshalString(key), value);
}

bool Scoreboard::ReduceScore(Player ^ player, String ^ id, int score)
{
    return ::Scoreboard::reduceScore(player->NativePtr, marshalString(id), score);
}

bool Scoreboard::DeleteScore(Player ^ player, String ^ objname)
{
    return ::Scoreboard::deleteScore(player->NativePtr, marshalString(objname));
}

bool Scoreboard::ScoreboardIdValid(ScoreboardId ^ id)
{
    return ::Scoreboard::scoreboardIdIsValid(id);
}

} // namespace MC
