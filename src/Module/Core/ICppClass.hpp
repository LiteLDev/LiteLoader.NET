#pragma once
namespace LiteLoader::NET
{
    public interface class IPointerConstructable
    {
        void SetNativePointer(nint_t ptr, bool ownsInstance);
    };

    public interface class ICppClass
    {
        property nint_t Intptr
        {
        public:
            nint_t get();
            void set(nint_t value);
        };
        
        property bool OwnsNativeInstance
        {
        public:
            bool get();
            void set(bool value);
        };

        void Destruct();

        size_t GetClassSize();
    };

    public interface class IConstructableCppClass :ICppClass, IPointerConstructable
    {
    };

    public interface class IAbstractCppClass :ICppClass
    {
    };
}