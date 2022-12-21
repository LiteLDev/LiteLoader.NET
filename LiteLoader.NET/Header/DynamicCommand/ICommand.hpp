#pragma once
#include "DynamicCommandAttributes.hpp"
#include "DynamicCommandHelper.hpp"

namespace LiteLoader::DynamicCommand {
	using namespace LiteLoader::DynamicCommand::Internal;

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
