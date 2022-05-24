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

        delegate List<string> TEST(int a1, bool a2, string a3);

        List<string> Test(int a1, bool a2, string a3)
        {
            logger.warn.WriteLine($"a1:{a1},a2:{a2},a3:{a3}");

            return new() { "str1", "str2", "str3" };
        }

        public void Execute()
        {
            RemoteCallAPI.ExportAs<TEST>(".NET", "ExortAsTest", Test);

            var imp = RemoteCallAPI.ImportAs<List<string>, int, bool, string>(".NET", "ExortAsTest");

            var ret = imp(233, true, "qaq");

            ret.ForEach((str) => { logger.warn.WriteLine($"str:{str}"); });
        }
    }
}
