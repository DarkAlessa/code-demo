cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(elsa VERSION 1.0.0 LANGUAGES C CXX)

# compiler flags/options INTERFACE
add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE $<BUILD_LOCAL_INTERFACE:cxx_std_23>)
target_compile_options(compiler_flags BEFORE INTERFACE
    $<BUILD_LOCAL_INTERFACE:-Wall;-Werror;-Wpedantic>
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/")

find_package(wxWidgets REQUIRED)

# include UsewxWidgets.cmake file to set up necessary variables
include(${wxWidgets_USE_FILE})

# include directory INTERFACE
add_library(include_interface INTERFACE)
target_include_directories(include_interface INTERFACE
    $<BUILD_LOCAL_INTERFACE:/src>
)

#add_executable(elsa WIN32)
add_executable(elsa)
target_sources(elsa PRIVATE
    ${CMAKE_SOURCE_DIR}/src/elsa.cpp
)

target_link_libraries(elsa PRIVATE
    include_interface
    compiler_flags
    ${wxWidgets_LIBRARIES}
)

#message(STATUS "==========================================================")
#message(STATUS "\${wxWidgets_USE_FILE}:     ${wxWidgets_USE_FILE}")
#message(STATUS "\${wxWidgets_INCLUDE_DIRS}: ${wxWidgets_INCLUDE_DIRS}")
#message(STATUS "==========================================================")
