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
        static Logger Logger { get; set; } = new("ExampleCommand");

        [CommandEnum]
        enum TestEnumType { mode1, mode2, mode3 }

        [CommandParameterOverload(0)]
        [CommandParameterOverload(1)]
        [CommandParameter(ParamType.Enum, IsMandatory = true, Option = CommandParameterOption.EnumAutocompleteExpansion)]
        TestEnumType TestEnum { get; set; }


        [CommandParameter(ParamType.Int, OverloadId = 0)]
        int Int_0 { get; set; }

        [CommandParameter(ParamType.Float, OverloadId = 1)]
        float Float_1 { get; set; }


        [CommandParameter(ParamType.String, OverloadId = 1)]
        string? String_1 { get; set; }

        [CommandParameter(ParamType.JsonValue, OverloadId = 1, IsMandatory = false)]
        string? Json_1 { get; set; }

        public void Execute(CommandOrigin origin, CommandOutput output)
        {
            Logger.info.WriteLine($"TestEnum:{TestEnum},Int_0:{Int_0},Float_1:{Float_1},String_1:{String_1??"Empty"},Json_1:{Json_1??"Empty"}");
        }
    }

}
