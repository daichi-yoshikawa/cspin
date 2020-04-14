#include <chrono>
#include <functional>
#include <string>

#include "cspin/timer_event.hpp"
#include "cspin/socket/sender.hpp"
#include "cspin/socket/udp_sender.hpp"

using namespace cspin::socket;

class Robot
{
public:
  Robot() : sender_(std::make_shared<UDPSender>("127.0.0.1", 12345)), cnt_(0)
  {
    CallbackFunction send_callback = std::bind(&Robot::send_callback, this, std::placeholders::_1);
    CallbackFunction send_error_callback = std::bind(&Robot::send_error_callback, this, std::placeholders::_1);

    sender_->setCallback(CallbackType::SEND, send_callback);
    sender_->setCallback(CallbackType::SEND_ERROR, send_error_callback);
  }

  void send()
  {
    ++cnt_;
    std::string send_data = "test message <`1234567890-=~!@#$%^&*()_+qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM[]\{}|;':\",./<>?";
    sender_->send(send_data);

    if(cnt_ > 10)
    {
      cnt_ = 0;
      std::cout << "Try connect socket." << std::endl;
      sender_->try_connect();
    }
    else if(cnt_ == 5)
    {
      std::cout << "Close socket." << std::endl;
      sender_->close();
    }
  }

  void send_callback(const std::string& send_data)
  {
    std::cout << "[" << cnt_ << "] MyRobot::send_callback is called: " << send_data << std::endl;
  }

  void send_error_callback(const std::string& err_msg)
  {
    std::cerr << "MyRobot::error_callback is called: " << err_msg << std::endl;
  }

private:
  SenderPtr sender_;
  uint32_t cnt_;
};

int main(int argc, char** argv)
{
  Robot robot;
  std::chrono::milliseconds interval(1000);
  std::function<void()> te_callback = std::bind(&Robot::send, &robot);
  cspin::TimerEventPtr te = std::make_shared<cspin::TimerEvent>(interval, te_callback, 1);
  te->start();
}
