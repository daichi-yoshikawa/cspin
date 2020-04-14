#ifndef CSPIN_INCLUDE_CSPIN_SOCKET_SOCKET_COMMUNICATION_HPP_
#define CSPIN_INCLUDE_CSPIN_SOCKET_SOCKET_COMMUNICATION_HPP_

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>

#include "cspin/exception.hpp"

namespace cspin
{
namespace socket
{

namespace defaults
{
static void empty_callback(const std::string& msg) {}

static void callback(const std::string& msg)
{
  std::cout << msg << std::endl;
}

static void send_callback(const std::string& data)
{
  std::cout << "Sent: " << data << std::endl;
}

static void receive_callback(const std::string& data)
{
  std::cout << "Received: " << data << std::endl;
}

static void error_callback(const std::string& err_msg)
{
  std::cerr << "Error: " << err_msg << std::endl;
}
} // namespace defaults

enum class CallbackType
{
  ACCEPT,
  CONNECT,
  SEND,
  RECEIVE,
  ACCEPT_ERROR,
  CONNECT_ERROR,
  SEND_ERROR,
  RECEIVE_ERROR,
};

using CallbackFunction = std::function<void(const std::string&)>;
using CallbackFunctionMap = std::map<CallbackType, CallbackFunction>;

class SocketCommunication
{
public:
  explicit SocketCommunication(const CallbackFunctionMap& callbacks) : callbacks_(callbacks.begin(), callbacks.end()) {}
  virtual ~SocketCommunication() {}

  void setCallback(CallbackType callback_type, const CallbackFunction& callback)
  {
    if(callbacks_.find(callback_type) == callbacks_.end())
    {
      callbacks_.insert({callback_type, callback});
    }
    callbacks_[callback_type] = callback;
  }

  CallbackFunction& getCallback(CallbackType callback_type) { return callbacks_[callback_type]; }

private:
  SocketCommunication();
  SocketCommunication(const SocketCommunication&);
  SocketCommunication& operator=(const SocketCommunication&);
  CallbackFunctionMap callbacks_;
};

using SocketCommunicationPtr = std::shared_ptr<SocketCommunication>;
using SocketCommunicationUPtr = std::unique_ptr<SocketCommunication>;
using SocketCommunicationSPtr = std::shared_ptr<SocketCommunication>;

} // namespace socket
} // namespace cspin

#endif // CSPIN_INCLUDE_CSPIN_SOCKET_SOCKET_COMMUNICATION_HPP_
