#include <iostream>

#include <chrono>
#include <functional>

#include "cspin/timer_event.hpp"

using namespace cspin;

void func()
{
  std::cout << "func is called." << std::endl;
}

class MyRobot
{
public:
  void func()
  {
    std::cout << "MyRobot::func is called." << std::endl;
  }
};

int main()
{
  std::cout << "Hello, cspin." << std::endl;

  /* You can register a function which has no arugment and no return value
     as a callback function(void func() {...}).
     Interval can be specified by chrono.
     In this example, func is called every 20 milliseconds.
     The 3rd argument of TimerEvent means priority but not
     supported in current version. Will be implemented in near future. */
  std::chrono::milliseconds interval1(200);
  TimerEventPtr te1 = std::make_shared<TimerEvent>(interval1, func, 1);
  te1->start();

  /* You can register class method as a callback function.
     The method is not supposed to have no argument and no return value.
     (void func() {...}) */
  MyRobot robot;
  std::function<void()> callback = std::bind(&MyRobot::func, &robot);
  std::chrono::milliseconds interval2(600);  
  TimerEventPtr te2 = std::make_shared<TimerEvent>(interval2, callback, 1);
  te2->start();

  return 0;
}
