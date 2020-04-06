#ifndef CSPIN_INCLUDE_CSPIN_NAMED_MUTEX_HPP_
#define CSPIN_INCLUDE_CSPIN_NAMED_MUTEX_HPP_

#include <boost/interprocess/sync/named_mutex.hpp>

namespace cspin
{
  using NamedMutex = boost::interprocess::named_mutex;
}

#endif // CSPIN_INCLUDE_CSPIN_NAMED_MUTEX_HPP_
