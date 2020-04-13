#include <functional>

#include "cspin/socket/udp_receiver.hpp"

using namespace cspin::socket;

class Robot
{
public:
  void receive_callback(const std::string& recv_data)
  {
    std::cout << "MyRobot::receive_callback is called: " << recv_data << std::endl;
  }

  void error_callback(const std::string& err_msg)
  {
    std::cerr << "MyRobot::error_callback is called: " << err_msg << std::endl;
  }
};

int main(int argc, char** argv)
{
  Robot robot;
  std::function<void(const std::string&)> receive_callback = std::bind(&Robot::receive_callback, &robot, std::placeholders::_1);
  std::function<void(const std::string&)> receive_error_callback = std::bind(&Robot::error_callback, &robot, std::placeholders::_1);

  UDPReceiver receiver("127.0.0.1", 12345);
  receiver.setCallback(CallbackType::RECEIVE, receive_callback);
  receiver.setCallback(CallbackType::RECEIVE_ERROR, receive_error_callback);
  receiver.run();

  return 0;
}
