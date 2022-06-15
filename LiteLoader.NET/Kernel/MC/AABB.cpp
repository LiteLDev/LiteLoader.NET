#include "../../Header/MC/AABB.hpp"
#include "../../Header/MC/Vec3.hpp"
#include "../../Header/MC/HitResult.hpp"

namespace MC {

	Vec3 AABB::AxisInside(AABB aabb, Vec3 vec)
	{
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->axisInside(aabb, vec);
	}

	HitResult^ AABB::Clip(Vec3 v1, Vec3 v2)
	{
		pin_ptr<AABB> p = this;
		return gcnew HitResult(((::AABB*)p)->clip(v1, v2));
	}

	Vec3 AABB::ClipCollide(AABB aabb, Vec3 vec, bool b, float% f)
	{
		pin_ptr<float> pf = &f;
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->clipCollide(aabb, vec, b, pf);
	}

	AABB AABB::CloneAndExpandAlongDirection(Vec3 vec)
	{
		pin_ptr<AABB> p = this;
		return AABB(((::AABB*)p)->cloneAndExpandAlongDirection(vec));
	}

	AABB AABB::CloneAndFloor(float f1, float f2)
	{
		pin_ptr<AABB> p = this;
		return AABB(((::AABB*)p)->cloneAndFloor(f1, f2));
	}

	AABB AABB::CloneAndFloorMinAndCeilingMax()
	{
		pin_ptr<AABB> p = this;
		return AABB(((::AABB*)p)->cloneAndFloorMinAndCeilingMax());
	}

	AABB AABB::CloneAndGrow(Vec3 vec)
	{
		pin_ptr<AABB> p = this;
		return AABB(((::AABB*)p)->cloneAndGrow(vec));
	}

	AABB AABB::CloneAndShrink(Vec3 vec)
	{
		pin_ptr<AABB> p = this;
		return AABB(((::AABB*)p)->cloneAndShrink(vec));
	}

	bool MC::AABB::Contains(AABB aabb)
	{
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->contains(aabb);
	}

	bool AABB::Contains(Vec3 vec)
	{
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->contains(vec);
	}

	float AABB::DistanceTo(AABB aabb)
	{
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->distanceTo(aabb);
	}

	float AABB::DistanceTo(Vec3 vec)
	{
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->distanceTo(vec);
	}

	bool AABB::IntersectSegment(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4)
	{
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->intersectSegment(v1, v2, ::Vec3(v3), ::Vec3(v4));
	}

	bool AABB::Intersects(AABB aabb)
	{
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->intersects(aabb);
	}

	bool AABB::Intersects(Vec3 v1, Vec3 v2)
	{
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->intersects(v1, v2);
	}

	bool AABB::IntersectsInner(AABB aabb)
	{
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->intersectsInner(aabb);
	}

	AABB AABB::Set(float f1, float f2, float f3, float f4, float f5, float f6)
	{
		pin_ptr<AABB> p = this;
		return AABB(((::AABB*)p)->set(f1, f2, f3, f4, f5, f6));
	}

	AABB AABB::Set(AABB aabb)
	{
		pin_ptr<AABB> p = this;
		return AABB(((::AABB*)p)->set(aabb));
	}

	AABB AABB::Set(Vec3 v1, Vec3 v2)
	{
		pin_ptr<AABB> p = this;
		return AABB(((::AABB*)p)->set(v1, v2));
	}

	AABB AABB::Shrink(Vec3 vec)
	{
		pin_ptr<AABB> p = this;
		return AABB(((::AABB*)p)->shrink(vec));
	}

	AABB AABB::TranslateCenterTo(Vec3 vec)
	{
		pin_ptr<AABB> p = this;
		return AABB(((::AABB*)p)->translateCenterTo(vec));
	}

	bool AABB::operator!=(AABB a, AABB b)
	{
		pin_ptr<AABB> pa = &a;
		pin_ptr<AABB> pb = &b;
		return *(::AABB*)pa != *(::AABB*)pb;
	}

	bool AABB::operator==(AABB a, AABB b)
	{
		pin_ptr<AABB> pa = &a;
		pin_ptr<AABB> pb = &b;
		return *(::AABB*)pa == *(::AABB*)pb;
	}

	Vec3 AABB::Bounds::get() {
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->getBounds();
	}

	Vec3 AABB::Center::get() {
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->getCenter();
	}

	float AABB::Size::get() {
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->getSize();
	}

	float AABB::Volume::get() {
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->getVolume();
	}

	//bool AABB::HasZeroVolume::get() {
	//	return ((::AABB*)p)->hasZeroVolume();
	//}

	bool AABB::IsValid::get() {
		pin_ptr<AABB> p = this;
		return ((::AABB*)p)->isValid();
	}
}