#ifndef CSPIN_INCLUDE_CSPIN_SOCKET_SENDER_HPP_
#define CSPIN_INCLUDE_CSPIN_SOCKET_SENDER_HPP_

#include <memory>

#include "cspin/socket/socket_communication.hpp"

namespace cspin
{
namespace socket
{

class Sender : private SocketCommunication
{
public:
  explicit Sender(const CallbackFunctionMap& callbacks) : SocketCommunication(callbacks) {}
  virtual ~Sender() {}

  void setCallback(CallbackType callback_type, const CallbackFunction& callback)
  {
    SocketCommunication::setCallback(callback_type, callback);
  }

  virtual void send(const std::string& send_data) = 0;
  virtual void close() = 0;
  virtual void try_connect() = 0;

protected:
  CallbackFunction& getCallback(CallbackType callback_type)
  {
    return SocketCommunication::getCallback(callback_type);
  }

private:
  Sender();
  Sender(const Sender&);
  Sender& operator=(const Sender&);
};

using SenderPtr = std::shared_ptr<Sender>;
using SenderUPtr = std::unique_ptr<Sender>;
using SenderSPtr = std::shared_ptr<Sender>;

} // namespace socket
} // namespace cspin

#endif // CSPIN_INCLUDE_CSPIN_SOCKET_SENDER_HPP_
