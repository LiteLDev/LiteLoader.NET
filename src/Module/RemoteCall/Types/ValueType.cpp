#include "ValueType.hpp"

#include <src\Header\MC\Player.hpp>
#include <src\Header\MC\BlockActor.hpp>
#include <src\Header\MC\Container.hpp>

#include "ItemType.hpp"
#include "BlockType.hpp"
#include "NbtType.hpp"
#include "WorldPosType.hpp"
#include "BlockPosType.hpp"

namespace LiteLoader::RemoteCall
{
    using number_type = ::RemoteCall::NumberType;
    using array_type = ::RemoteCall::ValueType::ArrayType;
    using object_type = ::RemoteCall::ValueType::ObjectType;
    using value_type = ::RemoteCall::ValueType;
    using world_pos_type = ::RemoteCall::WorldPosType;
    using block_pos_type = ::RemoteCall::BlockPosType;
    using item_type = ::RemoteCall::ItemType;
    using block_type = ::RemoteCall::BlockType;
    using nbt_type = ::RemoteCall::NbtType;
    using value = ::RemoteCall::Value;

    inline Valuetype::Valuetype()
        : ClassTemplate(new _T(), true)
    {
    }

    inline Valuetype::Valuetype(Valuetype% v)
        : ClassTemplate(new _T(*v.NativePtr), true)
    {
    }
    inline Valuetype::Valuetype(Value^ v)
        : ClassTemplate(new _T(*v->NativePtr), true)
    {
    }

    inline Valuetype::Valuetype(array<Valuetype^>^ v)
    {
        auto len = (int)v->Length;
        std::vector<_T> vec;
        for (int i = 0; i < len; i++)
        {
            vec[i] = (*v[i]->NativePtr);
        }
        NativePtr = new _T(std::move(vec));
        OwnsNativeInstance = true;
    }

    inline Valuetype::Valuetype(List<Valuetype^>^ v)
    {
        auto len = v->Count;
        std::vector<_T> vec;
        for (int i = 0; i < len; i++)
        {
            vec[i] = (*v[i]->NativePtr);
        }
        NativePtr = new _T(std::move(vec));
        OwnsNativeInstance = true;
    }

    inline Valuetype::Valuetype(List<String^>^ v)
    {
        auto len = v->Count;
        std::vector<_T> vec;
        for (int i = 0; i < len; i++)
        {
            vec[i] = (marshalString(v[i]));
        }
        NativePtr = new _T(std::move(vec));
        OwnsNativeInstance = true;
    }

    inline Valuetype::Valuetype(List<NumberType>^ v)
    {
        auto len = v->Count;
        std::vector<_T> vec;
        for (int i = 0; i < len; i++)
        {
            vec[i] = (v[i]._toNative());
        }
        NativePtr = new _T(std::move(vec));
        OwnsNativeInstance = true;
    }

    inline Valuetype::Valuetype(Dictionary<String^, Valuetype^>^ v)
    {
        auto len = v->Count;
        std::unordered_map<std::string, _T> umap;

        auto enumerator = v->GetEnumerator();
        while (enumerator.MoveNext())
        {
            auto% pair = enumerator.Current;
            umap[marshalString(pair.Key)] = *pair.Value->NativePtr;
        }
        NativePtr = new _T(std::move(umap));
        OwnsNativeInstance = true;
    }

    inline Valuetype::Valuetype(bool v)
        :ClassTemplate(new _T(::RemoteCall::pack(v)), true)
    {
    }

    inline Valuetype::Valuetype(String^ v)
        : ClassTemplate(new _T(::RemoteCall::pack(marshalString(v))), true)
    {
    }

    inline Valuetype::Valuetype(NumberType v)
        : ClassTemplate(new _T(::RemoteCall::pack(v._toNative())), true)

    {
    }

    inline Valuetype::Valuetype(MC::Player^ v)
        : ClassTemplate(new _T(::RemoteCall::pack(v->NativePtr)), true)
    {
    }

    inline Valuetype::Valuetype(MC::Actor^ v)
        : ClassTemplate(new _T(::RemoteCall::pack(v->NativePtr)), true)
    {
    }

    inline Valuetype::Valuetype(MC::BlockActor^ v)
        : ClassTemplate(new _T(::RemoteCall::pack(v->NativePtr)), true)
    {
    }

    inline Valuetype::Valuetype(MC::Container^ v)
        : ClassTemplate(new _T(::RemoteCall::pack(v->NativePtr)), true)
    {
    }

    inline Valuetype::Valuetype(WorldPosType^ v)
        : ClassTemplate(new _T(::RemoteCall::pack(world_pos_type(v))), true)
    {
    }

    inline Valuetype::Valuetype(BlockPosType^ v)
        : ClassTemplate(new _T(::RemoteCall::pack(*v->NativePtr)), true)
    {
    }

    inline Valuetype::Valuetype(ItemType^ v)
        : ClassTemplate(new _T(::RemoteCall::pack(*v->NativePtr)), true)
    {
    }

    inline Valuetype::Valuetype(BlockType^ v)
        : ClassTemplate(new _T(::RemoteCall::pack(*v->NativePtr)), true)
    {
    }

    inline Valuetype::Valuetype(NbtType^ v)
        : ClassTemplate(new _T(::RemoteCall::pack(*v->NativePtr)), true)
    {
    }

    generic<typename T> where T : IValueType
        inline T Valuetype::Get()
    {
        auto attrs
            = (T::typeid)->GetCustomAttributes(RemoteCallValueTypeAttribute::typeid, false);
        if (attrs->Length == 0)
            throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
        auto attr = static_cast<RemoteCallValueTypeAttribute^>(attrs[0]);
        switch (attr->type)
        {

        case InstanceType::ArrayType:
        {
            if (NativePtr->value.index() != (size_t)InstanceType::ArrayType)
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;

            auto& vec = std::get<::RemoteCall::ValueType::ArrayType>(NativePtr->value);
            auto ret = gcnew ArrayType(Parse(vec));
            return T(ret);
        }
        break;

        case InstanceType::ObjectType:
        {
            if (NativePtr->value.index() != (size_t)InstanceType::ObjectType)
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;

            auto& umap = std::get<::RemoteCall::ValueType::ObjectType>(NativePtr->value);
            auto ret = gcnew ObjectType(Parse(umap));
            return T(ret);
        }
        break;

        case InstanceType::Value:
        {
            if (NativePtr->value.index() != (size_t)InstanceType::Value)
                throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;

            auto& val = std::get<::RemoteCall::Value>(NativePtr->value);
            auto ret = gcnew Value(val);
            return T(ret);
        }
        break;

        }
        throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
    }

    inline String^ Valuetype::ToString() {
        auto type = InstanceType(NativePtr->value.index());

        String^ info = nullptr;
        switch (type)
        {
        case InstanceType::Value:
        {
            Value^ val;
            this->AsValue(val);
            info = "<" + "Value" + L',' + val->ToString() + ">";

        }
        break;
        case InstanceType::ArrayType:
        {
            ArrayType^ arr;
            this->AsArrayType(arr);
            info = "<" + "ArrayType" + L',' + arr->ToString() + ">";
        }
        break;
        case InstanceType::ObjectType:
        {
            ObjectType^ obj;
            this->AsObjectType(obj);
            info = "<" + "ObjectType" + L',' + obj->ToString() + ">";
        }
        break;
        }
        return info;
    }

    inline Valuetype::__ObjectType^ Valuetype::Parse(::RemoteCall::ValueType::ObjectType const& val) {
        auto ret = gcnew __ObjectType;
        for (auto& [k, v] : val) {
            ret->Add(marshalString(k), gcnew Valuetype(v));
        }
        return ret;
    }

    inline Valuetype::__ArrayType^ Valuetype::Parse(::RemoteCall::ValueType::ArrayType const& v) {
        auto len = (int)v.size();
        auto ret = gcnew __ArrayType(len);
        for (auto& i : v) {
            ret->Add(gcnew Valuetype(i));
        }
        return ret;
    }

    InstanceType Valuetype::Type::get()
    {
        return InstanceType(NativePtr->value.index());
    }

    inline bool Valuetype::AsArrayType(ArrayType^% v) {
        v = nullptr;
        if (NativePtr->value.index() != (size_t)InstanceType::ArrayType)
            return false;

        auto& vec = std::get<::RemoteCall::ValueType::ArrayType>(NativePtr->value);
        v = gcnew ArrayType(Parse(vec));
        return true;
    }

    inline bool Valuetype::AsObjectType(ObjectType^% v) {
        v = nullptr;
        if (NativePtr->value.index() != (size_t)InstanceType::ObjectType)
            return false;

        auto& umap = std::get<::RemoteCall::ValueType::ObjectType>(NativePtr->value);
        v = gcnew ObjectType(Parse(umap));
        return true;
    }

    inline bool Valuetype::AsValue(Value^% v) {
        v = nullptr;
        if (NativePtr->value.index() != (size_t)InstanceType::Value)
            return false;

        v = gcnew Value(std::get<::RemoteCall::Value>(NativePtr->value));
        return true;
    }

    inline Valuetype::Valuetype(Dictionary<String^, String^>^ v)
    {
        auto len = v->Count;
        ::RemoteCall::ValueType::ObjectType umap;
        for each (auto var in v)
        {
            umap.emplace(marshalString(var.Key), marshalString(var.Value));
        }
        NativePtr = new _T(std::move(umap));
        OwnsNativeInstance = true;
    }

    inline Valuetype::Valuetype(Dictionary<String^, NumberType>^ v)
    {
        auto len = v->Count;
        ::RemoteCall::ValueType::ObjectType umap;
        for each (auto var in v)
        {
            umap.emplace(marshalString(var.Key), var.Value._toNative());
        }
        NativePtr = new _T(std::move(umap));
        OwnsNativeInstance = true;
    }
}