project(
    'demo',
    'c',
    'cpp',
    default_options: 'cpp_std=c++23'
)

sdl2_dep       = dependency('sdl2')
sdl2_image_dep = dependency('sdl2_image')
sdl2_ttf_dep   = dependency('sdl2_ttf')

incdir = include_directories('src')

imgui_src = [
    'src/imgui/imgui.cpp',
    'src/imgui/imgui_demo.cpp',
    'src/imgui/imgui_draw.cpp',
    'src/imgui/imgui_tables.cpp',
    'src/imgui/imgui_widgets.cpp',
    'src/imgui/imgui_impl_sdl2.cpp',
    'src/imgui/imgui_impl_sdlrenderer2.cpp',
]

src = [
    'src/demo.cpp',
]

#c_compiler    = meson.get_compiler('c')
cpp_compiler  = meson.get_compiler('cpp')
warning_flags = ['-Wall', '-Werror', '-Wpedantic']
warning_flags = cpp_compiler.get_supported_arguments(warning_flags)
add_project_arguments(warning_flags, language: 'cpp')

executable('demo',
            src, imgui_src,
            include_directories: incdir,
            win_subsystem: 'console',
            dependencies: [
                sdl2_dep,
                sdl2_image_dep,
                sdl2_ttf_dep,
            ]
)