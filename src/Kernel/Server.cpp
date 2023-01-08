#include <src/Header/Server.hpp>
namespace LiteLoader
{
inline String^ ServerAPI::BdsVersion::get()
{
    return marshalString(::ll::getBdsVersion());
}

inline int ServerAPI::ServerProtocolVersion::get()
{
    return ::ll::getServerProtocolVersion();
}

inline bool ServerAPI::SetServerMotd(String^ d)
{
    return ::ll::setServerMotd(marshalString(d));
}

} // namespace LiteLoader