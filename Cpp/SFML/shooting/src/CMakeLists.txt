# fine SFML package : use "pkgconf --list-all | grep sfml" for show packages
find_package(SFML 2.6 COMPONENTS network audio graphics window system REQUIRED)

add_executable(shooting WIN32)
target_sources(shooting PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/shooting.cpp
)

target_link_libraries(shooting PRIVATE
    compiler_flags
    include_interface

    sfml-graphics 
    sfml-window 
    sfml-audio 
    sfml-network 
    sfml-system
)
