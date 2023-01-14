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

        move(T instance)
            :instance(instance)
        {
        }

    public:
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
