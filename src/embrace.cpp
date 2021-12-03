#include "config.hpp"

#include <iostream>
#include <cstdlib>

int main()
{
  auto const cfg {parse(std::cin)};

  if (config_parse_error const *e = std::get_if<config_parse_error>(&cfg); e) {
    std::cerr << "Failed to parse config file:\n" << e->reason << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
