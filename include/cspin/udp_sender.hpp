#ifndef CSPIN_INCLUDE_CSPIN_UDP_SENDER_HPP_
#define CSPIN_INCLUDE_CSPIN_UDP_SENDER_HPP_

#include <tuple>
#include <memory>
#include <string>

#include "boost/asio.hpp"

namespace cspin
{

using boost::asio::ip::udp;

class UDPSender
{
public:
  explicit UDPSender(const std::string& ip_address, uint32_t port);
  ~UDPSender() { this->close(); }

  struct Result
  {
    std::size_t sent_bytes;
    boost::system::error_code err;
  };

  Result send(const std::string& data) const;
  void reopen() { socket_->open(udp::v4()); }
  void close() { if(socket_ != nullptr) socket_->close(); }

private:
  UDPSender(const UDPSender&);
  UDPSender& operator=(UDPSender&);

  boost::asio::io_service io_service_;
  std::unique_ptr<udp::socket> socket_;
  udp::endpoint destination_point_;
};

using UDPSenderPtr = std::shared_ptr<UDPSender>;
using UDPSenderUPtr = std::unique_ptr<UDPSender>;
using UDPSenderSPtr = std::shared_ptr<UDPSender>;

}

#endif // CSPIN_INCLUDE_CSPIN_UDP_SENDER_HPP_
