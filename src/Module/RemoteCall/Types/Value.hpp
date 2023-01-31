#pragma once
#include <src\Main/ClassTemplate.hpp>

#include "NumberType.hpp"
#include <RemoteCallAPI.h>

#include <src\Header\MC\Vec3.hpp>
#include <src\Header\MC\BlockPos.hpp>

#include <src/Module/RemoteCall/Interfaces/IValueType.hpp>
#include <src/Module/RemoteCall/Enums/InstanceType.hpp>
#include <src/Module/RemoteCall/Attributes/RemoteCallValueTypeAttribute.hpp>

namespace MC
{
    ref class Player;
    ref class Actor;
    ref class BlockActor;
    ref class Container;
}

namespace LiteLoader::RemoteCall
{
    ref class ItemType;
    ref class BlockType;
    ref class NbtType;
    ref class WorldPosType;
    ref class BlockPosType;
}

namespace LiteLoader::RemoteCall
{
    [RemoteCallValueType(InstanceType::Value)]
    public ref class Value :ClassTemplate<Value, ::RemoteCall::Value>, IValueType
    {
        //ctor
    public:
        __ctor_all(Value, ::RemoteCall::Value);

        /// <summary>
        /// Copy
        /// </summary>
        /// <param name="val"></param>
        Value(Value% val);
        explicit Value(bool b);
        Value(String^ str);
        Value();
        Value(NumberType num);
        Value(MC::Player^ player);
        Value(MC::Actor^ actor);
        Value(MC::BlockActor^ bloackActor);
        Value(MC::Container^ container);
        Value(MC::Vec3 vec3);
        Value(MC::BlockPos blockPos);
        Value(ItemType^ itemType);
        Value(BlockType^ blockType);
        Value(NbtType^ nbtType);
        Value(WorldPosType^ posType);
        Value(BlockPosType^ posType);
        Value(double num);
        Value(float num);
        Value(__int64 num);
        Value(int num);
        Value(short num);
        Value(char num);
        Value(unsigned __int64 num);
        Value(unsigned int num);
        Value(unsigned short num);
        Value(unsigned char num);
        Value^ Clone();
    internal:
        Value(::RemoteCall::Value const& v);
    public:
        enum class InstanceType
        {
            Bool = 0,
            String = 1,
            Null = 2,
            NumberType = 3,
            Player = 4,
            Actor = 5,
            BlockActor = 6,
            Container = 7,
            WorldPosType = 8,
            BlockPosType = 9,
            ItemType = 10,
            BlockType = 11,
            NbtType = 12
        };
        //method
    public:
        property InstanceType Type
        {
            InstanceType get();
        }
        bool IsNull();
        bool AsBool([Out] bool% v);
        bool AsString([Out] String^% v);
        bool AsNumberType([Out] NumberType% v);
        bool AsPlayer([Out] MC::Player^% v);
        bool AsActor([Out] MC::Actor^% v);
        bool AsBlockActor([Out] MC::BlockActor^% v);
        bool AsContainer([Out] MC::Container^% v);
        bool AsWorldPosType([Out] WorldPosType^% v);
        bool AsBlockPosType([Out] BlockPosType^% v);
        bool AsItemType([Out] ItemType^% v);
        bool AsBlockType([Out] BlockType^% v);
        bool AsNbtType([Out] NbtType^% v);
        bool AsContainer([Out] BlockType^% v);
        //opeator
    public:

        Value^ SetNull();
        Value^ operator=(bool v);
        Value^ operator=(String^ v);
        Value^ operator=(NumberType v);
        Value^ operator=(MC::Player^ player);
        Value^ operator=(MC::Actor^ actor);
        Value^ operator=(MC::BlockActor^ blockActor);
        Value^ operator=(MC::Container^ container);
        Value^ operator=(WorldPosType^ worldPos);
        Value^ operator=(BlockPosType^ blockPos);
        Value^ operator=(ItemType^ itemType);
        Value^ operator=(BlockType^ blockType);
        Value^ operator=(NbtType^ nbtType);
        static operator Value ^ (bool v)
        {
            return gcnew Value(v);
        }
        static operator Value ^ (String^ v)
        {
            return gcnew Value(v);
        }
        static operator Value ^ (NumberType v)
        {
            return gcnew Value(v);
        }
        static operator Value ^ (MC::Player^ v)
        {
            return gcnew Value(v);
        }
        static operator Value ^ (MC::Actor^ v)
        {
            return gcnew Value(v);
        }
        static operator Value ^ (MC::BlockActor^ v)
        {
            return gcnew Value(v);
        }
        static operator Value ^ (MC::Container^ v)
        {
            return gcnew Value(v);
        }
        static operator Value ^ (MC::Vec3 v)
        {
            return gcnew Value(v);
        }
        static operator Value ^ (MC::BlockPos v)
        {
            return gcnew Value(v);
        }
        static operator Value ^ (ItemType^ v)
        {
            return gcnew Value(v);
        }
        static operator Value ^ (BlockType^ v)
        {
            return gcnew Value(v);
        }
        static operator Value ^ (NbtType^ v)
        {
            return gcnew Value(v);
        }

        static operator bool(Value^ v)
        {
            bool ret;
            if (!v->AsBool(ret))
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
            return ret;
        }
        static operator String ^ (Value^ v)
        {

            String^ ret;
            if (!v->AsString(ret))
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
            return ret;
        }
        static operator NumberType (Value^ v)
        {
            NumberType ret;
            if (!v->AsNumberType(ret))
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
            return ret;
        }
        static operator MC::Player ^ (Value^ v)
        {

            MC::Player^ ret;
            if (!v->AsPlayer(ret))
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
            return ret;
        }
        static operator MC::Actor ^ (Value^ v)
        {
            MC::Actor^ ret;
            if (!v->AsActor(ret))
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
            return ret;
        }
        static operator MC::BlockActor ^ (Value^ v)
        {
            MC::BlockActor^ ret;
            if (!v->AsBlockActor(ret))
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
            return ret;
        }
        static operator MC::Container ^ (Value^ v)
        {
            MC::Container^ ret;
            if (!v->AsContainer(ret))
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
            return ret;
        }
        static operator WorldPosType ^ (Value^ v)
        {
            WorldPosType^ ret;
            if (!v->AsWorldPosType(ret))
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
            return ret;
        }
        static operator BlockPosType ^ (Value^ v)
        {
            BlockPosType^ ret;
            if (!v->AsBlockPosType(ret))
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
            return ret;
        }
        static operator ItemType ^ (Value^ v)
        {
            ItemType^ ret;
            if (!v->AsItemType(ret))
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
            return ret;
        }
        static operator BlockType ^ (Value^ v)
        {
            BlockType^ ret;
            if (!v->AsBlockType(ret))
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
            return ret;
        }
        static operator NbtType ^ (Value^ v)
        {
            NbtType^ ret;
            if (!v->AsNbtType(ret))
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
            return ret;
        }

#define Value2SimpleType_Implicit(type)                                             \
        static operator type(Value^ v)                                              \
        {                                                                           \
        	if(v->NativePtr->index() != (size_t)InstanceType::NumberType)			\
        	throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;            \
        	return std::get<::RemoteCall::NumberType>(*v->NativePtr).get<type>();   \
        };

        Value2SimpleType_Implicit(double);
        Value2SimpleType_Implicit(float);
        Value2SimpleType_Implicit(__int64);
        Value2SimpleType_Implicit(int);
        Value2SimpleType_Implicit(short);
        Value2SimpleType_Implicit(char);
        Value2SimpleType_Implicit(unsigned __int64);
        Value2SimpleType_Implicit(unsigned int);
        Value2SimpleType_Implicit(unsigned short);
        Value2SimpleType_Implicit(unsigned char);

#undef Value2SimpleType_Implicit

    public:
        virtual String^ ToString() override;
    };
}