#pragma once

#include "Internal/DynamicExportFunctionRegister.hpp"
#include "Internal/DynamicImportFunctionRegister.hpp"
#include "ImportAs.hpp"
#include "ExportAs.hpp"

#include <LiteLoader.NET/Tools/CallbackConverter.hpp>

namespace LLNET::RemoteCall
{
	using namespace LLNET::RemoteCall::Internal;


	/// <summary>
	/// ========Remote Call API========
	/// <para>　</para>
	/// <para>Mainly designed for scripting engines</para>
	/// <para>Please call it in MC_SERVER thread or in ScheduleAPI</para>
	/// </summary>
	public ref class RemoteCallAPI __static
	{
	public:
#pragma warning(disable:4693)
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
		static bool ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ fn, IntPtr handle);


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

		/// <summary>
		/// Import a function that has no parameters and does not return a value.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		static RemoteCallHandler_void_0^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_0(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_0(instance, &ImportFunctionRegister::ImportFunc_void_0::Invoke);
		}


		/// <summary>
		/// Import a function that has a single parameter and does not return a value.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename T0>
		static RemoteCallHandler_void_1<T0>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_1<T0>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_1<T0>(instance, &ImportFunctionRegister::ImportFunc_void_1<T0>::Invoke);
		}


		/// <summary>
		/// Import a function that has two parameters and does not return a value.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename T0, typename T1>
		static RemoteCallHandler_void_2 <T0, T1>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_2<T0, T1>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_2<T0, T1>(instance, &ImportFunctionRegister::ImportFunc_void_2<T0, T1>::Invoke);
		}


		/// <summary>
		/// Import a function that has three parameters and does not return a value.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename T0, typename T1, typename T2>
		static RemoteCallHandler_void_3 <T0, T1, T2>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_3<T0, T1, T2>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_3<T0, T1, T2>(instance, &ImportFunctionRegister::ImportFunc_void_3<T0, T1, T2>::Invoke);
		}


		/// <summary>
		/// Import a function that has four parameters and does not return a value.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename T0, typename T1, typename T2, typename T3>
		static RemoteCallHandler_void_4 <T0, T1, T2, T3>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_4<T0, T1, T2, T3>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_4<T0, T1, T2, T3>(instance, &ImportFunctionRegister::ImportFunc_void_4<T0, T1, T2, T3>::Invoke);
		}


		/// <summary>
		/// Import a function that has five parameters and does not return a value.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename T0, typename T1, typename T2, typename T3, typename T4>
		static RemoteCallHandler_void_5 <T0, T1, T2, T3, T4>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_5<T0, T1, T2, T3, T4>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_5<T0, T1, T2, T3, T4>(instance, &ImportFunctionRegister::ImportFunc_void_5<T0, T1, T2, T3, T4>::Invoke);
		}


		/// <summary>
		/// Import a function that has six parameters and does not return a value.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		static RemoteCallHandler_void_6 <T0, T1, T2, T3, T4, T5>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_6<T0, T1, T2, T3, T4, T5>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_6<T0, T1, T2, T3, T4, T5>(instance, &ImportFunctionRegister::ImportFunc_void_6<T0, T1, T2, T3, T4, T5>::Invoke);
		}


		/// <summary>
		/// Import a function that has seven parameters and does not return a value.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		static RemoteCallHandler_void_7 <T0, T1, T2, T3, T4, T5, T6>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_7<T0, T1, T2, T3, T4, T5, T6>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_7<T0, T1, T2, T3, T4, T5, T6>(instance, &ImportFunctionRegister::ImportFunc_void_7<T0, T1, T2, T3, T4, T5, T6>::Invoke);
		}


		/// <summary>
		/// Import a function that has eight parameters and does not return a value.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		static RemoteCallHandler_void_8 <T0, T1, T2, T3, T4, T5, T6, T7>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_8<T0, T1, T2, T3, T4, T5, T6, T7>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_8<T0, T1, T2, T3, T4, T5, T6, T7>(instance, &ImportFunctionRegister::ImportFunc_void_8<T0, T1, T2, T3, T4, T5, T6, T7>::Invoke);
		}


		/// <summary>
		/// Import a function that has nine parameters and does not return a value.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		static RemoteCallHandler_void_9 <T0, T1, T2, T3, T4, T5, T6, T7, T8>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_9<T0, T1, T2, T3, T4, T5, T6, T7, T8>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_9<T0, T1, T2, T3, T4, T5, T6, T7, T8>(instance, &ImportFunctionRegister::ImportFunc_void_9<T0, T1, T2, T3, T4, T5, T6, T7, T8>::Invoke);
		}


		/// <summary>
		/// Import a function that has no parameters and returns a value of the type specified by the TResult parameter.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename RTN>
		static RemoteCallHandler_0 <RTN>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_0<RTN>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_0<RTN>(instance, &ImportFunctionRegister::ImportFunc_0<RTN>::Invoke);
		}


		/// <summary>
		/// Import a function that has one parameters and returns a value of the type specified by the TResult parameter.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename RTN, typename T0>
		static RemoteCallHandler_1 <RTN, T0>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_1<RTN, T0>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_1<RTN, T0>(instance, &ImportFunctionRegister::ImportFunc_1<RTN, T0>::Invoke);
		}


		/// <summary>
		/// Import a function that has two parameters and returns a value of the type specified by the TResult parameter.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename RTN, typename T0, typename T1>
		static RemoteCallHandler_2 <RTN, T0, T1>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_2<RTN, T0, T1>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_2<RTN, T0, T1>(instance, &ImportFunctionRegister::ImportFunc_2<RTN, T0, T1>::Invoke);
		}


		/// <summary>
		/// Import a function that has three parameters and returns a value of the type specified by the TResult parameter.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename RTN, typename T0, typename T1, typename T2>
		static RemoteCallHandler_3 <RTN, T0, T1, T2>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_3<RTN, T0, T1, T2>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_3<RTN, T0, T1, T2>(instance, &ImportFunctionRegister::ImportFunc_3<RTN, T0, T1, T2>::Invoke);
		}


		/// <summary>
		/// Import a function that has four parameters and returns a value of the type specified by the TResult parameter.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3>
		static RemoteCallHandler_4 <RTN, T0, T1, T2, T3>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_4<RTN, T0, T1, T2, T3>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_4<RTN, T0, T1, T2, T3>(instance, &ImportFunctionRegister::ImportFunc_4<RTN, T0, T1, T2, T3>::Invoke);
		}


		/// <summary>
		/// Import a function that has five parameters and returns a value of the type specified by the TResult parameter.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4>
		static RemoteCallHandler_5 <RTN, T0, T1, T2, T3, T4>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_5<RTN, T0, T1, T2, T3, T4>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_5<RTN, T0, T1, T2, T3, T4>(instance, &ImportFunctionRegister::ImportFunc_5<RTN, T0, T1, T2, T3, T4>::Invoke);
		}


		/// <summary>
		/// Import a function that has six parameters and returns a value of the type specified by the TResult parameter.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		static RemoteCallHandler_6 <RTN, T0, T1, T2, T3, T4, T5>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_6<RTN, T0, T1, T2, T3, T4, T5>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_6<RTN, T0, T1, T2, T3, T4, T5>(instance, &ImportFunctionRegister::ImportFunc_6<RTN, T0, T1, T2, T3, T4, T5>::Invoke);
		}


		/// <summary>
		/// Import a function that has seven parameters and returns a value of the type specified by the TResult parameter.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		static RemoteCallHandler_7 <RTN, T0, T1, T2, T3, T4, T5, T6>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_7<RTN, T0, T1, T2, T3, T4, T5, T6>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_7<RTN, T0, T1, T2, T3, T4, T5, T6>(instance, &ImportFunctionRegister::ImportFunc_7<RTN, T0, T1, T2, T3, T4, T5, T6>::Invoke);
		}


		/// <summary>
		/// Import a function that has eight parameters and returns a value of the type specified by the TResult parameter.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		static RemoteCallHandler_8 <RTN, T0, T1, T2, T3, T4, T5, T6, T7>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_8<RTN, T0, T1, T2, T3, T4, T5, T6, T7>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_8<RTN, T0, T1, T2, T3, T4, T5, T6, T7>(instance, &ImportFunctionRegister::ImportFunc_8<RTN, T0, T1, T2, T3, T4, T5, T6, T7>::Invoke);
		}


		/// <summary>
		/// Import a function that has nine parameters and returns a value of the type specified by the TResult parameter.
		/// </summary>
		/// <param name="nameSpace">－Import Function NameSpace</param>
		/// <param name="funcName">－Import Function</param>
		/// <returns>－Imported function.</returns>
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		static RemoteCallHandler_9 <RTN, T0, T1, T2, T3, T4, T5, T6, T7, T8>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_9<RTN, T0, T1, T2, T3, T4, T5, T6, T7, T8>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_9<RTN, T0, T1, T2, T3, T4, T5, T6, T7, T8>(instance, &ImportFunctionRegister::ImportFunc_9<RTN, T0, T1, T2, T3, T4, T5, T6, T7, T8>::Invoke);
		}
	public:
		//防止gc回收
		static Dictionary<uint64_t, llnet::callback::detail::IFunctionCaller^>^ CallbackData = gcnew Dictionary<uint64_t, llnet::callback::detail::IFunctionCaller^>;

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
	public ref class DynamicRemoteCallAPI __static
	{
	public:
		/// <summary>
		/// Will cause memory leak.　QAQ
		/// </summary>
		/// <returns></returns>,m 
		generic<typename TDelegate>
		where TDelegate:System::Delegate
			static bool ExportAs(String^ nameSpace, String^ funcName, TDelegate fn) {
			return DynamicExportFunctionRegister::RegisterExportFunction<TDelegate>(nameSpace, funcName, fn, CALLING_MODULE);
		};


		/// <summary>
		/// Will cause memory leak.　QAQ
		/// </summary>
		generic<typename TDelegate>
		where TDelegate:System::Delegate
		static TDelegate ImportAs(String^ nameSpace, String^ funcName) {
			return DynamicImportFunctionRegister::RegisterImportFunction<TDelegate>(nameSpace, funcName);
		}
	};
} // namespace LLNET::RemoteCall
