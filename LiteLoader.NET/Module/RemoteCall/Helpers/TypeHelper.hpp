#pragma once

#include <LiteLoader.NET/Module/RemoteCall/Types/ValueType.hpp>

namespace LiteLoader::RemoteCall::Helper
{
    public ref class TypeHelper 
    {
    public:

        enum class ValidType
        {
            Invalid,

            Double,
            Float,
            Int64,
            Int32,
            Int16,
            Int8,
            UInt64,
            UInt32,
            UInt16,
            UInt8,

            Bool,
            String,
            NumberType,
            Player,
            Actor,
            BlockActor,
            Container,
            Vec3,
            BlockPos,

            WorldPosType,
            BlockPosType,
            ItemType,
            BlockType,
            NbtType,

            List,
            Dictionary,

            Void
        };

        value struct FunctionInfo
        {
            value struct TypeInfo
            {
                System::Type^ _type;
                ValidType type;
                array<TypeInfo>^ genericArgs;
            };
            TypeInfo returnType;
            array<TypeInfo>^ parameters;
        };
        //ref class ExportFunc 
        //{
        //    String^ nameSpace;
        //    String^ funcName;
        //    FunctionInfo^ info;
        //    System::Delegate^ func;
        //    GCHandle gch;
        //private:
        //    inline ExportFunc(String^ nameSpace, String^ funcName, FunctionInfo^ info, System::Delegate^ del);

        //    inline NATIVECALLBACK::RemoteCall::ValueType _nativeFunc(std::vector<::RemoteCall::ValueType> vec);
        //public:
        //    static Pair<ExportFunc^, delNative^> Create(String^ nameSpace, String^ funcName, FunctionInfo^ info, System::Delegate^ del);

        //    virtual String^ ToString() override
        //    {
        //        return String::Format("NameSpace:{0},FunctionName:{1}", nameSpace, funcName);
        //    }
        //};

        static PAIR<bool, ValidType> TryGetValidType(System::Type^ t);

        static FunctionInfo::TypeInfo GenerateTypeInfo(System::Type^ t);

        /// <exception cref="LiteLoader::NET::InvalidRemoteCallTypeException"></exception>
        static FunctionInfo GenerateFunctionInfo(Delegate^ func);

        //static Object^ _parseParameter(FunctionInfo::TypeInfo const% info, ::RemoteCall::ValueType& val);

        //static ::RemoteCall::ValueType _parseReturnVal(FunctionInfo::TypeInfo const% info, Object^ val);

        //static List<ExportFunc^>^ ExportFunctions = gcnew List<ExportFunc^>;
    //public:
    //    generic<typename TDelegate>
    //    where TDelegate : System::Delegate
    //        static bool RegisterExportFunction(String^ nameSpace, String^ funcName, TDelegate func) {
    //        NULL_ARG_CHECK(nameSpace);
    //        NULL_ARG_CHECK(funcName);
    //        NULL_ARG_CHECK(func);
    //        auto funcinfo = gcnew FunctionInfo;
    //        auto method = func->Method;
    //        auto params = method->GetParameters();
    //        funcinfo->parameters = gcnew array<FunctionInfo::TypeInfo>(params->Length);
    //        funcinfo->returnType = _generateTypeInfo(method->ReturnType);
    //        for (int i = 0; i < params->Length; ++i) {
    //            funcinfo->parameters[i] = _generateTypeInfo(params[i]->ParameterType);
    //        }
    //        auto exportfunc = ExportFunc::Create(nameSpace, funcName, funcinfo, func);
    //        ExportFunctions->Add(exportfunc.Key);
    //        auto pfunc = static_cast<pNative>((void*)Marshal::GetFunctionPointerForDelegate(exportfunc.Value));
    //        return ::RemoteCall::exportFunc(marshalString(nameSpace), marshalString(funcName), pfunc, CALLING_MODULE);
    //        //debug
    //        //Console::WriteLine(succeed);
    //        /*Console::WriteLine("{0},{1}", typeinfo.type, typeinfo.genericArgs->Length);*/
    //    }
    };
}



