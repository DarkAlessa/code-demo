#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

class My_Area : public Gtk::DrawingArea {
public:
	My_Area();
	virtual ~My_Area() noexcept;
	
protected:
	void on_draw(const Cairo::RefPtr<Cairo::Context>&, int, int);

};

#endif // SEVEN_SEGMENT_H
