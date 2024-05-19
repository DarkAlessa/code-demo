cmake_minimum_required(VERSION 3.26 FATAL_ERROR)
project(shooting VERSION 1.0.0 LANGUAGES C CXX)

# compiler flags/options INTERFACE
add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE $<BUILD_LOCAL_INTERFACE:cxx_std_23>)
target_compile_options(compiler_flags BEFORE INTERFACE
  $<BUILD_LOCAL_INTERFACE:-Wall;-Werror;-Wpedantic>
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/")
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

# include directory INTERFACE
add_library(include_interface INTERFACE)
target_include_directories(include_interface INTERFACE
  $<BUILD_LOCAL_INTERFACE:${CMAKE_SOURCE_DIR}/src>
)

add_subdirectory(src)
