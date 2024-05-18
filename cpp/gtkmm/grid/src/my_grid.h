#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include <gtkmm/grid.h>
#include <gtkmm/button.h>

class My_Grid : public Gtk::Grid {
public:
	My_Grid();
	virtual ~My_Grid() noexcept;
	
protected:
	Gtk::Button bt_a;
	Gtk::Button bt_b;
	Gtk::Button bt_c;
	Gtk::Button bt_d;
	Gtk::Button bt_e;
};

#endif // SEVEN_SEGMENT_H
