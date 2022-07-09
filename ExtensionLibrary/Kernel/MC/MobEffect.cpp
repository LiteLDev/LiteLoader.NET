#include "../../Header/MC/MobEffect.hpp"
#pragma once

namespace MC::Extensions
{
	inline unsigned int MobEffectEX::Id::get() { return NativePtr->getId(); }

	inline bool MobEffectEX::IsHarmful::get() { return NativePtr->isHarmful(); }

	inline bool MobEffectEX::IsVisible::get() { return NativePtr->isVisible(); }

	inline MobEffectEX^ MC::Extensions::MobEffectEX::GetById(int id) {
		return gcnew MobEffectEX(::MobEffect::getById(id));
	}

	inline MobEffectEX^ MC::Extensions::MobEffectEX::GetByName(String^ name) {
		return gcnew MobEffectEX(::MobEffect::getByName(marshalString(name)));
	}
}

