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
        enum TestEnumType { enum1, enum2, enum3 }

        [CommandParameterOverload(0)]
        [CommandParameterOverload(1)]
        [CommandParameter(ParamType.Enum, IsMandatory = true, Option = CommandParameterOption.EnumAutocompleteExpansion)]
        TestEnumType TestEnum { get; set; }



        [CommandParameter(ParamType.Int, OverloadId = 0)]
        int Overload_0 { get; set; }


        [CommandParameter(ParamType.String, OverloadId = 1)]
        string? Overload_1 { get; set; }

        public void Execute(CommandOrigin origin, CommandOutput output)
        {
        }
    }

}
