#ifndef CSPIN_INCLUDE_CSPIN_TIMER_EVENT_HPP_
#define CSPIN_INCLUDE_CSPIN_TIMER_EVENT_HPP_

#include <iostream>
#include <chrono>
#include <functional>
#include <memory>
#include <thread>

namespace cspin
{

class TimerEvent
{
public:
  explicit TimerEvent(const std::chrono::milliseconds& interval, const std::function<void()>& callback, uint32_t priority);
  ~TimerEvent() {
    thread_.join();
  }

  void start();
  void stop();
  void timer_event_callback();

private:
  TimerEvent(const TimerEvent&);
  TimerEvent& operator=(const TimerEvent&);

  std::chrono::high_resolution_clock::duration interval_;
  std::function<void()> callback_;
  uint32_t priority_;
  std::thread thread_;
};

using TimerEventPtr = std::shared_ptr<TimerEvent>;
using TimerEventUPtr = std::unique_ptr<TimerEvent>;
using TimerEventSPtr = std::shared_ptr<TimerEvent>;

}

#endif // CSPIN_INCLUDE_CSPIN_TIMER_EVENT_HPP_
