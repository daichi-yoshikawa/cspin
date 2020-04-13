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

  void run() override
  {
    wait_to_connect();
    io_service_.run();
  }

  void send(const std::string& send_data) override
  {
    boost::asio::async_write(
      *socket_, boost::asio::buffer(send_data),
      boost::bind(
        &TCPClient::sent, this, send_data,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred)
    );
  }

  bool is_connected() const override { return is_connected_; }

  void close() override { if(socket_ != nullptr) socket_->close(); }

private:
  TCPClient(const TCPClient&);
  TCPClient& operator=(const TCPClient&);

  void wait_to_connect()
  {
    socket_->async_connect(
      server_point_, boost::bind(&TCPClient::connect, this, boost::asio::placeholders::error)
    );
  }
  
  void connect(const boost::system::error_code& error)
  {
    if(error)
    {
      this->getCallback(CallbackType::CONNECT_ERROR)(error.message());
      wait_to_connect();
      return;
    }
    is_connected_ = true;
    this->getCallback(CallbackType::CONNECT)("");
  }

  void sent(const std::string& send_data, const boost::system::error_code& error, size_t bytes_transferred)
  {
    if(error)
    {
      this->getCallback(CallbackType::SEND_ERROR)(error.message());
    }
    this->getCallback(CallbackType::SEND)(send_data);
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
