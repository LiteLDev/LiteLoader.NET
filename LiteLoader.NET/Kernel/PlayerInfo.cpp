#include <LiteLoader.NET/Header/PlayerInfo.hpp>

namespace LLNET::PlayerInfo {
    inline bool PlayerInfoAPI::Insert(System::String^ name, System::String^ xuid, System::String^ uuid)
    {
        return ::PlayerInfo::insert(marshalString(name), marshalString(xuid), marshalString(uuid));
    }
    inline System::String^ PlayerInfoAPI::GetXuid(System::String^ name)
    {
        return marshalString(::PlayerInfo::getXuid(marshalString(name)));
    }
    inline System::String^ PlayerInfoAPI::GetUUID(System::String^ name)
    {
        return marshalString(::PlayerInfo::getUUID(marshalString(name)));
    }
    inline System::String^ PlayerInfoAPI::FromXuid(System::String^ name)
    {
        return marshalString(::PlayerInfo::fromXuid(marshalString(name)));
    }
    inline System::String^ PlayerInfoAPI::FromUUID(System::String^ name)
    {
        return marshalString(::PlayerInfo::fromUUID(marshalString(name)));
    }
    inline void PlayerInfoAPI::ForEachInfo(ForEachInfoHandler^ callback)
    {
        _callback = callback;
        if (_callback == nullptr)
            return;
        NativeforEachInfoDelegate^ decallback = gcnew NativeforEachInfoDelegate(&PlayerInfoAPI::forEachInfoCallback);
        GCHandle gch = GCHandle::Alloc(decallback);
        auto pcallback = Marshal::GetFunctionPointerForDelegate(decallback).ToPointer();
        ::PlayerInfo::forEachInfo(static_cast<bool(*)(std::string_view, std::string_view, std::string_view)>(pcallback));
        gch.Free();
    }
    bool PlayerInfoAPI::forEachInfoCallback(std::string_view name, std::string_view xuid, std::string_view uuid)
    {
        return _callback(marshalString((std::string)name), marshalString((std::string)xuid), marshalString((std::string)uuid));
    }
}