using LLNET.DynamicCommand;
using LLNET.Logger;
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

    //Auto reset by create a new instance.
    [Command("testcmd", Description = ".NET test command", Permission = CommandPermissionLevel.Any, AutoReset = true)]
    public class TestCommand : ICommand
    {
        static Logger Logger { get; set; } = new("ExampleCommand");




        [CommandEnum]
        private enum Operation_list { list };

        [CommandEnum]
        private enum Operation_add { add, remove };




        //Command overload 0
        [CommandParameter(ParamType.Enum, OverloadId = 0, Option = CommandParameterOption.EnumAutocompleteExpansion)]
        //use kvPair to determine if this parameter has been set.
        private KeyValuePair<bool, Operation_add> Enum_Add { get; set; }


        [CommandParameter(ParamType.Int, OverloadId = 0)]
        int Count { get; set; }




        //Command overload 1
        [CommandParameter(ParamType.Enum, OverloadId = 1, Option = CommandParameterOption.EnumAutocompleteExpansion)]
        private KeyValuePair<bool, Operation_list> Enum_List { get; set; }



        /*      ParamType                                       Type
         *      Actor[command selector(@e...)]                  List<MC.Actor>
         *      ActorType[?]                                    MC.ActorDefinitionIdentifier
         *      Block[blocks]                                   MC.Block
         *      BlockPos[block position(~ ~ ~ or xyz...)]       MC.BlockPos
         *      Bool[true or false]                             bool
         *      Command[?]                                      MC.Command
         *      Effect[effects]                                 MC.MobEffect
         *      Enum                                            enum
         *      Float                                           float
         *      Int                                             int
         *      Item(items)                                     MC.CommandItem
         *      JsonValue[json string]                          string
         *      Message[?]                                      MC.CommandMessage
         *      Player[command selector(@a @p @r...)]           List<MC.Player>
         *      RawText                                         string
         *      SoftEnum[?]                                     ?
         *      String                                          string
         *      Vec3[position(~ ~ ~ or xyz....)]                MC.Vec3
         *      WildcardSelector[?]                             ?
         */

        public void Execute(CommandOrigin origin, CommandOutput output)
        {
            if (Enum_Add.Key)
            {
                Logger.Warn.WriteLine($"{Enum_Add.Value} Count:{Count}");
            }
            if (Enum_List.Key)
            {
                Logger.Warn.WriteLine($"{Enum_List.Value}");
            }
        }
    }

}
