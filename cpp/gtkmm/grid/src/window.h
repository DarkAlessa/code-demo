#ifndef WINDOW_H
#define WINDOW_H

#include "my_grid.h"
#include <gtkmm/window.h>

class My_window : public Gtk::Window {
public:
    My_window();
    virtual ~My_window() noexcept;

protected:
    My_Grid* my_grid;
};

#endif // WINDOW_H
