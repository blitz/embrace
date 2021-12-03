#include "config.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <string_view>

namespace {

auto parse_string(std::string_view str)
{
  std::string copy {str};
  std::istringstream ss {copy};

  return parse(ss);
}

}

TEST_CASE("empty config file is rejected") {
  REQUIRE(std::holds_alternative<config_parse_error>(parse_string("")));
}
