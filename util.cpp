#include "util.hpp"

#include <algorithm>
#include <iterator>
#include <vector>

namespace util {
size_t countInString(const std::string &sequence, const std::string &toCount) {
  if (toCount.size() == 1) {
    return std::count(sequence.cbegin(), sequence.cend(), toCount.front());
  }

  size_t count = 0;
  size_t index = sequence.find(toCount, 0);

  while (index != sequence.npos) {
    ++count;
    index = sequence.find(toCount, index + 1);
  }

  return count;
}

size_t countInString(std::string::const_iterator first, std::string::const_iterator last,
                     const std::string &toCount) {
  if (toCount.size() == 1) {
    return std::count(first, last, toCount.front());
  }

  size_t count = 0;

  auto toCountIt = toCount.cbegin();

  for (auto it = first; it != last; ++it) {
    if (*it == *toCountIt) {
      ++toCountIt;
      if (toCountIt == toCount.cend()) {
        ++count;
        toCountIt = toCount.cbegin();
      }
    } else {
      toCountIt = toCount.cbegin();
    }
  }

  return count;
}
} // namespace util
