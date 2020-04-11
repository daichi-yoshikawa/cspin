#ifndef CSPIN_INCLUDE_CSPIN_TCP_SERVER_HPP_
#define CSPIN_INCLUDE_CSPIN_TCP_SERVER_HPP_

#include <memory>

namespace cspin
{

class TCPServer
{
public:
private:
};

using TCPServerPtr = std::shared_ptr<TCPServer>;
using TCPServerUPtr = std::unique_ptr<TCPServer>;
using TCPServerSPtr = std::shared_ptr<TCPServer>;

}

#endif // CSPIN_INCLUDE_CSPIN_TCP_SERVER_HPP_
