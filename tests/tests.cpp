#include <catch.hpp>
#include <list>

#include "util.hpp"

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

TEST_CASE("util::count()", "[util]"){
  REQUIRE(util::count(std::string{}, std::string{}) == 0);
  REQUIRE(util::count(std::string{}, std::string{'e'}) == 0);
  REQUIRE(util::count(std::string{"hello"}, std::string{'l'}) == 2);
  REQUIRE(util::count(std::string{"hello"}, std::string{"ll"}) == 1);
  REQUIRE(util::count(std::vector<int>{}, std::vector<int>{0}) == 0);
  REQUIRE(util::count(std::list<int>{0,1,2,3,4}, std::list<int>{0}) == 1);
  REQUIRE(util::count(std::string{"000asdsdfjlasdkfj00asdfj00000ksdf00"}, std::string{"00"}) == 5);
  REQUIRE(util::count(std::string{"alskjflksajdfssplitaskdjaslkjdaskdjsplitalksjdalsjkdaskjiuorqwieursplitaslkdfjlskjadfssplit"}, std::string{"split"}) == 4);
  REQUIRE(noexcept(util::count(std::string{}, std::string{})));
  REQUIRE(noexcept(util::count(std::list<int>(), std::list<int>())));
}

