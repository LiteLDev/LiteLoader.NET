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

        static void Test(bool val)
        {
            logger.warn.WriteLine(val);
        }

        public void Execute()
        {
            //double ExampleCall(int a1,bool a2,List<string> strArr)

            var succeed = RemoteCallAPI.ExportFunc(".NET", "ExampleCall", (args) =>
            {

                var a = args[0];

                Test(a.AsValue(out var val0));
                Test(val0.AsNumberType(out var number0));
                var a1 = number0.AsInt();

                var b = args[1];

                Test(b.AsValue(out var val1));
                Test(val1.AsBool(out var a2));



                //List<string> strArr = args[2];

                //logger.info.WriteLine($"a1:{a1}");
                //logger.info.WriteLine($"a2:{a2}");

                //for (var i = 0; i<strArr.Count; ++i)
                //{
                //    logger.info.WriteLine($"strArr[{i}]<{strArr[i]}>");
                //}

                var ret = new Valuetype(233);
                return ret;
            });

            logger.warn.WriteLine(succeed);

            var func = RemoteCallAPI.ImportFunc(".NET", "ExampleCall");
            var ret = func(new() { 123456, true, 233.0 });
            double d = ret;

            logger.info.WriteLine($"ReturnVal:{d}");
        }
    }
}
