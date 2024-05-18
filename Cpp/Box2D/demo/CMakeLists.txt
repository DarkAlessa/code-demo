cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(omg C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(omg "${SOURCES}")
# fine SFML package : use "pkgconf --list-all | grep sfml" for show packages
find_package(SFML 2 REQUIRED network audio graphics window system)
target_link_libraries(omg
sfml-graphics 
sfml-window 
sfml-audio 
sfml-network 
sfml-system
"${CMAKE_SOURCE_DIR}/lib/libbox2d.a")
