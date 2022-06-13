//using Logger Namespace
using LLNET.Logger;

namespace ExamplePlugin.Examples
{
    public class ExampleLogger : IExample
    {
        /// <summary>
        /// Create A Logger Instance
        /// </summary>
        private readonly Logger logger = new("ExampleLogger");

        public void Execute()
        {
            //output
            logger.info.WriteLine("Info");

            logger.warn.WriteLine("Warn");

            //reset logger title
            logger.Title = "LoggerTitle";

            logger.error.WriteLine("Error");

            logger.Title = "ExampleLogger";


            //cpp style output
            _ = logger.info << "Message" << '\t' << 2333 << '\t' << this << logger.endl;

            //dispose logger
            logger.Dispose();
        }

        public override string ToString()
        {
            return "awa";
        }
    }
}
