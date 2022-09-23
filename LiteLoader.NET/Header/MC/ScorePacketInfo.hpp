#pragma once
#include <mc/ScorePacketInfo.hpp>
#include "Types.hpp"
#include "IdentityDefinition.hpp"

namespace MC
{
ref class ScoreboardId;
}

namespace MC
{
public
ref struct ScorePacketInfo : ClassTemplate<ScorePacketInfo, ::ScorePacketInfo>
{
public:
    __ctor_all(ScorePacketInfo, ::ScorePacketInfo);

#ifdef INCLUDE_MCAPI

    ScorePacketInfo(MC::ScoreboardId ^ s, ::String^ obj_name, MC::IdentityDefinition::Type type, unsigned int num, ::String^ fake);

    ScorePacketInfo(MC::ScorePacketInfo ^ _0);

    property MC::ScoreboardId ^ Sid {
        MC::ScoreboardId ^ get();
        void set(MC::ScoreboardId ^);
    };

    property ::String^ ObjName {
        ::String^ get();
        void set(::String^);
    };

    property unsigned int Score
    {
        unsigned int get();
        void set(unsigned int);
    };

    property MC::IdentityDefinition::Type Type
    {
        MC::IdentityDefinition::Type get();
        void set(MC::IdentityDefinition::Type);
    };

    property unsigned long long Pid
    {
        unsigned long long get();
        void set(unsigned long long);
    };

    property MC::ActorUniqueID ^ Aid {
        MC::ActorUniqueID ^ get();
        void set(MC::ActorUniqueID ^);
    };

    property ::String^ FakeName {
        ::String^ get();
        void set(::String^);
    };

#endif // INCLUDE_MCAPI
};
} // namespace MC
