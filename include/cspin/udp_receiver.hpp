#ifndef CSPIN_INCLUDE_CSPIN_UDP_RECEIVER_HPP_
#define CSPIN_INCLUDE_CSPIN_UDP_RECEIVER_HPP_

#include <iostream>
#include <memory>
#include "boost/array.hpp"
#include "boost/asio.hpp"
#include "boost/bind.hpp"

using boost::asio::ip::udp;
using boost::asio::ip::address;

namespace cspin
{

class UDPReceiver
{
public:
  UDPReceiver(const std::string& ip_address, uint32_t port)
    : endpoint_(address::from_string(ip_address), port)
  {
    socket_ = std::make_shared<udp::socket>(io_service_);
    socket_->open(udp::v4());
    socket_->bind(endpoint_);
  }

  void start()
  {
    receive();
    io_service_.run();
  }

private:
  void receive()
  {
    socket_->async_receive_from(
        boost::asio::buffer(buffer_recv_), endpoint_,
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
      std::cout << "Receive failed: " << error.message() << std::endl;
      return;
    }
    std::cout << "Received: " << std::string(buffer_recv_.begin(), buffer_recv_.begin()+bytes_transferred) << std::endl;
    receive();
  }
  
  boost::asio::io_service io_service_;
  std::shared_ptr<udp::socket> socket_;
  udp::endpoint endpoint_;
  boost::array<char, 4096> buffer_recv_;
};

}

#endif // CSPIN_INCLUDE_CSPIN_UDP_RECEIVER_HPP_
