#include "config.hpp"

#include <cstdlib>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <cstring>

namespace {

[[noreturn]] void execute(config const &cfg)
{
  // Convert a vector of strings to a vector of char pointers.
  std::vector<char *> c_program_args;

  c_program_args.reserve(cfg.program_args.size() + 1);

  for (auto &program_arg: cfg.program_args) {
    // Casting the const away to placate execv. It doesn't actually modify the string. *sigh*
    c_program_args.push_back(const_cast<char *>(program_arg.c_str()));
  }

  c_program_args.push_back(nullptr);

  // Execute the binary.
  int rc = execv(cfg.binary.c_str(), c_program_args.data());

  if (rc != 0) {
    std::cerr << "Failed to execute " << cfg.binary << ": " << strerror(errno) << "\n";
  }

  exit(EXIT_FAILURE);
}

}

int main()
{
  auto const cfg {parse(std::cin)};

  if (config_parse_error const *e = std::get_if<config_parse_error>(&cfg); e) {
    std::cerr << "Failed to parse config file:\n" << e->reason << "\n";
    return EXIT_FAILURE;
  }

  execute(std::get<config>(cfg));
}
