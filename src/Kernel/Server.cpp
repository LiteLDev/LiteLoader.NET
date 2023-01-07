#include <src/Header/Server.hpp>
namespace LiteLoader
{
inline String^ ServerAPI::GetBdsVersion()
{
    return marshalString(::ll::getBdsVersion());
}

inline int ServerAPI::GetServerProtocolVersion()
{
    return ::ll::getServerProtocolVersion();
}

inline bool ServerAPI::SetServerMotd(String^ d)
{
    return ::ll::setServerMotd(marshalString(d));
}

} // namespace LiteLoader