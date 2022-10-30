#pragma once
#include <mc/CommandVersion.hpp>
#include <LiteLoader.NET/Header/MC/Types.hpp>

namespace MC
{
public
ref class CommandVersion : ClassTemplate<CommandVersion, ::CommandVersion>
{
    __ctor_all(CommandVersion, ::CommandVersion);

    inline static CommandVersion ^ Create();
    inline bool IsCompatible(int a0);
    inline bool Covers(CommandVersion ^ cv);

    static property int CurrentVersion
    {
        static int get()
        {
            return ::CommandVersion::CurrentVersion;
        }
    }

    property int From
    {
        int get()
        {
            return NativePtr->mFrom;
        }
        void set(int value)
        {
            NativePtr->mFrom = value;
        }
    }
    property int To
    {
        int get()
        {
            return NativePtr->mTo;
        }
        void set(int value)
        {
            NativePtr->mTo = value;
        }
    }
};
} // namespace MC