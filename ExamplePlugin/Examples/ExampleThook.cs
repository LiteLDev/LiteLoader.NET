//#define LAMBDA

//using Hook Namespace
using LLNET.Hook;
using LLNET.Logger;
using MC;

namespace ExamplePlugin.Examples
{
    public class ExampleThook : IExample
    {


        public void Execute()
        {
            //Register hook class
            Thook.RegisterHook<FuenaceBlock_SetLit_Hook, Func<char, IntPtr, IntPtr, uint, long, long, IntPtr>>();
        }


        //Declare function prototype

        //Setup Hook Symbol
        [HookSymbol("?setLit@FurnaceBlock@@SAX_NAEAVBlockSource@@AEBVBlockPos@@W4BlockActorType@@AEBVBlock@@4@Z")]
        //IDA: struct BlockActor *__fastcall FurnaceBlock::setLit(char a1, BlockSource *a2, const struct BlockPos *a3, unsigned int a4, __int64 a5, __int64 a6)
        private class FuenaceBlock_SetLit_Hook : THookBase<Func<char, IntPtr, IntPtr, uint, long, long, IntPtr>>
        {
            private static readonly Logger logger = new("ExampleHook");

            //Hook Function
            private IntPtr SetLitHookFunction(char a1, IntPtr blockSource, IntPtr blockPos, uint a4, long a5, long a6)
            {

                BlockSource source = new(blockSource);
                BlockPos pos = new(blockPos);

                //BlockPos as string
                logger.error.WriteLine(pos);
                //Block typename
                logger.error.WriteLine(source.GetBlockInstance(pos).Block.TypeName);


                //Use original function
                return Original(a1, blockSource, blockPos, a4, a5, a6);
            }


            //Setup Function
            public override void Setup()
            {
#if !LAMBDA
                //Normal
                Hook = SetLitHookFunction;
#else
                //Or using Lambda expression
                Hook = (a1, bs, bp, a4, a5, a6) =>
                {
                    return Original(a1, bs, bp, a4, a5, a6);
                };
#endif
            }
        }

    }
}
