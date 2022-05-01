//using Command Namesapce
using LLNET.DynamicCommand;
using LLNET.Logger;
using MC;

namespace ExamplePlugin.Examples
{
    public class ExampleCommand : IExample
    {
        private static readonly Logger logger = new("ExampleCommand");
        public void Execute()
        {
            DynamicCommandInstance instance = DynamicCommand.CreateCommand("test", ".NET test command");
            instance.SetAlias("aliafortest");
            instance.SetCallback((cmd, origin, output, results) =>
            {
                Level.BroadcastText("hihi!", TextType.RAW);
                logger.info.WriteLine("commmand callback");
            });
            DynamicCommand.Setup(instance);
        }
    }
}
