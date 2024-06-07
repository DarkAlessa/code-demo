#ifndef WINDOW_H
#define WINDOW_H

#include "seven_segment.h"
#include <gtkmm/window.h>

class My_window : public Gtk::Window {
public:
    My_window();
    virtual ~My_window() noexcept;

protected:
    My_Area* my_area;
};

#endif // WINDOW_H
