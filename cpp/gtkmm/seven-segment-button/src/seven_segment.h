#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

#define WIDTH_MULTIPLIER 0.5741
#define A_MULTIPLIER     0.0741
#define B_MULTIPLIER     0.2594
#define G_MULTIPLIER     0.0093

struct Point {
    double x;
    double y;
    Point(double, double);
};

struct Border {
    double width;
    double height;
    Border(double, double);
};

struct Seven_Segment {
    double a;
    double b;
    double g;
    Seven_Segment(double, double, double);
};

class My_Area : public Gtk::DrawingArea {
public:
    My_Area(double);
    virtual ~My_Area() noexcept;
    
protected:
    void show_sm(const Cairo::RefPtr<Cairo::Context>&, int, Point) const;
    void on_draw(const Cairo::RefPtr<Cairo::Context>&, int, int);
    bool on_timeout();

    Point pos;
    Border border;
    Seven_Segment seg;
    unsigned int count;
};

#endif // SEVEN_SEGMENT_H
