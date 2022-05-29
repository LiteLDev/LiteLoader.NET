#pragma once
#include "DynamicCommandAttributes.hpp"
#include "DynamicCommandHelper.hpp"

namespace LLNET::DynamicCommand {
	using System::Reflection::BindingFlags;

	generic<typename TCommand>
	where TCommand:ICommand, gcnew()
		inline bool DynamicCommand::RegisterCommand()
	{
		auto cmdType = TCommand::typeid;
		auto cmdAttrArr = cmdType->GetCustomAttributes(CommandAttribute::typeid, false);
		if (cmdAttrArr == nullptr || cmdAttrArr->Length == 0)
			throw gcnew RegisterCommandException("Missing CommandAttribute!");
		auto cmdAttr = static_cast<CommandAttribute^>(cmdAttrArr[0]);

		if (String::IsNullOrWhiteSpace(cmdAttr->Name))
			throw gcnew RegisterCommandException("Empty Command Name!");

		auto cmdInstance = ::DynamicCommand::createCommand(
			marshalString(cmdAttr->Name),
			marshalString(cmdAttr->Description),
			::CommandPermissionLevel(cmdAttr->Permission),
			::CommandFlag((gcnew MC::CommandFlag(cmdAttr->Flag1))),
			::CommandFlag((gcnew MC::CommandFlag(cmdAttr->Flag2))),
			MODULE);

		auto nestedTypes = cmdType->GetNestedTypes(
			BindingFlags::Public
			| BindingFlags::NonPublic
			| BindingFlags::Instance);

			for each (auto type in nestedTypes)
			{
				if (type->IsEnum)
				{
					auto enumAttrArr = type->GetCustomAttributes(CommandEnumAttribute::typeid, false);
					if (enumAttrArr->Length > 0) 
					{

					}
				}
			}


			return false;
	}
}
