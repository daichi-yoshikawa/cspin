#include <functional>
#include <chrono>

#include "cspin/timer_event.hpp"
#include "cspin/socket/tcp_client.hpp"

using namespace cspin::socket;

class Robot
{
public:
  Robot() : client_("127.0.0.1", 33333), cnt_(0)
  {
    CallbackFunction connect_callback = std::bind(&Robot::connect_callback, this);
    CallbackFunction send_callback = std::bind(&Robot::send_callback, this, std::placeholders::_1);
    CallbackFunction connect_error_callback = std::bind(&Robot::connect_error_callback, this, std::placeholders::_1);
    CallbackFunction send_error_callback = std::bind(&Robot::send_error_callback, this, std::placeholders::_1);

    client_.setCallback(CallbackType::CONNECT, connect_callback);
    client_.setCallback(CallbackType::SEND, send_callback);
    client_.setCallback(CallbackType::CONNECT_ERROR, connect_error_callback);
    client_.setCallback(CallbackType::SEND_ERROR, send_error_callback);

    client_.run();
  }

  void func()
  {
    if(!client_.is_connected())
    {
      std::cout << "Waiting to connect ..." << std::endl;
      return;
    }

    std::string data = "test message <`1234567890-=~!@#$%^&*()_+qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM[]\{}|;':\",./<>?";

    if(cnt_ > 10)
    {
      //cnt_ = 0;
      //std::cout << "Reconnect socket." << std::endl;
      //client_.reconnect();
    }
    else if(cnt_ == 5)
    {
      //std::cout << "Disconnect socket." << std::endl;
      //client_.disconnect();
    }
    else
    {
      std::cout << "Send data." << std::endl;
      client_.send(data);
    }
    ++cnt_;
  }

  void connect_callback()
  {
    std::cout << "Robot::connect_callback is called: Connected." << std::endl;
  }

  void send_callback(const std::string& send_data)
  {
    std::cout << "Robot::send_callback is called: " << send_data << std::endl;
  }

  void connect_error_callback(const std::string& err_msg)
  {
    std::cout << "Robot::connect_error_callback is called: " << err_msg << std::endl;
  }

  void send_error_callback(const std::string& err_msg)
  {
    std::cout << "Robot::send_error_callback is called: " << err_msg << std::endl;
  }

private:
  TCPClient client_;
  uint32_t cnt_;
};


int main(int argc, char** argv)
{
  Robot robot;
  std::chrono::milliseconds interval(1000);
  std::function<void()> timer_event_callback = std::bind(&Robot::func, &robot);
  cspin::TimerEventPtr te = std::make_shared<cspin::TimerEvent>(interval, timer_event_callback, 1);
  te->start();
}
