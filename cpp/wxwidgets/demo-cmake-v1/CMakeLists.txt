cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(demo VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/")

find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(demo src/main.cpp)
target_link_libraries(demo PRIVATE ${wxWidgets_LIBRARIES})
