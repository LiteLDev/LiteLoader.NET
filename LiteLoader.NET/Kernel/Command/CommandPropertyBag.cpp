#include "../../Header/Command/CommandPropertyBag.hpp"
#include "../../Header/MC/BlockPos.hpp"
#include "../../Header/MC/Vec3.hpp"
namespace MC
{
inline void CommandPropertyBag::AddToResultList(String^ str0, String^ str1)
{
    NativePtr->addToResultList(marshalString(str0), marshalString(str1));
}

inline void CommandPropertyBag::Set(String^ str, BlockPos bp)
{
    NativePtr->set(marshalString(str), bp);
}

inline void CommandPropertyBag::Set(String^ str, Vec3 bp)
{
    NativePtr->set(marshalString(str), bp);
}

} // namespace MC