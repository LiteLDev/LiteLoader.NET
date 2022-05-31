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
        enum TestEnum1
        {
            val_1, va1_2, val_3
        }

        [CommandParameter(ParamType.Enum, IsMandatory = true, Option = CommandParameterOption.EnumAutocompleteExpansion)]
        TestEnum1 testEnum1;

        [CommandParameter(ParamType.Int)]
        int a1;

        public void Execute(CommandOrigin origin, CommandOutput output)
        {
            Console.WriteLine("EnumVal:{0},IntVal:{1}", testEnum1.ToString(), a1);
        }
    }

}
