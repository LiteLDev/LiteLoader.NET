#pragma once
#include "ICommand.hpp"

namespace LLNET::DynamicCommand {
	using namespace LLNET::DynamicCommand::Internal;

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

		if (String::IsNullOrWhiteSpace(cmdAttr->Description))
			throw gcnew RegisterCommandException("Empty Command Description!");

		auto cmdData = gcnew CommandManager::CommandData;

		cmdData->CmdType = cmdType;

		if (!String::IsNullOrWhiteSpace(cmdAttr->Alia))
			cmdData->Alias->Add(cmdAttr->Alia);

		auto aliaAttrArr = cmdType->GetCustomAttributes(CommandAliasAttribute::typeid, false);
		for each (auto aliaAttr in aliaAttrArr)
		{
			auto alia = static_cast<CommandAliasAttribute^>(aliaAttr)->Alia;
			if (String::IsNullOrWhiteSpace(alia))
				continue;
			cmdData->Alias->Add(alia);
		}

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
					String^ enumName = type->Name;

					auto currentEnums = gcnew Dictionary<String^, long>;
					cmdData->Enums->Add(CommandManager::EnumInfo{ enumName,currentEnums,type });

					auto enumValues = type->GetFields(BindingFlags::Public | BindingFlags::Static);
					for each (auto enumVal in enumValues)
					{
						currentEnums->Add(enumVal->Name, static_cast<int>(enumVal->GetValue(nullptr)));
					}
				}
			}
		}

		auto cmdFields = cmdType->GetFields(
			BindingFlags::Static
			| BindingFlags::Public
			| BindingFlags::NonPublic
			| BindingFlags::Instance);

		for each (auto field in cmdFields)
		{
			auto paramAttrArr = field->GetCustomAttributes(CommandParameterAttribute::typeid, false);
			if (paramAttrArr->Length == 0)
				continue;
			auto paramAttr = static_cast<CommandParameterAttribute^>(paramAttrArr[0]);

			String^ paramEnumName = nullptr;
			auto fieldType = field->FieldType;
			if (paramAttr->Type == DynamicCommand::ParameterType::Enum)
			{
				paramEnumName = fieldType->Name;
			}

			cmdData->Parameters->Add(CommandManager::ParamInfo{
				field->Name,
				paramAttr->Type,
				paramAttr->IsMandatory,
				paramEnumName,
				paramAttr->Identifier,
				paramAttr->Option,
				fieldType });
		}

		auto instance = ::DynamicCommand::createCommand(
				marshalString(cmdAttr->Name),
				marshalString(cmdAttr->Description),
				::CommandPermissionLevel(cmdAttr->Permission),
				::CommandFlag((gcnew MC::CommandFlag(cmdAttr->Flag1))),
				::CommandFlag((gcnew MC::CommandFlag(cmdAttr->Flag2))),
				MODULE);

		for each (auto alia in cmdData->Alias)
		{
			if (!instance->setAlias(marshalString(alia))) {
				delete cmdData;
				throw gcnew RegisterCommandException(String::Format("Set Alias Failed! at alia:<{}>", alia));
			}
		}

		for each (auto % Enum in cmdData->Enums)
		{
			std::vector<std::string> enumVec;
			for each (auto % _enum in Enum.enums)
			{
				enumVec.emplace_back(marshalString(_enum.Key));
			}
			instance->setEnum(marshalString(Enum.Name), enumVec);
		}

		for each (auto % param in cmdData->Parameters)
		{
			if (param.IsMandatory)
			{
				if (param.ParamType == DynamicCommand::ParameterType::Enum)
				{
					instance->mandatory(
						marshalString(param.Name),
						::DynamicCommand::ParameterType(param.ParamType),
						marshalString(param.EnumName),
						::CommandParameterOption(param.Option));
				}
				else
				{
					instance->mandatory(
						marshalString(param.Name),
						::DynamicCommand::ParameterType(param.ParamType),
						::CommandParameterOption(param.Option));
				}
			}
			else
			{
				if (param.ParamType == DynamicCommand::ParameterType::Enum)
				{
					instance->optional(
						marshalString(param.Name),
						::DynamicCommand::ParameterType(param.ParamType),
						marshalString(param.EnumName),
						::CommandParameterOption(param.Option));
				}
				else
				{
					instance->optional(
						marshalString(param.Name),
						::DynamicCommand::ParameterType(param.ParamType),
						::CommandParameterOption(param.Option));
				}
			}

		}
		cmdData->cmd = gcnew TCommand();

		auto cmdInterfaces = cmdType->GetInterfaces();
		bool inheritedICommandEvent = false;
		bool inheritedICommandData = false;
		for each (auto Interface in cmdInterfaces)
		{
			if (Interface == ICommandEvent::typeid)
			{
				inheritedICommandEvent = true;
				continue;
			}
			if (Interface == ICommandData::typeid)
				inheritedICommandData = true;
		}

		auto callback = gcnew CommandManager::NativeDynamicCommandCallback;
		callback->data = cmdData;
		auto delcallback = gcnew CommandManager::NativeDynamicCommandCallback::delCallback(
			callback, &CommandManager::NativeDynamicCommandCallback::NativeCallback);
		callback->gch = GCHandle::Alloc(delcallback);
		auto pcallback = static_cast<CommandManager::NativeDynamicCommandCallback::pCallback>(
			(void*)Marshal::GetFunctionPointerForDelegate(delcallback));

		instance->setCallback(pcallback);

		if (inheritedICommandData) {
			auto dynamicCmdInstance = gcnew DynamicCommandInstance(instance.get());
			((ICommandData^)(cmdData->cmd))->BeforeCommandSetup(cmdData, dynamicCmdInstance);
			delete dynamicCmdInstance;
		}

		if (inheritedICommandEvent) {
			auto dynamicCmdInstance = gcnew DynamicCommandInstance(instance.get());
			((ICommandEvent^)(cmdData->cmd))->BeforeCommandSetup(dynamicCmdInstance);
			delete dynamicCmdInstance;
		}

		cmdData->instance = ::DynamicCommand::setup(std::move(instance));

		if (inheritedICommandData) {
			auto dynamicCmdInstance = gcnew DynamicCommandInstance(const_cast<::DynamicCommandInstance*>(cmdData->instance));
			((ICommandData^)(cmdData->cmd))->AfterCommandSetup(cmdData, dynamicCmdInstance);
			delete dynamicCmdInstance;
		}

		if (inheritedICommandEvent) {
			auto dynamicCmdInstance = gcnew DynamicCommandInstance(const_cast<::DynamicCommandInstance*>(cmdData->instance));
			((ICommandEvent^)(cmdData->cmd))->AfterCommandSetup(dynamicCmdInstance);
			delete dynamicCmdInstance;
		}



		return false;
	}
}
