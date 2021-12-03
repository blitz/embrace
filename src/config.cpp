#include "config.hpp"

#include <nlohmann/json.hpp>

using nlohmann::json;

namespace {
/// Consume a comment line if there is one.
///
/// This is mostly useful to consume the initial shebang line in a file.
void consume_one_comment(std::istream &input) {
  if (input.peek() == '#') {
    std::string comment;
    std::getline(input, comment);
  }
}

}

std::variant<config, config_parse_error> parse(std::istream &input) {
  try {
    json j;

    // Drop an initial shebang line, if it is there.
    consume_one_comment(input);

    input >> j;

    return config {
      j.at("binary"),
      j.value("args", std::vector<std::string> {}),
    };
  } catch (json::exception &e) {
     return config_parse_error {
      e.what()
    };
  }
}
