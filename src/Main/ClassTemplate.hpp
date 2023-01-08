#pragma once

#include "ClassTemplate_SafeHandle.hpp"
#include "ClassTemplate_CriticalHandle.hpp"

template<typename RefType, typename NativeType, bool UseCritical = false>
using ClassTemplate = LiteLoader::NET::ClassTemplate<RefType, NativeType, UseCritical>;