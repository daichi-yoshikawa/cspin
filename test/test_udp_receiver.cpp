#include <functional>

#include "cspin/socket/socket_communication.hpp"
#include "cspin/socket/udp_receiver.hpp"

using namespace cspin::socket;

class Robot
{
public:
  Robot() : cnt_(0) {}

  void receive_callback(const std::string& recv_data)
  {
    ++cnt_;
    std::cout << "[" << cnt_ << "] MyRobot::receive_callback is called: " << recv_data << std::endl;
  }

  void error_callback(const std::string& err_msg)
  {
    std::cerr << "MyRobot::error_callback is called: " << err_msg << std::endl;
  }

private:
  uint32_t cnt_;
};

int main(int argc, char** argv)
{
  Robot robot;
  CallbackFunction receive_callback = std::bind(&Robot::receive_callback, &robot, std::placeholders::_1);
  CallbackFunction receive_error_callback = std::bind(&Robot::error_callback, &robot, std::placeholders::_1);

  SocketCommunicationPtr receiver = std::make_shared<UDPReceiver>("127.0.0.1", 12345);

  receiver->setCallback(CallbackType::RECEIVE, receive_callback);
  receiver->setCallback(CallbackType::RECEIVE_ERROR, receive_error_callback);
  receiver->run();

  return 0;
}
