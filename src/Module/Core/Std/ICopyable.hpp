#pragma once
namespace LiteLoader::NET::Std::Internal
{
    generic<typename TSelf>
    public interface class ICopyable
    {
        /// <summary>
        /// static method, just invoke copy_ctor and return the obj.
        /// </summary>
        virtual TSelf ConstructInstanceByCopy(TSelf _Right);
    };
}

namespace LiteLoader::NET::Std
{
    using LiteLoader::NET::Std::Internal::ICopyable;
}