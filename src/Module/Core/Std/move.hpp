#pragma once
#include "IMoveable.hpp"

namespace LiteLoader::NET::Std
{
    generic<typename T> where T:
    IMoveable
        public value struct move
    {
    private:
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
    };
}
