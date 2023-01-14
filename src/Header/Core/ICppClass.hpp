#pragma once
namespace LiteLoader::NET
{
    public interface class IPointerConstructable
    {
        virtual void SetNativePointer(nint_t ptr, bool ownsInstance);
    };

    public interface class ICppClass
    {
        property nint_t Intptr
        {
        public:
            virtual nint_t get();
        };

        virtual void Destruct();
    };

    public interface class IConstructableCppClass :ICppClass, IPointerConstructable
    {
    };

    public interface class IAbstractCppClass :ICppClass
    {
    };
}