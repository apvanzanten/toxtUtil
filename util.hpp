#ifndef UTIL_HPP
#define UTIL_HPP

#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

namespace util {
/** Splits a sequence of elements on any instances of a delimiter sequence (sequences must be of
same type and have at least std::BidirectionalIterator).
@param first Iterator to first element of sequence to be split.
@param last Iterator to last element of sequence to be split.
@param delimFirst Iterator to first element of delimiter sequence.
@param delimLast Iterator to last element of delimiter sequence.
@return A vector of iterator pairs, where each pair represents a sub-sequence (iterators pointing
to first element and past-the-end element).
*/
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
        parts.emplace_back(partFirst, std::prev(partLast, delimSize - 1));
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

/** Counts occurrences of a specific sequence in another sequence (sequences must be of same type
and have at least std::BidirectionalIterator), conceptually similar to std::count, but then for
counting sequences rather than single elements.
@param seqFirst Iterator to first element of sequence to count occurrences in.
@param seqLast Iterator to last element of sequence to count occurrences in.
@param countFirst Iterator to first element of sequence to count occurrences of.
@param countLast Iterator to last element of sequence to count occurrences of.
@return A size_t containig the number of occurrences.
*/
template <typename It>
constexpr size_t count(It seqFirst, const It &seqLast, const It countFirst, const It &countLast) {
  size_t res = 0;
  auto countIt = countFirst;

  for (auto &seqIt = seqFirst; seqIt != seqLast; ++seqIt) {
    if (*seqIt == *countIt) {
      ++countIt;
      if (countIt == countLast) {
        ++res;
        countIt = countFirst;
      }
    } else if (countIt != countFirst) {
      countIt = countFirst;
      --seqIt;
    }
  }

  return res;
}

/** Counts occurrences of a specific sequence in another sequence (sequences must be of same type
and have at least std::BidirectionalIterator), conceptually similar to std::count, but
then for counting sequences rather than single elements.
@param sequence Sequence to count occurrences in.
@param toCount Sequence to count occurrences of.
@return A size_t containing the number of occurrences.
*/
template <typename T> size_t count(const T &sequence, const T &toCount) {
  return count(sequence.cbegin(), sequence.cend(), toCount.cbegin(), toCount.cend());
}

size_t countInString(const std::string &sequence, const std::string &toCount);
size_t countInString(std::string::const_iterator first, std::string::const_iterator last,
                       const std::string &toCount);
} // namespace util
#endif
