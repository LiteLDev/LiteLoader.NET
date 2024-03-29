#include <src/Header/MC/ActorDefinitionIdentifier.hpp>

#include <src/Header/MC/HashedString.hpp>

namespace MC
{
inline String^ ActorDefinitionIdentifier::Namespace::get()
{
    return marshalString(NativePtr->mNamespace);
}
inline void ActorDefinitionIdentifier::Namespace::set(String^ ns)
{
    NativePtr->mNamespace = marshalString(ns);
}
inline String^ ActorDefinitionIdentifier::Identifier::get()
{
    return marshalString(NativePtr->mIdentifier);
}
inline void ActorDefinitionIdentifier::Identifier::set(String^ identifier)
{
    NativePtr->mIdentifier = marshalString(identifier);
}
inline String^ ActorDefinitionIdentifier::InitEvent::get()
{
    return marshalString(NativePtr->mInitEvent);
}
inline void ActorDefinitionIdentifier::InitEvent::set(String^ initEvent)
{
    NativePtr->mInitEvent = marshalString(initEvent);
}
inline String^ ActorDefinitionIdentifier::Fullname::get()
{
    return marshalString(NativePtr->mFullName);
}
inline void ActorDefinitionIdentifier::Fullname::set(String^ fullname)
{
    NativePtr->mFullName = marshalString(fullname);
}
inline HashedString ^ ActorDefinitionIdentifier::CanonicalName::get()
{
    return gcnew HashedString(NativePtr->mCanonicalName);
}
inline void ActorDefinitionIdentifier::CanonicalName::set(HashedString ^ canonicalName)
{
    NativePtr->mCanonicalName = canonicalName;
}
ActorDefinitionIdentifier ^ ActorDefinitionIdentifier::Create()
{
    return gcnew ActorDefinitionIdentifier(::ActorDefinitionIdentifier{});
}
ActorDefinitionIdentifier ^ ActorDefinitionIdentifier::Create(String^ ns, String^ identifier, String^ initEvent, String^ fullname, HashedString ^ canonicalName)
{
    ::ActorDefinitionIdentifier adi{};
    adi.mNamespace = marshalString(ns);
    adi.mIdentifier = marshalString(identifier);
    adi.mInitEvent = marshalString(initEvent);
    adi.mFullName = marshalString(fullname);
    adi.mCanonicalName = canonicalName;
    return gcnew ActorDefinitionIdentifier(std::move(adi));
}
} // namespace MC


#ifdef INCLUDE_MCAPI

MC::ActorDefinitionIdentifier::ActorDefinitionIdentifier(MC::ActorDefinitionIdentifier ^ _0)
{
    OwnsNativeInstance = true;
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(struct ::ActorDefinitionIdentifier*)_0->NativePtr;
    NativePtr = new struct ::ActorDefinitionIdentifier(__arg0);
}

MC::ActorDefinitionIdentifier::ActorDefinitionIdentifier(::String^ _0)
{
    OwnsNativeInstance = true;
    auto ___arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __arg0 = ___arg0.c_str();
    NativePtr = new struct ::ActorDefinitionIdentifier(__arg0);
}

MC::ActorDefinitionIdentifier::ActorDefinitionIdentifier(::String^ _0, ::String^ _1, ::String^ _2)
{
    OwnsNativeInstance = true;
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __arg1 = clix::marshalString<clix::E_UTF8>(_1);
    auto __arg2 = clix::marshalString<clix::E_UTF8>(_2);
    NativePtr = new struct ::ActorDefinitionIdentifier(__arg0, __arg1, __arg2);
}

void MC::ActorDefinitionIdentifier::Clear()
{
    ((struct ::ActorDefinitionIdentifier*)NativePtr)->clear();
}

void MC::ActorDefinitionIdentifier::Initialize(::String^ _0, ::String^ _1, ::String^ _2)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __arg1 = clix::marshalString<clix::E_UTF8>(_1);
    auto __arg2 = clix::marshalString<clix::E_UTF8>(_2);
    ((struct ::ActorDefinitionIdentifier*)NativePtr)->initialize(__arg0, __arg1, __arg2);
}

void MC::ActorDefinitionIdentifier::Initialize(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    ((struct ::ActorDefinitionIdentifier*)NativePtr)->initialize(__arg0);
}

bool MC::ActorDefinitionIdentifier::operator==(MC::ActorDefinitionIdentifier ^ __op, MC::ActorDefinitionIdentifier ^ _0)
{
    bool __opNull = ReferenceEquals(__op, nullptr);
    bool _0Null = ReferenceEquals(_0, nullptr);
    if (__opNull || _0Null)
        return __opNull && _0Null;
    auto& __arg0 = *(struct ::ActorDefinitionIdentifier*)__op->NativePtr;
    auto& __arg1 = *(struct ::ActorDefinitionIdentifier*)_0->NativePtr;
    auto __ret = __arg0 == __arg1;
    return __ret;
}

bool MC::ActorDefinitionIdentifier::Equals(::System::Object ^ obj)
{
    return this == safe_cast<MC::ActorDefinitionIdentifier ^>(obj);
}

::String^ MC::ActorDefinitionIdentifier::CanonicalName::get()
{
    auto& __ret = ((struct ::ActorDefinitionIdentifier*)NativePtr)->getCanonicalName();
    return (::String^)(clix::marshalString<clix::E_UTF8>(__ret));
}

::String^ MC::ActorDefinitionIdentifier::InitEvent::get()
{
    auto& __ret = ((struct ::ActorDefinitionIdentifier*)NativePtr)->getInitEvent();
    return (::String^)(clix::marshalString<clix::E_UTF8>(__ret));
}

void MC::ActorDefinitionIdentifier::InitEvent::set(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    ((struct ::ActorDefinitionIdentifier*)NativePtr)->setInitEvent(__arg0);
}

::String^ MC::ActorDefinitionIdentifier::Namespace::get()
{
    auto& __ret = ((struct ::ActorDefinitionIdentifier*)NativePtr)->getNamespace();
    return (::String^)(clix::marshalString<clix::E_UTF8>(__ret));
}

bool MC::ActorDefinitionIdentifier::IsEmpty::get()
{
    auto __ret = ((struct ::ActorDefinitionIdentifier*)NativePtr)->isEmpty();
    return __ret;
}

bool MC::ActorDefinitionIdentifier::IsVanilla::get()
{
    auto __ret = ((struct ::ActorDefinitionIdentifier*)NativePtr)->isVanilla();
    return __ret;
}

#endif // INCLUDE_MCAPI
