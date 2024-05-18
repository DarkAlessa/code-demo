# fine SFML package : use "pkgconf --list-all | grep sfml" for show packages
find_package(SFML 2.6 COMPONENTS network audio graphics window system REQUIRED)

add_executable(demo)
target_sources(demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/line.cpp
)

target_link_libraries(demo PRIVATE
    archive
    compiler_flags
    include_interface

    sfml-graphics 
    sfml-window 
    sfml-audio 
    sfml-network 
    sfml-system
)
