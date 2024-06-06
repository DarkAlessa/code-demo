// build command
// $ gcc main.c -o myapp `pkg-config --cflags --libs gtk4 libadwaita-1`

#include <gtk/gtk.h>
#include <libadwaita-1/adwaita.h>

#define TYPE_MY_APP (my_app_get_type())
G_DECLARE_FINAL_TYPE(MyApp, my_app, MY, APP, AdwApplication)

struct _MyApp {
    AdwApplication parent_instance;
};

G_DEFINE_TYPE(MyApp, my_app, ADW_TYPE_APPLICATION)

G_MODULE_EXPORT void on_button_clicked(GtkWidget *widget, gpointer user_data) {
    g_print("Button clicked!\n");
}

static void my_app_activate(GApplication *app) {
    GtkBuilder *builder;
    GObject *window;
    GObject *button;

    builder = gtk_builder_new_from_file("example.ui");

    window = gtk_builder_get_object(builder, "main_window");
    gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(app));

    button = gtk_builder_get_object(builder, "button");
//  สามารถประกาศ signal ใน .ui ไฟล์ได้ (ดูใน example.ui)
//  g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

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
