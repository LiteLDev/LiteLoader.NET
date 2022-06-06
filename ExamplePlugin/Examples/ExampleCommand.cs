using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using LLNET.Logger;
using LLNET.DynamicCommand;
using MC;


namespace ExamplePlugin.Examples
{
    using ParamType = LLNET.DynamicCommand.DynamicCommand.ParameterType;

    public class ExampleCommand : IExample
    {
        public void Execute()
        {
            DynamicCommand.RegisterCommand<TestCommand>();
        }
    }


    [Command("testcmd", Description = "test .net command", Permission = CommandPermissionLevel.Any)]
    public class TestCommand : ICommand
    {
        [CommandEnum]
        enum TestEnumType { mode1, mode2, mode3 }

        //[CommandParameterOverload(0)]
        //[CommandParameterOverload(1)]
        //[CommandParameter(ParamType.Enum, IsMandatory = true, Option = CommandParameterOption.EnumAutocompleteExpansion)]
        //TestEnumType TestEnum { get; set; }



        //[CommandParameter(ParamType.Int, OverloadId = 0)]
        //int int_0 { get; set; }

        //[CommandParameter(ParamType.Float, OverloadId = 1)]
        //float float_1 { get; set; }


        //[CommandParameter(ParamType.String, OverloadId = 1)]
        //string? string_1 { get; set; }

        //[CommandParameter(ParamType.JsonValue, OverloadId = 1, IsMandatory = false)]
        //string? json_1 { get; set; }

        public void Execute(CommandOrigin origin, CommandOutput output)
        {
        }
    }

}
