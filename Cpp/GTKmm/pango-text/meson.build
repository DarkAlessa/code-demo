project('demo', 'c', 'cpp',
        default_options: 'cpp_std=c++23')

gtkmm_dep = dependency('gtkmm-4.0', version: '>= 4.6.0')
pangomm_dep = dependency('pangomm-2.48')

incdir = include_directories('include')
src = [
	'src/main.cpp',
	'src/window.cpp',
	'src/text.cpp'
]

c_compiler    = meson.get_compiler('c')
cpp_compiler  = meson.get_compiler('cpp')
warning_flags = ['-Wall', '-Werror', '-Wextra', '-Wpedantic']
warning_flags = cpp_compiler.get_supported_arguments(warning_flags)
add_project_arguments(warning_flags, language: 'cpp')

executable('demo', src, 
           include_directories: incdir,
           win_subsystem: 'windows',
           dependencies: [gtkmm_dep, pangomm_dep])
