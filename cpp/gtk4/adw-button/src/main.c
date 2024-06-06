// build command
// $ gcc myapp.c -o myapp `pkg-config --cflags --libs gtk4 libadwaita-1`

#include <gtk/gtk.h>
#include <libadwaita-1/adwaita.h>

#define TYPE_MY_APP (my_app_get_type())
G_DECLARE_FINAL_TYPE(MyApp, my_app, MY, APP, AdwApplication)

struct _MyApp {
    AdwApplication parent_instance;
};

G_DEFINE_TYPE(MyApp, my_app, ADW_TYPE_APPLICATION)

static void my_app_activate(GApplication *app) {
    GtkWidget *window;
    GtkWidget *button;

    window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "Hello, Adwaita!");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    button = gtk_button_new_with_label("Click Me");
    g_signal_connect(button, "clicked", G_CALLBACK(g_print), "Button clicked!\n");
    gtk_window_set_child(GTK_WINDOW(window), button);

    gtk_window_present(GTK_WINDOW(window));
}

static void my_app_class_init(MyAppClass *klass) {
    G_APPLICATION_CLASS(klass)->activate = my_app_activate;
}

static void my_app_init(MyApp *self) {
    /* Initialization code here */
}

int main(int argc, char *argv[]) {
    g_autoptr(MyApp) app = g_object_new(TYPE_MY_APP, "application-id", "com.example.MyApp", NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
