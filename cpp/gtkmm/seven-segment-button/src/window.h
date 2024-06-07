#ifndef WINDOW_H
#define WINDOW_H

#include "seven_segment.h"
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/separator.h>

class My_window : public Gtk::Window {
public:
    My_window();
    virtual ~My_window() noexcept;

protected:
    My_Area my_area;
    Gtk::Box top_box;
    Gtk::Box v_box;
    Gtk::Box button_box;
    Gtk::Separator v_sep;
    Gtk::Button bt;
};

#endif // WINDOW_H
