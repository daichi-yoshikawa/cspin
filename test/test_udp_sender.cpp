#include <chrono>

#include "cspin/timer_event.hpp"
#include "cspin/udp_sender.hpp"

using namespace cspin;

void func()
{
  static UDPSender sender("127.0.0.1", 12345);

  std::string data = "test message <`1234567890-=~!@#$%^&*()_+qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM[]\{}|;':\",./<>?";
  sender.send(data);
}

int main(int argc, char** argv)
{
  std::chrono::milliseconds interval(10);
  TimerEventPtr te = std::make_shared<TimerEvent>(interval, func, 1);
  te->start();
}
