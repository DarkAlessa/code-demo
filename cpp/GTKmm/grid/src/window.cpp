#include "my_grid.h"
#include "window.h"

My_window::My_window()
: my_grid(Gtk::manage(new My_Grid))
{
	set_title("Grid");
	set_default_size(600, 600);
	set_child(*my_grid);
}

My_window::~My_window() noexcept {}
