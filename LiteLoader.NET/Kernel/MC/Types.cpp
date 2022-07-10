#include "../../Header/MC/Types.hpp"

#include "../../Header/MC/BlockPos.hpp"
#include "../../Header/MC/AABB.hpp"
#include "../../Header/MC/Vec3.hpp"

namespace MC
{

ActorUniqueID ^ ActorUniqueID::Create()
{
    return gcnew ActorUniqueID(::ActorUniqueID());
}
ActorUniqueID ^ ActorUniqueID::Create(long long i)
{
    return gcnew ActorUniqueID(::ActorUniqueID(i));
}
inline long long ActorUniqueID::get()
{
    return NativePtr->get();
}
inline ActorUniqueID::operator long long()
{
    return ((long long)*NativePtr);
}

ActorRuntimeID::ActorRuntimeID()
    : ClassTemplate(::ActorRuntimeID())
{
}
inline long long ActorRuntimeID::get()
{
    return NativePtr->get();
}
inline ActorRuntimeID::operator long long()
{
    return ((long long)*NativePtr);
}
} // namespace MC


MC::Mce::Color ^ MC::Mce::Color::FromHexString(::String^ _0)
{
    auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
    auto __ret = ::mce::Color::fromHexString(__arg0);
    auto ____ret = new class ::mce::Color(__ret);
    return (____ret == nullptr) ? nullptr : gcnew ::MC::Mce::Color((class ::mce::Color*)____ret, true);
}

bool MC::Mce::Color::operator==(MC::Mce::Color ^ __op, MC::Mce::Color ^ _0)
{
    bool __opNull = ReferenceEquals(__op, nullptr);
    bool _0Null = ReferenceEquals(_0, nullptr);
    if (__opNull || _0Null)
        return __opNull && _0Null;
    auto& __arg0 = *(class ::mce::Color*)__op->NativePtr;
    auto& __arg1 = *(class ::mce::Color*)_0->NativePtr;
    auto __ret = __arg0 == __arg1;
    return __ret;
}

bool MC::Mce::Color::Equals(::System::Object ^ obj)
{
    return this == safe_cast<MC::Mce::Color ^>(obj);
}

int MC::Mce::Color::ToABGR()
{
    auto __ret = ((class ::mce::Color*)NativePtr)->toABGR();
    return __ret;
}

int MC::Mce::Color::ToARGB()
{
    auto __ret = ((class ::mce::Color*)NativePtr)->toARGB();
    return __ret;
}

::String^ MC::Mce::Color::ToHexString()
{
    auto __ret = ((class ::mce::Color*)NativePtr)->toHexString();
    return clix::marshalString<clix::E_UTF8>(__ret);
}

MC::Mce::Color::Color(MC::Mce::Color ^ _0)
{
    OwnsNativeInstance = true;
    if (ReferenceEquals(_0, nullptr))
        throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
    auto& __arg0 = *(class ::mce::Color*)_0->NativePtr;
    NativePtr = new class ::mce::Color(__arg0);
}

::System::IntPtr MC::Mce::Color::__Instance::get()
{
    return ::System::IntPtr(NativePtr);
}

void MC::Mce::Color::__Instance::set(::System::IntPtr object)
{
    NativePtr = (class ::mce::Color*)object.ToPointer();
}
MC::Mce::Color ^ MC::Mce::Color::NIL::get()
{
    return (&::mce::Color::NIL == nullptr) ? nullptr : gcnew ::MC::Mce::Color((class ::mce::Color*)&::mce::Color::NIL);
}
