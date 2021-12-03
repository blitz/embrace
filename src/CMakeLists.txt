cmake_minimum_required(VERSION 3.13)
project(embrace CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

include(CTest)

## Build Description

add_executable(embrace embrace.cpp config.cpp)

## Add dependencies

find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(embrace PRIVATE nlohmann_json::nlohmann_json)

## Tests

if(BUILD_TESTING)
  enable_testing()

  find_package(Catch2 REQUIRED)
  include(Catch)

  add_executable(test_unit
    config.cpp
    config_tests.cpp
    )
  target_link_libraries(test_unit Catch2::Catch2WithMain)

  catch_discover_tests(test_unit)
endif()

## Installation

install(TARGETS embrace DESTINATION ${CMAKE_INSTALL_BINDIR})
