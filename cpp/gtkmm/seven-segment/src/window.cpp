#include "window.h"

My_window::My_window()
: my_area(Gtk::manage(new My_Area(100.0)))
{
	set_title("7 Segments");
	set_default_size(400, 400);
	my_area->set_content_width(400);
	my_area->set_content_height(400);
	set_child(*my_area);
}

My_window::~My_window() noexcept {}