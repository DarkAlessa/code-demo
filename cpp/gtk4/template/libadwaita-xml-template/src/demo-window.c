#include "demo-window.h"

struct _DemoWindow {
    AdwApplicationWindow parent;
    GtkHeaderBar   *header_bar;
};

G_DEFINE_TYPE(DemoWindow, demo_window, ADW_TYPE_APPLICATION_WINDOW)

DemoWindow *demo_window_new(DemoApplication *app) {
    return g_object_new(DEMO_WINDOW_TYPE, "application", app, NULL);
}

static void demo_window_init(DemoWindow *win) {
    gtk_widget_init_template(GTK_WIDGET(win));
}

static void demo_window_class_init(DemoWindowClass *klass) {
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(klass), "/org/gtk/demo/builder.ui");
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(klass), DemoWindow, header_bar);
}
