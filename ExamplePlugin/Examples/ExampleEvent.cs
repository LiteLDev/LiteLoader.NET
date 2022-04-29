//using Event Namespace
using LLNET.Event;
using LLNET.Logger;

namespace ExamplePlugin.Examples
{
    internal class ExampleEvent : IExample
    {
        private static readonly Logger logger = new("ExampleEvent");
        public void Execute()
        {
            //Subscribe an event with Callback function
            PlayerJoinEvent.Subscribe(PlayerJoinEventCallback);



            //using lambda expression
            PlayerJoinEvent.Subscribe(ev =>
            {
                logger.warn.WriteLine(ev.Player.BlockPos);
                return true;
            });



            //Subscribe and Unsubscribe
            var listener = PlayerCmdEvent.Subscribe(ev =>
            {
                return true;
            });

            PlayerCmdEvent.Unsubscribe(listener);



            //Subscribe an cpp reference event
            PlayerChatEvent.Subscribe_Ref(ev =>
            {
                logger.warn.WriteLine(ev.Message);
                ev.Message = "New Message";
                return true;
            });
            PlayerChatEvent.Subscribe_Ref(ev =>
            {
                logger.warn.WriteLine(ev.Message);
                return false;
            });



            //More easier to use
            PlayerJumpEvent.Event += ev =>
            {
                logger.warn.WriteLine("Event1");
                return true;
            };
            PlayerJumpEvent.Event += ev =>
            {
                logger.warn.WriteLine("Event2");
                return true;
            };
            PlayerJumpEvent.Event += ev =>
            {
                logger.warn.WriteLine("Event3");
                return true;
            };




            bool signal = false;
            bool func(PlayerUseItemOnEvent ev)
            {
                if (!signal)
                {
                    logger.warn.WriteLine("Callback Function Invoke.");
                    signal = true;
                }
                else
                {
                    logger.warn.WriteLine("Remove Event Callback.");
                    PlayerUseItemOnEvent.Event -= func;
                }
                return true;
            }
            PlayerUseItemOnEvent.Event += func;

        }

        private bool PlayerJoinEventCallback(PlayerJoinEvent ev)
        {
            logger.info.WriteLine(ev.Player.Name);
            logger.info.WriteLine(ev.Player.IP);

            //return false to intercept event
            return true;
        }
    }
}
