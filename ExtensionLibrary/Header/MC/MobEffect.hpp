#pragma once

#include <MC/MobEffect.hpp>

#include "../../Tools/.NETGlobal.hpp"
#include "../../Tools/ClassAdapter.hpp"
#include "../../Tools/PropertryHelper.h"

namespace MC::Extensions
{
	ref class MobEffectEX :MC::MobEffect
	{
	public:
		__ctor_ex(MobEffectEX, MC::MobEffect, ::MobEffect);
	public:
		property unsigned int Id {unsigned int get(); }
		property bool IsHarmful { bool get(); }
		property bool IsVisible {bool get(); }
	public:
		static MobEffectEX^ GetById(int id);
		static MobEffectEX^ GetByName(String^ name);
	};
}