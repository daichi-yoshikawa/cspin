#ifndef CSPIN_INCLUDE_CSPIN_UDP_SENDER_HPP_
#define CSPIN_INCLUDE_CSPIN_UDP_SENDER_HPP_

#include <iostream>
#include <memory>
#include <string>

#include "boost/asio.hpp"

namespace cspin
{

using boost::asio::ip::udp;
using boost::asio::ip::address;

class UDPSender
{
public:
  UDPSender(const std::string& ip_address, uint32_t port)
    : endpoint_(address::from_string(ip_address), port)
  {
    socket_ = std::make_shared<udp::socket>(io_service_);
    socket_->open(udp::v4());
  }

  ~UDPSender()
  {
    if(socket_ != nullptr) socket_->close();
  }

  void send(const std::string& data)
  {
    boost::system::error_code err;
    auto sent = socket_->send_to(boost::asio::buffer(data), endpoint_, 0, err);
  }

  void close()
  {
    socket_->close();
  }

private:
  boost::asio::io_service io_service_;
  std::shared_ptr<udp::socket> socket_;
  udp::endpoint endpoint_;
};

}

#endif // CSPIN_INCLUDE_CSPIN_UDP_SENDER_HPP_
