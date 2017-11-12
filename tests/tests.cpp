#include <catch.hpp>

#include "util.hpp"
TEST_CASE("util::splitOn()", "[util]") {

  SECTION("string single element delimiter, no occurence") {
    const std::string in = "1234";
    const std::string delim = "x";

    const auto res = util::splitOn(in, delim);
    REQUIRE(res == std::vector<std::string>({"1234"}));
  }

  SECTION("string: single character delimiter, multiple parts") {
    const std::string in = "0x123x4567x8x9";
    const char delimiter = 'x';

    const auto res = util::splitOn(in, delimiter);

    REQUIRE(res == std::vector<std::string>({"0", "123", "4567", "8", "9"}));
  }

  SECTION("string: multiple character delimiter, multiple parts") {
    const std::string in = "0split123split4567split8split9";
    const std::string delimiter = "split";

    const auto res = util::splitOn(in, delimiter);

    REQUIRE(res == std::vector<std::string>({"0", "123", "4567", "8", "9"}));
  }
  SECTION("vector<int>: multiple element delimiter, multiple parts") {
    const std::vector<int> in = {0, 9, 9, 9, 1, 2, 3, 9, 9, 9, 4, 5, 6, 7, 9, 9, 9, 8, 9, 9, 9, 9};
    const std::vector<int> delimiter = {9, 9, 9};

    const auto res = util::splitOn(in, delimiter);

    REQUIRE(res == std::vector<std::vector<int>>({{0}, {1, 2, 3}, {4, 5, 6, 7}, {8}, {9}}));
  }
}

TEST_CASE("util::splitOn() iterator-based version", "[util]") {
  SECTION("string single element delimiter, no occurence") {
    const std::string in = "1234";
    const std::string delim = "split";

    const auto res = util::splitOn(in.begin(), in.end(), delim.begin(), delim.end());
    REQUIRE(res.size() == 1);
    REQUIRE(in == std::string(res[0].first, res[0].second));
  }

  SECTION("string: single character delimiter, multiple parts") {
    const std::string in = "0x123x4567x8x9";
    const std::string delimiter = "x";

    const auto res = util::splitOn(in.cbegin(), in.cend(), delimiter.cbegin(), delimiter.cend());
    std::vector<std::string> parts;
    for (const auto &itPair : res) {
      parts.emplace_back(itPair.first, itPair.second);
    }

    REQUIRE(parts == std::vector<std::string>({"0", "123", "4567", "8", "9"}));
  }

  SECTION("string: multiple character delimiter, multiple parts") {
    const std::string in = "0split123split4567split8split9";
    const std::string delimiter = "split";

    const auto res = util::splitOn(in.begin(), in.end(), delimiter.begin(), delimiter.end());
    std::vector<std::string> parts;
    for (const auto &itPair : res) {
      parts.emplace_back(itPair.first, itPair.second);
    }

    REQUIRE(parts == std::vector<std::string>({"0", "123", "4567", "8", "9"}));
  }

  SECTION("vector<int>: multiple element delimiter, multiple parts") {
    const std::vector<int> in = {0, 9, 9, 9, 1, 2, 3, 9, 9, 9, 4, 5, 6, 7, 9, 9, 9, 8, 9, 9, 9, 9};
    const std::vector<int> delimiter = {9, 9, 9};

    const auto res = util::splitOn(in.cbegin(), in.cend(), delimiter.cbegin(), delimiter.cend());
    std::vector<std::vector<int>> parts;
    for (const auto &itPair : res) {
      parts.emplace_back(itPair.first, itPair.second);
    }

    REQUIRE(parts == std::vector<std::vector<int>>({{0}, {1, 2, 3}, {4, 5, 6, 7}, {8}, {9}}));
  }
}

TEST_CASE("util::countInString()", "[util]") {
  SECTION("pattern to count is single character, all characters in string are "
          "that character") {
    const std::string in = "xxxx";
    const std::string toCount = "x";

    const auto res = util::countInString(in, toCount);

    REQUIRE(res == 4);
  }
  SECTION("patter to count is 2 characters, many different characters in string, multiple "
          "occurrences of pattern to count.") {
    const std::string in = "sdlfk 23 jwea 23 jg 23 s;j6j 2 3 as 23 df2jsj 23 asd62";
    const std::string toCount = "23";

    const auto res = util::countInString(in, toCount);

    REQUIRE(res == 5);
  }
}
