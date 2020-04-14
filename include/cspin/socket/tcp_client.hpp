#ifndef CSPIN_INCLUDE_CSPIN_SOCKET_TCP_CLIENT_HPP_
#define CSPIN_INCLUDE_CSPIN_SOCKET_TCP_CLIENT_HPP_

#include <memory>
#include <string>

#include "boost/asio.hpp"
#include "boost/bind.hpp"

#include "cspin/socket/socket_communication.hpp"

namespace cspin
{
namespace socket
{

using boost::asio::ip::tcp;

class TCPClient : public SocketCommunication
{
public:
  explicit TCPClient(const std::string& ip_address, uint16_t port)
    : SocketCommunication(
          CallbackFunctionMap({
              { CallbackType::CONNECT, defaults::callback },
              { CallbackType::SEND, defaults::send_callback },
              { CallbackType::CONNECT_ERROR, defaults::error_callback },
              { CallbackType::SEND_ERROR, defaults::error_callback },
          })
      ),
      server_point_(boost::asio::ip::address::from_string(ip_address), port),
      is_connected_(false)
  {
    socket_ = std::make_unique<tcp::socket>(io_service_);
  }

  ~TCPClient() { this->close(); }

  void send(const std::string& send_data) override
  {
    if(!is_connected_) this->connect();
    if(!is_connected_) return;

    boost::system::error_code error;
    boost::asio::write(
        *socket_, boost::asio::buffer(send_data), error);

    if(error)
    {
      is_connected_ = false;
      this->getCallback(CallbackType::SEND_ERROR)(error.message());
      socket_->close();
    }
    else
    {
      this->getCallback(CallbackType::SEND)(send_data);
    }
  }

  void try_connect() override { this->connect(); }

  void close() override { if(socket_ != nullptr) socket_->close(); }

private:
  TCPClient(const TCPClient&);
  TCPClient& operator=(const TCPClient&);

  void connect()
  {
    boost::system::error_code error;
    socket_->connect(server_point_, error);

    if(error)
    {
      is_connected_ = false;
      this->getCallback(CallbackType::CONNECT_ERROR)(error.message());
      socket_->close();
    }
    else
    {
      is_connected_ = true;
      this->getCallback(CallbackType::CONNECT)("");
    }
  }

  boost::asio::io_service io_service_;
  std::unique_ptr<tcp::socket> socket_;
  tcp::endpoint server_point_;
  std::string buffer_;
  bool is_connected_;
};

using TCPClientPtr = std::shared_ptr<TCPClient>;
using TCPClientUPtr = std::unique_ptr<TCPClient>;
using TCPClientSPtr = std::shared_ptr<TCPClient>;

} // namespace socket
} // namespace cspin

#endif // CSPIN_INCLUDE_CSPIN_SOCKET_TCP_CLIENT_HPP_
