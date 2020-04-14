#ifndef CSPIN_INCLUDE_CSPIN_NAMED_MUTEX_HPP_
#define CSPIN_INCLUDE_CSPIN_NAMED_MUTEX_HPP_

#include <boost/interprocess/sync/named_mutex.hpp>

namespace cspin
{

using namespace boost::interprocess;
using NamedMutex = named_mutex;
using NamedMutexPtr = std::shared_ptr<named_mutex>;
using NamedMutexUPtr = std::unique_ptr<named_mutex>;
using NamedMutexSPtr = std::shared_ptr<named_mutex>;

} // namespace cspin

#endif // CSPIN_INCLUDE_CSPIN_NAMED_MUTEX_HPP_
