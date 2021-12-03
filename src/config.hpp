#pragma once

#include <vector>
#include <map>
#include <istream>
#include <variant>

struct config {
  /// The program that needs to be started. This must be a path to an executable file.
  std::string binary;

  /// Any program arguments that need to be passed to `program` in addition to what's specified on the command
  /// line. These arguments precede arguments given on the command line.
  std::vector<std::string> args;

  /// Additional environment variables as name/value pairs.
  ///
  /// Anything environment variable specified in here will override an existing environment variable with the same
  /// name.
  std::map<std::string, std::string> env;
};

/// An error that occurred during configuration parsing.
struct config_parse_error {
  std::string reason;
};

/// Parse a stream into a configuration file.
std::variant<config, config_parse_error> parse(std::istream &input);
