#ifndef CSPIN_INCLUDE_CSPIN_SOCKET_UDP_SENDER_HPP_
#define CSPIN_INCLUDE_CSPIN_SOCKET_UDP_SENDER_HPP_

#include <memory>
#include <string>

#include "boost/asio.hpp"

#include "cspin/socket/socket_communication.hpp"

namespace cspin
{
namespace socket
{

using boost::asio::ip::udp;

class UDPSender : public SocketCommunication
{
public:
  explicit UDPSender(const std::string& ip_address, uint16_t port)
    : SocketCommunication(
        CallbackFunctionMap({
            { CallbackType::SEND, defaults::empty_callback },
            { CallbackType::SEND_ERROR, defaults::empty_callback }
        })
      ),
      receiver_point_(boost::asio::ip::address::from_string(ip_address), port)
  {
    socket_ = std::make_unique<udp::socket>(io_service_);
    socket_->open(udp::v4());
  }

  ~UDPSender() { this->close(); }

  void send(const std::string& send_data) override
  {
    boost::system::error_code error;
    socket_->send_to(boost::asio::buffer(send_data), receiver_point_, 0, error);
    if(error)
    {
      this->getCallback(CallbackType::SEND_ERROR)(error.message());
    }
    this->getCallback(CallbackType::SEND)(send_data);
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

} // namespace socket
} // namespace cspin

#endif // CSPIN_INCLUDE_CSPIN_SOCKET_UDP_SENDER_HPP_
