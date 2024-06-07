#include "window.h"

My_window::My_window()
:   my_area(100.0),
    top_box(Gtk::Orientation::HORIZONTAL, 0),
    v_box(Gtk::Orientation::VERTICAL, 4),
    button_box(Gtk::Orientation::HORIZONTAL, 0),
    v_sep(Gtk::Orientation::VERTICAL),
    bt("Button 1")
{
    set_title("7 Segments");
    set_default_size(640, 480);
    my_area.set_content_width(400);
    my_area.set_content_height(400);
    my_area.set_expand(true);

    button_box.append(bt);

    v_box.set_size_request(100, -1);
    v_box.set_margin(6);
    v_box.append(button_box);

    top_box.append(v_box);
    top_box.append(v_sep);
    top_box.append(my_area);
    
    set_child(top_box);
}

My_window::~My_window() noexcept {}
