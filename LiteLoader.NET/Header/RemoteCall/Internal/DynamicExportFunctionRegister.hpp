#pragma once
#include "DynamicRemoteCallFunctionRegisterBase.hpp"
namespace LLNET::RemoteCall::Internal {
	public ref class DynamicExportFunctionRegister :DynamicRemoteCallFunctionRegisterBase {
	public:
		delegate ::RemoteCall::ValueType delNative(std::vector<::RemoteCall::ValueType>);
		delegate void* DynamicMethodDelegate(void*);
		delegate void* TEST(void*);
		typedef ::RemoteCall::ValueType(*pNative)(std::vector<::RemoteCall::ValueType>);

		ref struct ExportedFunc {
			String^ nameSpace;
			String^ funcName;
			System::Delegate^ func;
			GCHandle gch;
			TEST^ dynamicMethod;
			::RemoteCall::ValueType _Invoke(std::vector<::RemoteCall::ValueType> vec);
		};

		generic<typename TDelegate>
		where TDelegate : System::Delegate
			static bool RegisterExportFunction(String^ nameSpace, String^ funcName, TDelegate function, HMODULE handle) {
			NULL_ARG_CHECK(nameSpace);
			NULL_ARG_CHECK(funcName);
			NULL_ARG_CHECK(function);

			auto func = gcnew ExportedFunc;
			func->nameSpace = nameSpace;
			func->funcName = funcName;
			func->func = function;

			auto invokemethod = function->Method;
			auto params = invokemethod->GetParameters();

			auto funcinfo = gcnew FunctionInfo;
			funcinfo->parameters = gcnew array<FunctionInfo::TypeInfo>(params->Length);
			funcinfo->returnType = _generateTypeInfo(invokemethod->ReturnType);
			for (int i = 0; i < params->Length; ++i) {
				funcinfo->parameters[i] = _generateTypeInfo(params[i]->ParameterType);
			}

			auto methodArgs = gcnew array<System::Type^>(2);
			methodArgs[0] = ExportedFunc::typeid;
			methodArgs[1] = VOID_POINTER_TYPE;

			auto method = gcnew DynamicMethod(funcName, VOID_POINTER_TYPE, methodArgs, true);
			auto il = method->GetILGenerator();

			Dictionary<int, LocalBuilder^> locals;
			for (int i = 0; i < funcinfo->parameters->Length; i++)
			{
				locals.Add(i, il->DeclareLocal(funcinfo->parameters[i]._type));
			}

			for (int i = 0; i < funcinfo->parameters->Length; i++)
			{
				il->Emit(oc::Ldarg_1);
				il->Emit(oc::Ldc_I4_S, i);
				_INFO(il->EmitCall(oc::Call, _HelperMethod(_get_ValueType_from_ArrayType_by_index), nullptr));
				_INFO(IL_ValueTypeToManagedObject(il, funcinfo->parameters[i], locals));
				_INFO(il->Emit(oc::Stloc_S, i));
			}

			_INFO(il->Emit(oc::Ldarg_0));
			_INFO(il->Emit(oc::Ldfld, ExportedFunc::typeid->GetField("func")));
			for (int i = 0; i < funcinfo->parameters->Length; i++)
			{
				_INFO(il->Emit(oc::Ldloc_S, i));
			}
			_INFO(il->EmitCall(oc::Call, TDelegate::typeid->GetMethod("Invoke"), nullptr));
			_INFO(IL_ManagedObjectToValueType(il, funcinfo->returnType, locals));
			_INFO(il->Emit(oc::Ret));

			func->dynamicMethod = (TEST^)method->CreateDelegate(TEST::typeid, func);
			auto delfunc = gcnew delNative(func, &ExportedFunc::_Invoke);
			func->gch = GCHandle::Alloc(delfunc);
			auto pfunc = static_cast<pNative>((void*)Marshal::GetFunctionPointerForDelegate(delfunc));
			return ::RemoteCall::exportFunc(marshalString(nameSpace), marshalString(funcName), pfunc, handle);
		}
	};
}
