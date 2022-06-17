#pragma once

#include "ImportAs.hpp"
#include "ExportAs.hpp"

namespace LLNET::RemoteCall
{
	/// <summary>
	/// ========Remote Call API========
	/// <para>　</para>
	/// <para>Mainly designed for scripting engines</para>
	/// <para>Please call it in MC_SERVER thread or in ScheduleAPI</para>
	/// </summary>
	public ref class RemoteCallAPI abstract
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
		/// <para>　<code>ExportFunc(".NET","ExampleFunction",(args) => { });</code></para>
		/// <para></para>
		/// </summary>
		/// <param name="nameSpace">－Export Function NameSpace</param>
		/// <param name="funcName">－Export Function Name</param>
		/// <param name="fn">－Export Function</param>
		/// <returns>－Is The Export Successful</returns>
		static bool ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ fn);


		/// <summary>
		/// <para>Export a function with NameSpace, function name, and plugin handler.</para>
		/// <para>　</para>
		/// <para>example:</para>
		/// <para>　<code>ExportFunc(".NET","ExampleFunction",(args) => { });</code></para>
		/// <para></para>
		/// </summary>
		/// <param name="nameSpace">－Export Function NameSpace</param>
		/// <param name="funcName">－Export Function Name</param>
		/// <param name="fn">－Export Function</param>
		/// <param name="handler">－Plugin Handler</param>
		/// <returns>－Is The Export Successful</returns>
		static bool ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ fn, IntPtr handler);


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
		static bool RemoveFuncs(List<Pair<String^, String^>>^ funcs);


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
		/// <param name="fn">－Export Function</param>
		/// <returns>－Is The Export Successful</returns>
		/// <exception cref="LLNET::Core::InvalidRemoteCallTypeException"></exception>
		generic<typename TDelegate>
		where TDelegate:System::Delegate
			static bool ExportAs(String^ nameSpace, String^ funcName, TDelegate fn) {
			return ExportFunctionRegister::RegisterExportFunction<TDelegate>(nameSpace, funcName, fn);
		};

		generic<typename TDelegate>
		where TDelegate:System::Delegate
			static TDelegate ImportAs(String^ nameSpace, String^ funcName) {
			return ImportFunctionRegister::RegisterImportFunction<TDelegate>(nameSpace, funcName);
		}



	public:
		//防止gc回收
		static Dictionary<uint64_t, NativeCallbackHandler^>^ CallbackData = gcnew Dictionary<uint64_t, NativeCallbackHandler^>;

	private:
		ref class RemoteCallHelper
		{
		private:
			::RemoteCall::CallbackFn const* pFunc;
			Valuetype^ Invoke(List<Valuetype^>^ list) {
				NULL_ARG_CHEEK(list);

				auto count = (size_t)list->Count;
				std::vector<::RemoteCall::ValueType> stdvector;
				for (auto i = 0; i < count; ++i)
				{
					stdvector.emplace_back(*list[i]->NativePtr);
				}
				auto& ret = (*pFunc)(stdvector);
				return gcnew Valuetype(ret);
			};
			RemoteCallHelper(::RemoteCall::CallbackFn const& p)
				: pFunc(new ::RemoteCall::CallbackFn(std::move(p)))
			{
			}
			~RemoteCallHelper() {
				delete pFunc;
			}

		public:
			static Pair<RemoteCallHelper^, CallbackFn^> Create(::RemoteCall::CallbackFn const& p) {
				auto instance = gcnew RemoteCallHelper(p);
				return Pair< RemoteCallHelper^, CallbackFn^>(instance, gcnew CallbackFn(instance, &RemoteCallHelper::Invoke));
			}
		};

	};
} // namespace LLNET::RemoteCall
