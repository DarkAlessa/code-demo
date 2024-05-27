#include <gtk/gtk.h>

#include "demo-window.h"

struct _DemoWindow {
    GtkApplicationWindow parent;
};

G_DEFINE_TYPE(DemoWindow, demo_window, GTK_TYPE_APPLICATION_WINDOW)

DemoWindow *demo_window_new(DemoApplication *app) {
    return g_object_new(DEMO_WINDOW_TYPE, "application", app, NULL);
}

static void demo_window_init(DemoWindow *win) {
    gtk_widget_init_template(GTK_WIDGET(win));
}

static void demo_window_class_init(DemoWindowClass *class) {
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class), "/org/gtk/demo/builder.ui");
}
