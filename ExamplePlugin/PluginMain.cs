#region Configs

//#define _LOGGER_
//#define _EVENT_
//#define _SCHEDULE_
#define _THOOK_
//#define _DYNAMICCOMMAND_
#define _COMMAND_
//#define _REMOTECALL_
//#define _FORM_

#endregion

using ExamplePlugin.Examples;
using LLNET.Core;
using System.Runtime.InteropServices;

[assembly: LibPath("plugins\\ExamplePlugin\\libs")]

/// <summary>
/// Custom Namespace
/// </summary>
namespace LiteLDev;


/// <summary>
/// Plugin Entry Class
/// </summary>
[PluginMain("ExamplePlugin")]
public class ExamplePlugin : IPluginInitializer
{
    //public ExamplePlugin()
    //{
    //    MetaData = new Dictionary<string, string>
    //    {
    //        {"Something", "..."},
    //        {"foo", "bar"}
    //    };
    //}

    public Dictionary<string, string> MetaData => new()
        {
            {"Something", "..."},
            {"foo", "bar"}
        };

    public Version Version => new(2, 2, 5);

    public string Introduction => "Example plugin for Liteloader.NET";

    /// <summary>
    /// Plugin Entry
    /// </summary>
    public void OnInitialize()
    {
#if _LOGGER_
        ExampleLogger exampleLogger = new();
        exampleLogger.Execute();
#endif
#if _EVENT_
        ExampleEvent exampleEvent = new();
        exampleEvent.Execute();
#endif
#if _SCHEDULE_
        ExampleSchedule exampleSchedule = new();
        exampleSchedule.Execute();
#endif
#if _THOOK_
        ExampleThook exampleThook = new();
        exampleThook.Execute();
#endif
#if _DYNAMICCOMMAND_
        ExampleDynamicCommand exampleDynamicCommand = new();
        exampleDynamicCommand.Execute();
#endif
#if _COMMAND_
        ExampleCommand exampleCommand = new();
        exampleCommand.Execute();
#endif
#if _REMOTECALL_
        ExampleRemoteCall exampleRemoteCall = new();
        exampleRemoteCall.Execute();
#endif
#if _FORM_
        ExampleForm exampleForm = new();
        exampleForm.Execute();
#endif
    }
}