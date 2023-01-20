#pragma once
#include <src/Module/Core/ICppClass.hpp>

namespace LiteLoader::NET::Std
{
    generic<typename T> value struct move;
}

namespace LiteLoader::NET::Std::Internal
{
    generic<typename TSelf>
    public interface class IMoveable
    {
        /// <summary>
        /// static method, just invoke move_ctor and return the obj.
        /// </summary>
        virtual TSelf ConstructInstanceByMove(move<TSelf> _Right);
    };
}

#include "move.hpp"

namespace LiteLoader::NET::Std
{
    using LiteLoader::NET::Std::Internal::IMoveable;
}