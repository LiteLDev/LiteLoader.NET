#include "Value.hpp"
#include <LiteLoader.NET\Header\MC\Player.hpp>
#include <LiteLoader.NET\Header\MC\BlockActor.hpp>
#include <LiteLoader.NET\Header\MC\Container.hpp>

#include "ItemType.hpp"
#include "BlockType.hpp"
#include "NbtType.hpp"
#include "WorldPosType.hpp"
#include "BlockPosType.hpp"

namespace LiteLoader::RemoteCall
{
    using _Value = ::RemoteCall::Value;

    Value::Value(Value% val)
        :ClassTemplate(new _Value(*val.nativePtr), val.ownsNativeInstance)
    {
    }

    inline Value::Value(bool b)
        : ClassTemplate(new _Value(b), true)
    {
    }

    inline Value::Value(String^ str)
        : ClassTemplate(new _Value(marshalString(str)), true)
    {
    }

    inline Value::Value()
        : ClassTemplate(new _Value(nullptr_t(nullptr)), true)
    {
    }

    inline Value::Value(NumberType num)
        : ClassTemplate(new _Value(num._toNative()), true)
    {
    }

    inline Value::Value(MC::Player^ player)
        : ClassTemplate(new _Value(player->NativePtr), true)
    {
    }

    inline Value::Value(MC::Actor^ actor)
        : ClassTemplate(new _Value(actor->NativePtr), true)
    {
    }

    inline Value::Value(MC::BlockActor^ bloackActor)
        : ClassTemplate(new _Value(bloackActor->NativePtr), true)
    {
    }

    inline Value::Value(MC::Container^ container)
        : ClassTemplate(new _Value(container->NativePtr), true)
    {
    }

    inline Value::Value(MC::Vec3 vec3)
        : ClassTemplate(new _Value(::Vec3(vec3)), true)
    {
    }

    inline Value::Value(MC::BlockPos blockPos)
        : ClassTemplate(new _Value((::BlockPos)blockPos), true)
    {
    }

    inline Value::Value(ItemType^ itemType)
        : ClassTemplate(new _Value(*itemType->NativePtr), true)
    {
    }

    inline Value::Value(BlockType^ blockType)
        : ClassTemplate(new _Value(*blockType->NativePtr), true)
    {
    }

    inline Value::Value(NbtType^ nbtType)
        : ClassTemplate(new _Value(*nbtType->NativePtr), true)
    {
    }

    inline Value::Value(WorldPosType^ posType)
        : ClassTemplate(new _Value(*posType->NativePtr), true)
    {
    }

    inline Value::Value(BlockPosType^ posType)
        : ClassTemplate(new _Value(*posType->NativePtr), true)
    {
    }

    inline Value::Value(double num)
        : ClassTemplate(new _Value(::RemoteCall::NumberType(num)), true)
    {
    }

    inline Value::Value(float num)
        : ClassTemplate(new _Value(::RemoteCall::NumberType(num)), true)
    {
    }

    inline Value::Value(__int64 num)
        : ClassTemplate(new _Value(::RemoteCall::NumberType(num)), true)
    {
    }

    inline Value::Value(int num)
        : ClassTemplate(new _Value(::RemoteCall::NumberType(num)), true)
    {
    }

    inline Value::Value(short num)
        : ClassTemplate(new _Value(::RemoteCall::NumberType(num)), true)
    {
    }

    inline Value::Value(char num)
        : ClassTemplate(new _Value(::RemoteCall::NumberType(num)), true)
    {
    }

    inline Value::Value(unsigned __int64 num)
        : ClassTemplate(new _Value(::RemoteCall::NumberType(num)), true)
    {
    }

    inline Value::Value(unsigned int num)
        : ClassTemplate(new _Value(::RemoteCall::NumberType(num)), true)
    {
    }

    inline Value::Value(unsigned short num)
        : ClassTemplate(new _Value(::RemoteCall::NumberType(num)), true)
    {
    }

    inline Value::Value(unsigned char num)
        : ClassTemplate(new _Value(::RemoteCall::NumberType(num)), true)
    {
    }

    inline Value^ Value::Clone() {
        return gcnew Value(*this);
    }

    inline Value::Value(::RemoteCall::Value const& v)
        :ClassTemplate(new _Value(v), true)
    {
    }

    inline bool Value::IsNull() {
        return NativePtr->index() == (size_t)InstanceType::Null;
    }

    inline bool Value::AsBool(bool% v) {
        if (NativePtr->index() != (size_t)InstanceType::Bool)
            return false;
        v = std::get<bool>(*NativePtr);
        return true;
    }

    inline bool Value::AsString(String^% v) {
        if (NativePtr->index() != (size_t)InstanceType::String)
            return false;
        auto& _v = std::get<std::string>(*NativePtr);
        v = marshalString(_v);
        return true;
    }

    inline bool Value::AsNumberType(NumberType% v) {
        v = NumberType();
        if (NativePtr->index() != (size_t)InstanceType::NumberType)
            return false;
        auto& _v = std::get<::RemoteCall::NumberType>(*NativePtr);
        v = NumberType(*(__int64*)&_v, *(double*)(((uintptr_t)&_v) + sizeof(__int64)));
        return true;
    }

    inline bool Value::AsPlayer(MC::Player^% v) {
        v = nullptr;
        if (NativePtr->index() != (size_t)InstanceType::Player)
            return false;
        v = gcnew MC::Player(std::get<::Player*>(*NativePtr));
        return true;
    }

    inline bool Value::AsActor(MC::Actor^% v) {
        v = nullptr;
        if (NativePtr->index() != (size_t)InstanceType::Actor)
            return false;
        v = gcnew MC::Actor(std::get<::Actor*>(*NativePtr));
        return true;
    }

    inline bool Value::AsBlockActor(MC::BlockActor^% v) {
        v = nullptr;
        if (NativePtr->index() != (size_t)InstanceType::BlockActor)
            return false;
        v = gcnew MC::BlockActor(std::get<::BlockActor*>(*NativePtr));
        return true;
    }

    inline bool Value::AsContainer(MC::Container^% v) {
        v = nullptr;
        if (NativePtr->index() != (size_t)InstanceType::Container)
            return false;
        v = gcnew MC::Container(std::get<::Container*>(*NativePtr));
        return true;
    }

    inline bool Value::AsWorldPosType(WorldPosType^% v) {
        v = nullptr;
        if (NativePtr->index() != (size_t)InstanceType::WorldPosType)
            return false;
        v = gcnew WorldPosType(std::get<::RemoteCall::WorldPosType>(*NativePtr));
        return true;
    }

    inline bool Value::AsBlockPosType(BlockPosType^% v) {
        v = nullptr;
        if (NativePtr->index() != (size_t)InstanceType::BlockPosType)
            return false;
        v = gcnew BlockPosType(std::get<::RemoteCall::BlockPosType>(*NativePtr));
        return true;
    }

    inline bool Value::AsItemType(ItemType^% v) {
        v = nullptr;
        if (NativePtr->index() != (size_t)InstanceType::ItemType)
            return false;
        v = gcnew ItemType(std::get<::RemoteCall::ItemType>(*NativePtr));
        return true;
    }

    inline bool Value::AsBlockType(BlockType^% v) {
        v = nullptr;
        if (NativePtr->index() != (size_t)InstanceType::BlockType)
            return false;
        v = gcnew BlockType(std::get<::RemoteCall::BlockType>(*NativePtr));
        return true;
    }

    inline bool Value::AsNbtType(NbtType^% v) {
        v = nullptr;
        if (NativePtr->index() != (size_t)InstanceType::NbtType)
            return false;
        v = gcnew NbtType(std::get<::RemoteCall::NbtType>(*NativePtr));
        return true;
    }

    inline bool Value::AsContainer(BlockType^% v) {
        v = nullptr;
        if (NativePtr->index() != (size_t)InstanceType::BlockType)
            return false;
        v = gcnew BlockType(std::get<::RemoteCall::BlockType>(*NativePtr));
        return true;
    }

    inline Value^ Value::SetNull() {
        *NativePtr = nullptr_t(nullptr);
        return this;
    }

    inline Value::InstanceType Value::Type::get()
    {
        return InstanceType(NativePtr->index());
    }

    Value^ Value::operator=(bool v) {
        *NativePtr = v;
        return this;
    }

    Value^ Value::operator=(String^ v) {
        *NativePtr = marshalString(v);
        return this;
    }

    Value^ Value::operator=(NumberType v) {
        *NativePtr = v._toNative();
        return this;
    }

    Value^ Value::operator=(MC::Player^ player) {
        *NativePtr = player->NativePtr;
        return this;
    }

    Value^ Value::operator=(MC::Actor^ actor) {
        *NativePtr = actor->NativePtr;
        return this;
    }

    Value^ Value::operator=(MC::BlockActor^ blockActor) {
        *NativePtr = blockActor->NativePtr;
        return this;
    }

    Value^ Value::operator=(MC::Container^ container) {
        *NativePtr = container->NativePtr;
        return this;
    }

    Value^ Value::operator=(WorldPosType^ worldPos) {
        *NativePtr = *worldPos->NativePtr;
        return this;
    }

    Value^ Value::operator=(BlockPosType^ blockPos) {
        *NativePtr = *blockPos->NativePtr;
        return this;
    }

    Value^ Value::operator=(ItemType^ itemType) {
        *NativePtr = *itemType->NativePtr;
        return this;
    }

    Value^ Value::operator=(BlockType^ blockType) {
        *NativePtr = *blockType->NativePtr;
        return this;
    }

    Value^ Value::operator=(NbtType^ nbtType) {
        *NativePtr = *nbtType->NativePtr;
        return this;
    }
    inline String^ Value::ToString() {
        auto type = InstanceType(NativePtr->index());
        String^ info;
        switch (type)
        {
        case InstanceType::Bool:
            info = static_cast<bool>(this).ToString();
            break;
        case InstanceType::String:
            info = operator System::String ^ (this);
            break;
        case InstanceType::Null:
            info = "Null";
            break;
        case InstanceType::NumberType:
        {
            auto& number = std::get<::RemoteCall::NumberType>(*NativePtr);
            info = String::Format("<{0},{1}>", number.f, number.i);
        }
        break;
        case InstanceType::Player:
        {
            auto p = std::get<::Player*>(*NativePtr);
            info = String::Format("{0},{1}", marshalString(p->getRealName()), marshalString(p->getPos().toString()));
        }
        break;
        case InstanceType::Actor:
        {
            auto p = std::get<::Actor*>(*NativePtr);
            info = String::Format("{0},{1}", marshalString(p->getTypeName()), marshalString(p->getPos().toString()));
        }
        break;
        case InstanceType::BlockActor:
        {
            auto p = std::get<::BlockActor*>(*NativePtr);
            info = String::Format("{0},{1}", marshalString(p->getName()), marshalString(p->getPosition().toString()));

        }
        break;
        case InstanceType::Container:
        {
            auto p = std::get<::Container*>(*NativePtr);
            info = String::Format("{0},{1}", marshalString(p->getTypeName()), MC::ContainerType(p->getContainerType()).ToString());
        }
        break;
        case InstanceType::WorldPosType:
        {
            auto& pos = std::get<::RemoteCall::WorldPosType>(*NativePtr);
            info = marshalString(pos.pos.toString() + "," + std::to_string(pos.dimId));
        }
        break;
        case InstanceType::BlockPosType:
        {
            auto& pos = std::get<::RemoteCall::BlockPosType>(*NativePtr);
            info = marshalString(pos.pos.toString() + "," + std::to_string(pos.dimId));
            break;
        }
        case InstanceType::ItemType:
        {
            ItemType^ item;
            this->AsItemType(item);
            info = item->ToString();
        }
        break;
        case InstanceType::BlockType:
        {
            BlockType^ block;
            this->AsBlockType(block);
            info = block->ToString();
        }
        break;
        case InstanceType::NbtType:
        {
            NbtType^ nbt;
            this->AsNbtType(nbt);
            info = nbt->ToString();
        }
        break;
        default:
            break;
        }
        return String::Format("InstanceType:{0},{1}", type, info);
    }
}