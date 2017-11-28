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

  template <typename It>
  constexpr size_t count(It seqFirst, const It & seqLast, const It countFirst, const It & countLast){
    size_t res = 0;
    auto countIt = countFirst;

    for(auto & seqIt = seqFirst; seqIt != seqLast; ++seqIt){
      if(*seqIt == *countIt){
        ++countIt;
        if(countIt == countLast){
          ++res;
          countIt = countFirst;
        }
      } else if(countIt != countFirst){
        countIt = countFirst;
        --seqIt;
      }
    }

    return res;
  }

  template <typename T>
  size_t count(const T & sequence, const T & toCount){
    return count(sequence.cbegin(), sequence.cend(), toCount.cbegin(), toCount.cend());
  }

  size_t countInString(const std::string &sequence, const std::string &toCount) {
    return count(sequence, toCount);
  }

  size_t countInString(std::string::const_iterator first, std::string::const_iterator last,
                       const std::string &toCount){
    return count(first, last, toCount.cbegin(), toCount.cend());
  }
} // namespace util
#endif
