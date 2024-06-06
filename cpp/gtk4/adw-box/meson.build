project('demo', 'c',
        default_options: 'c_std=c23')

gtk_dep = dependency('gtk4', version: '>= 4.6.0')
libadwaita_dep = dependency('libadwaita-1')

incdir = include_directories('src')

src = [
    'src/main.c',
]

c_compiler    = meson.get_compiler('c')
warning_flags = ['-Wall', '-Werror', '-Wpedantic']
warning_flags = c_compiler.get_supported_arguments(warning_flags)
add_project_arguments(warning_flags, language: 'c')

executable('demo', src,
           include_directories: incdir,
           win_subsystem: 'windows',
           dependencies: [gtk_dep, libadwaita_dep])
