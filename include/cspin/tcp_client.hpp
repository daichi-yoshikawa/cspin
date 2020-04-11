#ifndef CSPIN_INCLUDE_CSPIN_TCP_CLIENT_HPP_
#define CSPIN_INCLUDE_CSPIN_TCP_CLIENT_HPP_

#include <memory>

namespace cspin
{

class TCPClient
{
public:
private:
};

using TCPClientPtr = std::shared_ptr<TCPClient>;
using TCPClientUPtr = std::unique_ptr<TCPClient>;
using TCPClientSPtr = std::shared_ptr<TCPClient>;

}

#endif // CSPIN_INCLUDE_CSPIN_TCP_CLIENT_HPP_
