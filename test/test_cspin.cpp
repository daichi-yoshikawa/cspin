#include <iostream>
#include <string>

#include <chrono>
#include <functional>

#include "cspin/shared_memory.hpp"
#include "cspin/timer_event.hpp"

using namespace cspin;

class MyRobot
{
public:
  void ctrl_one_step()
  {
    uint32_t x = 0;
    for(uint32_t i = 0; i < 10; ++i)
    {
      x = i;
      std::cout << i << std::endl;
    }
  }

private:
};

int main(int argc, char** argv)
{
  SharedMemory<double> shm = SharedMemory<double>("shm", true);
  std::cout << "Hello, cspin." << std::endl;

  MyRobot robot;
  std::chrono::milliseconds interval(1);
  std::function<void()> callback = std::bind(&MyRobot::ctrl_one_step, &robot);

  TimerEventPtr te = std::make_shared<TimerEvent>(interval, callback, 1);
  using clock = std::chrono::high_resolution_clock;
  te->start();

  double a = 40.0;
  shm.write(a);
  double b = 20.0;
  std::cout << b << std::endl;
  shm.read(b);
  std::cout << b << std::endl;

  return 0;
}
