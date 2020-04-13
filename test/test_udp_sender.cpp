#include <chrono>

#include "cspin/timer_event.hpp"
#include "cspin/socket/udp_sender.hpp"

using namespace cspin::socket;

void func()
{
  static UDPSender sender("127.0.0.1", 12345);
  static uint32_t cnt = 0;

  std::string data = "test message <`1234567890-=~!@#$%^&*()_+qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM[]\{}|;':\",./<>?";
  sender.send(data);

  if(cnt > 10)
  {
    cnt = 0;
    std::cout << "Reopen socket." << std::endl;
    sender.reopen();
  }
  else if(cnt == 5)
  {
    std::cout << "Close socket." << std::endl;
    sender.close();
  }
  ++cnt;
}

int main(int argc, char** argv)
{
  std::chrono::milliseconds interval(1000);
  cspin::TimerEventPtr te = std::make_shared<cspin::TimerEvent>(interval, func, 1);
  te->start();
}
