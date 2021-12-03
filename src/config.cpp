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

    std::vector<std::string> args (j.at("args"));

    if (args.size() == 0) {
      throw config_parse_error {
        "The args configuration option must have at least one element.\n"
        "If in doubt, the first element of args should be the same as the binary name."
          };
    }

    return config {
      j.at("binary"),
      args,
      j.value("env", std::map<std::string, std::string> {}),
    };
  } catch (json::exception &e) {
     return config_parse_error {
      e.what()
    };
  }
}
