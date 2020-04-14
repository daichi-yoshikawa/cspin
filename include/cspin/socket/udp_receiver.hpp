#ifndef CSPIN_INCLUDE_CSPIN_SOCKET_UDP_RECEIVER_HPP_
#define CSPIN_INCLUDE_CSPIN_SOCKET_UDP_RECEIVER_HPP_

#include <vector>
#include <memory>

#include "boost/asio.hpp"
#include "boost/bind.hpp"

#include "cspin/socket/receiver.hpp"
#include "cspin/socket/socket_communication.hpp"

namespace cspin
{
namespace socket
{

using boost::asio::ip::udp;

class UDPReceiver : public Receiver
{
public:
  explicit UDPReceiver(const std::string& ip_address, uint16_t port, std::size_t buffer_size = 4096)
    : Receiver(
          CallbackFunctionMap({
              { CallbackType::RECEIVE, defaults::receive_callback },
              { CallbackType::RECEIVE_ERROR, defaults::error_callback }
          })
      ),
      sender_point_(boost::asio::ip::address::from_string(ip_address), port),
      buffer_size_(buffer_size),
      buffer_(buffer_size)
  {
    socket_ = std::make_unique<udp::socket>(io_service_);
    socket_->open(udp::v4());
    socket_->bind(sender_point_);
  }

  ~UDPReceiver() { this->close(); }

  void start() override
  {
    wait_to_receive();
    io_service_.run();
  }

  void close() override { if(socket_ != nullptr) socket_->close(); }

private:
  UDPReceiver(const UDPReceiver&);
  UDPReceiver& operator=(const UDPReceiver&);

  void wait_to_receive()
  {
    socket_->async_receive_from(
        boost::asio::buffer(buffer_), sender_point_,
        boost::bind(
            &UDPReceiver::receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );
  }

  void receive(const boost::system::error_code& error, size_t bytes_transferred)
  {
    if(error)
    {
      this->getCallback(CallbackType::RECEIVE_ERROR)(error.message());
      return;
    }

    this->getCallback(CallbackType::RECEIVE)(std::string(buffer_.begin(), buffer_.begin()+bytes_transferred));
    wait_to_receive();
  }

  boost::asio::io_service io_service_;
  std::unique_ptr<udp::socket> socket_;
  udp::endpoint sender_point_;
  std::vector<char> buffer_;
  std::size_t buffer_size_;
};

using UDPReceiverPtr = std::shared_ptr<UDPReceiver>;
using UDPReceiverUPtr = std::unique_ptr<UDPReceiver>;
using UDPReceiverSPtr = std::shared_ptr<UDPReceiver>;

} // namespace socket
} // namespace cspin

#endif // CSPIN_INCLUDE_CSPIN_SOCKET_UDP_RECEIVER_HPP_
