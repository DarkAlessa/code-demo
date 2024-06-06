#include "demo-window.h"

struct _DemoWindow {
    AdwApplicationWindow parent;
    AdwHeaderBar* header_bar;
    AdwOverlaySplitView* overlay;
    GtkButton* button;
    GtkSeparator* v_sep;

};

G_DEFINE_TYPE(DemoWindow, demo_window, ADW_TYPE_APPLICATION_WINDOW)

DemoWindow *demo_window_new(DemoApplication *app) {
    return g_object_new(DEMO_WINDOW_TYPE, "application", app, NULL);
}

static void demo_window_init(DemoWindow *win) {
    gtk_widget_init_template(GTK_WIDGET(win));
}

void button_cb_1() {
    g_print("Hello Button 1\n");
}

void button_cb_2() {
    g_print("Hello Button 2\n");
}

void button_cb_3() {
    g_print("Hello Button 3\n");
}

static void demo_window_class_init(DemoWindowClass *klass) {
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(klass), "/org/gtk/demo/builder.ui");
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(klass), DemoWindow, header_bar);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(klass), DemoWindow, overlay);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(klass), DemoWindow, button);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(klass), DemoWindow, v_sep);

    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), button_cb_1);
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), button_cb_2);
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS(klass), button_cb_3);
}
