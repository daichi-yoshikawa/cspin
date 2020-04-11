#ifndef CSPIN_INCLUDE_CSPIN_UDP_RECEIVER_HPP_
#define CSPIN_INCLUDE_CSPIN_UDP_RECEIVER_HPP_

#include <iostream>
#include <functional>
#include <memory>
#include <array>
#include "boost/asio.hpp"
#include "boost/bind.hpp"

namespace cspin
{

using boost::asio::ip::udp;
using boost::asio::ip::address;

template<size_t N>
class UDPReceiver
{
public:
  explicit UDPReceiver(const std::string& ip_address, uint32_t port)
    : sender_point_(boost::asio::ip::address::from_string(ip_address), port),
      receive_callback_(UDPReceiver::default_receive_callback),
      error_callback_(UDPReceiver::default_error_callback)
  {
    socket_ = std::make_unique<udp::socket>(io_service_);
    socket_->open(udp::v4());
    socket_->bind(sender_point_);
  }

  ~UDPReceiver() { this->close(); }

  static void default_receive_callback(const std::string& recv_data)
  {
    std::cout << "Received : " << recv_data << std::endl;
  }

  static void default_error_callback(const std::string& err_msg)
  {
    std::cerr << err_msg << std::endl;
  }

  void run()
  {
    receive();
    io_service_.run();
  }

  void setReceiveCallback(const std::function<void(const std::string&)>& callback)
  {
    receive_callback_ = callback;
  }

  void setErrorCallback(const std::function<void(const std::string&)>& callback)
  {
    error_callback_ = callback;
  }

  void reopen()
  {
    if(socket_ == nullptr) std::make_unique<udp::socket>(io_service_);
    socket_->open(udp::v4());
    socket_->bind(sender_point_);
  }

  void close() { if(socket_ != nullptr) socket_->close(); }

private:
  UDPReceiver(const UDPReceiver&);
  UDPReceiver& operator=(const UDPReceiver&);

  void receive()
  {
    socket_->async_receive_from(
      boost::asio::buffer(buffer_), sender_point_,
      boost::bind(
        &UDPReceiver::receive_impl, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred)
    );
  }

  void receive_impl(const boost::system::error_code& error, size_t bytes_transferred)
  {
    if(error)
    {
      error_callback_(error.message());
      return;
    }
    receive_callback_(std::string(buffer_.begin(), buffer_.begin()+bytes_transferred));
    receive();
  }

  boost::asio::io_service io_service_;
  std::unique_ptr<udp::socket> socket_;
  udp::endpoint sender_point_;
  std::array<char, N> buffer_;
  std::function<void(const std::string&)> receive_callback_;
  std::function<void(const std::string&)> error_callback_;
};

}

#endif // CSPIN_INCLUDE_CSPIN_UDP_RECEIVER_HPP_
