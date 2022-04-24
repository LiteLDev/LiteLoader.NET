#region Configs

//#define _LOGGER_ 
#define _EVENT_

#endregion

using ExamplePlugin.Examples;

/// <summary>
/// Plugin Entry Namespace
/// </summary>
namespace PluginMain
{
    /// <summary>
    /// Plugin Entry Class
    /// </summary>
    public class Plugin
    {
        /// <summary>
        /// Plugin Entry
        /// </summary>
        public static void OnPostInit()
        {

#if _LOGGER_
            ExampleLogger exampleLogger = new();
            exampleLogger.Execute();
#endif

#if _EVENT_
            ExampleEvent exampleEvent = new();
            exampleEvent.Execute();
#endif
        }
    }
}