

cmake_minimum_required(VERSION 3.25.2)

project(
    foresight
    VERSION 0.1
    DESCRIPTION "Predictive Text"
    LANGUAGES CXX
)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(
    "${PROJECT_SOURCE_DIR}/include/config.h.in"
    "${PROJECT_BINARY_DIR}/include/config.h"
)

# compiler flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

add_subdirectory(external/spdlog)

add_executable(${PROJECT_NAME} src/main.cpp src/trie.cpp src/app.cpp)

# include directories (must be after add_executable)
target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_BINARY_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/external/spdlog/include"
)

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog_header_only)
