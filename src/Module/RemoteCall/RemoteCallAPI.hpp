#pragma once
#include <src/Main/DotNETGlobal.hpp>

namespace LiteLoader::RemoteCall
{
    ref class Valuetype;
}

namespace LiteLoader::RemoteCall
{
    public ref class RemoteCallAPI sealed
    {
    public:
        /// <summary>
        /// Remote call function prototype.
        /// </summary>
        delegate Valuetype^ CallbackFn(List<Valuetype^>^);
        /// <summary>
        /// <para>Export a function with NameSpace, function name.</para>
        /// <para>　</para>
        /// <para>example:</para>
        /// <para>　<code>ExportedFunc(".NET","ExampleFunction",(args) => { });</code></para>
        /// <para></para>
        /// </summary>
        /// <param name="nameSpace">－Export Function NameSpace</param>
        /// <param name="funcName">－Export Function Name</param>
        /// <param name="fn">－Export Function</param>
        /// <returns>－Is The Export Successful</returns>
        static bool ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ fn);
        /// <summary>
        /// <para>Export a function with NameSpace, function name, and plugin handle.</para>
        /// <para>　</para>
        /// <para>example:</para>
        /// <para>　<code>ExportedFunc(".NET","ExampleFunction",(args) => { });</code></para>
        /// <para></para>
        /// </summary>
        /// <param name="nameSpace">－Export Function NameSpace</param>
        /// <param name="funcName">－Export Function Name</param>
        /// <param name="fn">－Export Function</param>
        /// <param name="handle">－Plugin Handler</param>
        /// <returns>－Is The Export Successful</returns>
        static bool ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ fn, nint_t handle);
        /// <summary>
        /// Import a function with NameSpace, function name.
        /// </summary>
        /// <param name="nameSpace">－Import Function NameSpace</param>
        /// <param name="funcName">－Import Funcrion Name</param>
        /// <returns>－Imported function.</returns>
        static CallbackFn^ ImportFunc(String^ nameSpace, String^ funcName);
        /// <summary>
        /// Determine if this function has been exported.
        /// </summary>
        /// <param name="nameSpace">－Function NameSpace</param>
        /// <param name="funcName">－Function Name</param>
        /// <returns></returns>
        static bool HasFunc(String^ nameSpace, String^ funcName);
        /// <summary>
        /// Remove exported function by NameSpace and function name.
        /// </summary>
        /// <param name="nameSpace">－Function NameSpace</param>
        /// <param name="funcName">－Function Name</param>
        /// <returns></returns>
        static bool RemoveFunc(String^ nameSpace, String^ funcName);
        static bool RemoveNameSpace(String^ nameSpace);
        static bool RemoveFuncs(List<VALUE_TUPLE<String^, String^>>^ funcs);
        /// <summary>
        /// Import a function as a function porotype.
        /// </summary>
        /// <param name="nameSpace">－Import Function NameSpace</param>
        /// <param name="funcName">－Import Function</param>
        /// <returns>－Imported function.</returns>
        generic<typename TDelegate> where TDelegate:Delegate
            static TDelegate ImportAs(String^ nameSpace, String^ funcName);
        /// <summary>
        /// Export a function as a function porotype.
        /// <para>　</para>
        ///	<para>
        /// <example>
        /// <para>Example:</para>
        /// <code>
        /// delegate bool Example(int a1, string str, List&lt;double&gt; doubleList);
        /// <para>　</para>
        /// <para>ExportAs&lt;Example&gt;(".NET","ExampleFunction",(a1,str,doubleList)=>{</para>
        /// <para>return true;</para>
        /// <para>});</para>
        /// </code>
        ///	</example>
        /// </para>
        /// </summary>
        /// <typeparam name="TDelegate">－Function Porotype</typeparam>
        /// <param name="nameSpace">－Export Function NameSpace</param>
        /// <param name="funcName">－Export Function Name</param>
        /// <param name="func">－Export Function</param>
        /// <returns>－Is The Export Successful</returns>
        /// <exception cref="LiteLoader::NET::InvalidRemoteCallTypeException"></exception>
        generic<typename TDelegate> where TDelegate:Delegate
            static bool ExportAs(String^ nameSpace, String^ funcName, TDelegate func);
    };
}

