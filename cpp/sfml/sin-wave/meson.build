project('graph', 'cpp',
        default_options: 'cpp_std=c++23'
)

sfml_dep = dependency('sfml-all')
if not sfml_dep.found()
  error('SFML not found')
endif

incdir = include_directories('src')

src = [
    'src/main.cpp',
    'src/graph.cpp',
]

cpp_compiler = meson.get_compiler('cpp')
warning_flags = ['-Wall', '-Werror', '-Wpedantic']
warning_flags = cpp_compiler.get_supported_arguments(warning_flags)
add_project_arguments(warning_flags, language: 'cpp')

executable('graph', src,
  include_directories: incdir,
  win_subsystem: 'windows',
  dependencies: sfml_dep
)