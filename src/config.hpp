#pragma once

#include <vector>
#include <istream>
#include <variant>

using name_value = std::pair<std::string, std::string>;

struct config {
  /// The environment variables that need to be set as name/value pairs.
  std::vector<name_value> env_set;

  /// The program that needs to be started. This must be a path to an executable file.
  std::string program;

  /// Any program arguments that need to be passed to `program` in addition to what's specified on the command
  /// line. These arguments precede arguments given on the command line.
  std::vector<std::string> program_args;
};

/// An error that occurred during configuration parsing.
struct config_parse_error {
  std::string reason;
};

/// Parse a stream into a configuration file.
std::variant<config, config_parse_error> parse(std::istream &input);
