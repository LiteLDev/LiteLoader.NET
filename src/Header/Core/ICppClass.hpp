#pragma once
namespace LiteLoader::NET
{
    public interface class ICppClass
    {
        property System::IntPtr Intptr
        {
        public:
            virtual System::IntPtr get();
        };

        virtual void Destructor(void* ptr);
    };
}