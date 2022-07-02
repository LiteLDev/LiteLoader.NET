#include "../../Header/MC/MobEffect.hpp"
#pragma once

namespace MC::Extensions
{
	inline unsigned int MobEffect_EX::Id::get() { return NativePtr->getId(); }

	inline bool MobEffect_EX::IsHarmful::get() { return NativePtr->isHarmful(); }

	inline bool MobEffect_EX::IsVisible::get() { return NativePtr->isVisible(); }

	inline MobEffect_EX^ MC::Extensions::MobEffect_EX::GetById(int id) {
		return gcnew MobEffect_EX(::MobEffect::getById(id));
	}

	inline MobEffect_EX^ MC::Extensions::MobEffect_EX::GetByName(String^ name) {
		return gcnew MobEffect_EX(::MobEffect::getByName(marshalString(name)));
	}
}

