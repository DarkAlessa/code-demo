#include <libadwaita-1/adwaita.h>
#include <gtk/gtk.h>

static void activate(GtkApplication *app) {
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "libadwaita demo");
    gtk_window_set_default_size(GTK_WINDOW(window), 768, 576);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    g_autoptr(AdwApplication) app = adw_application_new("com.github.DarkAlessa", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
