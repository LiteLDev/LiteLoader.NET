#include <src/Header/MC/Types.hpp>

#include <src/Header/MC/BlockPos.hpp>
#include <src/Header/MC/AABB.hpp>
#include <src/Header/MC/Vec3.hpp>

namespace MC
{
    namespace Mce
    {
        inline UUID::operator ::mce::UUID()
        {
            pin_ptr<UUID> p = this;
            auto ret = ::mce::UUID();
            memcpy(&ret, p, sizeof(::mce::UUID));
            return ret;
        }

        inline String^ UUID::AsString()
        {
            pin_ptr<UUID> p = this;
            return marshalString(((::mce::UUID*)p)->asString());
        }

        inline String^ UUID::ToString()
        {
            return AsString();
        }

        inline UUID UUID::FromString(String^ str)
        {
            return ::mce::UUID::fromString(marshalString(str));
        }

        inline UUID UUID::SeedFromString(String^ str)
        {
            return ::mce::UUID::seedFromString(marshalString(str));
        }

        inline bool UUID::IsEmpty::get()
        {
            pin_ptr<UUID> p = this;
            return ((::mce::UUID*)p)->isEmpty();
        }

        inline Color::operator ::mce::Color()
        {
            return ::mce::Color{ r,g,b,a };
        }

        inline Color::Color(float r, float g, float b, float a)
            : r(r)
            , g(g)
            , b(b)
            , a(a) {}

        inline Color::Color(float r, float g, float b)
            : r(r)
            , g(g)
            , b(b)
            , a(1) {}

        inline Color::Color(int ir, int ig, int ib, int ia)
            : r(ir / 255.0f)
            , g(ig / 255.0f)
            , b(ib / 255.0f)
            , a(ia / 255.0f) {}

        inline Color::Color(int ir, int ig, int ib)
            : r(ir / 255.0f)
            , g(ig / 255.0f)
            , b(ib / 255.0f)
            , a(255 / 255.0f) {}

        inline Color::operator bool(Color obj) {
            return !(obj == NIL);
        }

        inline double Color::DistanceTo(Color% obj)
        {
            pin_ptr<Color> p = this;
            pin_ptr<Color> pobj = &obj;
            return ((::mce::Color*)p)->distanceTo(*(::mce::Color*)pobj);
        }

        inline String^ Color::ToConsoleCode(bool foreground)
        {
            pin_ptr<Color> p = this;
            return marshalString(((::mce::Color*)p)->toConsoleCode(foreground));
        }

        inline String^ Color::ToConsoleCode()
        {
            return ToConsoleCode(true);
        }

        inline String^ Color::ToNearestColorCode()
        {
            pin_ptr<Color> p = this;
            return marshalString(((::mce::Color*)p)->toNearestColorCode());
        }

        inline Color Color::FromConsoleCode(String^ str)
        {
            return ::mce::Color::fromConsoleCode(marshalString(str));
        }

        inline Color Color::FromColorCode(String^ str)
        {
            return ::mce::Color::fromColorCode(marshalString(str));
        }

        inline Color Color::sRGBToLinear()
        {
            pin_ptr<Color> p = this;
            return ((::mce::Color*)p)->sRGBToLinear();
        }

        inline Color Color::LinearTosRGB()
        {
            pin_ptr<Color> p = this;
            return ((::mce::Color*)p)->LinearTosRGB();
        }

        inline Color Color::LinearToXYZ()
        {
            pin_ptr<Color> p = this;
            return ((::mce::Color*)p)->LinearToXYZ();
        }

        inline Color Color::XYZToLinear()
        {
            pin_ptr<Color> p = this;
            return ((::mce::Color*)p)->XYZToLinear();
        }

        inline Color Color::XYZToLab()
        {
            pin_ptr<Color> p = this;
            return ((::mce::Color*)p)->XYZToLab();
        }

        inline Color Color::LabToXYZ()
        {
            pin_ptr<Color> p = this;
            return ((::mce::Color*)p)->LabToXYZ();
        }

        inline double Color::DeltaE76(Color% obj)
        {
            pin_ptr<Color> p = this;
            pin_ptr<Color> pobj = &obj;
            return ((::mce::Color*)p)->deltaE76(*(::mce::Color*)pobj);
        }

        inline double Color::DeltaE94(Color% obj)
        {
            pin_ptr<Color> p = this;
            pin_ptr<Color> pobj = &obj;
            return ((::mce::Color*)p)->deltaE76(*(::mce::Color*)pobj);
        }

        inline double Color::DeltaE00(Color% obj)
        {
            pin_ptr<Color> p = this;
            pin_ptr<Color> pobj = &obj;
            return ((::mce::Color*)p)->deltaE76(*(::mce::Color*)pobj);
        }

        inline Color Color::FromHexString(String^ str)
        {
            return ::mce::Color::fromHexString(marshalString(str));
        }

        inline bool Color::operator==(Color a, Color b)
        {
            pin_ptr<Color> pa = &a;
            pin_ptr<Color> pb = &b;
            return *(::mce::Color*)pa == *(::mce::Color*)pb;
        }

        inline int Color::ToABGR()
        {
            pin_ptr<Color> p = this;
            return ((::mce::Color*)p)->toABGR();
        }

        inline int Color::ToARGB()
        {
            pin_ptr<Color> p = this;
            return ((::mce::Color*)p)->toARGB();
        }

        inline String^ Color::ToHexString()
        {
            pin_ptr<Color> p = this;
            return marshalString(((::mce::Color*)p)->toHexString());
        }

        inline  MC::Vec3 Color::ToVec3() 
        {
            return Vec3{ r, g, b };
        }

        inline Color Color::FromVec3(MC::Vec3% k)
        {
            return Color{ k.x, k.y, k.z, 1.0f };
        }

        inline  MC::BlockPos Color::ToBlockPos() 
        {
            return BlockPos{ int(r * 255.0f), int(g * 255.0f), int(b * 255.0f) };
        }

        inline Color Color::fromBlockPos(MC::BlockPos% k) 
        {
            return  Color{ k.x / 255.0f, k.y / 255.0f, k.z / 255.0f, 1.0f };
        }

        inline bool Color::operator!=(const Color& c) 
        {
            return !(c == *this);
        }

        inline Color Color::operator*(Color obj, float c) 
        {
            return Color{ obj.r * c, obj.g * c, obj.b * c, obj.a * c };
        }

        inline Color Color::operator/(Color obj, float c) 
        {
            return Color{ obj.r / c, obj.g / c, obj.b / c, obj.a / c };
        }

        inline Color Color::operator+(Color obj, float c) 
        {
            return Color{ obj.r + c, obj.g + c, obj.b + c, obj.a + c };
        }

        inline Color Color::operator-(Color obj, float c) 
        {
            return Color{ obj.r - c, obj.g - c, obj.b - c, obj.a - c };
        }

        inline Color Color::operator+(Color obj, Color c) 
        {
            return Color{ obj.r + c.r, obj.g + c.g, obj.b + c.b, obj.a + c.a };
        }

        inline Color Color::operator*(Color obj, Color c) 
        {
            return Color{ obj.r * c.r, obj.g * c.g, obj.b * c.b, obj.a * c.a };
        }

        inline Color Color::operator/(Color obj, Color c) 
        {
            return Color{ obj.r / c.r, obj.g / c.g, obj.b / c.b, obj.a / c.a };
        }

        inline Color Color::operator-(Color obj, Color c) 
        {
            return Color{ obj.r - c.r, obj.g - c.g, obj.b - c.b, obj.a - c.a };
        }

        inline Color Color::Max(Color% k, Color% l) 
        {
            pin_ptr<Color> pk = &k;
            pin_ptr<Color> pl = &l;
            return ::mce::Color::max(*(::mce::Color*)pk, *(::mce::Color*)pl);
        }

        inline Color Color::Min(Color% k, Color% l) 
        {
            pin_ptr<Color> pk = &k;
            pin_ptr<Color> pl = &l;
            return ::mce::Color::min(*(::mce::Color*)pk, *(::mce::Color*)pl);
        }

        inline Color Color::Lerp(Color% k, Color% l, float m) 
        {
            return k * (1.0f - m) + l * m;
        }

        inline Color Color::Mix(Color% k, Color% l, float m) 
        {
            return Lerp(k, l, m);
        }

        inline int Color::GetHashCode()
        {
            return (int)HashVal;
        }

        inline size_t Color::HashVal::get()
        {
            pin_ptr<Color> p = this;
            std::hash<::mce::Color> hash;
            return hash(*(::mce::Color*)p);
        }
    }

    inline ActorUniqueID::operator ::ActorUniqueID()
    {
        return { id };
    }

    inline ActorUniqueID::ActorUniqueID(::ActorUniqueID const* p)
        :id(p->id) {}

    inline ActorUniqueID::ActorUniqueID(long long i)
        : id(i) {}

    inline long long ActorUniqueID::Id::get()
    {
        return id;
    }

    inline void ActorUniqueID::Id::set(long long value)
    {
        id = value;
    }

    inline ActorUniqueID::operator long long(ActorUniqueID obj)
    {
        return obj.id;
    }

    ActorRuntimeID::ActorRuntimeID()
        : ClassTemplate(::ActorRuntimeID())
    {
    }
    ActorRuntimeID::ActorRuntimeID(unsigned long long id)
        : ClassTemplate(::ActorRuntimeID())
    {
        NativePtr->id = id;
    }
    inline unsigned long long ActorRuntimeID::Id::get()
    {
        return NativePtr->id;
    }
    inline void ActorRuntimeID::Id::set(unsigned long long value)
    {
        NativePtr->id = value;
    }
    inline ActorRuntimeID::operator unsigned long long(ActorRuntimeID^ id)
    {
        return *id->NativePtr;
    }

    generic<typename A, typename T>
    inline AutomaticID<A, T>::AutomaticID()
    {
        id = T(0);
    }
    generic<typename A, typename T>
    inline AutomaticID<A, T>::AutomaticID(T x)
    {
        id = x;
    }
    generic<typename A, typename T>
    inline AutomaticID<A, T>::operator T(AutomaticID<A, T>^ _this)
    {
        return _this->id;
    }
} // namespace MC
