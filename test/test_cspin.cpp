#include <iostream>
#include <string>

#include <chrono>
#include <functional>

#include "cspin/shared_memory.hpp"
#include "cspin/timer_event.hpp"
#include "cspin/udp_client.hpp"

using namespace cspin;

void func()
{
  //std::cout << 2 << std::endl;
}

class MyRobot
{
public:
  void ctrl_one_step()
  {
    //std::cout << 1 << std::endl;
  }
};

int main(int argc, char** argv)
{
  SharedMemory<double> shm = SharedMemory<double>("shm", true);
  std::cout << "Hello, cspin." << std::endl;

  MyRobot robot;
  std::chrono::milliseconds interval1(10);
  std::function<void()> callback = std::bind(&MyRobot::ctrl_one_step, &robot);

  TimerEventPtr te1 = std::make_shared<TimerEvent>(interval1, callback, 1);
  te1->start();
  std::chrono::milliseconds interval2(20);
  TimerEventPtr te2 = std::make_shared<TimerEvent>(interval2, func, 1);
  te2->start();

  double a = 40.0;
  shm.write(a);
  double b = 20.0;
  std::cout << b << std::endl;
  shm.read(b);
  std::cout << b << std::endl;

  UDPClient<std::string> udp_client("localhost", "5000", 10);

  return 0;
}
