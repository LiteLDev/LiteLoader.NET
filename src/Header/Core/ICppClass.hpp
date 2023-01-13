#pragma once
namespace LiteLoader::NET
{
    public interface class IPointerConstructable
    {
        virtual void SetNativePointer(IntPtr ptr, bool ownsInstance);
    };

    public interface class ICppClass
    {
        property System::IntPtr Intptr
        {
        public:
            virtual System::IntPtr get();
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