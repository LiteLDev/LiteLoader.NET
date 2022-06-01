#pragma once
#include "DynamicCommandAttributes.hpp"

namespace LLNET::DynamicCommand {
	using namespace LLNET::DynamicCommand::Internal;

	/// <summary>
	/// Inherited this interface to register a new command by DynamicCommand.RegisterCommand&lt;ICommand&gt;().
	/// <example>
	/// <para>　</para>
	/// <code>
	/// <para>[Command("examplecmd", Description = "example command.", Permission = MC.CommandPermissionLevel.Any)]</para>
	/// <para>class ExampleCommand : ICommand</para>
	/// <para>{</para>
	/// <para>　　void Execute(MC.CommandOrigin origin, MC.CommandOutput output){ }</para>
	/// <para>　</para>
	/// <para>　　[CommandParameter(ParamType.String)]</para>
	/// <para>　　string? Parameter_1 { get; set; }</para>
	/// <para>};</para>
	/// </code>
	/// </example>
	/// </summary>
	public interface class ICommand {
		void Execute(MC::CommandOrigin^ origin, MC::CommandOutput^ output);
	};

	public interface class ICommandEvent {
		void BeforeCommandSetup(DynamicCommandInstance^ cmd);
		void AfterCommandSetup(DynamicCommandInstance^ cmd);
	};

	public interface class ICommandData {
		void BeforeCommandSetup(CommandManager::CommandData^ cmdData, DynamicCommandInstance^ cmd);
		void AfterCommandSetup(CommandManager::CommandData^ cmdData, DynamicCommandInstance^ cmd);
	};
}


void LLNET::DynamicCommand::Internal::CommandManager::NativeDynamicCommandCallback::NativeCallback(::DynamicCommand const& cmd, ::CommandOrigin const& origin, ::CommandOutput& output, std::unordered_map<std::string, ::DynamicCommand::Result>& results)
{
	auto params = gcnew List<ParamInfo>(data->Parameters);

	for (auto& [k, v] : results)
	{
		for (int i = 0; i < params->Count;)
		{
			auto% currentParam = params[i];
			if (currentParam.Name != marshalString(k))
			{
				++i;
			}
			else
			{
				auto result = _parseResult(v, currentParam);
				if (currentParam.IsField)
				{
					currentParam.Fieldinfo->SetValue(data->cmd, result);
				}
				else
				{
					currentParam.PropertyInfo->SetValue(data->cmd, result);
				}
				params->Remove(currentParam);
				break;
			}
		}
	}

	auto _origin = gcnew MC::CommandOrigin(const_cast<::CommandOrigin*>(&origin));
	auto _output = gcnew MC::CommandOutput(&output);

	data->cmd->Execute(_origin, _output);

	delete _origin;
	delete _output;
	if (data->autoReset)
		data->cmd = static_cast<ICommand^>(System::Activator::CreateInstance(data->CmdType));
}

System::Object^ LLNET::DynamicCommand::CommandManager::NativeDynamicCommandCallback::_parseResult(::DynamicCommand::Result& result, ParamInfo% paramInfo)
{
	if (!result.isSet)
		return nullptr; // null
	switch (result.type)
	{
	case ::DynamicCommand::ParameterType::Bool:
		return result.getRaw<bool>();
	case ::DynamicCommand::ParameterType::Int:
		return result.getRaw<int>();
	case ::DynamicCommand::ParameterType::Float:
		return result.getRaw<float>();
	case ::DynamicCommand::ParameterType::String:
		return marshalString(result.getRaw<std::string>());
	case ::DynamicCommand::ParameterType::Actor:
	{
		auto arr = gcnew List<MC::Actor^>;
		for (auto i : result.get<std::vector<Actor*>>())
		{
			arr->Add(gcnew MC::Actor(i));
		}
		return arr;
	}
	case ::DynamicCommand::ParameterType::Player:
	{
		auto arr = gcnew List<MC::Player^>;
		for (auto i : result.get<std::vector<Player*>>())
		{
			arr->Add(gcnew MC::Player(i));
		}
		return arr;
	}
	case ::DynamicCommand::ParameterType::BlockPos:
	{
		return gcnew MC::BlockPos(result.get<BlockPos>());
	}
	case ::DynamicCommand::ParameterType::Vec3:
	{
		return gcnew MC::Vec3(result.get<Vec3>());
	}
	case ::DynamicCommand::ParameterType::Message:
		return gcnew MC::CommandMessage(const_cast<::CommandMessage*>(&result.getRaw<::CommandMessage>()));
	case ::DynamicCommand::ParameterType::RawText:
		return marshalString(result.getRaw<std::string>());
	case ::DynamicCommand::ParameterType::JsonValue:
		return marshalString(JsonHelpers::serialize(result.getRaw<Json::Value>()));
	case ::DynamicCommand::ParameterType::Item:
		return gcnew MC::CommandItem(result.getRaw<CommandItem>());
	case ::DynamicCommand::ParameterType::Block:
		return gcnew MC::Block(const_cast<Block*>(result.getRaw<Block const*>()));
	case ::DynamicCommand::ParameterType::Effect:
		return gcnew MC::MobEffect((MobEffect*)result.getRaw<MobEffect const*>());
	case ::DynamicCommand::ParameterType::Enum:
	{
		for each (auto enuminfo in data->Enums)
		{
			if (paramInfo.EnumName == enuminfo.Name)
			{
				return enuminfo.enums[marshalString(result.getRaw<std::string>())];
			}
		}
	}
	case ::DynamicCommand::ParameterType::SoftEnum:
		return marshalString(result.getRaw<std::string>());
	case ::DynamicCommand::ParameterType::Command:
		return gcnew MC::Command((::__Command*)result.getRaw<std::unique_ptr<::Command>>().get());
	case ::DynamicCommand::ParameterType::ActorType:
		return gcnew MC::ActorDefinitionIdentifier((ActorDefinitionIdentifier*)result.getRaw<ActorDefinitionIdentifier const*>());
	default:
		return nullptr; // null
		break;
	}
}
