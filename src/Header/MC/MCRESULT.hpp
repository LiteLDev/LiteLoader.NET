#pragma once
#include <mc/MCRESULT.hpp>
#include "Types.hpp"

namespace MC
{
public
ref struct MCRESULT : ClassTemplate<MCRESULT, ::MCRESULT>
{
    __ctor(MCRESULT, ::MCRESULT);
    __ctor_default(MCRESULT, ::MCRESULT);
    property array<unsigned char> ^ Filler {
        inline array<unsigned char> ^ get();
        inline void set(array<unsigned char> ^ arg);
    };
    inline operator bool();
    inline int GetFullCode();
    inline bool IsSuccess();
};
} // namespace MC
