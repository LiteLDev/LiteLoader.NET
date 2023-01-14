#pragma once
namespace LiteLoader::NET
{
public
value class SecondaryRankPtr
{
private:
    void** ptr;

public:
    SecondaryRankPtr(void** p2)
        : ptr(p2)
    {
    }
    /// <param name="p2">:Secondary Rank Pointer nint_t </param>
    SecondaryRankPtr(nint_t p2)
        : ptr((void**)p2.ToPointer())
    {
    }
    inline void** ToSecPointer()
    {
        return ptr;
    }
    inline void* ToPointer()
    {
        return *ptr;
    }
    /// <returns>nint_t(ptr)   type:void**</returns>
    inline nint_t ToSecIntPtr()
    {
        return nint_t(ptr);
    }
    /// <returns>nint_t(*ptr)   type:void*</returns>
    inline nint_t ToIntPtr()
    {
        return nint_t(*ptr);
    }
    inline operator void**()
    {
        return ptr;
    }
    inline operator void*()
    {
        return *ptr;
    }
};
}
