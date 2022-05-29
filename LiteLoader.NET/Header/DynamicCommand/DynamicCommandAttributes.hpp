#pragma once
#include "../../Main/.NETGlobal.hpp"

namespace LLNET::DynamicCommand {
	using System::AttributeUsageAttribute;
	using System::AttributeTargets;
	using System::Attribute;

	[AttributeUsage(AttributeTargets::Class)]
	public ref class CommandAttribute :Attribute
	{
	public:
		CommandAttribute(String^ name)
			:Name(name)
		{
		}
		String^ Name;
		String^ Description = "";
		MC::CommandPermissionLevel Permission = MC::CommandPermissionLevel::GameMasters;
		MC::CommandFlagValue Flag1 = MC::CommandFlagValue(0x80);
		MC::CommandFlagValue Flag2 = MC::CommandFlagValue(0);
		String^ Alia = "";
	};

	[AttributeUsage(AttributeTargets::Class, AllowMultiple = true)]
	public ref class CommandAliasAttribute :Attribute
	{
	public:
		CommandAliasAttribute(String^ alia)
			:Alia(alia)
		{
		}
		String^ Alia;
	};

	[AttributeUsage(AttributeTargets::Enum)]
	public ref class CommandEnumAttribute :Attribute
	{
		String^ Name = nullptr;
	};

	[AttributeUsage(AttributeTargets::Field)]
	public ref class CommandParameterAttribute :Attribute
	{
		DynamicCommand::ParameterType Type;
	};
}
