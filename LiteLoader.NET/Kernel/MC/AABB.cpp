#include "../../Header/MC/AABB.hpp"
#include "../../Header/MC/Vec3.hpp"
#include "../../Header/MC/HitResult.hpp"

namespace MC {

	Vec3 AABB::PointA::get() {
		return NativePtr->pointA;
	}

	Vec3 AABB::PointB::get() {
		return NativePtr->pointB;
	}

	AABB::AABB(Vec3 v1, Vec3 v2)
		:ClassTemplate(::AABB(v1, v2))
	{
	}

	AABB::AABB(Vec3 vec, float f)
		:ClassTemplate(::AABB(vec, f))
	{
	}

	AABB::AABB(float f1, float f2, float f3, float f4, float f5, float f6)
		:ClassTemplate(::AABB(f1, f2, f3, f4, f5, f6))
	{
	}

	Vec3 AABB::AxisInside(AABB^ aabb, Vec3 vec)
	{
		return NativePtr->axisInside(aabb, vec);
	}

	HitResult^ AABB::Clip(Vec3 v1, Vec3 v2)
	{
		return gcnew HitResult(NativePtr->clip(v1, v2));
	}

	Vec3 AABB::ClipCollide(AABB^ aabb, Vec3 vec, bool b, float% f)
	{
		pin_ptr<float> p = &f;
		return NativePtr->clipCollide(aabb, vec, b, p);
	}

	AABB^ AABB::CloneAndExpandAlongDirection(Vec3 vec)
	{
		return gcnew AABB(NativePtr->cloneAndExpandAlongDirection(vec));
	}

	AABB^ AABB::CloneAndFloor(float f1, float f2)
	{
		return gcnew AABB(NativePtr->cloneAndFloor(f1, f2));
	}

	AABB^ AABB::CloneAndFloorMinAndCeilingMax()
	{
		return gcnew AABB(NativePtr->cloneAndFloorMinAndCeilingMax());
	}

	AABB^ AABB::CloneAndGrow(Vec3 vec)
	{
		return gcnew AABB(NativePtr->cloneAndGrow(vec));
	}

	AABB^ AABB::CloneAndShrink(Vec3 vec)
	{
		return gcnew AABB(NativePtr->cloneAndShrink(vec));
	}

	bool MC::AABB::Contains(AABB^ aabb)
	{
		return NativePtr->contains(aabb);
	}

	bool AABB::Contains(Vec3 vec)
	{
		return NativePtr->contains(vec);
	}

	float AABB::DistanceTo(AABB^ aabb)
	{
		return NativePtr->distanceTo(aabb);
	}

	float AABB::DistanceTo(Vec3 vec)
	{
		return NativePtr->distanceTo(vec);
	}

	bool AABB::IntersectSegment(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4)
	{
		return NativePtr->intersectSegment(v1, v2, ::Vec3(v3), ::Vec3(v4));
	}

	bool AABB::Intersects(AABB^ aabb)
	{
		return NativePtr->intersects(aabb);
	}

	bool AABB::Intersects(Vec3 v1, Vec3 v2)
	{
		return NativePtr->intersects(v1, v2);
	}

	bool AABB::IntersectsInner(AABB^ aabb)
	{
		return NativePtr->intersectsInner(aabb);
	}

	AABB^ AABB::Set(float f1, float f2, float f3, float f4, float f5, float f6)
	{
		return gcnew AABB(NativePtr->set(f1, f2, f3, f4, f5, f6));
	}

	AABB^ AABB::Set(AABB^ aabb)
	{
		return gcnew AABB(NativePtr->set(aabb));
	}

	AABB^ AABB::Set(Vec3 v1, Vec3 v2)
	{
		return gcnew AABB(NativePtr->set(v1, v2));
	}

	AABB^ AABB::Shrink(Vec3 vec)
	{
		return gcnew AABB(NativePtr->shrink(vec));
	}

	AABB^ AABB::TranslateCenterTo(Vec3 vec)
	{
		return gcnew AABB(NativePtr->translateCenterTo(vec));
	}

	bool AABB::operator!=(AABB^ a, AABB^ b)
	{
		return *a->NativePtr != *b->NativePtr;
	}

	bool AABB::operator==(AABB^ a, AABB^ b)
	{
		return *a->NativePtr == *b->NativePtr;
	}

	Vec3 AABB::Bounds::get() {
		return NativePtr->getBounds();
	}

	Vec3 AABB::Center::get() {
		return NativePtr->getCenter();
	}

	float AABB::Size::get() {
		return NativePtr->getSize();
	}

	float AABB::Volume::get() {
		return NativePtr->getVolume();
	}

	//bool AABB::HasZeroVolume::get() {
	//	return NativePtr->hasZeroVolume();
	//}

	bool AABB::IsValid::get() {
		return NativePtr->isValid();
	}

	AABB^ AABB::BLOCK_SHAPE::get() {
		return gcnew AABB(const_cast<::AABB*>(&::AABB::BLOCK_SHAPE));
	}

	AABB^ AABB::BOX_AT_ORIGIN_WITH_NO_VOLUME::get() {
		return gcnew AABB(const_cast<::AABB*>(&::AABB::BOX_AT_ORIGIN_WITH_NO_VOLUME));
	}

}