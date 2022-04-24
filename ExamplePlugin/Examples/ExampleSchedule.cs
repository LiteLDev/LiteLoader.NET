using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//using Schedule Namespace
using LLNET.Schedule;
using LLNET.Logger;

namespace ExamplePlugin.Examples
{
    public class ExampleSchedule : IExample
    {
        public void Execute()
        {
            ScheduleAPI.Repeat(() => { }, 1);
        }
    }
}
