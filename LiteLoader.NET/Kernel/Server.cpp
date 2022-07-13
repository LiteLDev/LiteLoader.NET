#include "../Header/Server.h"
namespace LLNET::LL
{
inline String^ ServerAPI::GetBdsVersion()
{
    return marshalString(::LL::getBdsVersion());
}

inline int ServerAPI::GetServerProtocolVersion()
{
    return ::LL::getServerProtocolVersion();
}

inline bool ServerAPI::SetServerMotd(String^ d)
{
    return ::LL::setServerMotd(marshalString(d));
}

} // namespace LLNET::LL