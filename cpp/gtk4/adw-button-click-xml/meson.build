project('demo', 'c',
        default_options: 'c_std=c23')

gnome = import('gnome')

gtk_dep = dependency('gtk4', version: '>= 4.6.0')
libadwaita_dep = dependency('libadwaita-1')

incdir = include_directories('src')

src = [
    'src/main.c',
    'src/demo-application.c',
    'src/demo-window.c',
]

src += gnome.compile_resources('demo-resources',
    'src/demo.gresource.xml',
    source_dir: 'src',

    # ถ้าไม่มี source_dir: 'src' ต้องเพิ่ม src ในไฟล์ *.demo.gresource.xml
    # 👉 <file preprocess="xml-stripblanks">src/builder.ui</file>
    # และใน demo_window_class_init() ใน demo-window.c
    # 👉 gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class), "/org/gtk/demo/src/builder.ui");
)

c_compiler    = meson.get_compiler('c')
warning_flags = ['-Wall', '-Werror', '-Wpedantic']
warning_flags = c_compiler.get_supported_arguments(warning_flags)
add_project_arguments(warning_flags, language: 'c')

executable('demo', src,
           include_directories: incdir,
           win_subsystem: 'console',
           dependencies: [gtk_dep, libadwaita_dep])
