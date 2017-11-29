#include "util.hpp"

namespace util {
  size_t countInString(const std::string &sequence, const std::string &toCount) {
    return count(sequence, toCount);
  }

  size_t countInString(std::string::const_iterator first, std::string::const_iterator last,
                       const std::string &toCount){
    return count(first, last, toCount.cbegin(), toCount.cend());
  }
} // namespace util
