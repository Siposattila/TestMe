cmake_minimum_required(VERSION 3.22)

project(TestMe)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TestMe_SOURCES
	src/main.cpp
)

add_executable(TestMe)

target_sources(TestMe PRIVATE ${TestMe_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TestMe_SOURCES})

include(FetchContent)
include(cmake/tree-sitter.cmake)
include(cmake/gtest.cmake)

target_compile_features(TestMe PRIVATE
	cxx_std_17
)
