//using Form Namesapce
using LLNET.Form;
using LLNET.Logger;
using LLNET.DynamicCommand;
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
                logger.info.WriteLine("PlayerName:{0}", pl.Name);
                logger.info.WriteLine("buttonVal:{0}", val);
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
                var input = (Input)val["InputName"];

                logger.info.WriteLine("FormInput:{0}", input?.Value);
            };

            CreateCommand();
        }


        public void Execute()
        {

        }

        private static void CreateCommand()
        {

            var command = DynamicCommand.CreateCommand("testformcommand", "command description", CommandPermissionLevel.Any);

            var simpleFormParam = command.SetEnum("Form Type", new() { "simpleform", "customform" });

            command.Mandatory("FormEnum", DynamicCommand.ParameterType.Enum, simpleFormParam??"");

            command.SetCallback((cmd, origin, output, results) =>
            {
                switch ((string)results["FormEnum"].Get())
                {
                    case "simpleform":
                        {
                            simpleForm.SendTo(origin.Player);
                        }
                        break;
                    case "customform":
                        {
                            customForm.SendTo(origin.Player);
                        }
                        break;
                }
            });
        }
    }
}
