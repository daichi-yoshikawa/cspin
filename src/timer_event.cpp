#include "cspin/timer_event.hpp"

namespace cspin
{

TimerEvent::TimerEvent(const std::chrono::milliseconds& interval, const std::function<void()>& callback, uint32_t priority)
  : interval_(std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(interval)), callback_(callback), priority_(priority)
{

}

void TimerEvent::start()
{
  // Get start time.
  thread_ = std::thread(std::bind(&TimerEvent::timer_event_callback, this));
  // Get consumed time.
  // Sleep.
}

void TimerEvent::stop()
{
}

void TimerEvent::timer_event_callback()
{
  using clock = std::chrono::high_resolution_clock;

  while(true)
  {
    clock::time_point start = clock::now();
    callback_();
    clock::duration duration = clock::now() - start;
    std::this_thread::sleep_for(interval_ - duration);
  }
}

}
