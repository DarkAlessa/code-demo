#include "demo-application.h"
#include "demo-window.h"

struct _DemoApplication {
	AdwApplication parent;
};

G_DEFINE_TYPE(DemoApplication, demo_application, ADW_TYPE_APPLICATION)

DemoApplication *demo_application_new(void) {
    return g_object_new(DEMO_APPLICATION_TYPE, "application-id", "org.gtk.demo", "flags",
                        G_APPLICATION_HANDLES_OPEN, NULL);
}

static void demo_application_init(DemoApplication *app) {}

static void demo_application_activate(GApplication *app) {
    DemoWindow *win = demo_window_new(DEMO_APPLICATION(app));
    gtk_window_present(GTK_WINDOW(win));
}

static void demo_application_class_init(DemoApplicationClass *class) {
    G_APPLICATION_CLASS(class)->activate = demo_application_activate;
}
