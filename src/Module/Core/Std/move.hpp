#pragma once
#include "IMoveable.hpp"

namespace LiteLoader::NET::Std
{
    generic<typename T>
    public value struct move
    {
    internal:
        T instance;

    public:
        move(T instance)
            :instance(instance)
        {
        }

        static operator T(move v)
        {
            return v.instance;
        }

        explicit static operator move(T v)
        {
            return move(v);
        }

        T Get()
        {
            return instance;
        }
    };
}
