#include "config.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <string_view>

using namespace std::string_literals;

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

TEST_CASE("minimal config file is parsed") {
  auto cfg {parse_string("{\"binary\": \"sometool\", \"args\": [\"argv0\", \"argv1\"]}\n")};

  REQUIRE(std::holds_alternative<config>(cfg));

  REQUIRE(std::get<config>(cfg).binary == "sometool");
  REQUIRE(std::get<config>(cfg).args == std::vector<std::string> { "argv0", "argv1" });
}

TEST_CASE("config file with environment overrides is parsed") {
  auto cfg {parse_string("{\"binary\": \"sometool\", \"args\": [\"argv0\"], \"env\": { \"xxx\": \"yyy\"}}\n")};

  REQUIRE(std::holds_alternative<config>(cfg));

  REQUIRE(std::get<config>(cfg).binary == "sometool");
  REQUIRE(std::get<config>(cfg).env == std::map<std::string, std::string> { std::make_pair("xxx"s, "yyy"s) });
}


TEST_CASE("shebang line is ignored") {
  REQUIRE(std::holds_alternative<config>(parse_string("#!/bin/foo\n{\"binary\": \"foo\", \"args\": [\"x\"]}\n")));
}
