#pragma once
#include <mc/ActorDefinitionIdentifier.hpp>
#include "Types.hpp"

namespace MC
{
ref class HashedString;
}

namespace MC
{
public
ref struct ActorDefinitionIdentifier : ClassTemplate<ActorDefinitionIdentifier, ::ActorDefinitionIdentifier>
{
public:
    __ctor_all(ActorDefinitionIdentifier, ::ActorDefinitionIdentifier);
    __ctor_default(ActorDefinitionIdentifier, ::ActorDefinitionIdentifier);

    static ActorDefinitionIdentifier ^ Create();
    static ActorDefinitionIdentifier ^ Create(String^ ns, String^ identifier, String^ event, String^ fullname, HashedString ^ canonicalHash);

    property String^ Namespace {System::String^ get(); void set(System::String^ ns); };
    property String^ Identifier {System::String^ get(); void set(System::String^ identifier); };
    property String^ InitEvent {System::String^ get(); void set(System::String^ event); };
    property String^ Fullname {System::String^ get(); void set(System::String^ fullname); };
    property HashedString ^ CanonicalName {HashedString^ get(); void set(HashedString^ canonicalHash); };

#ifdef INCLUDE_MCAPI


    ActorDefinitionIdentifier(MC::ActorDefinitionIdentifier ^ _0);

    ActorDefinitionIdentifier(::String^ _0);

    ActorDefinitionIdentifier(::String^ _0, ::String^ _1, ::String^ _2);


    property ::String^
        CanonicalName {
            ::String^ get();
        };

    property ::String^
        InitEvent {
            ::String^ get();
            void set(::String^);
        };

    property ::String^
        Namespace {
            ::String^ get();
        };

    property bool IsEmpty
    {
        bool get();
    };

    property bool IsVanilla
    {
        bool get();
    };

    void Clear();

    void Initialize(::String^ _0, ::String^ _1, ::String^ _2);

    void Initialize(::String^ _0);

    static bool operator==(MC::ActorDefinitionIdentifier ^ __op, MC::ActorDefinitionIdentifier ^ _0);

    virtual bool Equals(::System::Object ^ obj) override;

#endif // INCLUDE_MCAPI
};
} // namespace MC