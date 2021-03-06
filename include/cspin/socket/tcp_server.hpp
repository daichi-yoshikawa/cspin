#ifndef CSPIN_INCLUDE_CSPIN_SOCKET_TCP_SERVER_HPP_
#define CSPIN_INCLUDE_CSPIN_SOCKET_TCP_SERVER_HPP_

#include <memory>

#include "boost/asio.hpp"
#include "boost/bind.hpp"

#include "cspin/socket/receiver.hpp"
#include "cspin/socket/socket_communication.hpp"

namespace cspin
{
namespace socket
{

using boost::asio::ip::tcp;

class TCPServer : public Receiver
{
public:
  explicit TCPServer(const std::string& ip_address, uint16_t port, std::size_t buffer_size = 4096)
    : Receiver(
          CallbackFunctionMap({
              { CallbackType::ACCEPT, defaults::callback },
              { CallbackType::RECEIVE, defaults::receive_callback },
              { CallbackType::ACCEPT_ERROR, defaults::error_callback },
              { CallbackType::RECEIVE_ERROR, defaults::error_callback }
          })
      ),
      client_point_(boost::asio::ip::address::from_string(ip_address), port),
      buffer_size_(buffer_size)
  {
    acceptor_ = std::make_unique<tcp::acceptor>(io_service_, client_point_);
    socket_ = std::make_unique<tcp::socket>(io_service_);
  }

  ~TCPServer() { this->close(); }

  void start() override
  {
    wait_to_accept();
    io_service_.run();
  }

  void close() override { if(socket_ != nullptr) socket_->close(); }

private:
  TCPServer(const TCPServer&);
  TCPServer& operator=(const TCPServer&);

  void wait_to_accept()
  {
    acceptor_->async_accept(
        *socket_, boost::bind(
            &TCPServer::accept, this, boost::asio::placeholders::error)
    );
  }

  void accept(const boost::system::error_code& error)
  {
    if(error)
    {
      this->getCallback(CallbackType::ACCEPT_ERROR)(error.message());
      socket_->close();
      wait_to_accept();
      return;
    }
    this->getCallback(CallbackType::ACCEPT)("");
    wait_to_receive();
  }

  void wait_to_receive()
  {
    boost::asio::async_read(
      *socket_,
      buffer_,
      boost::asio::transfer_at_least(1),
      boost::bind(
          &TCPServer::receive, this,
          boost::asio::placeholders::error)
    );
  }

  void receive(const boost::system::error_code& error)
  {
    if(error)
    {
      this->getCallback(CallbackType::RECEIVE_ERROR)(error.message());
      socket_->close();
      wait_to_accept();
      return;
    }

    this->getCallback(CallbackType::RECEIVE)(boost::asio::buffer_cast<const char*>(buffer_.data()));
    buffer_.consume(buffer_.size());
    wait_to_receive();
  }

  boost::asio::io_service io_service_;
  std::unique_ptr<tcp::acceptor> acceptor_;
  std::unique_ptr<tcp::socket> socket_;
  tcp::endpoint client_point_;
  boost::asio::streambuf buffer_;
  size_t buffer_size_;
};

using TCPServerPtr = std::shared_ptr<TCPServer>;
using TCPServerUPtr = std::unique_ptr<TCPServer>;
using TCPServerSPtr = std::shared_ptr<TCPServer>;

} // namespace socket
} // namespace cspin

#endif // CSPIN_INCLUDE_CSPIN_SOCKET_TCP_SERVER_HPP_
