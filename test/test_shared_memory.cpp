#include <iostream>
#include <string>

#include <chrono>
#include <functional>

#include "cspin/named_mutex.hpp"
#include "cspin/scoped_lock.hpp"
#include "cspin/shared_memory.hpp"
#include "cspin/timer_event.hpp"

using namespace cspin;

class MyRobot
{
public:
  MyRobot()
    : shm_(std::make_shared<SharedMemory<double>>("my_shm_name", true)) {}
  //mutex_(std::make_shared<NamedMutex>("my_mutex_name")) {}

  void func()
  {
    double a = 0.0;
    {
      //ScopedLock<NamedMutex> lock(*mutex_);
      shm_->read(a);
      std::cout << "MyRobot read value : " << a << std::endl;
    }

    {
      //ScopedLock<NamedMutex> lock(*mutex_);
      std::cout << "MyRobot write value : -3.0" << std::endl;
      shm_->write(-3.0);
    }
  }

private:
  SharedMemoryPtr<double> shm_;
  //NamedMutexPtr mutex_;
};

class YourRobot
{
public:
  YourRobot()
    : shm_(std::make_shared<SharedMemory<double>>("my_shm_name", true)) {}
  //mutex_(std::make_shared<NamedMutex>("my_mutex_name")) {}

  void func()
  {
    double a = 0.0;
    {
      //ScopedLock<NamedMutex> lock(*mutex_);
      shm_->read(a);
      std::cout << "YourRobot read value : " << a << std::endl;
    }

    {
      //ScopedLock<NamedMutex> lock(*mutex_);
      std::cout << "YourRobot write value : 5.0" << std::endl;
      shm_->write(5.0);
    }
  }

private:
  SharedMemoryPtr<double> shm_;
  //NamedMutexPtr mutex_;
};

int main()
{
  MyRobot my_robot;
  std::chrono::milliseconds interval1(200);
  std::function<void()> callback1 = std::bind(&MyRobot::func, &my_robot);
  TimerEventPtr te1 = std::make_shared<TimerEvent>(interval1, callback1, 1);
  te1->start();

  YourRobot your_robot;
  std::chrono::milliseconds interval2(300);
  std::function<void()> callback2 = std::bind(&YourRobot::func, &your_robot);
  TimerEventPtr te2 = std::make_shared<TimerEvent>(interval2, callback2, 1);
  te2->start();

  return 0;
}
