#pragma once
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <LiteLoader.NET/Tools/CallbackConverter.hpp>

#include "TypeHelper.hpp"
#include "TypeCastHelper.hpp"
#include "MemoryHelper.hpp"

namespace LiteLoader::RemoteCall::Helper
{
    using array_type = ::RemoteCall::ValueType::ArrayType;
    using array_type_native_iterator = ::RemoteCall::ValueType::ArrayType::iterator;
    using value_type = ::RemoteCall::ValueType;

    public delegate value_type NativeCallback(array_type);
    public delegate MemoryHelper::Allocator ConverterCallback(void*);

    using oc = System::Reflection::Emit::OpCodes;
    using converter = LiteLoader::NET::callback::converter<
        value_type(array_type), MemoryHelper::Allocator(void*), ConverterCallback>;

    using System::Reflection::Emit::DynamicMethod;
    using System::Reflection::Emit::LocalBuilder;
    using System::Reflection::Emit::ILGenerator;
    using System::Reflection::Emit::Label;

    using IFuncCaller = LiteLoader::NET::IFunctionCaller;

    public ref struct ExportedFuncInstance
    {
        DynamicMethod^ intertopManagedFunc;
        ConverterCallback^ intertopManagedFuncDelegate;

        Delegate^ exportedManagedFunc;

        void* exportedNativeFunc;
        IFuncCaller^ funcHandle;
    };

    public ref class EmitHelper __static
    {
    public:

        ref struct ILCodeBulider
        {
            enum class BuliderType { Export, Import };
            SystemType^ exportedManagedFuncDelegateType;
            Dictionary<int, LocalBuilder^>^ localVars;
            Dictionary<int, Label>^ labels;
            TypeHelper::FunctionInfo funcInfo;
            BuliderType buliderType;
            DynamicMethod^ method;
            ILGenerator^ il;
            List<LocalBuilder^>^ localAllocatorInstances;

            ILCodeBulider(String^ nameSpace, String^ funcName, TypeHelper::FunctionInfo% info, BuliderType type, SystemType^ delegateType);
            bool Build(Delegate^ func, [Out] Object^% instance);
            int DeclareLocal(SystemType^ type);
            int DefineLabel();

            void IL_CastArrayTypeToList(TypeHelper::FunctionInfo::TypeInfo% info);
            void IL_CastObjectTypeToDictionary(TypeHelper::FunctionInfo::TypeInfo% info);
            void IL_CastNativeTypes(TypeHelper::FunctionInfo::TypeInfo% info);

            void IL_CastListToArrayType(TypeHelper::FunctionInfo::TypeInfo% info);
            void IL_CastDictionaryToObjectType(TypeHelper::FunctionInfo::TypeInfo% info);
            void IL_CastListToArrayType(TypeHelper::FunctionInfo::TypeInfo% info, bool isSelfCalled);
            void IL_CastDictionaryToObjectType(TypeHelper::FunctionInfo::TypeInfo% info, bool isSelfCalled);
            void IL_CastManagedTypes(TypeHelper::FunctionInfo::TypeInfo% info);
            void IL_CastManagedTypes(TypeHelper::FunctionInfo::TypeInfo% info,bool isRet);

            bool BuildExportDynamicMethod();
            bool BuildImportDynamicMethod();
        };
    };
}

