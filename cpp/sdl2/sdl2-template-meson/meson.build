project('game', 'c', 'cpp',
        default_options: 'cpp_std=c++23')

sdl2_dep       = dependency('sdl2')
sdl2_image_dep = dependency('sdl2_image')
sdl2_ttf_dep   = dependency('sdl2_ttf')

incdir = include_directories('src', 'src/engine')

src = [
    'src/main.cpp',
    'src/game.cpp',
    'src/engine/fps.cpp'
]

c_compiler    = meson.get_compiler('c')
cpp_compiler  = meson.get_compiler('cpp')
warning_flags = ['-Wall', '-Werror', '-Wpedantic']
warning_flags = cpp_compiler.get_supported_arguments(warning_flags)
add_project_arguments(warning_flags, language: 'cpp')

executable('game', src, 
        include_directories: incdir,
        win_subsystem: 'console',
        dependencies: [sdl2_dep, sdl2_image_dep, sdl2_ttf_dep])