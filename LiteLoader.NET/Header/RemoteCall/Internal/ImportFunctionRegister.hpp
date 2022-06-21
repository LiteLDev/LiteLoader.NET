#pragma once
#include "RemoteCallRegisterBase.hpp"
namespace LLNET::RemoteCall::Internal {
	public ref class ImportFunctionRegister :RemoteCallRegisterBase
	{
	public:
		ref struct ImportedFunc {
			String^ nameSpace;
			String^ funcName;
			::RemoteCall::CallbackFn* pfunc;

			void* _Invoke(void* vec);

			~ImportedFunc() {
				delete pfunc;
			}
			static initonly MethodInfo^ Invoke = ImportedFunc::typeid->GetMethod("_Invoke");
		};

		generic<typename TDelegate>
		where TDelegate : System::Delegate
		static TDelegate RegisterImportFunction(String^ nameSpace, String^ funcName) {
			NULL_ARG_CHEEK(nameSpace);
			NULL_ARG_CHEEK(funcName);
			auto& _func = ::RemoteCall::importFunc(marshalString(nameSpace), marshalString(funcName));
			if (!_func)
				throw gcnew LLNET::Core::RemoteCallImportFunctionException(String::Format("Fail to import!Function[{0}.{1}] has not been exported", nameSpace, funcName));

			auto func = gcnew ImportedFunc;
			func->nameSpace = nameSpace;
			func->funcName = funcName;
			func->pfunc = new ::RemoteCall::CallbackFn(std::move(_func));

			auto delegateType = TDelegate::typeid;
			auto invokeMethod = delegateType->GetMethod("Invoke");
			auto params = invokeMethod->GetParameters();

			//generate funcinfo
			auto funcinfo = gcnew FunctionInfo;
			funcinfo->parameters = gcnew array<FunctionInfo::TypeInfo>(params->Length);
			funcinfo->returnType = _generateTypeInfo(invokeMethod->ReturnType);
			for (int i = 0; i < params->Length; ++i) {
				funcinfo->parameters[i] = _generateTypeInfo(params[i]->ParameterType);
			}
			//end


			auto methodArgs = gcnew array<System::Type^>(funcinfo->parameters->Length + 1);
			methodArgs[0] = ImportedFunc::typeid;
			for (int i = 1; i < methodArgs->Length; ++i) {
				methodArgs[i] = funcinfo->parameters[i - 1]._type;
			}

			auto method = gcnew DynamicMethod(funcName, invokeMethod->ReturnType, methodArgs, true);
			auto il = method->GetILGenerator();

			Dictionary<int, LocalBuilder^> locals;
			auto native_func_param_pArrayType_index = locals.Count;
			locals.Add(native_func_param_pArrayType_index, il->DeclareLocal(VOID_POINTER_TYPE));

			auto native_func_ret_pValueType_index = locals.Count;
			locals.Add(native_func_ret_pValueType_index, il->DeclareLocal(VOID_POINTER_TYPE));

			_INFO(il->EmitCall(oc::Call, _HelperMethod(_create_ArrayType), nullptr));
			_INFO(il->Emit(oc::Stloc_S, locals[native_func_param_pArrayType_index]));

			for (int i = 0; i < funcinfo->parameters->Length; ++i) {
				switch (i + 1)
				{
				case 1:_INFO(il->Emit(oc::Ldarg_1)); break;
				case 2:_INFO(il->Emit(oc::Ldarg_2)); break;
				case 3:_INFO(il->Emit(oc::Ldarg_3)); break;
				default: _INFO(il->Emit(oc::Ldarg_S, i + 1)); break;
				}
				_INFO(IL_ManagedObjectToValueType(il, funcinfo->parameters[i], locals));
				_INFO(il->Emit(oc::Ldloc_S, locals[native_func_param_pArrayType_index]));
				_INFO(il->EmitCall(oc::Call, _HelperMethod(_emplace_ValueType_back_to_ArrayType_and_delete), nullptr));
			}
			//load this
			_INFO(il->Emit(oc::Ldarg_0));
			_INFO(il->Emit(oc::Ldloc_S, locals[native_func_param_pArrayType_index]));
			_INFO(il->EmitCall(oc::Call, ImportedFunc::Invoke, nullptr));
			_INFO(IL_ValueTypeToManagedObject(il, funcinfo->returnType, locals));
			_INFO(il->Emit(oc::Ldloc_S, locals[native_func_param_pArrayType_index]));
			_INFO(il->EmitCall(oc::Call, _HelperMethod(_delete_ArrayType), nullptr));
			_INFO(il->Emit(oc::Ret));

			auto ret = (TDelegate)method->CreateDelegate(TDelegate::typeid, func);
			return ret;
		}
	};
}


