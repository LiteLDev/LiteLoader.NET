using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using LLNET.RemoteCall;
using LLNET.Logger;

namespace ExamplePlugin.Examples
{
    //piece of junk
    public class ExampleRemoteCall : IExample
    {

        static readonly Logger logger = new("ExampleRemoteCall");

        public void Execute()
        {
            //double ExampleCall(int a1,bool a2,List<string> strArr)

            RemoteCallAPI.ExportFunc(".NET", "ExampleCall", (args) =>
            {

                int a1 = args[0];
                bool a2 = args[1];
                List<string> strArr = args[2];

                logger.info.WriteLine($"a1:{a1}");
                logger.info.WriteLine($"a2:{a2}");

                for (var i = 0; i<strArr.Count; ++i)
                {
                    logger.info.WriteLine($"strArr[{i}]<{strArr[i]}>");
                }

                return 0.0;
            });

            var func = RemoteCallAPI.ImportFunc(".NET", "ExampleCall");

            logger.info.WriteLine($"ReturnVal:{func(new() { 1, false, new List<string> { "1", "2", "3" } })}");
        }
    }
}
