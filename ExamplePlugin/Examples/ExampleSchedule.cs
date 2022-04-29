//using Schedule Namespace
using LLNET.Logger;
using LLNET.Schedule;

namespace ExamplePlugin.Examples
{
    public class ExampleSchedule : IExample
    {
        private static readonly Logger logger = new("ExampleSchedule");
        public void Execute()
        {
            // Delay this callback to next game tick (20 ticks = 1 second)
            ScheduleAPI.NextTick(() =>
            {
                logger.error.WriteLine("hello");
            });


            // Delay this callback for 20 ticks (20 ticks = 1 second)
            ScheduleAPI.Delay(() =>
            {
                logger.error.WriteLine("hello");
            }, 20);


            // Schedule this callback once per 40 ticks (20 ticks = 1 second)
            ScheduleAPI.Repeat(() =>
            {
                logger.error.WriteLine("hello");
            }, 40);


            // Delay first call to callback for 20 ticks
            // then schedule this callback once per 60 ticks (20 ticks = 1 second)
            ScheduleTask sche = ScheduleAPI.DelayRepeat(() =>
            {
                logger.error.WriteLine("hello");
            }, 40, 60);


            // Cancel the schedule
            sche.Cancel();
        }
    }
}
