#pragma once
#include "include.hpp"
#include "Interfaces.hpp"

namespace LiteLoader::RemoteCall {
    public
    ref class NbtType : ClassTemplate<NbtType, ::RemoteCall::NbtType>, IValue
    {
    internal:
        __ctor_copy(NbtType, ::RemoteCall::NbtType);
        __ctor_move(NbtType, ::RemoteCall::NbtType);
    public:
        NbtType(MC::CompoundTag^ tag)
            : ClassTemplate(new ::RemoteCall::NbtType(tag->NativePtr), true)
        {
        }

        MC::CompoundTag^ Get() {
            return gcnew MC::CompoundTag(NativePtr->get<CompoundTag*>());
        }

    public:
        static operator NbtType ^ (MC::CompoundTag^ v) {
            return gcnew NbtType(v);
        }
        static operator MC::CompoundTag ^ (NbtType^ v) {
            return v->Get();
        }
    internal:
        NbtType(::RemoteCall::NbtType const& v)
            :ClassTemplate(new ::RemoteCall::NbtType(v), true)
        {
        }
    public:
        virtual String^ ToString() override {
            return marshalString(NativePtr->get<::CompoundTag*>()->toSNBT());
        }
    };

    public
    ref class ItemType : ClassTemplate<ItemType, ::RemoteCall::ItemType>, IValue
    {
    internal:
        __ctor_copy(ItemType, ::RemoteCall::ItemType);
        __ctor_move(ItemType, ::RemoteCall::ItemType);
    public:
        ItemType(MC::ItemStack^ item)
            : ClassTemplate(new ::RemoteCall::ItemType(item->NativePtr), true)
        {
        }

        MC::ItemStack^ Get() {
            return gcnew MC::ItemStack(NativePtr->get<::ItemStack*>());
        }
    public:
        static operator ItemType ^ (MC::ItemStack^ v) {
            return gcnew ItemType(v);
        }
        static operator MC::ItemStack ^ (ItemType^ v) {
            return v->Get();
        }
    internal:
        ItemType(::RemoteCall::ItemType const& v)
            :ClassTemplate(new ::RemoteCall::ItemType(v), true)
        {
        }
    public:
        virtual String^ ToString() override {
            auto p = NativePtr->get<ItemStack*>();
            return String::Format("{0},{1}", marshalString(p->getTypeName()), p->getCount());
        }
    };

    public
    ref class BlockType : ClassTemplate<BlockType, ::RemoteCall::BlockType>, IValue
    {
    internal:
        __ctor_copy(BlockType, ::RemoteCall::BlockType);
        __ctor_move(BlockType, ::RemoteCall::BlockType);
    public:
        BlockType(MC::BlockInstance^ block)
            : ClassTemplate(new ::RemoteCall::BlockType(*block->NativePtr), true)
        {
        }
        MC::BlockInstance^ Get() {
            return gcnew MC::BlockInstance(NativePtr->get<::BlockInstance>());
        }
    public:
        static operator BlockType ^ (MC::BlockInstance^ v) {
            return gcnew BlockType(v);
        }
        static operator MC::BlockInstance ^ (BlockType^ v) {
            return v->Get();
        }
    internal:
        BlockType(::RemoteCall::BlockType const& v)
            :ClassTemplate(new ::RemoteCall::BlockType(v), true)
        {
        }
    public:
        virtual String^ ToString() override {
            auto& p = NativePtr->get<::BlockInstance>();
            return String::Format("{0},{1}", marshalString(p.getBlock()->getTypeName()), marshalString(p.getPosition().toString()));
        }
    };

    public
    ref class WorldPosType :ClassTemplate<WorldPosType, ::RemoteCall::WorldPosType>
    {
    internal:
        __ctor_copy(WorldPosType, ::RemoteCall::WorldPosType);
        __ctor_move(WorldPosType, ::RemoteCall::WorldPosType);
    public:
        WorldPosType(MC::Vec3 pos, int dimId)
            :ClassTemplate(::RemoteCall::WorldPosType(pos, dimId)) {}
        WorldPosType(MC::Vec3 pos)
            :ClassTemplate(::RemoteCall::WorldPosType(pos)) {}
        //WorldPosType(KeyValuePair<MC::Vec3, int> pos)
        //    :ClassTemplate(::RemoteCall::WorldPosType(pos.Key, pos.Value)) {}
        WorldPosType(Pair<MC::Vec3, int> pos)
            :ClassTemplate(::RemoteCall::WorldPosType(pos.Key, pos.Value)) {}

        property Vec3% Pos {
            Vec3% get() { return *(Vec3*)&NativePtr->pos; }
        }

        property MC::BlockPos BlockPos {
            MC::BlockPos get() { return MC::BlockPos(MC::Vec3(NativePtr->pos)); }
        }

        property Pair<MC::Vec3, int> PosPair {
            Pair<MC::Vec3, int> get() { return Pair<MC::Vec3, int>(*(MC::Vec3*)&NativePtr->pos, NativePtr->dimId); }
        }

        property Pair<MC::BlockPos, int> BlockPosPair {
            Pair<MC::BlockPos, int> get() { return Pair<MC::BlockPos, int>(BlockPos, NativePtr->dimId); }
        }

        property int DimId {
            int get() { return NativePtr->dimId; }
            void set(int value) { NativePtr->dimId = value; }
        }
    };

    public
    ref class BlockPosType :ClassTemplate<BlockPosType, ::RemoteCall::BlockPosType>
    {
    internal:
        __ctor_copy(BlockPosType, ::RemoteCall::BlockPosType);
        __ctor_move(BlockPosType, ::RemoteCall::BlockPosType);
    public:
        BlockPosType(MC::BlockPos pos)
            :ClassTemplate(::RemoteCall::BlockPosType(pos)) {}
        BlockPosType(MC::BlockPos pos, int dimId)
            :ClassTemplate(::RemoteCall::BlockPosType(pos, dimId)) {}
        BlockPosType(Pair<MC::BlockPos, int> pos)
            :ClassTemplate(::RemoteCall::BlockPosType(pos.Key, pos.Value)) {}

        property MC::BlockPos Pos {
            MC::BlockPos get() { return MC::BlockPos(NativePtr->pos); }
            void set(MC::BlockPos value) { NativePtr->pos = value; }
        }

        property MC::Vec3 Vec3 {
            MC::Vec3 get() { return NativePtr->pos.toVec3(); }
        }

        property Pair<MC::Vec3, int> Vec3Pair {
            Pair<MC::Vec3, int> get() { return Pair<MC::Vec3, int>(Vec3, NativePtr->dimId); }
        }

        property Pair<MC::BlockPos, int> BlockPosPair {
            Pair<MC::BlockPos, int> get() { return Pair<MC::BlockPos, int>(MC::BlockPos(NativePtr->pos), NativePtr->dimId); }
        }

        property int DimId {
            int get() { return NativePtr->dimId; }
            void set(int value) { NativePtr->dimId = value; }
        }
    };



    ref class Valuetype;

    enum class InstanceType : size_t
    {
        Value = 0,
        ArrayType = 1,
        ObjectType = 2,
    };

    [System::AttributeUsage(System::AttributeTargets::Class)]
    public ref class RemoteCallValueTypeAttribute : System::Attribute
    {
    public:
        InstanceType type;
        RemoteCallValueTypeAttribute(InstanceType t)
            : type(t)
        {
        }
    };

    [RemoteCallValueType(InstanceType::ObjectType)]
    public ref class ObjectType : IValueType
    {
    public:
        ObjectType(Dictionary<String^, Valuetype^>^ v)
            : value(v)
        {
        }
        operator Dictionary<String^, Valuetype^> ^ () {
            return value;
        };
        Dictionary<String^, Valuetype^>^ value;
    public:
        virtual String^ ToString() override {
            return value->Count.ToString();
        }
    };

    [RemoteCallValueType(InstanceType::ArrayType)]
    public ref class ArrayType : IValueType
    {
    public:
        ArrayType(List<Valuetype^>^ v)
            :value(v)
        {
        }
        operator List<Valuetype^> ^ () {
            return value;
        }
        List<Valuetype^>^ value;
    public:
        virtual String^ ToString() override {
            return value->Count.ToString();
        }
    };
}
