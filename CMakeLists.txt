cmake_minimum_required(VERSION 3.28)
project(i_can_code_shell LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Expose the active build database to clangd in this source directory.
file(CREATE_LINK "${CMAKE_BINARY_DIR}/compile_commands.json"
    "${PROJECT_SOURCE_DIR}/compile_commands.json" SYMBOLIC)
include(CTest)
add_subdirectory(in-c)
add_subdirectory(in-cpp)
