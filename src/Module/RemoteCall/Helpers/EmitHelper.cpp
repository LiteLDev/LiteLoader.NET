#include <mutex>
#include "EmitHelper.hpp"

#include <src/Header/Logger/Logger.hpp>

namespace LiteLoader::RemoteCall::Helper
{
#define VOID_PTR_TYPE void::typeid->MakePointerType()
#define CTOR(type,argTypes) type->GetConstructor(argTypes)
#define METHOD(type,name) type->GetMethod(name)
#define METHOD_WITH_ARGS(type,name,args) type->GetMethod(name,args)
#define FIELD(type,name) type->GetField(name)

    //#define QAQ(message) il->EmitWriteLine(#message);

    //#ifdef REMOTECALL_DEBUG
    //#define INFO(message) il->EmitWriteLine("line:"+__LINE__+L','+#message)
    //#else
    //#define INFO(message)
    //#endif // REMOTECALL_DEBUG



    value_type _invoke_managed_func(ConverterCallback^ del, array_type args)
    {
        MemoryHelper::Allocator _ret;
        _ret = del(&args);

        value_type ret = *reinterpret_cast<value_type*>(_ret.valueTypeInstancePtr);
        _ret.Free();
        return ret;
    }

    MemoryHelper::Allocator _invoke_native_func_std_function(
        std::function<value_type(array_type)>* func, void* array_type_ptr)
    {
        auto ret = MemoryHelper::Allocator();

        auto _ret = (*func)(*reinterpret_cast<array_type*>(array_type_ptr));
        ret.valueTypeInstancePtr = new value_type(std::move(_ret));

        return ret;
    }

    EmitHelper::ILCodeBulider::ILCodeBulider(String^ nameSpace, String^ funcName, TypeHelper::FunctionInfo% info, BuliderType type, SystemType^ delegateType)
    {
        funcInfo = info;
        buliderType = type;
        localVars = gcnew Dictionary<int, LocalBuilder^>;
        labels = gcnew Dictionary<int, Label>;
        managedFuncDelegateType = delegateType;
        localAllocatorInstances = gcnew List<LocalBuilder^>;
        this->nameSpace = nameSpace;
        this->funcName = funcName;

        switch (type)
        {
        case BuliderType::Export:
        {
            method = gcnew DynamicMethod(
                nameSpace + L'.' + funcName,
                typeof(MemoryHelper::Allocator),
                PackArray<SystemType^>(typeof(ExportedFuncInstance), VOID_PTR_TYPE));
        }
        break;
        case BuliderType::Import:
        {
            auto methodInfo = delegateType->GetMethod("Invoke");
            auto params = methodInfo->GetParameters();;
            auto typeArr = gcnew array<SystemType^>(params->Length + 1);

            typeArr[0] = typeof(ImportedFuncInstance);
            for (int i = 0; i < params->Length; ++i)
            {
                typeArr[i + 1] = params[i]->ParameterType;
            }
            method = gcnew DynamicMethod(
                nameSpace + L'.' + funcName,
                methodInfo->ReturnType,
                typeArr);
        }
        break;
        }

        il = method->GetILGenerator();
    }

    bool EmitHelper::ILCodeBulider::Build(Delegate^ exportfunc, [Out] Object^% instance)
    {
        instance = nullptr;

        switch (buliderType)
        {
        case BuliderType::Export:
        {
            if (!BuildExportDynamicMethod())
                return false;

            auto funcInstance = gcnew ExportedFuncInstance();
            auto del = method->CreateDelegate(typeof(ConverterCallback), funcInstance);

            funcInstance->intertopManagedFunc = method;
            funcInstance->intertopManagedFuncDelegate = As<ConverterCallback^>(del);
            funcInstance->exportedManagedFunc = exportfunc;

            auto pair = converter::create<_invoke_managed_func>(funcInstance->intertopManagedFuncDelegate);

            funcInstance->exportedNativeFunc = pair.first;
            funcInstance->funcHandle = pair.second;

            instance = funcInstance;

            return true;
        }
        break;
        case BuliderType::Import:
        {
            if (!BuildImportDynamicMethod())
                return false;

            auto funcInstance = gcnew ImportedFuncInstance();
            auto del = method->CreateDelegate(managedFuncDelegateType, funcInstance);

            funcInstance->intertopManagedFunc = method;
            funcInstance->intertopManagedFuncDelegate = del;

            auto& stdfunc = ::RemoteCall::importFunc(marshalString(nameSpace), marshalString(funcName));

            if (!static_cast<bool>(stdfunc))
                return false;

            auto pair = converter::create<_invoke_native_func_std_function>(stdfunc);

            funcInstance->importedNativeFunc = &const_cast<call_back_func&>(stdfunc);
            funcInstance->importedManagedFunc = pair.first;
            funcInstance->funcHandle = pair.second;

            instance = funcInstance;

            return true;
        }
        break;
        default:
        {
            return false;
        }
        }
    }

    int EmitHelper::ILCodeBulider::DeclareLocal(SystemType^ type)
    {
        auto ret = localVars->Count;
        localVars->Add(ret, il->DeclareLocal(type));
        return ret;
    }

    int EmitHelper::ILCodeBulider::DefineLabel()
    {
        auto ret = labels->Count;
        labels->Add(ret, il->DefineLabel());
        return ret;
    }

    bool EmitHelper::ILCodeBulider::BuildExportDynamicMethod()
    {
        for each (auto % typeInfo in funcInfo.parameters)
            DeclareLocal(typeInfo._type);

        for (int i = 0; i < funcInfo.parameters->Length; ++i)
        {
            auto local__arrayTypeRef = DeclareLocal(typeof(TypeCastHelper::ArrayTypeWeakRef));

            //init ArrayTypeWeakRef
            il->Emit(oc::Ldloca_S, local__arrayTypeRef);
            il->Emit(oc::Ldarg_1);
            il->Emit(oc::Call, CTOR(typeof(TypeCastHelper::ArrayTypeWeakRef), PackArray<SystemType^>(VOID_PTR_TYPE)));
            //get array_type pointer
            il->Emit(oc::Ldloca_S, local__arrayTypeRef);
            il->Emit(oc::Ldc_I4, i);
            il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ArrayTypeWeakRef), "GetArrayTypePtrByIndex"), nullptr);

            IL_CastNativeTypes(funcInfo.parameters[i]);

            il->Emit(oc::Stloc_S, i);
        }

        //load this
        il->Emit(oc::Ldarg_0);
        il->Emit(oc::Ldfld, FIELD(typeof(ExportedFuncInstance), "exportedManagedFunc"));
        for (int i = 0; i < funcInfo.parameters->Length; ++i)
        {
            il->Emit(oc::Ldloc_S, i);
        }
        il->EmitCall(oc::Call, METHOD(managedFuncDelegateType, "Invoke"), nullptr);

        IL_CastManagedTypes(funcInfo.returnType);

        for each (auto allocator in localAllocatorInstances)
        {
            il->Emit(oc::Ldloca_S, allocator);
            il->EmitCall(oc::Call, METHOD(typeof(MemoryHelper::Allocator), "Free"), nullptr);
        }

        il->Emit(oc::Ret);

        return true;
    }

    bool EmitHelper::ILCodeBulider::BuildImportDynamicMethod()
    {
        auto local__args_allocator = DeclareLocal(typeof(MemoryHelper::Allocator));
        auto local__args_arrayTypeRef = DeclareLocal(typeof(TypeCastHelper::ArrayTypeWeakRef));
        auto local__ret_allocator = DeclareLocal(typeof(MemoryHelper::Allocator));
        auto local__ret = DeclareLocal(funcInfo.returnType._type);

        //init allocator
        il->Emit(oc::Ldloca_S, local__args_allocator);
        il->Emit(oc::Initobj, typeof(MemoryHelper::Allocator));
        il->Emit(oc::Ldloca_S, local__args_allocator);
        il->EmitCall(oc::Call, METHOD(typeof(MemoryHelper::Allocator), "Alloc"), nullptr);
        il->Emit(oc::Ldloca_S, local__args_allocator);
        il->EmitCall(oc::Call, METHOD(typeof(MemoryHelper::Allocator), "SetValueAsArrayType"), nullptr);
        il->Emit(oc::Stloc_S, local__args_arrayTypeRef);

        for (int i = 0; i < funcInfo.parameters->Length; ++i)
        {
            il->Emit(oc::Ldloca_S, local__args_arrayTypeRef);
            //skip this
            il->Emit(oc::Ldarg_S, i + 1);
            IL_CastManagedTypes(funcInfo.parameters[i], false);
            il->EmitCall(
                oc::Call,
                METHOD_WITH_ARGS(typeof(MemoryHelper), "ArrayType_EmplaceBack",
                    PackArray<SystemType^>(
                        typeof(TypeCastHelper::ArrayTypeWeakRef)->MakeByRefType(),
                        typeof(MemoryHelper::Allocator)->MakeByRefType())),
                nullptr);
        }

        //load this
        il->Emit(oc::Ldarg_0);
        il->Emit(oc::Ldfld, FIELD(typeof(ImportedFuncInstance), "importedManagedFunc"));
        //get array_type pointer
        il->Emit(oc::Ldloca_S, local__args_arrayTypeRef);
        il->Emit(oc::Ldfld, FIELD(typeof(TypeCastHelper::ArrayTypeWeakRef), "ptr"));

        il->EmitCall(oc::Call, METHOD(typeof(ConverterCallback), "Invoke"), nullptr);
        il->Emit(oc::Stloc_S, local__ret_allocator);

        il->Emit(oc::Ldloca_S, local__ret_allocator);
        il->EmitCall(oc::Call, METHOD(typeof(MemoryHelper::Allocator), "GetPtr"), nullptr);
        IL_CastNativeTypes(funcInfo.returnType);

        il->Emit(oc::Stloc_S, local__ret);

        for each (auto allocator in localAllocatorInstances)
        {
            il->Emit(oc::Ldloca_S, allocator);
            il->EmitCall(oc::Call, METHOD(typeof(MemoryHelper::Allocator), "Free"), nullptr);
        }

        il->Emit(oc::Ldloca_S, local__args_allocator);
        il->EmitCall(oc::Call, METHOD(typeof(MemoryHelper::Allocator), "Free"), nullptr);
        
        il->Emit(oc::Ldloca_S, local__ret_allocator);
        il->EmitCall(oc::Call, METHOD(typeof(MemoryHelper::Allocator), "Free"), nullptr);

        il->Emit(oc::Ldloc_S, local__ret);
        il->Emit(oc::Ret);

        return true;
    }

    void EmitHelper::ILCodeBulider::IL_CastArrayTypeToList(TypeHelper::FunctionInfo::TypeInfo% info)
    {
        auto local__arrayTypeRef = DeclareLocal(typeof(TypeCastHelper::ArrayTypeWeakRef));
        auto local__list = DeclareLocal(info._type);
        auto local__ptr = DeclareLocal(VOID_PTR_TYPE);
        auto local__loop_size = DeclareLocal(typeof(int));
        auto local__loop_i = DeclareLocal(typeof(int));

        il->Emit(oc::Stloc_S, local__ptr);

        //init ArrayTypeWeakRef
        il->Emit(oc::Ldloca_S, local__arrayTypeRef);
        il->Emit(oc::Ldloc_S, local__ptr);
        il->Emit(oc::Call, CTOR(typeof(TypeCastHelper::ArrayTypeWeakRef), PackArray<SystemType^>(VOID_PTR_TYPE)));
        //init list<>
        il->Emit(oc::Ldloca_S, local__arrayTypeRef);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ArrayTypeWeakRef), "Size"), nullptr);
        il->Emit(oc::Conv_I4);
        il->Emit(oc::Stloc_S, local__loop_size);
        il->Emit(oc::Ldloc_S, local__loop_size);
        il->Emit(oc::Newobj, CTOR(info._type, PackArray<SystemType^>(typeof(int))));
        il->Emit(oc::Stloc_S, local__list);

        //loop(for)
        //(int i = 0)
        il->Emit(oc::Ldc_I4_0);
        il->Emit(oc::Stloc_S, local__loop_i);

        auto loop_start_label = DefineLabel();
        auto loop_body_label = DefineLabel();
        il->Emit(oc::Br_S, loop_start_label);
        il->MarkLabel(labels[loop_body_label]);
        //{
        //load list<> obj
        il->Emit(oc::Ldloc_S, local__list);
        //get value_type pointer
        il->Emit(oc::Ldloca_S, local__arrayTypeRef);
        il->Emit(oc::Ldloc, local__loop_i);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ArrayTypeWeakRef), "GetArrayTypePtrByIndex"), nullptr);
        //cast type
        IL_CastNativeTypes(info.genericArgs[0]);
        ////add obj to list<>
        il->EmitCall(oc::Call, METHOD(info._type, "Add"), nullptr);
        //}
        //	(i++)
        il->Emit(oc::Ldloc_S, local__loop_i);
        il->Emit(oc::Ldc_I4_1);
        il->Emit(oc::Add);
        il->Emit(oc::Stloc_S, local__loop_i);
        //	(i < size)
        il->MarkLabel(labels[loop_start_label]);
        il->Emit(oc::Ldloc_S, local__loop_i);
        il->Emit(oc::Ldloc_S, local__loop_size);
        il->Emit(oc::Clt);
        il->Emit(oc::Brtrue_S, loop_body_label);
        //loop end

        //load list<> obj
        il->Emit(oc::Ldloc_S, local__list);
    }

    void EmitHelper::ILCodeBulider::IL_CastObjectTypeToDictionary(TypeHelper::FunctionInfo::TypeInfo% info)
    {
        auto local__objectTypeRef = DeclareLocal(typeof(TypeCastHelper::ObjectTypeWeakRef));
        auto local__objectTypeRef_iterator = DeclareLocal(typeof(TypeCastHelper::ObjectTypeWeakRef::iterator));
        auto local__dictionary = DeclareLocal(info._type);
        auto local__ptr = DeclareLocal(VOID_PTR_TYPE);

        il->Emit(oc::Stloc_S, local__ptr);
        //init ObjectTypeWeakRef
        il->Emit(oc::Ldloca_S, local__objectTypeRef);
        il->Emit(oc::Ldloc_S, local__ptr);
        il->Emit(oc::Call, CTOR(typeof(TypeCastHelper::ObjectTypeWeakRef), PackArray<SystemType^>(VOID_PTR_TYPE)));
        //init Dictionary<>
        il->Emit(oc::Ldloca_S, local__objectTypeRef);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ObjectTypeWeakRef), "Size"), nullptr);
        il->Emit(oc::Conv_I4);
        il->Emit(oc::Newobj, CTOR(info._type, PackArray<SystemType^>(typeof(int))));
        il->Emit(oc::Stloc_S, local__dictionary);
        //init ObjectTypeWeakRef.iterator
        il->Emit(oc::Ldloca_S, local__objectTypeRef);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ObjectTypeWeakRef), "GetIterator"), nullptr);
        il->Emit(oc::Stloc_S, local__objectTypeRef_iterator);
        //loop(while)
        auto loop__foreach_array_start = DefineLabel();
        auto loop__foreach_array_end = DefineLabel();
        //while(arrayTypeRef.MoveNext())
        il->MarkLabel(labels[loop__foreach_array_start]);
        il->Emit(oc::Ldloca_S, local__objectTypeRef_iterator);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ObjectTypeWeakRef::iterator), "MoveNext"), nullptr);
        il->Emit(oc::Brfalse_S, labels[loop__foreach_array_end]);
        //{
        //load dictionary<> obj
        il->Emit(oc::Ldloc_S, local__dictionary);
        //get key
        il->Emit(oc::Ldloca_S, local__objectTypeRef_iterator);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ObjectTypeWeakRef::iterator), "GetKey"), nullptr);
        //get value (value_type pointer)
        il->Emit(oc::Ldloca_S, local__objectTypeRef_iterator);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ObjectTypeWeakRef::iterator), "GetValue"), nullptr);
        ////cast type
        IL_CastNativeTypes(info.genericArgs[1]);
        ////add key&value to dictionary<>
        il->EmitCall(oc::Call, METHOD(info._type, "Add"), nullptr);
        //}
        il->Emit(oc::Br_S, labels[loop__foreach_array_start]);
        il->MarkLabel(labels[loop__foreach_array_end]);
        //loop end

        //load dictionary<> obj
        il->Emit(oc::Ldloc_S, local__dictionary);
    }

    void EmitHelper::ILCodeBulider::IL_CastNativeTypes(TypeHelper::FunctionInfo::TypeInfo% info)
    {
        using ValidType = TypeHelper::ValidType;

        switch (info.type)
        {
        case ValidType::Invalid:      throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
        case ValidType::Double:       il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2double), nullptr);       break;
        case ValidType::Float:        il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2float), nullptr);        break;
        case ValidType::Int64:        il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2int64_t), nullptr);      break;
        case ValidType::Int32:        il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2int32_t), nullptr);      break;
        case ValidType::Int16:        il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2int16_t), nullptr);      break;
        case ValidType::Int8:         il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2int8_t), nullptr);       break;
        case ValidType::UInt64:       il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2uint64_t), nullptr);     break;
        case ValidType::UInt32:       il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2uint32_t), nullptr);     break;
        case ValidType::UInt16:       il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2uint16_t), nullptr);     break;
        case ValidType::UInt8:        il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2uint8_t), nullptr);      break;
        case ValidType::Bool:         il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2bool), nullptr);         break;
        case ValidType::String:       il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2string), nullptr);       break;
        case ValidType::NumberType:   il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2NumberType), nullptr);   break;
        case ValidType::Player:       il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2Player), nullptr);       break;
        case ValidType::Actor:        il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2Actor), nullptr);        break;
        case ValidType::BlockActor:   il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2BlockActor), nullptr);   break;
        case ValidType::Container:    il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2Container), nullptr);    break;
        case ValidType::Vec3:         il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2Vec3), nullptr);         break;
        case ValidType::BlockPos:     il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2BlockPos), nullptr);     break;
        case ValidType::WorldPosType: il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2WorldPosType), nullptr); break;
        case ValidType::BlockPosType: il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2BlockPosType), nullptr); break;
        case ValidType::ItemType:     il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2ItemType), nullptr);     break;
        case ValidType::BlockType:    il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2BlockType), nullptr);    break;
        case ValidType::NbtType:      il->EmitCall(oc::Call, TYPECASTHELPER_METHOD_INFO(Native2NbtType), nullptr);      break;
        case ValidType::List:         IL_CastArrayTypeToList(info);                                                     break;
        case ValidType::Dictionary:   IL_CastObjectTypeToDictionary(info);                                              break;
        case ValidType::Void:         il->Emit(oc::Pop);
        }
    }

    void EmitHelper::ILCodeBulider::IL_CastListToArrayType(TypeHelper::FunctionInfo::TypeInfo% info)
    {
        IL_CastListToArrayType(info, false);
    }

    void EmitHelper::ILCodeBulider::IL_CastDictionaryToObjectType(TypeHelper::FunctionInfo::TypeInfo% info)
    {
        IL_CastDictionaryToObjectType(info, false);
    }

    void EmitHelper::ILCodeBulider::IL_CastListToArrayType(TypeHelper::FunctionInfo::TypeInfo% info, bool isSelfCalled)
    {
        using ValidType = TypeHelper::ValidType;

        auto method__getEnumerator = METHOD(info._type, "GetEnumerator");

        auto type__enumerator = method__getEnumerator->ReturnType;

        auto local__list = DeclareLocal(info._type);
        auto local__allocator = DeclareLocal(typeof(MemoryHelper::Allocator));
        auto local__arrayTypeRef = DeclareLocal(typeof(TypeCastHelper::ArrayTypeWeakRef));
        auto local__list_enumerator = DeclareLocal(type__enumerator);

        localAllocatorInstances->Add(localVars[local__allocator]);


        il->Emit(oc::Stloc_S, local__list);
        //init allocator
        il->Emit(oc::Ldloca_S, local__allocator);
        il->Emit(oc::Initobj, typeof(MemoryHelper::Allocator));
        //alloc memory
        il->Emit(oc::Ldloca_S, local__allocator);
        il->EmitCall(oc::Call, METHOD(typeof(MemoryHelper::Allocator), "Alloc"), nullptr);
        //construct internal value_type obj as array_type
        il->Emit(oc::Ldloca_S, local__allocator);
        il->EmitCall(oc::Call, METHOD(typeof(MemoryHelper::Allocator), "SetValueAsArrayType"), nullptr);
        il->Emit(oc::Stloc_S, local__arrayTypeRef);
        //init enumerator
        il->Emit(oc::Ldloc_S, local__list);
        il->EmitCall(oc::Call, method__getEnumerator, nullptr);
        il->Emit(oc::Stloc_S, local__list_enumerator);

        //loop(while)
        auto loop__foreach_array_start = DefineLabel();
        auto loop__foreach_array_end = DefineLabel();
        //while(enumerator.MoveNext())
        il->MarkLabel(labels[loop__foreach_array_start]);
        il->Emit(oc::Ldloca_S, local__list_enumerator);
        il->EmitCall(oc::Call, METHOD(type__enumerator, "MoveNext"), nullptr);
        il->Emit(oc::Brfalse_S, labels[loop__foreach_array_end]);
        //{
        il->Emit(oc::Ldloca_S, local__arrayTypeRef);
        il->Emit(oc::Ldloca_S, local__list_enumerator);
        il->EmitCall(oc::Call, METHOD(type__enumerator, "get_Current"), nullptr);

        switch (info.genericArgs[0].type)
        {
        case ValidType::Void:
        case ValidType::Invalid:
            throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
        case ValidType::List:
        {
            IL_CastListToArrayType(info.genericArgs[0], true);
            il->EmitCall(
                oc::Call,
                METHOD_WITH_ARGS(typeof(MemoryHelper), "ArrayType_EmplaceBack",
                    PackArray<SystemType^>(
                        typeof(TypeCastHelper::ArrayTypeWeakRef)->MakeByRefType(),
                        typeof(TypeCastHelper::ArrayTypeWeakRef)->MakeByRefType())),
                nullptr);
        }
        break;
        case ValidType::Dictionary:
        {
            IL_CastDictionaryToObjectType(info.genericArgs[1], true);
            il->EmitCall(
                oc::Call,
                METHOD_WITH_ARGS(typeof(MemoryHelper), "ArrayType_EmplaceBack",
                    PackArray<SystemType^>(
                        typeof(TypeCastHelper::ArrayTypeWeakRef)->MakeByRefType(),
                        typeof(TypeCastHelper::ObjectTypeWeakRef)->MakeByRefType())),
                nullptr);
        }
        break;
        default:
        {
            il->EmitCall(
                oc::Call,
                METHOD_WITH_ARGS(typeof(MemoryHelper), "ArrayType_EmplaceBack",
                    PackArray<SystemType^>(
                        typeof(TypeCastHelper::ArrayTypeWeakRef)->MakeByRefType(),
                        info.genericArgs[0]._type)),
                nullptr);
        }
        break;
        }
        il->Emit(oc::Br_S, labels[loop__foreach_array_start]);
        il->MarkLabel(labels[loop__foreach_array_end]);
        //loop end

        if (isSelfCalled)
            il->Emit(oc::Ldloca_S, local__arrayTypeRef);
        else
            il->Emit(oc::Ldloca_S, local__allocator);
    }

    void EmitHelper::ILCodeBulider::IL_CastDictionaryToObjectType(TypeHelper::FunctionInfo::TypeInfo% info, bool isSelfCalled)
    {
        using ValidType = TypeHelper::ValidType;

        auto method__getEnumerator = METHOD(info._type, "GetEnumerator");
        auto type__enumerator = method__getEnumerator->ReturnType;
        auto method__get_Current = METHOD(type__enumerator, "get_Current");
        auto type__pair = method__get_Current->ReturnType;

        auto local__dictionary = DeclareLocal(info._type);
        auto local__allocator = DeclareLocal(typeof(MemoryHelper::Allocator));
        auto local__objectTypeRef = DeclareLocal(typeof(TypeCastHelper::ObjectTypeWeakRef));
        auto local__dictionary_enumerator = DeclareLocal(type__enumerator);
        auto local__pair = DeclareLocal(type__pair);

        localAllocatorInstances->Add(localVars[local__allocator]);


        il->Emit(oc::Stloc_S, local__dictionary);
        //init allocator
        il->Emit(oc::Ldloca_S, local__allocator);
        il->Emit(oc::Initobj, typeof(MemoryHelper::Allocator));
        //alloc memory
        il->Emit(oc::Ldloca_S, local__allocator);
        il->EmitCall(oc::Call, METHOD(typeof(MemoryHelper::Allocator), "Alloc"), nullptr);
        //construct internal value_type obj as object_type
        il->Emit(oc::Ldloca_S, local__allocator);
        il->EmitCall(oc::Call, METHOD(typeof(MemoryHelper::Allocator), "SetValueAsObjectType"), nullptr);
        il->Emit(oc::Stloc_S, local__objectTypeRef);
        //init enumerator
        il->Emit(oc::Ldloc_S, local__dictionary);
        il->EmitCall(oc::Call, method__getEnumerator, nullptr);
        il->Emit(oc::Stloc_S, local__dictionary_enumerator);

        //loop(while)
        auto loop__foreach_array_start = DefineLabel();
        auto loop__foreach_array_end = DefineLabel();
        //while(enumerator.MoveNext())
        il->MarkLabel(labels[loop__foreach_array_start]);
        il->Emit(oc::Ldloca_S, local__dictionary_enumerator);
        il->EmitCall(oc::Call, METHOD(type__enumerator, "MoveNext"), nullptr);
        il->Emit(oc::Brfalse_S, labels[loop__foreach_array_end]);
        ////{
        il->Emit(oc::Ldloca_S, local__dictionary_enumerator);
        il->EmitCall(oc::Call, method__get_Current, nullptr);
        il->Emit(oc::Stloc_S, local__pair);

        switch (info.genericArgs[1].type)
        {
        case ValidType::Void:
        case ValidType::Invalid:
            throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
        case ValidType::List:
        {
            il->Emit(oc::Ldloca_S, local__pair);
            il->EmitCall(oc::Call, METHOD(type__pair, "get_Value"), nullptr);
            IL_CastListToArrayType(info.genericArgs[1], true);
            auto local__temp_arrayTypeRef = DeclareLocal(typeof(TypeCastHelper::ArrayTypeWeakRef));
            il->Emit(oc::Stloc_S, local__temp_arrayTypeRef);

            il->Emit(oc::Ldloca_S, local__objectTypeRef);
            il->Emit(oc::Ldloca_S, local__pair);
            il->EmitCall(oc::Call, METHOD(type__pair, "get_Key"), nullptr);
            il->Emit(oc::Ldloc_S, local__temp_arrayTypeRef);

            il->EmitCall(
                oc::Call,
                METHOD_WITH_ARGS(typeof(MemoryHelper), "ObjectType_EmplaceBack",
                    PackArray<SystemType^>(
                        typeof(TypeCastHelper::ObjectTypeWeakRef)->MakeByRefType(),
                        typeof(String),
                        typeof(TypeCastHelper::ArrayTypeWeakRef)->MakeByRefType())),
                nullptr);
        }
        break;
        case ValidType::Dictionary:
        {
            il->Emit(oc::Ldloca_S, local__pair);
            il->EmitCall(oc::Call, METHOD(type__pair, "get_Value"), nullptr);
            IL_CastDictionaryToObjectType(info.genericArgs[1], true);
            il->Emit(oc::Pop);
            auto local__temp_ObjectTypeRef = DeclareLocal(typeof(TypeCastHelper::ObjectTypeWeakRef));
            il->Emit(oc::Stloc_S, local__temp_ObjectTypeRef);

            il->Emit(oc::Ldloca_S, local__objectTypeRef);
            il->Emit(oc::Ldloca_S, local__pair);
            il->EmitCall(oc::Call, METHOD(type__pair, "get_Key"), nullptr);
            il->Emit(oc::Ldloc_S, local__temp_ObjectTypeRef);

            il->EmitCall(
                oc::Call,
                METHOD_WITH_ARGS(typeof(MemoryHelper), "ObjectType_EmplaceBack",
                    PackArray<SystemType^>(
                        typeof(TypeCastHelper::ObjectTypeWeakRef)->MakeByRefType(),
                        typeof(String),
                        typeof(TypeCastHelper::ObjectTypeWeakRef)->MakeByRefType())),
                nullptr);
        }
        break;
        default:
        {
            il->Emit(oc::Ldloca_S, local__objectTypeRef);
            il->Emit(oc::Ldloca_S, local__pair);
            il->EmitCall(oc::Call, METHOD(type__pair, "get_Key"), nullptr);
            il->Emit(oc::Ldloca_S, local__pair);
            il->EmitCall(oc::Call, METHOD(type__pair, "get_Value"), nullptr);

            il->EmitCall(
                oc::Call,
                METHOD_WITH_ARGS(typeof(MemoryHelper), "ObjectType_EmplaceBack",
                    PackArray<SystemType^>(
                        typeof(TypeCastHelper::ObjectTypeWeakRef)->MakeByRefType(),
                        typeof(String),
                        info.genericArgs[1]._type)),
                nullptr);
        }
        break;
        }
        //}
        il->Emit(oc::Br_S, labels[loop__foreach_array_start]);
        il->MarkLabel(labels[loop__foreach_array_end]);
        //loop end

        if (isSelfCalled)
            il->Emit(oc::Ldloca_S, local__objectTypeRef);
        else
            il->Emit(oc::Ldloca_S, local__allocator);
    }

    void EmitHelper::ILCodeBulider::IL_CastManagedTypes(TypeHelper::FunctionInfo::TypeInfo% info)
    {
        IL_CastManagedTypes(info, true);
    }

    void EmitHelper::ILCodeBulider::IL_CastManagedTypes(TypeHelper::FunctionInfo::TypeInfo% info, bool isRet)
    {
        using ValidType = TypeHelper::ValidType;

        auto ret__allocator = DeclareLocal(typeof(MemoryHelper::Allocator));
        auto local__var = DeclareLocal(info._type);

        if (!isRet)
            localAllocatorInstances->Add(localVars[ret__allocator]);

        il->Emit(oc::Stloc_S, local__var);

        //init allocator
        il->Emit(oc::Ldloca_S, ret__allocator);
        il->Emit(oc::Initobj, typeof(MemoryHelper::Allocator));
        //alloc memory
        il->Emit(oc::Ldloca_S, ret__allocator);
        il->EmitCall(oc::Call, METHOD(typeof(MemoryHelper::Allocator), "Alloc"), nullptr);

        switch (info.type)
        {
        case ValidType::Invalid:
            throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
        case ValidType::List:
        {
            il->Emit(oc::Ldloca_S, ret__allocator);
            il->Emit(oc::Ldloc_S, local__var);
            IL_CastListToArrayType(info, true);
            il->EmitCall(
                oc::Call,
                METHOD_WITH_ARGS(
                    typeof(MemoryHelper::Allocator),
                    "SetValueByMove",
                    PackArray<SystemType^>(typeof(TypeCastHelper::ArrayTypeWeakRef)->MakeByRefType())),
                nullptr);
        }
        break;
        case ValidType::Dictionary:
        {
            il->Emit(oc::Ldloca_S, ret__allocator);
            il->Emit(oc::Ldloc_S, local__var);
            IL_CastDictionaryToObjectType(info, true);
            il->EmitCall(
                oc::Call,
                METHOD_WITH_ARGS(
                    typeof(MemoryHelper::Allocator),
                    "SetValueByMove",
                    PackArray<SystemType^>(typeof(TypeCastHelper::ObjectTypeWeakRef)->MakeByRefType())),
                nullptr);
        }
        break;
        case ValidType::Void:
        {
            il->Emit(oc::Ldloca_S, ret__allocator);
            il->EmitCall(
                oc::Call,
                METHOD_WITH_ARGS(
                    typeof(MemoryHelper::Allocator),
                    "SetValue",
                    PackArray<SystemType^>()),
                nullptr);
        }
        break;
        default:
        {
            il->Emit(oc::Ldloca_S, ret__allocator);
            il->Emit(oc::Ldloc_S, local__var);
            il->EmitCall(
                oc::Call,
                METHOD_WITH_ARGS(
                    typeof(MemoryHelper::Allocator),
                    "SetValue",
                    PackArray<SystemType^>(info._type)),
                nullptr);
        }
        break;
        }

        il->Emit(isRet ? oc::Ldloc_S : oc::Ldloca_S, ret__allocator);
    }
}