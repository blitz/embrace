#include "config.hpp"

#include <nlohmann/json.hpp>

using nlohmann::json;

std::variant<config, config_parse_error> parse(std::istream &input) {
  try {
    json j;
    input >> j;

    return config {};
  } catch (json::exception &e) {
    return config_parse_error {
      e.what()
    };
  }
}
