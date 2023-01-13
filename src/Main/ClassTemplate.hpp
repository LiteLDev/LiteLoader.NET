#pragma once

#include "ClassTemplate_SafeHandle.hpp"
#include "ClassTemplate_CriticalHandle.hpp"

template<typename RefType, typename NativeType, bool isAbstract = false, bool UseCritical = false>
using ClassTemplate = LiteLoader::NET::Internal::ClassTemplate<RefType, NativeType, isAbstract, UseCritical>;