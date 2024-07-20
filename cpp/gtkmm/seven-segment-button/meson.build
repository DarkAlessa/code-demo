project('demo', 'cpp',
        default_options: 'cpp_std=c++23')

gtkmm_dep = dependency('gtkmm-4.0', version: '>= 4.6.0')
if not gtkmm_dep.found()
  error('gtkmm-4.0 not found')
endif

incdir = include_directories('src')

src = [
	'src/main.cpp',
	'src/window.cpp',
	'src/seven_segment.cpp'
]

#c_compiler    = meson.get_compiler('c')
cpp_compiler  = meson.get_compiler('cpp')
warning_flags = ['-Wall', '-Werror', '-Wextra', '-Wpedantic']
warning_flags = cpp_compiler.get_supported_arguments(warning_flags)
add_project_arguments(warning_flags, language: 'cpp')

executable('demo', src, 
           include_directories: incdir,
           win_subsystem: 'windows',
           dependencies: gtkmm_dep)
