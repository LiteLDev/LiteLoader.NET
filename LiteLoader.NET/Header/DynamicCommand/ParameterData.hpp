#pragma once
#include <DynamicCommandAPI.h>

struct __ParameterData : public ::DynamicCommand::ParameterData
{
public:
	using Base = ParameterData;
	inline ::DynamicCommand::ParameterType GetType();
	inline void SetType(::DynamicCommand::ParameterType t);
	inline size_t GetOffset();
	inline void SetOffest(size_t o);
	inline std::string GetName();
	inline void SetName(std::string& s);
	inline std::string GetDescription();
	inline void SetDescription(std::string& s);
	inline std::string GetIdentifier();
	inline void SetIdentifier(std::string& s);
	//inline bool GetOptional();
	inline void SetOptional(bool b);
	inline CommandParameterOption GetOption();
	inline void SetOption(CommandParameterOption o);
	__ParameterData() = delete;
	__ParameterData(__ParameterData const& p);
	__ParameterData(std::string const& name, ::DynamicCommand::ParameterType type, bool optional = false, std::string const& enumOptions = "", std::string const& identifier = "", CommandParameterOption parameterOption = (CommandParameterOption)0);
	__ParameterData(std::string const& name, ::DynamicCommand::ParameterType type, std::string const& enumOptions = "", std::string const& identifier = "", CommandParameterOption parameterOption = (CommandParameterOption)0);
};
