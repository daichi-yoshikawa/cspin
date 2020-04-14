#ifndef CSPIN_INCLUDE_CSPIN_SOCKET_RECEIVER_HPP_
#define CSPIN_INCLUDE_CSPIN_SOCKET_RECEIVER_HPP_

#include <memory>

#include "cspin/socket/socket_communication.hpp"

namespace cspin
{
namespace socket
{

class Receiver : private SocketCommunication
{
public:
  explicit Receiver(const CallbackFunctionMap& callbacks) : SocketCommunication(callbacks) {}
  virtual ~Receiver() {}

  void setCallback(CallbackType callback_type, const CallbackFunction& callback)
  {
    SocketCommunication::setCallback(callback_type, callback);
  }

  virtual void start() = 0;
  virtual void close() = 0;

protected:
  CallbackFunction& getCallback(CallbackType callback_type)
  {
    return SocketCommunication::getCallback(callback_type);
  }

private:
  Receiver();
  Receiver(const Receiver&);
  Receiver& operator=(const Receiver&);
};

using ReceiverPtr = std::shared_ptr<Receiver>;
using ReceiverUPtr = std::unique_ptr<Receiver>;
using ReceiverSPtr = std::shared_ptr<Receiver>;

} // namespace socket
} // namespace cspin

#endif // CSPIN_INCLUDE_CSPIN_SOCKET_RECEIVER_HPP_
