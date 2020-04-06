#ifndef CSPIN_INCLUDE_CSPIN_SCOPED_LOCK_HPP_
#define CSPIN_INCLUDE_CSPIN_SCOPED_LOCK_HPP_

#include <mutex>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

namespace cspin
{
template<typename T>
using ScopedLock = boost::interprocess::scoped_lock<T>;
}

#endif // CSPIN_INCLUDE_CSPIN_SCOPED_LOCK_HPP_
