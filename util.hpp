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

template <typename T>
constexpr std::vector<T> splitOn(const T &sequence, const typename T::value_type &delimiter) {
  std::vector<T> parts(1);

  for (const auto &element : sequence) {
    if (element == delimiter) {
      parts.push_back({});
    } else {
      parts.back().push_back(element);
    }
  }

  if (parts.front().empty()) {
    parts.erase(parts.begin());
  }
  if (parts.size() > 1 && parts.back().empty()) {
    parts.erase(std::prev(parts.end()));
  }

  return parts;
}

template <typename T> constexpr std::vector<T> splitOn(const T &sequence, const T &delimiter) {
  if (delimiter.size() == 1) {
    return splitOn(sequence, delimiter.front());
  }

  if (sequence.size() < delimiter.size()) {
    return {sequence};
  }

  std::vector<T> parts(1);
  auto delimIt = delimiter.begin();
  T delimiterBuffer;
  for (const auto &element : sequence) {
    if (element == *delimIt) {
      delimiterBuffer.push_back(element);
      ++delimIt;
      if (delimIt == delimiter.end()) {
        delimiterBuffer.clear();
        delimIt = delimiter.begin();
        parts.push_back({});
      }
    } else {
      if (delimIt != delimiter.begin()) {
        parts.back().insert(parts.back().end(), delimiterBuffer.begin(), delimiterBuffer.end());
        delimiterBuffer.clear();
        delimIt = delimiter.begin();
      }
      parts.back().push_back(element);
    }
  }
  if (!delimiterBuffer.empty()) {
    parts.back().insert(parts.back().end(), delimiterBuffer.begin(), delimiterBuffer.end());
  }

  if (parts.front().empty()) {
    parts.erase(parts.begin());
  }
  if (parts.back().empty() && parts.size() > 1) {
    parts.erase(std::prev(parts.end()));
  }

  return parts;
}

size_t countInString(const std::string &sequence, const std::string &toCount);

size_t countInString(std::string::const_iterator first, std::string::const_iterator last,
                     const std::string &toCount);
} // namespace util
#endif
