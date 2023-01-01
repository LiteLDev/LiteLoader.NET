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

    delegate void* ConverterCallback(void*);

    using oc = System::Reflection::Emit::OpCodes;
    using converter = LiteLoader::NET::callback::converter<
        value_type(array_type), void* (void*), ConverterCallback>;

    using System::Reflection::Emit::DynamicMethod;
    using System::Reflection::Emit::LocalBuilder;
    using System::Reflection::Emit::ILGenerator;
    using System::Reflection::Emit::Label;

    using IFuncCaller = LiteLoader::NET::IFunctionCaller;

    public ref class EmitHelper sealed
    {
    public:

        ref struct ExportedFuncInstance
        {
            DynamicMethod^ intertopManagedFunc;
            void* exportedNativeFunc;
            IFuncCaller^ funcHandle;
            Object^ exportedManagedFunc;
        };

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

            // generic<typename TDelegate> where TDelegate: Delegate
                ILCodeBulider(String^ nameSpace, String^ funcName, TypeHelper::FunctionInfo% info, BuliderType type);
            bool Build();
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

            bool BuildExport();
            bool BuildImport();
        };

        /// <exception cref="LiteLoader::NET::InvalidRemoteCallTypeException"></exception>
        generic<typename TDelegate> where TDelegate : Delegate
            void CreateExportNativeFuncPtr(String^ nameSpace, String^ funcName, TDelegate func);
    };
}

