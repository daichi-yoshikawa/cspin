#include <functional>

#include "cspin/socket/tcp_server.hpp"

using namespace cspin::socket;

class Robot
{
public:
  Robot() : cnt_(0) {}

  void accept_callback(const std::string&)
  {
    std::cout << "MyRobot::accept_callback is called." << std::endl;
  }

  void receive_callback(const std::string& recv_data)
  {
    ++cnt_;
    std::cout << "[" << cnt_ << "] MyRobot::receive_callback is called: " << recv_data << std::endl;
  }

  void accept_error_callback(const std::string& err_msg)
  {
    std::cout << "MyRobot::accept_callback is called: " << err_msg << std::endl;
  }

  void receive_error_callback(const std::string& err_msg)
  {
    std::cerr << "MyRobot::receive_error_callback is called: " << err_msg << std::endl;
  }

private:
  uint32_t cnt_;
};

int main(int argc, char** argv)
{
  Robot robot;
  CallbackFunction accept_callback = std::bind(&Robot::accept_callback, &robot, std::placeholders::_1);
  CallbackFunction receive_callback = std::bind(&Robot::receive_callback, &robot, std::placeholders::_1);
  CallbackFunction accept_error_callback = std::bind(&Robot::accept_error_callback, &robot, std::placeholders::_1);
  CallbackFunction receive_error_callback = std::bind(&Robot::receive_error_callback, &robot, std::placeholders::_1);

  TCPServer server("127.0.0.1", 33333);

  server.setCallback(CallbackType::ACCEPT, accept_callback);
  server.setCallback(CallbackType::RECEIVE, receive_callback);
  server.setCallback(CallbackType::ACCEPT_ERROR, accept_error_callback);
  server.setCallback(CallbackType::RECEIVE_ERROR, receive_error_callback);
  server.run();

  return 0;
}
