#include "window.h"
#include <gtkmm/application.h>
#include <gtkmm/settings.h>
#include <iostream>

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create("demo");
    
    /* Dark theme
    auto settings = Gtk::Settings::get_default();
    settings->property_gtk_application_prefer_dark_theme() = true;
    */

    return app->make_window_and_run<My_window>(argc, argv);
}
