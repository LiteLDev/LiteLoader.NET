#pragma once
#include <exception>
#include <src/Module/Core/Exceptions.hpp>
#include <src/Module/Core/Std/string.hpp>

namespace LiteLoader::NET::Std
{
    private ref class __Exception :ClassTemplate<__Exception, std::exception>
    {
    public:
        __ctor_all(__Exception, std::exception);
    public:
        __ctor_default(__Exception, std::exception);

        virtual string^ what()
        {
            return gcnew string(std::string(NativePtr->what()));
        }
    };

    public ref class exception : LiteLoaderDotNETException
    {
    internal:
        __Exception^ ex;

        exception(__Exception^ ex)
            :LiteLoaderDotNETException(ex->what()->ToString())
        {
        }

    public:
        virtual string^ what()
        {
            return ex->what();
        }
    };
}