#ifndef CSPIN_INCLUDE_CSPIN_UTILS_HPP_
#define CSPIN_INCLUDE_CSPIN_UTILS_HPP_

#include <limits>

namespace cspin
{
namespace utils
{

template<typename UT, typename ST>
inline ST unsigned_to_signed(UT val)
{
  if(val > std::numeric_limits<ST>::max())
  {
    throw std::overflow_error(
        "unsigned_to_signed failed because of overflow. Given value cannot be stored in signed variable.");
  }

  return static_cast<ST>(val);
}

} // namespace utils
} // namespace cspin

#endif // CSPIN_INCLUDE_CSPIN_UTILS_HPP_
