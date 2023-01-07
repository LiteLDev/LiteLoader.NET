#include <src/Header/DynamicCommand/ParameterData.hpp>

inline ::DynamicCommand::ParameterType __ParameterData::GetType()
{
    return type;
}

inline void __ParameterData::SetType(::DynamicCommand::ParameterType t)
{
    type = t;
}

inline size_t __ParameterData::GetOffset()
{
    return offset;
}

inline void __ParameterData::SetOffest(size_t o)
{
    offset = o;
}

inline std::string __ParameterData::GetName()
{
    return name;
}

inline void __ParameterData::SetName(std::string& s)
{
    name = s;
}

inline std::string __ParameterData::GetDescription()
{
    return description;
}

inline void __ParameterData::SetDescription(std::string& s)
{
    description = s;
}

inline std::string __ParameterData::GetIdentifier()
{
    return identifier;
}

inline void __ParameterData::SetIdentifier(std::string& s)
{
    identifier = s;
}

//inline bool __ParameterData::GetOptional()
//{
//    return option;
//}

inline void __ParameterData::SetOptional(bool b)
{
    optional = b;
}

inline CommandParameterOption __ParameterData::GetOption()
{
    return option;
}

inline void __ParameterData::SetOption(CommandParameterOption o)
{
    option = o;
}

inline __ParameterData::__ParameterData(__ParameterData const& p)
    : ParameterData(p)
{
}

inline __ParameterData::__ParameterData(std::string const& name, ::DynamicCommand::ParameterType type, bool optional, std::string const& enumOptions, std::string const& identifier, CommandParameterOption parameterOption)
    : Base(name, type, optional, enumOptions, identifier, parameterOption)
{
}

inline __ParameterData::__ParameterData(std::string const& name, ::DynamicCommand::ParameterType type, std::string const& enumOptions, std::string const& identifier, CommandParameterOption parameterOption)
    : Base(name, type, enumOptions, identifier, parameterOption)
{
}