#ifndef UTIL_HPP
#define UTIL_HPP

#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

namespace util {
template <typename It> // It should be a bidirectional iterator
constexpr std::vector<std::pair<It, It>> splitOn(It first, It last, It delimFirst, It delimLast) {
  std::vector<std::pair<It, It>> parts;

  auto partFirst = first;
  auto partLast = first;
  auto delimIt = delimFirst;
  const size_t delimSize = std::distance(delimFirst, delimLast);

  while (partLast != last) {
    if (*partLast == *delimIt) {
      ++delimIt;
      if (delimIt == delimLast) {
        parts.emplace_back(partFirst, std::prev(partLast, delimSize -1));
        partFirst = std::next(partLast);
        delimIt = delimFirst;
      }
    } else {
      delimIt = delimFirst;
    }

    ++partLast;
  }
  parts.emplace_back(partFirst, partLast);

  return parts;
}

size_t countInString(const std::string &sequence, const std::string &toCount);

size_t countInString(std::string::const_iterator first, std::string::const_iterator last,
                     const std::string &toCount);
} // namespace util
#endif
