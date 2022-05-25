#pragma once

#include "ImportAs.hpp"

namespace LLNET::RemoteCall
{
	public
	ref class RemoteCallAPI abstract
	{
	public:
		delegate Valuetype^ CallbackFn(List<Valuetype^>^);
		static bool ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ fn);
		static bool ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ fn, IntPtr handler);

		static CallbackFn^ ImportFunc(String^ nameSpace, String^ funcName);

		static bool HasFunc(String^ nameSpace, String^ funcName);
		static bool RemoveFunc(String^ nameSpace, String^ funcName);
		static bool RemoveNameSpace(String^ nameSpace);
		static bool RemoveFuncs(List<Pair<String^, String^>>^ funcs);

		generic<typename TDelegate>
		where TDelegate:System::Delegate
			static bool ExportAs(String^ nameSpace, String^ funcName, TDelegate f);


		static RemoteCallHandler_void_0^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_0(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_0(instance, &ImportFunctionRegister::ImportFunc_void_0::Invoke);
		}
		generic<typename T0>
		static RemoteCallHandler_void_1<T0>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_1<T0>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_1<T0>(instance, &ImportFunctionRegister::ImportFunc_void_1<T0>::Invoke);
		}
		generic<typename T0, typename T1>
		static RemoteCallHandler_void_2 <T0, T1>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_2<T0, T1>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_2<T0, T1>(instance, &ImportFunctionRegister::ImportFunc_void_2<T0, T1>::Invoke);
		}
		generic<typename T0, typename T1, typename T2>
		static RemoteCallHandler_void_3 <T0, T1, T2>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_3<T0, T1, T2>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_3<T0, T1, T2>(instance, &ImportFunctionRegister::ImportFunc_void_3<T0, T1, T2>::Invoke);
		}
		generic<typename T0, typename T1, typename T2, typename T3>
		static RemoteCallHandler_void_4 <T0, T1, T2, T3>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_4<T0, T1, T2, T3>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_4<T0, T1, T2, T3>(instance, &ImportFunctionRegister::ImportFunc_void_4<T0, T1, T2, T3>::Invoke);
		}
		generic<typename T0, typename T1, typename T2, typename T3, typename T4>
		static RemoteCallHandler_void_5 <T0, T1, T2, T3, T4>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_5<T0, T1, T2, T3, T4>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_5<T0, T1, T2, T3, T4>(instance, &ImportFunctionRegister::ImportFunc_void_5<T0, T1, T2, T3, T4>::Invoke);
		}
		generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		static RemoteCallHandler_void_6 <T0, T1, T2, T3, T4, T5>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_6<T0, T1, T2, T3, T4, T5>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_6<T0, T1, T2, T3, T4, T5>(instance, &ImportFunctionRegister::ImportFunc_void_6<T0, T1, T2, T3, T4, T5>::Invoke);
		}
		generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		static RemoteCallHandler_void_7 <T0, T1, T2, T3, T4, T5, T6>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_7<T0, T1, T2, T3, T4, T5, T6>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_7<T0, T1, T2, T3, T4, T5, T6>(instance, &ImportFunctionRegister::ImportFunc_void_7<T0, T1, T2, T3, T4, T5, T6>::Invoke);
		}
		generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		static RemoteCallHandler_void_8 <T0, T1, T2, T3, T4, T5, T6, T7>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_8<T0, T1, T2, T3, T4, T5, T6, T7>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_8<T0, T1, T2, T3, T4, T5, T6, T7>(instance, &ImportFunctionRegister::ImportFunc_void_8<T0, T1, T2, T3, T4, T5, T6, T7>::Invoke);
		}
		generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		static RemoteCallHandler_void_9 <T0, T1, T2, T3, T4, T5, T6, T7, T8>^ Import_As(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_void_9<T0, T1, T2, T3, T4, T5, T6, T7, T8>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_void_9<T0, T1, T2, T3, T4, T5, T6, T7, T8>(instance, &ImportFunctionRegister::ImportFunc_void_9<T0, T1, T2, T3, T4, T5, T6, T7, T8>::Invoke);
		}



		generic<typename RTN>
		static RemoteCallHandler_0 <RTN>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_0<RTN>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_0<RTN>(instance, &ImportFunctionRegister::ImportFunc_0<RTN>::Invoke);
		}
		generic<typename RTN, typename T0>
		static RemoteCallHandler_1 <RTN, T0>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_1<RTN, T0>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_1<RTN, T0>(instance, &ImportFunctionRegister::ImportFunc_1<RTN, T0>::Invoke);
		}
		generic<typename RTN, typename T0, typename T1>
		static RemoteCallHandler_2 <RTN, T0, T1>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_2<RTN, T0, T1>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_2<RTN, T0, T1>(instance, &ImportFunctionRegister::ImportFunc_2<RTN, T0, T1>::Invoke);
		}
		generic<typename RTN, typename T0, typename T1, typename T2>
		static RemoteCallHandler_3 <RTN, T0, T1, T2>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_3<RTN, T0, T1, T2>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_3<RTN, T0, T1, T2>(instance, &ImportFunctionRegister::ImportFunc_3<RTN, T0, T1, T2>::Invoke);
		}
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3>
		static RemoteCallHandler_4 <RTN, T0, T1, T2, T3>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_4<RTN, T0, T1, T2, T3>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_4<RTN, T0, T1, T2, T3>(instance, &ImportFunctionRegister::ImportFunc_4<RTN, T0, T1, T2, T3>::Invoke);
		}
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4>
		static RemoteCallHandler_5 <RTN, T0, T1, T2, T3, T4>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_5<RTN, T0, T1, T2, T3, T4>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_5<RTN, T0, T1, T2, T3, T4>(instance, &ImportFunctionRegister::ImportFunc_5<RTN, T0, T1, T2, T3, T4>::Invoke);
		}
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		static RemoteCallHandler_6 <RTN, T0, T1, T2, T3, T4, T5>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_6<RTN, T0, T1, T2, T3, T4, T5>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_6<RTN, T0, T1, T2, T3, T4, T5>(instance, &ImportFunctionRegister::ImportFunc_6<RTN, T0, T1, T2, T3, T4, T5>::Invoke);
		}
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		static RemoteCallHandler_7 <RTN, T0, T1, T2, T3, T4, T5, T6>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_7<RTN, T0, T1, T2, T3, T4, T5, T6>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_7<RTN, T0, T1, T2, T3, T4, T5, T6>(instance, &ImportFunctionRegister::ImportFunc_7<RTN, T0, T1, T2, T3, T4, T5, T6>::Invoke);
		}
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		static RemoteCallHandler_8 <RTN, T0, T1, T2, T3, T4, T5, T6, T7>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_8<RTN, T0, T1, T2, T3, T4, T5, T6, T7>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_8<RTN, T0, T1, T2, T3, T4, T5, T6, T7>(instance, &ImportFunctionRegister::ImportFunc_8<RTN, T0, T1, T2, T3, T4, T5, T6, T7>::Invoke);
		}
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		static RemoteCallHandler_9 <RTN, T0, T1, T2, T3, T4, T5, T6, T7, T8>^ ImportAs(String^ nameSpace, String^ funcName) {
			auto instance = gcnew ImportFunctionRegister::ImportFunc_9<RTN, T0, T1, T2, T3, T4, T5, T6, T7, T8>(nameSpace, funcName);
			if (!*instance->pfunc)
				return nullptr;
			return gcnew RemoteCallHandler_9<RTN, T0, T1, T2, T3, T4, T5, T6, T7, T8>(instance, &ImportFunctionRegister::ImportFunc_9<RTN, T0, T1, T2, T3, T4, T5, T6, T7, T8>::Invoke);
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



	generic<typename TDelegate>
	where TDelegate:System::Delegate
		inline bool RemoteCallAPI::ExportAs(String^ nameSpace, String^ funcName, TDelegate f)
	{
		return ExportFunctionRegister::RegisterExportFunction<TDelegate>(nameSpace, funcName, f);
	};

} // namespace LLNET::RemoteCall
