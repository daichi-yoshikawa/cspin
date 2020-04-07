#ifndef CSPIN_INCLUDE_CSPIN_SHARED_MEMORY_HPP_
#define CSPIN_INCLUDE_CSPIN_SHARED_MEMORY_HPP_

#include <iostream>
#include <string>
#include <memory>

#include <boost/interprocess/managed_shared_memory.hpp>

#include "cspin/scoped_lock.hpp"
#include "cspin/named_mutex.hpp"

namespace ipc = boost::interprocess;

namespace cspin
{

template<typename T>
void write_with_lock(T* shm_data, const T& data, std::shared_ptr<NamedMutex>& mutex_)
{
  ScopedLock<NamedMutex> lock(*mutex_);
  *shm_data = data;
}

template<typename T>
void write_without_lock(T* shm_data, const T& data, std::shared_ptr<NamedMutex>& mutex_)
{
  *shm_data = data;
}

template<typename T>
void read_with_lock(T* shm_data, T& data, std::shared_ptr<NamedMutex>& mutex_)
{
  ScopedLock<NamedMutex> lock(*mutex_);
  data = *shm_data;
}

template<typename T>
void read_without_lock(T* shm_data, T& data, std::shared_ptr<NamedMutex>& mutex_)
{
  data = *shm_data;
}

template<typename T>
class SharedMemory
{
public:
  explicit SharedMemory(const std::string& global_name, bool autolock = true)
    : global_name_(global_name), size_(sizeof(T))
  {
    try
    {
      std::string mutex_name = global_name_;
      mutex_ = std::make_shared<NamedMutex>(
        ipc::open_or_create, mutex_name.c_str());

      ScopedLock<NamedMutex>(*mutex_);
      try
      {
        shm_ = std::make_shared<ipc::shared_memory_object>(
          ipc::open_or_create, global_name_.c_str(), ipc::read_write);
        shm_->truncate(size_);
      }
      catch(ipc::interprocess_exception&)
      {
        try
        {
          ipc::shared_memory_object::remove(global_name_.c_str());
          shm_ = std::make_shared<ipc::shared_memory_object>(
            ipc::open_or_create, global_name_.c_str(), ipc::read_write);
          shm_->truncate(size_);
        }
        catch(ipc::interprocess_exception& e)
        {
          throw e;
        }
      }
      region_ = std::make_shared<ipc::mapped_region>(*shm_, ipc::read_write);
      shm_data_ = static_cast<T*>(region_->get_address());
    }
    catch(std::bad_alloc& e)
    {
      throw e;
    }
    catch(std::exception& e)
    {
      throw e;
    }

    if(autolock)
    {
      write_ = write_with_lock<T>;
      read_ = read_with_lock<T>;
    }
    else
    {
      write_ = write_without_lock<T>;
      read_ = read_without_lock<T>;
    }
  }

  // ipc::shared_memory_object::remove never throw.
  ~SharedMemory()
  {
    ipc::shared_memory_object::remove(global_name_.c_str());
  }

  void remove()
  {
    ScopedLock<NamedMutex> lock(*mutex_);
    ipc::shared_memory_object::remove(global_name_.c_str());
  }

  void write(const T& data)
  {
    write_(shm_data_, data, mutex_);
  }

  void read(T& data)
  {
    read_(shm_data_, data, mutex_);
  }

private:
  SharedMemory& operator=(const SharedMemory&);

  std::string global_name_;
  std::size_t size_;

  std::shared_ptr<ipc::shared_memory_object> shm_;
  std::shared_ptr<ipc::mapped_region> region_;
  std::shared_ptr<NamedMutex> mutex_;

  T* shm_data_;
  void (*write_)(T*, const T&, std::shared_ptr<NamedMutex>&);
  void (*read_)(T*, T&, std::shared_ptr<NamedMutex>&);
};

template<typename T>
using SharedMemoryPtr = std::shared_ptr< SharedMemory<T> >;
template<typename T>
using SharedMemoryUPtr = std::unique_ptr< SharedMemory<T> >;
template<typename T>
using SharedMemorySPtr = std::shared_ptr< SharedMemory<T> >;

}

#endif // CSPIN_INCLUDE_CSPIN_SHARED_MEMORY_HPP_
