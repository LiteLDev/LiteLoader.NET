#pragma once

#include <MC/MobEffect.hpp>

#include "../../Tools/.NETGlobal.hpp"
#include "../../Tools/ClassAdapter.hpp"
#include "../../Tools/PropertryHelper.h"

namespace MC::Extensions
{
	ref class MobEffect_EX :MC::MobEffect
	{
	public:
		__ctor_ex(MobEffect_EX, MC::MobEffect, ::MobEffect);
	public:
		property unsigned int Id {unsigned int get(); }
		property bool IsHarmful { bool get(); }
		property bool IsVisible {bool get(); }
	public:
		static MobEffect_EX^ GetById(int id);
		static MobEffect_EX^ GetByName(String^ name);
	};
}