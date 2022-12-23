#pragma once
#include "ExportAs.hpp"

namespace LiteLoader::RemoteCall {

    public delegate void RemoteCallHandler_void_0();
    generic<typename T0>
    public delegate void RemoteCallHandler_void_1(T0);
    generic<typename T0, typename T1>
    public delegate void RemoteCallHandler_void_2(T0, T1);
    generic<typename T0, typename T1, typename T2>
    public delegate void RemoteCallHandler_void_3(T0, T1, T2);
    generic<typename T0, typename T1, typename T2, typename T3>
    public delegate void RemoteCallHandler_void_4(T0, T1, T2, T3);
    generic<typename T0, typename T1, typename T2, typename T3, typename T4>
    public delegate void RemoteCallHandler_void_5(T0, T1, T2, T3, T4);
    generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    public delegate void RemoteCallHandler_void_6(T0, T1, T2, T3, T4, T5);
    generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    public delegate void RemoteCallHandler_void_7(T0, T1, T2, T3, T4, T5, T6);
    generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    public delegate void RemoteCallHandler_void_8(T0, T1, T2, T3, T4, T5, T6, T7);
    generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    public delegate void RemoteCallHandler_void_9(T0, T1, T2, T3, T4, T5, T6, T7, T8);



    generic<typename RTN>
    public delegate RTN RemoteCallHandler_0();
    generic<typename RTN, typename T0>
    public delegate RTN RemoteCallHandler_1(T0);
    generic<typename RTN, typename T0, typename T1>
    public delegate RTN RemoteCallHandler_2(T0, T1);
    generic<typename RTN, typename T0, typename T1, typename T2>
    public delegate RTN RemoteCallHandler_3(T0, T1, T2);
    generic<typename RTN, typename T0, typename T1, typename T2, typename T3>
    public delegate RTN RemoteCallHandler_4(T0, T1, T2, T3);
    generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4>
    public delegate RTN RemoteCallHandler_5(T0, T1, T2, T3, T4);
    generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    public delegate RTN RemoteCallHandler_6(T0, T1, T2, T3, T4, T5);
    generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    public delegate RTN RemoteCallHandler_7(T0, T1, T2, T3, T4, T5, T6);
    generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    public delegate RTN RemoteCallHandler_8(T0, T1, T2, T3, T4, T5, T6, T7);
    generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    public delegate RTN RemoteCallHandler_9(T0, T1, T2, T3, T4, T5, T6, T7, T8);



    ref class ImportFunctionRegister {

    public:
        ref class ImportFuncBase abstract {
        public:
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
            Object^ _Invoke(...array<Object^>^ args);
        };

        generic<typename RTN>
        ref class ImportFunc_0 :ImportFuncBase {
        public:
            ImportFunc_0(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(RTN::typeid);
            }
            RTN Invoke() {
                return (RTN)_Invoke();
            }
        };
        generic<typename RTN, typename T0>
        ref class ImportFunc_1 :ImportFuncBase {
        public:
            ImportFunc_1(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(RTN::typeid, T0::typeid);
            }
            RTN Invoke(T0 a0) {
                return (RTN)_Invoke(a0);
            }
        };
        generic<typename RTN, typename T0, typename T1>
        ref class ImportFunc_2 :ImportFuncBase {
        public:
            ImportFunc_2(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(RTN::typeid, T0::typeid, T1::typeid);
            }
            RTN Invoke(T0 a0, T1 a1) {
                return (RTN)_Invoke(a0, a1);
            }
        };
        generic<typename RTN, typename T0, typename T1, typename T2>
        ref class ImportFunc_3 :ImportFuncBase {
        public:
            ImportFunc_3(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(RTN::typeid, T0::typeid, T1::typeid, T2::typeid);
            }
            RTN Invoke(T0 a0, T1 a1, T2 a2) {
                return (RTN)_Invoke(a0, a1, a2);
            }
        };
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3>
        ref class ImportFunc_4 :ImportFuncBase {
        public:
            ImportFunc_4(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(RTN::typeid, T0::typeid, T1::typeid, T2::typeid, T3::typeid);
            }
            RTN Invoke(T0 a0, T1 a1, T2 a2, T3 a3) {
                return (RTN)_Invoke(a0, a1, a2, a3);
            }
        };
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4>
        ref class ImportFunc_5 :ImportFuncBase {
        public:
            ImportFunc_5(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(RTN::typeid, T0::typeid, T1::typeid, T2::typeid, T3::typeid, T4::typeid);
            }
            RTN Invoke(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {
                return (RTN)_Invoke(a0, a1, a2, a3, a4);
            }
        };
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
        ref class ImportFunc_6 :ImportFuncBase {
        public:
            ImportFunc_6(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(RTN::typeid, T0::typeid, T1::typeid, T2::typeid, T3::typeid, T4::typeid, T5::typeid);
            }
            RTN Invoke(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
                return (RTN)_Invoke(a0, a1, a2, a3, a4, a5);
            }
        };
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        ref class ImportFunc_7 :ImportFuncBase {
        public:
            ImportFunc_7(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(RTN::typeid, T0::typeid, T1::typeid, T2::typeid, T3::typeid, T4::typeid, T5::typeid, T6::typeid);
            }
            RTN Invoke(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
                return (RTN)_Invoke(a0, a1, a2, a3, a4, a5, a6);
            }
        };
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        ref class ImportFunc_8 :ImportFuncBase {
        public:
            ImportFunc_8(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(RTN::typeid, T0::typeid, T1::typeid, T2::typeid, T3::typeid, T4::typeid, T5::typeid, T6::typeid, T7::typeid);
            }
            RTN Invoke(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {
                return (RTN)_Invoke(a0, a1, a2, a3, a4, a5, a6, a7);
            }
        };
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
        ref class ImportFunc_9 :ImportFuncBase {
        public:
            ImportFunc_9(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(RTN::typeid, T0::typeid, T1::typeid, T2::typeid, T3::typeid, T4::typeid, T5::typeid, T6::typeid, T7::typeid, T8::typeid);
            }
            RTN Invoke(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8) {
                return (RTN)_Invoke(a0, a1, a2, a3, a4, a5, a6, a7, a8);
            }
        };


        ref class ImportFunc_void_0 :ImportFuncBase {
        public:
            ImportFunc_void_0(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(nullptr);
            }
            void Invoke() {
                _Invoke();
            }
        };
        generic<typename T0>
        ref class ImportFunc_void_1 :ImportFuncBase {
        public:
            ImportFunc_void_1(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(nullptr, T0::typeid);
            }
            void Invoke(T0 a0) {
                _Invoke(a0);
            }
        };
        generic<typename T0, typename T1>
        ref class ImportFunc_void_2 :ImportFuncBase {
        public:
            ImportFunc_void_2(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(nullptr, T0::typeid, T1::typeid);
            }
            void Invoke(T0 a0, T1 a1) {
                _Invoke(a0, a1);
            }
        };
        generic<typename T0, typename T1, typename T2>
        ref class ImportFunc_void_3 :ImportFuncBase {
        public:
            ImportFunc_void_3(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(nullptr, T0::typeid, T1::typeid, T2::typeid);
            }
            void Invoke(T0 a0, T1 a1, T2 a2) {
                _Invoke(a0, a1, a2);
            }
        };
        generic<typename T0, typename T1, typename T2, typename T3>
        ref class ImportFunc_void_4 :ImportFuncBase {
        public:
            ImportFunc_void_4(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(nullptr, T0::typeid, T1::typeid, T2::typeid, T3::typeid);
            }
            void Invoke(T0 a0, T1 a1, T2 a2, T3 a3) {
                _Invoke(a0, a1, a2, a3);
            }
        };
        generic<typename T0, typename T1, typename T2, typename T3, typename T4>
        ref class ImportFunc_void_5 :ImportFuncBase {
        public:
            ImportFunc_void_5(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(nullptr, T0::typeid, T1::typeid, T2::typeid, T3::typeid, T4::typeid);
            }
            void Invoke(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {
                _Invoke(a0, a1, a2, a3, a4);
            }
        };
        generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
        ref class ImportFunc_void_6 :ImportFuncBase {
        public:
            ImportFunc_void_6(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(nullptr, T0::typeid, T1::typeid, T2::typeid, T3::typeid, T4::typeid, T5::typeid);
            }
            void Invoke(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
                _Invoke(a0, a1, a2, a3, a4, a5);
            }
        };
        generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        ref class ImportFunc_void_7 :ImportFuncBase {
        public:
            ImportFunc_void_7(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(nullptr, T0::typeid, T1::typeid, T2::typeid, T3::typeid, T4::typeid, T5::typeid, T6::typeid);
            }
            void Invoke(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
                _Invoke(a0, a1, a2, a3, a4, a5, a6);
            }
        };
        generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        ref class ImportFunc_void_8 :ImportFuncBase {
        public:
            ImportFunc_void_8(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(nullptr, T0::typeid, T1::typeid, T2::typeid, T3::typeid, T4::typeid, T5::typeid, T6::typeid, T7::typeid);
            }
            void Invoke(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {
                _Invoke(a0, a1, a2, a3, a4, a5, a6, a7);
            }
        };
        generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
        ref class ImportFunc_void_9 :ImportFuncBase {
        public:
            ImportFunc_void_9(String^ nameSpace, String^ funcName)
                :ImportFuncBase(nameSpace, funcName)
            {
                info = _tryPraseFunctionInfo(nullptr, T0::typeid, T1::typeid, T2::typeid, T3::typeid, T4::typeid, T5::typeid, T6::typeid, T7::typeid, T8::typeid);
            }
            void Invoke(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8) {
                _Invoke(a0, a1, a2, a3, a4, a5, a6, a7, a8);
            }
        };

    internal:
        using FunctionInfo = ExportFunctionRegister::FunctionInfo;

    internal:
        static FunctionInfo^ _tryPraseFunctionInfo(System::Type^ returnType, ...array<System::Type^>^ types);
        inline static ::RemoteCall::ValueType _parseParameter(FunctionInfo::TypeInfo const% info, Object^ val);
        inline static Object^ _parseReturnVal(FunctionInfo::TypeInfo const% info, ::RemoteCall::ValueType& val);
    };
}

namespace LiteLoader::RemoteCall {
    ExportFunctionRegister::FunctionInfo^ ImportFunctionRegister::_tryPraseFunctionInfo(System::Type^ returnType, ...array<System::Type^>^ types)
    {
        if (returnType == nullptr)
            returnType = void::typeid;
        auto ret = gcnew ExportFunctionRegister::FunctionInfo();
        ret->returnType = ExportFunctionRegister::_generateTypeInfo(returnType);
        ret->parameters = gcnew array<ExportFunctionRegister::FunctionInfo::TypeInfo>(types->Length);
        for (int i = 0; i < types->Length; ++i)
        {
            ret->parameters[i] = ExportFunctionRegister::_generateTypeInfo(types[i]);
        }
        return ret;
    }
    inline ::RemoteCall::ValueType LiteLoader::RemoteCall::ImportFunctionRegister::_parseParameter(FunctionInfo::TypeInfo const% info, Object^ val)
    {
        return std::move(ExportFunctionRegister::_parseReturnVal(info, val));
    }
    inline System::Object^ LiteLoader::RemoteCall::ImportFunctionRegister::_parseReturnVal(FunctionInfo::TypeInfo const% info, ::RemoteCall::ValueType& val)
    {
        return ExportFunctionRegister::_parseParameter(info, val);
    }
    System::Object^ ImportFunctionRegister::ImportFuncBase::_Invoke(...array<Object^>^ args)
    {
        std::vector<::RemoteCall::ValueType> vec;
        for (int i = 0; i < args->Length; ++i) {
            vec.emplace_back(_parseParameter(info->parameters[i], args[i]));
        }
        auto ret = (*pfunc)(vec);
        return _parseReturnVal(info->returnType, ret);
    }
}