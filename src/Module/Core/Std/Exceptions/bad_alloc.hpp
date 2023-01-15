#pragma once
#include "exception.hpp"

namespace LiteLoader::NET::Std
{
    public ref class bad_alloc :exception
    {
    internal:
        bad_alloc(__Exception^ ex)
            :exception(ex) {}
    };

    public ref class bad_array_new_length :bad_alloc
    {
    internal:
        bad_array_new_length(__Exception^ ex)
            :bad_alloc(ex) {}
    };
}