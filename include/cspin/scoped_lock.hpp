#ifndef CSPIN_INCLUDE_CSPIN_SCOPED_LOCK_HPP_
#define CSPIN_INCLUDE_CSPIN_SCOPED_LOCK_HPP_

#include <memory>
#include <mutex>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

namespace cspin
{

using namespace boost::interprocess;
template<typename T>
using ScopedLock = scoped_lock<T>;
template<typename T>
using ScopedLockPtr = std::shared_ptr< scoped_lock<T> >;
template<typename T>
using ScopedLockUPtr = std::unique_ptr< scoped_lock<T> >;
template<typename T>
using ScopedLockSPtr = std::shared_ptr< scoped_lock<T> >;

} // namespace cspin

#endif // CSPIN_INCLUDE_CSPIN_SCOPED_LOCK_HPP_
