#include <libadwaita-1/adwaita.h>
#include <gtk/gtk.h>

static void activate(GtkApplication *app) {
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Box Libadwaita");
    gtk_window_set_default_size(GTK_WINDOW(window), 768, 576);

    GtkWidget* button1 = gtk_button_new_with_label("Button 1");
    GtkWidget* button2 = gtk_button_new_with_label("Button 2");
    GtkWidget* button3 = gtk_button_new_with_label("Button 3");
    GtkWidget* button4 = gtk_button_new_with_label("Button 4");

    GtkWidget* top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget* left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    GtkWidget* right_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget* b1_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget* b2_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget* b3_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget* b4_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget* vseparator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    GtkWidget* hseparator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    // button box
    gtk_box_append(GTK_BOX(b1_box), button1);
    gtk_box_append(GTK_BOX(b2_box), button2);
    gtk_box_append(GTK_BOX(b3_box), button3);
    gtk_box_append(GTK_BOX(b4_box), button4);
    // left box
    gtk_widget_set_size_request(left_box, 140, -1); // height -1 (default)
    gtk_widget_set_margin_top(left_box, 10);
    gtk_widget_set_margin_bottom(left_box, 10);
    gtk_widget_set_margin_start(left_box, 10);
    gtk_widget_set_margin_end(left_box, 10);
    gtk_box_append(GTK_BOX(left_box), b1_box);
    gtk_box_append(GTK_BOX(left_box), b2_box);
    gtk_box_append(GTK_BOX(left_box), hseparator);
    gtk_box_append(GTK_BOX(left_box), b3_box);
    gtk_box_append(GTK_BOX(left_box), b4_box);
    // top box
    gtk_box_append(GTK_BOX(top_box), left_box);
    gtk_box_append(GTK_BOX(top_box), vseparator);
    gtk_box_append(GTK_BOX(top_box), right_box);

    gtk_window_set_child(GTK_WINDOW(window), top_box);
    gtk_window_present(GTK_WINDOW(window));

}

int main(int argc, char **argv) {
    g_autoptr(AdwApplication) app = adw_application_new("com.github.DarkAlessa", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
