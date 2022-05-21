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
                List<Valuetype> list = args[2];

                List<string> strArr = new(list.Count);
                foreach (var item in list)
                {
                    item.Get<Value>().AsString(out var str);
                    strArr.Add(str);
                }

                StringBuilder builder = new();
                foreach(var item in strArr)
                {
                    builder.Append(item).Append(' ');
                }

                logger.info.WriteLine($"a1:{a1}");
                logger.info.WriteLine($"a2:{a2}");
                logger.info.WriteLine($"strArr< count:{strArr.Count},str:{builder}>");

                return 0.0;
            });
        }
    }
}
