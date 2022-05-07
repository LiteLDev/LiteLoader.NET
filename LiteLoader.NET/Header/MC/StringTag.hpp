#pragma once
#include "Tag.hpp"
#include <MC/StringTag.hpp>
namespace MC
{
public
ref class StringTag : public Tag
{
public:
    __ctor_base(StringTag, ::StringTag, Tag);

    inline String^ Value();
    inline StringTag ^ operator=(std::string val);
    inline static StringTag ^ Create();
    inline bool Set(String^ val);
    inline String^ Get();

#ifdef INCLUDE_MCAPI
    StringTag(::String^ _0);

    StringTag();

    virtual void DeleteChildren() override;

    virtual ::String^ ToString() override;

    virtual MC::Tag::Type GetId();

    virtual bool Equals(MC::Tag ^ _0) override;

    virtual unsigned long long hash();
#endif // INCLUDE_MCAPI
};
} // namespace MC
