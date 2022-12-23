#pragma once
#include "ValueType.hpp"
namespace LiteLoader::RemoteCall {
    using System::Reflection::MethodInfo;
    ref class RemoteCallFunctionRegisterBase {
    internal:
        enum class ValidType {
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
        ref struct FunctionInfo {
            value struct TypeInfo {
                System::Type^ _type;
                ValidType type;
                array<TypeInfo>^ genericArgs;
            };
            TypeInfo returnType;
            array<TypeInfo>^ parameters;
        };
        static Pair<bool, ValidType> _tryGetValidType(System::Type^ t);
        static FunctionInfo::TypeInfo _generateTypeInfo(System::Type^ t);

    public:
        inline static ::RemoteCall::ValueType _double2Native(double val);
        inline static ::RemoteCall::ValueType _float2Native(float val);
        inline static ::RemoteCall::ValueType _int64_t2Native(int64_t val);
        inline static ::RemoteCall::ValueType _int32_t2Native(int32_t val);
        inline static ::RemoteCall::ValueType _int16_t2Native(int16_t val);
        inline static ::RemoteCall::ValueType _int8_t2Native(int8_t val);
        inline static ::RemoteCall::ValueType _uint64_t2Native(uint64_t val);
        inline static ::RemoteCall::ValueType _uint32_t2Native(uint32_t val);
        inline static ::RemoteCall::ValueType _uint16_t2Native(uint16_t val);
        inline static ::RemoteCall::ValueType _uint8_t2Native(uint8_t val);
        inline static ::RemoteCall::ValueType _bool2Native(bool val);
        inline static ::RemoteCall::ValueType _string2Native(String^ val);
        inline static ::RemoteCall::ValueType _NumberType2Native(NumberType val);
        inline static ::RemoteCall::ValueType _Player2Native(MC::Player^ val);
        inline static ::RemoteCall::ValueType _Actor2Native(MC::Actor^ val);
        inline static ::RemoteCall::ValueType _BlockActor2Native(MC::BlockActor^ val);
        inline static ::RemoteCall::ValueType _Container2Native(MC::Container^ val);
        inline static ::RemoteCall::ValueType _Vec32Native(MC::Vec3 val);
        inline static ::RemoteCall::ValueType _BlockPos2Native(MC::BlockPos val);
        inline static ::RemoteCall::ValueType _WorldPosType2Native(WorldPosType^ val);
        inline static ::RemoteCall::ValueType _BlockPosType2Native(BlockPosType^ val);
        inline static ::RemoteCall::ValueType _ItemType2Native(ItemType^ val);
        inline static ::RemoteCall::ValueType _BlockType2Native(BlockType^ val);
        inline static ::RemoteCall::ValueType _NbtType2Native(NbtType^ val);
        inline static ::RemoteCall::ValueType _null2Native();

#define __VALUE std::get<::RemoteCall::Value>(((::RemoteCall::ValueType*)val)->value)
#define __NUMBERTYPE std::get<::RemoteCall::NumberType>(__VALUE)

        inline static double _Native2double(void* val);
        inline static float _Native2float(void* val);
        inline static int64_t _Native2int64_t(void* val);
        inline static int32_t _Native2int32_t(void* val);
        inline static int16_t _Native2int16_t(void* val);
        inline static int8_t _Native2int8_t(void* val);
        inline static uint64_t _Native2uint64_t(void* val);
        inline static uint32_t _Native2uint32_t(void* val);
        inline static uint16_t _Native2uint16_t(void* val);
        inline static uint8_t _Native2uint8_t(void* val);
        inline static bool _Native2bool(void* val);
        inline static String^ _Native2string(void* val);
        inline static NumberType _Native2NumberType(void* val);
        inline static MC::Player^ _Native2Player(void* val);
        inline static MC::Actor^ _Native2Actor(void* val);
        inline static MC::BlockActor^ _Native2BlockActor(void* val);
        inline static MC::Container^ _Native2Container(void* val);
        inline static MC::Vec3 _Native2Vec3(void* val);
        inline static MC::BlockPos _Native2BlockPos(void* val);
        inline static WorldPosType^ _Native2WorldPosType(void* val);
        inline static BlockPosType^ _Native2BlockPosType(void* val);
        inline static ItemType^ _Native2ItemType(void* val);
        inline static BlockType^ _Native2BlockType(void* val);
        inline static NbtType^ _Native2NbtType(void* val);
        inline static System::Object^ _Native2null(void* val);

        inline static std::vector<::RemoteCall::ValueType> _create_ArrayType();
        inline static void _delete_ArrayType(void* vec);
        inline static void _delete_ValueType(void* valuetype);
        inline static void _emplace_back(void* vec, void* val);
        inline static ::RemoteCall::ValueType _ArrayType2ValueType(void* arr);
        inline static void* _get_pArrayType_form_ValueType(void* val);
        inline static int _get_ValueArrayType_size(void* arr);
        inline static int _get_ArrayType_size(void* arr);
        inline static void* _get_pValueType_from_ValueArrayType_by_index(void* val, int index);
        inline static void* _get_pValueType_from_ArrayType_by_index(void* arr, int index);
        inline static void _ValueType_move_to_ValueType(void* val1, void* val2);

#define __METHOD_INFO(name,funcname)\
static initonly MethodInfo^ name = RemoteCallFunctionRegisterBase::typeid->GetMethod(#funcname)

#define METHOD_INFO(typeName) \
__METHOD_INFO(typeName##2Native,_##typeName##2Native);\
__METHOD_INFO(Native2##typeName,_##Native2##typeName)

        METHOD_INFO(double);
        METHOD_INFO(float);
        METHOD_INFO(int64_t);
        METHOD_INFO(int32_t);
        METHOD_INFO(int16_t);
        METHOD_INFO(int8_t);
        METHOD_INFO(uint64_t);
        METHOD_INFO(uint32_t);
        METHOD_INFO(uint16_t);
        METHOD_INFO(uint8_t);
        METHOD_INFO(bool);
        METHOD_INFO(string);
        METHOD_INFO(NumberType);
        METHOD_INFO(Player);
        METHOD_INFO(Actor);
        METHOD_INFO(BlockActor);
        METHOD_INFO(Container);
        METHOD_INFO(Vec3);
        METHOD_INFO(BlockPos);
        METHOD_INFO(WorldPosType);
        METHOD_INFO(BlockPosType);
        METHOD_INFO(ItemType);
        METHOD_INFO(BlockType);
        METHOD_INFO(NbtType);
        METHOD_INFO(null);

        __METHOD_INFO(emplace_back, _emplace_back);
        __METHOD_INFO(create_ArrayType, _create_ArrayType);
        __METHOD_INFO(delete_ArrayType, _delete_ArrayType);
        __METHOD_INFO(delete_ValueType, _delete_ValueType);
        __METHOD_INFO(ArrayType2ValueType, _ArrayType2ValueType);
        __METHOD_INFO(get_ValueArrayType_size, _get_ValueArrayType_size);
        __METHOD_INFO(get_ArrayType_size, _get_ArrayType_size);
        __METHOD_INFO(get_pValueType_from_ValueArrayType_by_index, _get_pValueType_from_ValueArrayType_by_index);
        __METHOD_INFO(get_pValueType_from_ArrayType_by_index, _get_pValueType_from_ArrayType_by_index);
        __METHOD_INFO(get_pArrayType_form_ValueType, _get_pArrayType_form_ValueType);
        __METHOD_INFO(ValueType_move_to_ValueType, _ValueType_move_to_ValueType);
    };
}

inline Pair<bool, LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::ValidType> LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_tryGetValidType(System::Type^ t)
{
    using RTN = Pair<bool, ValidType>;

    if (t == double::typeid)
        return RTN(true, ValidType::Double);
    if (t == float::typeid)
        return RTN(true, ValidType::Float);
    if (t == int64_t::typeid)
        return RTN(true, ValidType::Int64);
    if (t == int32_t::typeid)
        return RTN(true, ValidType::Int32);
    if (t == int16_t::typeid)
        return RTN(true, ValidType::Int16);
    if (t == int8_t::typeid)
        return RTN(true, ValidType::Int8);
    if (t == uint64_t::typeid)
        return RTN(true, ValidType::UInt64);
    if (t == uint32_t::typeid)
        return RTN(true, ValidType::UInt32);
    if (t == uint16_t::typeid)
        return RTN(true, ValidType::UInt16);
    if (t == uint8_t::typeid)
        return RTN(true, ValidType::UInt8);

    if (t == bool::typeid)
        return RTN(true, ValidType::Bool);
    if (t == String::typeid)
        return RTN(true, ValidType::String);
    if (t == NumberType::typeid)
        return RTN(true, ValidType::NumberType);
    if (t == MC::Player::typeid)
        return RTN(true, ValidType::Player);
    if (t == MC::Actor::typeid)
        return RTN(true, ValidType::Actor);
    if (t == MC::BlockActor::typeid)
        return RTN(true, ValidType::BlockActor);
    if (t == MC::Container::typeid)
        return RTN(true, ValidType::Container);
    if (t == MC::Vec3::typeid)
        return RTN(true, ValidType::Vec3);
    if (t == MC::BlockPos::typeid)
        return RTN(true, ValidType::BlockPos);


    if (t == WorldPosType::typeid)
        return RTN(true, ValidType::WorldPosType);
    if (t == BlockPosType::typeid)
        return RTN(true, ValidType::BlockPosType);
    if (t == ItemType::typeid)
        return RTN(true, ValidType::ItemType);
    if (t == BlockType::typeid)
        return RTN(true, ValidType::BlockType);
    if (t == NbtType::typeid)
        return RTN(true, ValidType::NbtType);
    if (t == void::typeid)
        return RTN(true, ValidType::Void);

    if (t->Namespace == "System.Collections.Generic" && t->Name == "List`1")
        return RTN(true, ValidType::List);

    if (t->Namespace == "System.Collections.Generic" && t->Name == "Dictionary`2") {
        auto genericTypes = t->GenericTypeArguments;
        if (genericTypes[0] != String::typeid) {
            return RTN(false, ValidType::Invalid);
        }
        return RTN(true, ValidType::Dictionary);

    }
    return RTN(false, ValidType::Invalid);
}

inline LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::FunctionInfo::TypeInfo LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_generateTypeInfo(System::Type^ t)
{

    auto type = _tryGetValidType(t);
    if (!type.Key)
        throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;

    auto ret = FunctionInfo::TypeInfo();
    ret._type = t;
    ret.type = type.Value;

    switch (type.Value)
    {
    case ValidType::List:
    {
        ret.genericArgs = gcnew array<FunctionInfo::TypeInfo>(1);

        ret.genericArgs[0] = _generateTypeInfo(t->GenericTypeArguments[0]);
    }
    break;

    case ValidType::Dictionary:
    {
        ret.genericArgs = gcnew array<FunctionInfo::TypeInfo>(2);

        ret.genericArgs[0] = _generateTypeInfo(t->GenericTypeArguments[0]);
        ret.genericArgs[1] = _generateTypeInfo(t->GenericTypeArguments[1]);
    }
    break;

    default:
        break;
    case ValidType::Invalid:
        throw gcnew LiteLoader::NET::InvalidRemoteCallTypeException;
    }

    return ret;
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline std::vector<::RemoteCall::ValueType> LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_create_ArrayType()
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__);
#endif // REMOTECALL_DEBUG

    return std::vector<::RemoteCall::ValueType>();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline void LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_delete_ArrayType(void* vec)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(vec).ToString());
#endif // REMOTECALL_DEBUG

    ((std::vector<::RemoteCall::ValueType>*)vec)->~vector();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline void LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_delete_ValueType(void* valuetype)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(valuetype).ToString());
#endif // REMOTECALL_DEBUG

    delete ((::RemoteCall::ValueType*)valuetype);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_double2Native(double val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + val);
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::pack(val);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_float2Native(float val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + val);
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::pack(val);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_int64_t2Native(int64_t val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + val);
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::pack(val);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_int32_t2Native(int32_t val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + val);

    auto value = ::RemoteCall::pack(val);
    Console::WriteLine(std::get<::RemoteCall::NumberType>(std::get<::RemoteCall::Value>(::RemoteCall::pack(val).value)).get<int32_t>());
    Console::WriteLine("addess vec:" + ((intptr_t)&value).ToString());
    return value;

#else
    return ::RemoteCall::pack(val);

#endif // REMOTECALL_DEBUG

}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_int16_t2Native(int16_t val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + val);
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::pack(val);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_int8_t2Native(int8_t val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + val);
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::pack(val);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_uint64_t2Native(uint64_t val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + val);
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::pack(val);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_uint32_t2Native(uint32_t val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + val);
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::pack(val);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_uint16_t2Native(uint16_t val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + val);
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::pack(val);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_uint8_t2Native(uint8_t val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + val);
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::pack(val);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_bool2Native(bool val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + val);
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::pack(val);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_string2Native(String^ val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + val);
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::pack(marshalString(val));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_NumberType2Native(NumberType val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__);
#endif // REMOTECALL_DEBUG

    return static_cast<NumberType>(val)._toNative();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Player2Native(MC::Player^ val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__);
#endif // REMOTECALL_DEBUG

    return static_cast<MC::Player^>(val)->NativePtr;
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Actor2Native(MC::Actor^ val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__);
#endif // REMOTECALL_DEBUG

    return static_cast<MC::Actor^>(val)->NativePtr;
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_BlockActor2Native(MC::BlockActor^ val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__);
#endif // REMOTECALL_DEBUG

    return static_cast<MC::BlockActor^>(val)->NativePtr;
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Container2Native(MC::Container^ val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__);
#endif // REMOTECALL_DEBUG

    return static_cast<MC::Container^>(val)->NativePtr;
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Vec32Native(MC::Vec3 val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + val);
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::packValue(std::make_pair(::Vec3(static_cast<MC::Vec3>(val)), 0));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_BlockPos2Native(MC::BlockPos val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__);
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::packValue(std::make_pair(::BlockPos(static_cast<MC::BlockPos>(val)), 0));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_WorldPosType2Native(WorldPosType^ val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__);
#endif // REMOTECALL_DEBUG

    return *static_cast<WorldPosType^>(val)->NativePtr;
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_BlockPosType2Native(BlockPosType^ val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__);
#endif // REMOTECALL_DEBUG

    return *static_cast<BlockPosType^>(val)->NativePtr;
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_ItemType2Native(ItemType^ val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__);
#endif // REMOTECALL_DEBUG

    return *static_cast<ItemType^>(val)->NativePtr;
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_BlockType2Native(BlockType^ val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__);
#endif // REMOTECALL_DEBUG

    return *static_cast<BlockType^>(val)->NativePtr;
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_NbtType2Native(NbtType^ val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__);
#endif // REMOTECALL_DEBUG

    return *static_cast<NbtType^>(val)->NativePtr;
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_null2Native()
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__);
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::ValueType(nullptr);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline double LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2double(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return __NUMBERTYPE.get<double>();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline float LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2float(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return __NUMBERTYPE.get<float>();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline int64_t LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2int64_t(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return __NUMBERTYPE.get<int64_t>();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline int32_t LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2int32_t(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return __NUMBERTYPE.get<int32_t>();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline int16_t LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2int16_t(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return __NUMBERTYPE.get<int16_t>();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline int8_t LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2int8_t(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return __NUMBERTYPE.get<int8_t>();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline uint64_t LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2uint64_t(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return __NUMBERTYPE.get<uint64_t>();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline uint32_t LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2uint32_t(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return __NUMBERTYPE.get<uint32_t>();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline uint16_t LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2uint16_t(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return __NUMBERTYPE.get<uint16_t>();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline uint8_t LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2uint8_t(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return __NUMBERTYPE.get<uint8_t>();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline bool LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2bool(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return std::get<bool>(__VALUE);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline String^ LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2string(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return marshalString(std::get<std::string>(__VALUE));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline LiteLoader::RemoteCall::NumberType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2NumberType(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return NumberType(__NUMBERTYPE);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline MC::Player^ LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2Player(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return gcnew MC::Player(std::get<::Player*>(__VALUE));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline MC::Actor^ LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2Actor(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return gcnew MC::Actor(std::get<::Actor*>(__VALUE));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline MC::BlockActor^ LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2BlockActor(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return gcnew MC::BlockActor(std::get<::BlockActor*>(__VALUE));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline MC::Container^ LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2Container(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return gcnew MC::Container(std::get<::Container*>(__VALUE));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline MC::Vec3 LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2Vec3(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return MC::Vec3(std::get<::RemoteCall::WorldPosType>(__VALUE).pos);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline MC::BlockPos LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2BlockPos(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return MC::BlockPos(std::get<::RemoteCall::BlockPosType>(__VALUE).pos);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline LiteLoader::RemoteCall::WorldPosType^ LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2WorldPosType(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return gcnew WorldPosType(std::get<::RemoteCall::WorldPosType>(__VALUE));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline LiteLoader::RemoteCall::BlockPosType^ LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2BlockPosType(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return gcnew BlockPosType(std::get<::RemoteCall::BlockPosType>(__VALUE));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline LiteLoader::RemoteCall::ItemType^ LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2ItemType(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return gcnew ItemType(std::get<::RemoteCall::ItemType>(__VALUE));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline LiteLoader::RemoteCall::BlockType^ LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2BlockType(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return gcnew BlockType(std::get<::RemoteCall::BlockType>(__VALUE));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline LiteLoader::RemoteCall::NbtType^ LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2NbtType(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return gcnew NbtType(std::get<::RemoteCall::NbtType>(__VALUE));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline System::Object^ LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_Native2null(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return nullptr;
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline void LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_emplace_back(void* vec, void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(vec).ToString() + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    ((::std::vector<::RemoteCall::ValueType>*)vec)->emplace_back(std::move(*(::RemoteCall::ValueType*)val));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline ::RemoteCall::ValueType LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_ArrayType2ValueType(void* arr)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(arr).ToString());
#endif // REMOTECALL_DEBUG

    return ::RemoteCall::ValueType(std::move(*(std::vector<::RemoteCall::ValueType>*)arr));
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline void* LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_get_pArrayType_form_ValueType(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return &std::get<::RemoteCall::ValueType::ArrayType>(((::RemoteCall::ValueType*)val)->value);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline int LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_get_ValueArrayType_size(void* val)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return (int)std::get<::RemoteCall::ValueType::ArrayType>(((::RemoteCall::ValueType*)val)->value).size();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline void* LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_get_pValueType_from_ValueArrayType_by_index(void* val, int index)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val).ToString());
#endif // REMOTECALL_DEBUG

    return &(std::get<::RemoteCall::ValueType::ArrayType>(((::RemoteCall::ValueType*)val)->value)[index]);
}

inline void* LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_get_pValueType_from_ArrayType_by_index(void* arr, int index) {
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(arr).ToString());
#endif // REMOTECALL_DEBUG

    return &((*(::RemoteCall::ValueType::ArrayType*)arr)[index]);
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline int LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_get_ArrayType_size(void* arr)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(arr).ToString());
#endif // REMOTECALL_DEBUG

    return (int)((std::vector<::RemoteCall::ValueType>*)arr)->size();
}

[MethodImpl(MethodImplOptions::AggressiveInlining)]
inline void LiteLoader::RemoteCall::RemoteCallFunctionRegisterBase::_ValueType_move_to_ValueType(void* val1, void* val2)
{
#ifdef REMOTECALL_DEBUG
    REMOTECALL_DEBUG_INFO(__FUNCSIG__ + intptr_t(val1).ToString() + intptr_t(val2).ToString());
#endif // REMOTECALL_DEBUG

    * (::RemoteCall::ValueType*)val2 = std::move(*(::RemoteCall::ValueType*)val1);
}