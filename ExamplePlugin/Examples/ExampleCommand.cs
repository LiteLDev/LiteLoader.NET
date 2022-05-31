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
        enum TestEnumType { Enum1, Enum2, Enum3 }

        [CommandParameterOverload(0)]
        [CommandParameter(ParamType.Enum, IsMandatory = true, Option = CommandParameterOption.EnumAutocompleteExpansion)]
        TestEnumType TestEnum { get; set; }

        [CommandParameter(ParamType.Int)]
        int A_1 { get; set; }

        public void Execute(CommandOrigin origin, CommandOutput output)
        {
            Console.WriteLine("EnumVal:{0},IntVal:{1}", TestEnum.ToString(), A_1);
        }
    }

}
