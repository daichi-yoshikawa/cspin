#include <iostream>
#include "cspin/udp_sender.hpp"

using namespace cspin;

UDPSender::UDPSender(const std::string& ip_address, uint32_t port)
  : destination_point_(boost::asio::ip::address::from_string(ip_address), port)
{
  socket_ = std::make_unique<udp::socket>(io_service_);
  socket_->open(udp::v4());
}

UDPSender::Result UDPSender::send(const std::string& data) const
{
  UDPSender::Result result;
  result.sent_bytes = socket_->send_to(boost::asio::buffer(data), destination_point_, 0, result.err);
  return result;
}
