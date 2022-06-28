//using Form Namesapce
using LLNET.DynamicCommand;
using LLNET.Form;
using LLNET.Logger;
using MC;

namespace ExamplePlugin.Examples
{
    public class ExampleForm : IExample
    {
        private static readonly Logger logger = new("ExampleForm");

        //Create a simple form
        private static readonly SimpleForm simpleForm = new("ExampleForm", "A Example Form");

        //Create a custom form
        private static readonly CustomForm customForm = new("CustomFormTitle");

        static ExampleForm()
        {
            //Append an simple button
            simpleForm.Append(new("Button1"));

            //Set form callback
            simpleForm.Callback = (pl, val) =>
            {
                logger.info.WriteLine($"PlayerName:{pl.Name}");
                logger.info.WriteLine($"buttonVal:{val}");
            };




            //add label
            customForm.Append(new Label("LabelName", "LabelTitle"));

            //add input
            customForm.Append(new Input("InputName", "InputTitle"));

            //add toggle
            customForm.Append(new Toggle("ToggleName", "ToggleTitle"));

            //add slider
            customForm.Append(new Slider("SliderName", "SliderTitle", 0, 100));

            //add dropdown
            customForm.Append(new Dropdown("DropdownName", "DropdownTitle", new()
            {
                "DropDown-1",
                "DropDown-2",
                "DropDown-3"
            }));

            //add stepslider
            customForm.Append(new StepSlider("StepSlider", "TestStepSlider", new()
            {
                "StepSlider-1",
                "StepSlider-2",
                "StepSlider-3"
            }));

            customForm.Callback = (pl, val) =>
            {
                Input input = (Input)val["InputName"];
                foreach (var item in val)
                {
                    logger.Info.WriteLine(item.Key);
                    logger.Info.WriteLine(item.Value.ElementType+item.Value.Value);
                }

                logger.info.WriteLine($"FormInput:{input.Value}");
            };

            CreateCommand();
        }


        public void Execute()
        {

        }

        private static void CreateCommand()
        {

            //DynamicCommandInstance command = DynamicCommand.CreateCommand("testformcommand", "command description", CommandPermissionLevel.Any);

            //string simpleFormParam = command.SetEnum("Form Type", new() { "simpleform", "customform" });

            //command.Mandatory("FormEnum", DynamicCommand.ParameterType.Enum, simpleFormParam ?? string.Empty);

            //command.SetCallback((cmd, origin, output, results) =>
            //{
            //    switch (results["FormEnum"].Get().ToString())
            //    {
            //        case "simpleform":
            //            {
            //                simpleForm.SendTo(origin.Player);
            //            }
            //            break;
            //        case "customform":
            //            {
            //                customForm.SendTo(origin.Player);
            //            }
            //            break;
            //    }
            //});

            //command.AddOverload(new List<string>());

            //DynamicCommand.Setup(command);

            DynamicCommand.RegisterCommand<FormCommand>();
        }

        [Command("testformcommand", Description = "Test .NET Form Command", Permission = CommandPermissionLevel.Any)]
        [CommandEmptyOverload]
        class FormCommand : ICommand
        {
            [CommandEnum]
            enum FormType { simpleform, customform };

            [CommandParameter(DynamicCommand.ParameterType.Enum, Option = CommandParameterOption.EnumAutocompleteExpansion)]
            FormType Form_Type { get; set; }

            public void Execute(CommandOrigin origin, CommandOutput output)
            {
                switch (Form_Type)
                {
                    case FormType.simpleform:
                        {
                            simpleForm.SendTo(origin.Player);
                        }
                        break;
                    case FormType.customform:
                        {
                            customForm.SendTo(origin.Player);
                        }
                        break;
                }
            }
        }
    }
}
