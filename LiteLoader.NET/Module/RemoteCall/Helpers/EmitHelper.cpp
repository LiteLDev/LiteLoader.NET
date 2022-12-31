#include "EmitHelper.hpp"

namespace LiteLoader::RemoteCall::Helper
{
#define VOID_PTR_TYPE void::typeid->MakePointerType()
#define CTOR(type,argTypes) type->GetConstructor(argTypes)
#define METHOD(type,name) type->GetMethod(name)
#define METHOD_WITH_ARGS(type,name,args) type->GetMethod(name,args)
#define FIELD(type,name) type->GetField(name)

    generic<typename TDelegate> where TDelegate : Delegate
        void EmitHelper::CreateExportNativeFuncPtr(String^ nameSpace, String^ funcName, TDelegate func)
    {

        auto dynamicMethod = gcnew DynamicMethod(
            nameSpace + L'.' + funcName,
            VOID_PTR_TYPE,
            gcnew array<SystemType^>{ VOID_PTR_TYPE });


    }

    generic<typename TDelegate> where TDelegate: Delegate
        EmitHelper::ILCodeBulider::ILCodeBulider(String^ nameSpace, String^ funcName, TypeHelper::FunctionInfo% info, BuliderType type)
    {
        funcInfo = info;
        buliderType = type;
        localVars = gcnew Dictionary<int, LocalBuilder^>;
        labels = gcnew Dictionary<int, Label>;
        exportedManagedFuncDelegateType = typeof(TDelegate);
        localAllocatorInstances = gcnew List<LocalBuilder^>;

        switch (type)
        {
        case BuliderType::Export:
            method = gcnew DynamicMethod(
                nameSpace + L'.' + funcName,
                VOID_PTR_TYPE,
                PackArray<SystemType^>(typeof(EmitHelper::ExportedFuncInstance), VOID_PTR_TYPE));
            break;
        case BuliderType::Import:
            throw gcnew System::NotImplementedException;
            break;
        default:
            break;
        }

        il = method->GetILGenerator();
    }

    bool EmitHelper::ILCodeBulider::Build()
    {
        switch (buliderType)
        {
        case BuliderType::Export:
            BuildExport();
            break;
        case BuliderType::Import:
            BuildImport();
            break;
        default:
            break;
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
        auto ret = localVars->Count;
        labels->Add(ret, il->DefineLabel());
        return ret;
    }

    bool EmitHelper::ILCodeBulider::BuildExport()
    {
        for each (auto % typeInfo in funcInfo.parameters)
            DeclareLocal(typeInfo._type);

        for (int i = 0; i < funcInfo.parameters->Length; ++i)
        {
            auto local__arrayTypeRef = DeclareLocal(typeof(TypeCastHelper::ArrayTypeWeakRef));

            //init ArrayTypeWeakRef
            il->Emit(oc::Ldarg_1);
            il->Emit(oc::Newobj, CTOR(typeof(TypeCastHelper::ArrayTypeWeakRef), PackArray<SystemType^>(VOID_PTR_TYPE)));
            il->Emit(oc::Stloc_S, localVars[local__arrayTypeRef]);

            il->Emit(oc::Ldc_I8, i);
            il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ArrayTypeWeakRef), "get_default"), nullptr);
            il->EmitCall(oc::Call, METHOD(typeof(IntPtr), "ToPointer"), nullptr);

            IL_CastNativeTypes(funcInfo.parameters[i]);

            il->Emit(oc::Stloc_S, i);
        }

        //load this
        il->Emit(oc::Ldarg_0);
        il->Emit(oc::Ldfld, FIELD(typeof(EmitHelper::ExportedFuncInstance), "exportedManagedFunc"));
        il->EmitCall(oc::Call, METHOD(exportedManagedFuncDelegateType, "Invoke"), nullptr);
    }

    bool EmitHelper::ILCodeBulider::BuildImport()
    {

    }

    void EmitHelper::ILCodeBulider::IL_CastArrayTypeToList(TypeHelper::FunctionInfo::TypeInfo% info)
    {
        auto local__arrayTypeRef = DeclareLocal(typeof(TypeCastHelper::ArrayTypeWeakRef));
        auto local__arrayTypeRef_iterator = DeclareLocal(typeof(TypeCastHelper::ArrayTypeWeakRef::iterator));
        auto local__list = DeclareLocal(info._type);

        //init ArrayTypeWeakRef
        il->Emit(oc::Newobj, CTOR(typeof(TypeCastHelper::ArrayTypeWeakRef), PackArray<SystemType^>(VOID_PTR_TYPE)));
        il->Emit(oc::Stloc_S, localVars[local__arrayTypeRef]);
        //init list<>
        il->Emit(oc::Ldloca_S, localVars[local__arrayTypeRef]);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ArrayTypeWeakRef), "Size"), nullptr);
        il->Emit(oc::Conv_I4);
        il->Emit(oc::Newobj, CTOR(info._type, PackArray<SystemType^>(typeof(int))));
        il->Emit(oc::Stloc_S, localVars[local__list]);
        //init ArrayTypeWeakRef.iterator
        il->Emit(oc::Ldloca_S, localVars[local__arrayTypeRef]);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ArrayTypeWeakRef), "GetIterator"), nullptr);
        il->Emit(oc::Stloc_S, localVars[local__arrayTypeRef_iterator]);

        //loop(while)
        auto loop__foreach_array_start = DefineLabel();
        auto loop__foreach_array_end = DefineLabel();
        //while(arrayTypeRef.MoveNext())
        il->MarkLabel(labels[loop__foreach_array_start]);
        il->Emit(oc::Ldloca_S, localVars[local__arrayTypeRef_iterator]);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ArrayTypeWeakRef::iterator), "MoveNext"), nullptr);
        il->Emit(oc::Brfalse_S, labels[loop__foreach_array_end]);
        //{
        //load list<> obj
        il->Emit(oc::Ldloc_S, localVars[local__list]);
        //get value_type pointer
        il->Emit(oc::Ldloca_S, localVars[local__arrayTypeRef_iterator]);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ArrayTypeWeakRef::iterator), "GetCurrentPtr"), nullptr);
        //cast type
        IL_CastNativeTypes(info.genericArgs[0]);
        //add obj to list<>
        il->EmitCall(oc::Call, METHOD(info._type, "Add"), nullptr);
        //}
        il->Emit(oc::Br_S, labels[loop__foreach_array_start]);
        il->MarkLabel(labels[loop__foreach_array_end]);
        //loop end

        //load list<> obj
        il->Emit(oc::Ldloc_S, localVars[local__list]);
    }

    void EmitHelper::ILCodeBulider::IL_CastObjectTypeToDictionary(TypeHelper::FunctionInfo::TypeInfo% info)
    {
        auto local__objectTypeRef = DeclareLocal(typeof(TypeCastHelper::ObjectTypeWeakRef));
        auto local__objectTypeRef_iterator = DeclareLocal(typeof(TypeCastHelper::ObjectTypeWeakRef::iterator));
        auto local__dictionary = DeclareLocal(info._type);

        //init ObjectTypeWeakRef
        il->Emit(oc::Newobj, CTOR(typeof(TypeCastHelper::ObjectTypeWeakRef), PackArray<SystemType^>(VOID_PTR_TYPE)));
        il->Emit(oc::Stloc_S, localVars[local__objectTypeRef]);
        //init Dictionary<>
        il->Emit(oc::Ldloca_S, localVars[local__objectTypeRef]);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ObjectTypeWeakRef), "Size"), nullptr);
        il->Emit(oc::Conv_I4);
        il->Emit(oc::Newobj, CTOR(info._type, PackArray<SystemType^>(typeof(int))));
        il->Emit(oc::Stloc_S, localVars[local__dictionary]);
        //init ObjectTypeWeakRef.iterator
        il->Emit(oc::Ldloca_S, localVars[local__objectTypeRef]);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ObjectTypeWeakRef), "GetIterator"), nullptr);
        il->Emit(oc::Stloc_S, localVars[local__objectTypeRef_iterator]);

        //loop(while)
        auto loop__foreach_array_start = DefineLabel();
        auto loop__foreach_array_end = DefineLabel();
        //while(arrayTypeRef.MoveNext())
        il->MarkLabel(labels[loop__foreach_array_start]);
        il->Emit(oc::Ldloca_S, localVars[local__objectTypeRef_iterator]);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ObjectTypeWeakRef::iterator), "MoveNext"), nullptr);
        il->Emit(oc::Brfalse_S, labels[loop__foreach_array_end]);
        //{
        //load dictionary<> obj
        il->Emit(oc::Ldloc_S, localVars[local__dictionary]);
        //get key
        il->Emit(oc::Ldloca_S, localVars[local__objectTypeRef_iterator]);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ObjectTypeWeakRef::iterator), "GetKey"), nullptr);
        //get value (value_type pointer)
        il->Emit(oc::Ldloca_S, localVars[local__objectTypeRef_iterator]);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ObjectTypeWeakRef::iterator), "GetValue"), nullptr);
        //cast type
        IL_CastNativeTypes(info.genericArgs[0]);
        //add key&value to dictionary<>
        il->EmitCall(oc::Call, METHOD(info._type, "Add"), nullptr);
        //}
        il->Emit(oc::Br_S, labels[loop__foreach_array_start]);
        il->MarkLabel(labels[loop__foreach_array_end]);
        //loop end

        //load dictionary<> obj
        il->Emit(oc::Ldloc_S, localVars[local__dictionary]);
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
        case ValidType::List:         IL_CastArrayTypeToList(info.genericArgs[0]);                                      break;
        case ValidType::Dictionary:   IL_CastObjectTypeToDictionary(info.genericArgs[1]);                               break;
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

        auto method__getEnumator = METHOD(info._type, "GetEnumator");

        auto type__enumator = method__getEnumator->ReturnType;

        auto local__list = DeclareLocal(info._type);
        auto local__allocator = DeclareLocal(typeof(MemoryHelper::Allocator));
        auto local__arrayTypeRef = DeclareLocal(typeof(TypeCastHelper::ArrayTypeWeakRef));
        auto local__list_enumator = DeclareLocal(type__enumator);

        localAllocatorInstances->Add(localVars[local__allocator]);


        il->Emit(oc::Stloc_S, localVars[local__list]);
        //init allocator
        il->Emit(oc::Newobj, CTOR(typeof(MemoryHelper::Allocator), PackArray<SystemType^>()));
        il->Emit(oc::Stloc_S, localVars[local__allocator]);
        //alloc memory
        il->Emit(oc::Ldloca_S, localVars[local__allocator]);
        il->EmitCall(oc::Call, METHOD(typeof(MemoryHelper::Allocator), "Alloc"), nullptr);
        //construct internal value_type obj as array_type
        il->Emit(oc::Ldloca_S, localVars[local__allocator]);
        il->EmitCall(oc::Call, METHOD(typeof(MemoryHelper::Allocator), "SetValueAsArrayType"), nullptr);
        il->Emit(oc::Stloc_S, localVars[local__arrayTypeRef]);
        //init enumator
        il->Emit(oc::Ldloc_S, localVars[local__list]);
        il->EmitCall(oc::Call, method__getEnumator, nullptr);
        il->Emit(oc::Stloc_S, localVars[local__list_enumator]);

        //loop(while)
        auto loop__foreach_array_start = DefineLabel();
        auto loop__foreach_array_end = DefineLabel();
        //while(enumator.MoveNext())
        il->MarkLabel(labels[loop__foreach_array_start]);
        il->Emit(oc::Ldloca_S, localVars[local__list_enumator]);
        il->EmitCall(oc::Call, METHOD(typeof(TypeCastHelper::ObjectTypeWeakRef::iterator), "MoveNext"), nullptr);
        il->Emit(oc::Brfalse_S, labels[loop__foreach_array_end]);
        //{
        il->Emit(oc::Ldloca_S, localVars[local__arrayTypeRef]);
        il->Emit(oc::Ldloca_S, localVars[local__list_enumator]);
        il->EmitCall(oc::Call, METHOD(type__enumator, "get_Current"), nullptr);

        switch (info.genericArgs[0].type)
        {
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
            IL_CastDictionaryToObjectType(info.genericArgs[0], true);
            il->EmitCall(
                oc::Call,
                METHOD_WITH_ARGS(typeof(MemoryHelper), "ArrayType_EmplaceBack",
                    PackArray<SystemType^>(
                        typeof(TypeCastHelper::ArrayTypeWeakRef)->MakeByRefType(),
                        typeof(TypeCastHelper::ArrayTypeWeakRef)->MakeByRefType())),
                nullptr);
        }
        break;
        default:
        {
            il->EmitCall(
                oc::Call,
                METHOD_WITH_ARGS(typeof(MemoryHelper), "ArrayType_EmplaceBack",
                    PackArray<SystemType^>(typeof(TypeCastHelper::ArrayTypeWeakRef)->MakeByRefType(),
                        info.genericArgs[0]._type)),
                nullptr);
        }
        break;
        }
        //}
        il->Emit(oc::Br_S, labels[loop__foreach_array_start]);
        il->MarkLabel(labels[loop__foreach_array_end]);
        //loop end

        if (isSelfCalled)
            il->Emit(oc::Ldloca_S, localVars[local__arrayTypeRef]);
        else
            il->Emit(oc::Ldloca_S, localVars[local__allocator]);
    }
    void EmitHelper::ILCodeBulider::IL_CastDictionaryToObjectType(TypeHelper::FunctionInfo::TypeInfo% info, bool isSelfCalled)
    {
        throw gcnew System::NotImplementedException();
    }
    void EmitHelper::ILCodeBulider::IL_CastManagedTypes(TypeHelper::FunctionInfo::TypeInfo% info)
    {
        throw gcnew System::NotImplementedException();
    }
}