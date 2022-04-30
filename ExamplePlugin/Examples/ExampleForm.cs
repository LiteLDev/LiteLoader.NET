//using Form Namesapce
using LLNET.Form;
using LLNET.Logger;

namespace ExamplePlugin.Examples
{
    public class ExampleForm : IExample
    {
        private static readonly Logger logger = new("ExampleForm");
        public void Execute()
        {
            //Create a simple form
            SimpleForm simpleForm = new("ExampleForm", "A Example Form");

            //Append an simple button
            simpleForm.Append(new Button("Button1"));

            //Set form callback
            simpleForm.callback = (pl, val) =>
            {
                logger.info.WriteLine("PlayerName:{0}", pl.Name);
                logger.info.WriteLine("buttonVal:{0}", val);
            };

            //Send form to player
            MC.Level.GetAllPlayers().ForEach(player =>
            {
                simpleForm.SendTo(player);
            });
        }
    }
}
