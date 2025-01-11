cmake_minimum_required(VERSION 3.22)

project(TestMe)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE TestMe_SOURCES "src/*.cpp")
list(FILTER TestMe_SOURCES EXCLUDE REGEX "src/main.cpp")
message(STATUS ${TestMe_SOURCES})
add_executable(TestMe "src/main.cpp")
target_sources(TestMe PRIVATE ${TestMe_SOURCES})

include(cmake/cpm.cmake)
include(cmake/tree-sitter.cmake)
include(cmake/gtest.cmake)

set(INCLUDE_DIRS
    "${tree-sitter_SOURCE_DIR}/lib/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
include_directories(${INCLUDE_DIRS})

target_link_libraries(TestMe PRIVATE
    ${tree-sitter_LIBRARIES}
)
target_compile_features(TestMe PRIVATE cxx_std_20)
