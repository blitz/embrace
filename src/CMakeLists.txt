cmake_minimum_required(VERSION 3.10)
project(embrace)

find_package(PkgConfig REQUIRED)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

## Build Description

add_executable(embrace embrace.cpp)

## Add dependencies

pkg_check_modules(JSONC REQUIRED json-c)

target_link_libraries(embrace ${JSONC_LIBRARIES})
target_include_directories(embrace PUBLIC ${JSONC_INCLUDE_DIRS})
target_compile_options(embrace PUBLIC ${JSONC_CFLAGS_OTHER})

## Installation

install(TARGETS embrace DESTINATION ${CMAKE_INSTALL_BINDIR})
