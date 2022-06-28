#pragma once
#include "ICommand.hpp"

namespace LLNET::DynamicCommand {
	using namespace LLNET::DynamicCommand::Internal;

	using System::Reflection::BindingFlags;

	generic<typename TCommand>
	where TCommand:ICommand, gcnew()
		bool DynamicCommand::RegisterCommand()
	{
		auto cmdType = TCommand::typeid;

#pragma region CommandAttribute

		auto cmdAttrArr = cmdType->GetCustomAttributes(CommandAttribute::typeid, false);
		if (cmdAttrArr == nullptr || cmdAttrArr->Length == 0)
			throw gcnew RegisterCommandException("Missing CommandAttribute!");

		auto cmdAttr = static_cast<CommandAttribute^>(cmdAttrArr[0]);

		if (String::IsNullOrWhiteSpace(cmdAttr->Name))
			throw gcnew RegisterCommandException("Empty Command Name!");

		if (String::IsNullOrWhiteSpace(cmdAttr->Description))
			throw gcnew RegisterCommandException("Empty Command Description!");

#pragma endregion
		auto cmdData = gcnew CommandManager::CommandData;
		cmdData->CmdType = cmdType;
		cmdData->autoReset = cmdAttr->AutoReset;
#pragma region CommandAliasAttribute

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

#pragma endregion
#pragma region CommandEnumAttribute

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

					auto currentEnums = gcnew Dictionary<String^, Object^>;
					cmdData->Enums->Add(CommandManager::EnumInfo{ enumName,currentEnums,type });

					auto enumValues = type->GetFields(BindingFlags::Public | BindingFlags::Static);
					for each (auto enumVal in enumValues)
					{
						currentEnums->Add(enumVal->Name, enumVal->GetValue(nullptr));
					}
				}
			}
		}

#pragma endregion
#pragma region CommandParameterAttribute_Field

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

			auto overloads = gcnew List<int>;
			if (!overloads->Contains(paramAttr->overloadId))
				overloads->Add(paramAttr->overloadId);

			cmdData->Parameters->Add(CommandManager::ParamInfo{
				field->Name,
				paramAttr->Type,
				paramAttr->IsMandatory,
				overloads,
				paramEnumName,
				paramAttr->Identifier,
				paramAttr->Option,
				field,
				nullptr,
				true });

			auto overloadAttrArr = field->GetCustomAttributes(CommandParameterOverloadAttribute::typeid, false);
			for each (auto overloadAttr in overloadAttrArr)
			{
				auto id = (static_cast<CommandParameterOverloadAttribute^>(overloadAttr))->OverloadId;
				if (!overloads->Contains(id))
					overloads->Add(id);
			}
		}

#pragma endregion
#pragma region CommandParameterAttribute_Property

		auto cmdProperties = cmdType->GetProperties(
			BindingFlags::Static
			| BindingFlags::Public
			| BindingFlags::NonPublic
			| BindingFlags::Instance);

		for each (auto Property in cmdProperties)
		{
			auto paramAttrArr = Property->GetCustomAttributes(CommandParameterAttribute::typeid, false);
			if (paramAttrArr->Length == 0)
				continue;

			if (!Property->CanWrite)
				throw gcnew RegisterCommandException(String::Format("Property Cannot Be Written! Property:<{0}>", Property->Name));

			auto paramAttr = static_cast<CommandParameterAttribute^>(paramAttrArr[0]);

			String^ paramEnumName = nullptr;
			auto propertyType = Property->PropertyType;
			if (paramAttr->Type == DynamicCommand::ParameterType::Enum)
			{
				paramEnumName = propertyType->Name;
			}

			auto overloads = gcnew List<int>;
			if (!overloads->Contains(paramAttr->overloadId))
				overloads->Add(paramAttr->overloadId);

			cmdData->Parameters->Add(CommandManager::ParamInfo{
				Property->Name,
				paramAttr->Type,
				paramAttr->IsMandatory,
				overloads,
				paramEnumName,
				paramAttr->Identifier,
				paramAttr->Option,
				nullptr,
				Property,
				false });

			auto overloadAttrArr = Property->GetCustomAttributes(CommandParameterOverloadAttribute::typeid, false);
			for each (auto overloadAttr in overloadAttrArr)
			{
				auto id = (static_cast<CommandParameterOverloadAttribute^>(overloadAttr))->OverloadId;
				if (!overloads->Contains(id))
					overloads->Add(id);
			}
		}

#pragma endregion


		auto instance = ::DynamicCommand::createCommand(
			marshalString(cmdAttr->Name),
			marshalString(cmdAttr->Description),
			::CommandPermissionLevel(cmdAttr->Permission),
			::CommandFlag((gcnew MC::CommandFlag(cmdAttr->Flag1))),
			::CommandFlag((gcnew MC::CommandFlag(cmdAttr->Flag2))),
			Global::__GetCurrentModule(Assembly::GetCallingAssembly()));

		for each (auto alia in cmdData->Alias)
		{
			if (!instance->setAlias(marshalString(alia)))
				throw gcnew RegisterCommandException(String::Format("Set Alias Failed! at alia:<{}>", alia));
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

		auto Overloads = gcnew Dictionary<int, List<CommandManager::ParamInfo>^>;
		for each (auto % param in cmdData->Parameters)
		{
			for each (auto id in param.OverloadIds)
			{
				if (!Overloads->ContainsKey(id))
					Overloads->Add(id, gcnew List<CommandManager::ParamInfo>);
				Overloads[id]->Add(param);
			}
		}

		std::vector<std::string> strVec;
		if (Overloads->Count != 0)
			for each (auto % overload in Overloads)
			{
				for each (auto param in overload.Value)
				{
					if (param.ParamType == DynamicCommand::ParameterType::Enum)
						strVec.emplace_back(marshalString(param.EnumName));
					else
						strVec.emplace_back(marshalString(param.Name));
				}
				instance->addOverload(std::move(strVec));
				strVec.clear();
			}
		else
			instance->addOverload(std::move(strVec));

		auto cmdAttrEmptyOverloadArr = cmdType->GetCustomAttributes(CommandAttribute::typeid, false);
		if (cmdAttrEmptyOverloadArr->Length > 0)
			instance->addOverload(std::vector<std::string>());


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