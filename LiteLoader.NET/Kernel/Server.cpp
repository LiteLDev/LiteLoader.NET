#include "../Header/Server.h"
namespace LLNET::LL
{
inline String^ ServerAPI::GetBdsVersion()
{
    return marshalString<Encoding::E_UTF8>(::LL::getBdsVersion());
}

inline int ServerAPI::GetServerProtocolVersion()
{
    return ::LL::getServerProtocolVersion();
}

inline bool ServerAPI::SetServerMotd(String^ d)
{
    return ::LL::setServerMotd(marshalString<Encoding::E_UTF8>(d));
}

} // namespace LLNET::LL