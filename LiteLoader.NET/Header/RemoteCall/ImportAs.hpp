#pragma once
#include "ExportAs.hpp"

namespace LLNET::RemoteCall {
	public interface class ImportAsDeclares {
	public:
		delegate void RemoteCallPrototype_void_0();
		generic<typename T0>
		delegate void RemoteCallPrototype_void_1(T0);
		generic<typename T0, typename T1>
		delegate void RemoteCallPrototype_void_2(T0, T1);
		generic<typename T0, typename T1, typename T2>
		delegate void RemoteCallPrototype_void_3(T0, T1, T2);
		generic<typename T0, typename T1, typename T2, typename T3>
		delegate void RemoteCallPrototype_void_4(T0, T1, T2, T3);
		generic<typename T0, typename T1, typename T2, typename T3, typename T4>
		delegate void RemoteCallPrototype_void_5(T0, T1, T2, T3, T4);
		generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		delegate void RemoteCallPrototype_void_6(T0, T1, T2, T3, T4, T5);
		generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		delegate void RemoteCallPrototype_void_7(T0, T1, T2, T3, T4, T5, T6);
		generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		delegate void RemoteCallPrototype_void_8(T0, T1, T2, T3, T4, T5, T6, T7);
		generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		delegate void RemoteCallPrototype_void_9(T0, T1, T2, T3, T4, T5, T6, T7, T8);



		generic<typename RTN>
		delegate RTN RemoteCallPrototype_0();
		generic<typename RTN, typename T0>
		delegate RTN RemoteCallPrototype_1(T0);
		generic<typename RTN, typename T0, typename T1>
		delegate RTN RemoteCallPrototype_2(T0, T1);
		generic<typename RTN, typename T0, typename T1, typename T2>
		delegate RTN RemoteCallPrototype_3(T0, T1, T2);
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3>
		delegate RTN RemoteCallPrototype_4(T0, T1, T2, T3);
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4>
		delegate RTN RemoteCallPrototype_5(T0, T1, T2, T3, T4);
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		delegate RTN RemoteCallPrototype_6(T0, T1, T2, T3, T4, T5);
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		delegate RTN RemoteCallPrototype_7(T0, T1, T2, T3, T4, T5, T6);
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		delegate RTN RemoteCallPrototype_8(T0, T1, T2, T3, T4, T5, T6, T7);
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		delegate RTN RemoteCallPrototype_9(T0, T1, T2, T3, T4, T5, T6, T7, T8);
	};

	ref class ImportFunctionRegister {
		static ImportAsDeclares::RemoteCallPrototype_void_0^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic< typename T0>
		static ImportAsDeclares::RemoteCallPrototype_void_1<T0>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic< typename T0, typename T1>
		static ImportAsDeclares::RemoteCallPrototype_void_2 <T0, T1>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic< typename T0, typename T1, typename T2>
		static ImportAsDeclares::RemoteCallPrototype_void_3 <T0, T1, T2>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic< typename T0, typename T1, typename T2, typename T3>
		static ImportAsDeclares::RemoteCallPrototype_void_4 <T0, T1, T2, T3>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic< typename T0, typename T1, typename T2, typename T3, typename T4>
		static ImportAsDeclares::RemoteCallPrototype_void_5 <T0, T1, T2, T3, T4>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		static ImportAsDeclares::RemoteCallPrototype_void_6 <T0, T1, T2, T3, T4, T5>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		static ImportAsDeclares::RemoteCallPrototype_void_7 <T0, T1, T2, T3, T4, T5, T6>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		static ImportAsDeclares::RemoteCallPrototype_void_8 <T0, T1, T2, T3, T4, T5, T6, T7>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		static ImportAsDeclares::RemoteCallPrototype_void_9 <T0, T1, T2, T3, T4, T5, T6, T7, T8>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}



		generic<typename RTN>
		static ImportAsDeclares::RemoteCallPrototype_0 <RTN>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic<typename RTN, typename T0>
		static ImportAsDeclares::RemoteCallPrototype_1 <RTN, T0>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic<typename RTN, typename T0, typename T1>
		static ImportAsDeclares::RemoteCallPrototype_2 <RTN, T0, T1>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic<typename RTN, typename T0, typename T1, typename T2>
		static ImportAsDeclares::RemoteCallPrototype_3 <RTN, T0, T1, T2>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3>
		static ImportAsDeclares::RemoteCallPrototype_4 <RTN, T0, T1, T2, T3>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4>
		static ImportAsDeclares::RemoteCallPrototype_5 <RTN, T0, T1, T2, T3, T4>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		static ImportAsDeclares::RemoteCallPrototype_6 <RTN, T0, T1, T2, T3, T4, T5>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		static ImportAsDeclares::RemoteCallPrototype_7 <RTN, T0, T1, T2, T3, T4, T5, T6>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		static ImportAsDeclares::RemoteCallPrototype_8 <RTN, T0, T1, T2, T3, T4, T5, T6, T7>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
		generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		static ImportAsDeclares::RemoteCallPrototype_9 < RTN, T0, T1, T2, T3, T4, T5, T6, T7, T8>^ RegisterFunction(String^ nameSpace, String^ funcName) {

		}
	internal:
		ref class ImportFuncBase abstract {
		protected:
			String^ nameSpace;
			String^ funcName;
			ExportFunctionRegister::FunctionInfo^ info;
			::RemoteCall::CallbackFn* pfunc;
			ImportFuncBase(String^ nameSpace, String^ funcName)
				:nameSpace(nameSpace), funcName(funcName), pfunc(nullptr)
			{
				pfunc = new ::RemoteCall::CallbackFn(std::move(::RemoteCall::importFunc(marshalString(nameSpace), marshalString(funcName))));
			}
			~ImportFuncBase() {
				delete pfunc;
				pfunc = nullptr;
			}
		};

		generic<typename RTN>
		ref class ImportFunc_0 :ImportFuncBase {
		public:
			ImportFunc_0(String^ nameSpace, String^ funcName)
				:ImportFuncBase(nameSpace, funcName)
			{
				info = _tryPraseFunctionInfo(RTN::typeid);
			}
			RTN _invoke() {

			}
		};
	internal:
		static ExportFunctionRegister::FunctionInfo^ _tryPraseFunctionInfo(System::Type^ returnType, ...array<System::Type^>^ types);
	};
}

namespace LLNET::RemoteCall {
	ExportFunctionRegister::FunctionInfo^ LLNET::RemoteCall::ImportFunctionRegister::_tryPraseFunctionInfo(System::Type^ returnType, ...array<System::Type^>^ types)
	{
		auto ret = gcnew ExportFunctionRegister::FunctionInfo();
	}
}