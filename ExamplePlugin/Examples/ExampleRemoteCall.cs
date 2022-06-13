
using LLNET.Logger;
using LLNET.RemoteCall;

namespace ExamplePlugin.Examples
{
    //piece of junk
    public class ExampleRemoteCall : IExample
    {
        private static readonly Logger logger = new("ExampleRemoteCall");

        private static void Test(bool val)
        {
            logger.warn.WriteLine(val);
        }

        private List<string> Test(int a1, bool a2, string a3)
        {
            logger.warn.WriteLine($"a1:{a1},a2:{a2},a3:{a3}");

            return new() { "str1", "str2", "str3" };
        }

        public void Execute()
        {
            RemoteCallAPI.ExportAs<Func<int, bool, string, List<string>>>(".NET", "ExportAsTest", Test);

            RemoteCallHandler_3<List<string>, int, bool, string> imp = RemoteCallAPI.ImportAs<List<string>, int, bool, string>(".NET", "ExportAsTest");

            List<string> ret = imp(233, true, "qaq");

            ret.ForEach((str) => { logger.warn.WriteLine($"str:{str}"); });
        }
    }
}
