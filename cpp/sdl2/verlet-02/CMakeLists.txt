cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(verlet VERSION 1.0.0 LANGUAGES C CXX)

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
    $<BUILD_LOCAL_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_LOCAL_INTERFACE:${SDL2_INCLUDE_DIRS}>
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_gfx REQUIRED)
#find_package(SDL2_mixer REQUIRED)
#find_package(SDL2_net REQUIRED)

#add_executable(verlet WIN32)
add_executable(verlet)
target_sources(verlet PRIVATE
    ${CMAKE_SOURCE_DIR}/src/verlet.cpp
)

target_link_libraries(verlet PRIVATE
    include_interface
    compiler_flags

    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
)

#message(STATUS "///////////////////////////////////")
#message(STATUS "${SDL2_INCLUDE_DIRS}")
#message(STATUS "${SDL2_LIBRARIES}")
#message(STATUS "///////////////////////////////////")
