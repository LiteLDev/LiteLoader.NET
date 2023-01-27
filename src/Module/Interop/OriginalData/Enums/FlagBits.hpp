#pragma once
namespace LiteLoader::NET::Interop::OrignalData
{
    public enum class FlagBits
    {
        None = 0,
        Const = 1,
        Constructor = 2,
        Destructor = 3,
        Operate = 4,
        UnkonwnFunc = 5,
        StaticGlobalVar = 6,
        __Ptr64Spec = 7,
        HasThis = __Ptr64Spec,
        IsPureCall = 8
    };
}