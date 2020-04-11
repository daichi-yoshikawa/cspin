#ifndef CSPIN_INCLUDE_CSPIN_UDP_SENDER_HPP_
#define CSPIN_INCLUDE_CSPIN_UDP_SENDER_HPP_

#include <tuple>
#include <memory>
#include <string>

#include "boost/asio.hpp"

using boost::asio::ip::udp;

namespace cspin
{

class UDPSender
{
public:
  explicit UDPSender(const std::string& ip_address, uint32_t port)
    : receiver_point_(boost::asio::ip::address::from_string(ip_address), port)
  {
    socket_ = std::make_unique<udp::socket>(io_service_);
    socket_->open(udp::v4());
  }
  
  ~UDPSender() { this->close(); }

  struct Result
  {
    std::size_t sent_bytes;
    boost::system::error_code err;
  };

  Result send(const std::string& data) const
  {
    Result result;
    result.sent_bytes = socket_->send_to(boost::asio::buffer(data), receiver_point_, 0, result.err);
    return result;
  }

  void reopen() {
    if(socket_ == nullptr) std::make_unique<udp::socket>(io_service_);
    socket_->open(udp::v4());
  }

  void close() { if(socket_ != nullptr) socket_->close(); }

private:
  UDPSender(const UDPSender&);
  UDPSender& operator=(UDPSender&);

  boost::asio::io_service io_service_;
  std::unique_ptr<udp::socket> socket_;
  udp::endpoint receiver_point_;
};

using UDPSenderPtr = std::shared_ptr<UDPSender>;
using UDPSenderUPtr = std::unique_ptr<UDPSender>;
using UDPSenderSPtr = std::shared_ptr<UDPSender>;

}

#endif // CSPIN_INCLUDE_CSPIN_UDP_SENDER_HPP_
