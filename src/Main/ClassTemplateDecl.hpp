#pragma once

namespace LiteLoader::NET::Internal
{
    template <typename REFCLASS, typename NATIVECLASS, bool isAbstract = false, bool UseCritical = false>
    ref class ClassTemplate;
}
