cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(demo C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/")
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

add_executable(demo
  ${CMAKE_SOURCE_DIR}/src/demo.cpp
  ${CMAKE_SOURCE_DIR}/src/app.cpp
)

target_include_directories(demo PRIVATE
  ${GTKMM_INCLUDE_DIRS} 
  ${CMAKE_SOURCE_DIR}/src
)

target_compile_options(demo PRIVATE
  ${GTKMM_CFLAGS_OTHER}
  ${CMAKE_CXX_FLAGS}
  -Wall
  -Werror
  -Wpedantic
)

#target_link_directories(demo PRIVATE ${GTKMM_LIBRARY_DIRS})

target_link_libraries(demo PRIVATE ${GTKMM_LIBRARIES})
