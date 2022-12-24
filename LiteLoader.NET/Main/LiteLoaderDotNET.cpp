#pragma unmanaged
#include <Utils/WinHelper.h>
#include <LLAPI.h>

#include "Config.hpp"

#pragma unmanaged
extern void LoadMain();

#pragma unmanaged
void entry()
{
    _set_se_translator(seh_exception::TranslateSEHtoCE);

    LoadMain();
}
