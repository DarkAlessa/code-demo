#include "seven_segment.h"
#include <glibmm/main.h>
#include <array>

Point::Point(double x, double y) : x(x), y(y) {}

Border::Border(double width, double height) : width(width), height(height) {}

Seven_Segment::Seven_Segment(double a, double b, double g) : a(a), b(b), g(g) {}

My_Area::My_Area(double text_height)
: pos{0.0, 0.0}
, border{text_height * WIDTH_MULTIPLIER, text_height}
, seg{text_height * A_MULTIPLIER, text_height * B_MULTIPLIER, text_height * G_MULTIPLIER}
, count(0)
{
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &My_Area::on_timeout), 400);
    set_draw_func(sigc::mem_fun(*this, &My_Area::on_draw));
}

My_Area::~My_Area() noexcept = default;

bool My_Area::on_timeout() {
    queue_draw();
    count++;
    return true;
}

void My_Area::show_sm(const Cairo::RefPtr<Cairo::Context>& cr, int num, Point pos) const {
    const std::array<unsigned char, 10> number = {
        0b0111111, /* 0 */
        0b0000110, /* 1 */
        0b1011011, /* 2 */
        0b1001111, /* 3 */
        0b1100110, /* 4 */
        0b1101101, /* 5 */
        0b1111101, /* 6 */
        0b0000111, /* 7 */
        0b1111111, /* 8 */
        0b1101111  /* 9 */
    };

    // Border
    // cr->save();
    // cr->set_source_rgb(0.8, 0.0, 0.0);
    // cr->rectangle(pos.x, pos.y, border.width, border.height);
    // cr->stroke();
    // cr->restore();

    cr->set_source_rgb(0.141, 0.141, 0.141);

    // A
    if (number[num] & 0b0000001) {
        cr->save();
        cr->translate(pos.x + seg.a + seg.g, pos.y + seg.a);
        cr->move_to(0.0, 0.0);
        cr->line_to(seg.a, -seg.a);
        cr->line_to(seg.a + seg.b, -seg.a);
        cr->line_to(seg.a + seg.b + seg.a, 0.0);
        cr->line_to(seg.a + seg.b, seg.a);
        cr->line_to(seg.a, seg.a);
        cr->close_path();
        cr->fill();
        cr->restore();
    }
    // B
    if (number[num] & 0b0000010) {
        cr->save();
        cr->translate(pos.x + (3 * seg.a) + (2 * seg.g) + seg.b, pos.y + seg.a + seg.g);
        cr->move_to(0.0, 0.0);
        cr->line_to(seg.a, seg.a);
        cr->line_to(seg.a, seg.a + seg.b);
        cr->line_to(0.0, seg.a + seg.b + seg.a);
        cr->line_to(-seg.a, seg.a + seg.b);
        cr->line_to(-seg.a, seg.a);
        cr->close_path();
        cr->fill();
        cr->restore();
    }
    // C
    if (number[num] & 0b0000100) {
        cr->save();
        cr->translate(pos.x + (3 * seg.a) + (2 * seg.g) + seg.b, pos.y + (3 * seg.a) + (3 * seg.g) + seg.b);
        cr->move_to(0.0, 0.0);
        cr->line_to(seg.a, seg.a);
        cr->line_to(seg.a, seg.a + seg.b);
        cr->line_to(0.0, seg.a + seg.b + seg.a);
        cr->line_to(-seg.a, seg.a + seg.b);
        cr->line_to(-seg.a, seg.a);
        cr->close_path();
        cr->fill();
        cr->restore();
    }
    // D
    if (number[num] & 0b0001000) {
        cr->save();
        cr->translate(pos.x + seg.a + seg.g, pos.y + (5 * seg.a) + (4 * seg.g) + (2 * seg.b));
        cr->move_to(0.0, 0.0);
        cr->line_to(seg.a, -seg.a);
        cr->line_to(seg.a + seg.b, -seg.a);
        cr->line_to(seg.a + seg.b + seg.a, 0.0);
        cr->line_to(seg.a + seg.b, seg.a);
        cr->line_to(seg.a, seg.a);
        cr->close_path();
        cr->fill();
        cr->restore();
    }
    // E
    if (number[num] & 0b0010000) {
        cr->save();
        cr->translate(pos.x + seg.a, pos.y + (3 * seg.a) + (3 * seg.g) + seg.b);
        cr->move_to(0.0, 0.0);
        cr->line_to(seg.a, seg.a);
        cr->line_to(seg.a, seg.a + seg.b);
        cr->line_to(0.0, seg.a + seg.b + seg.a);
        cr->line_to(-seg.a, seg.a + seg.b);
        cr->line_to(-seg.a, seg.a);
        cr->close_path();
        cr->fill();
        cr->restore();
    }
    // F
    if (number[num] & 0b0100000) {
        cr->save();
        cr->translate(pos.x + seg.a, pos.y + seg.a + seg.g);
        cr->move_to(0.0, 0.0);
        cr->line_to(seg.a, seg.a);
        cr->line_to(seg.a, seg.a + seg.b);
        cr->line_to(0.0, seg.a + seg.b + seg.a);
        cr->line_to(-seg.a, seg.a + seg.b);
        cr->line_to(-seg.a, seg.a);
        cr->close_path();
        cr->fill();
        cr->restore();
    }
    // G
    if (number[num] & 0b1000000) {
        cr->save();
        cr->translate(pos.x + seg.a + seg.g, pos.y + (3 * seg.a) + (2 * seg.g) + seg.b);
        cr->move_to(0.0, 0.0);
        cr->line_to(seg.a, -seg.a);
        cr->line_to(seg.a + seg.b, -seg.a);
        cr->line_to(seg.a + seg.b + seg.a, 0.0);
        cr->line_to(seg.a + seg.b, seg.a);
        cr->line_to(seg.a, seg.a);
        cr->close_path();
        cr->fill();
        cr->restore();
    }   
}

void My_Area::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
    pos = {width / 4.0, height / 4.0};

    cr->save();
    cr->set_source_rgb(0.902, 0.98, 0.91);
    cr->paint();
    cr->restore();

    int x = count / 1 % 10;
    int y = count / 10 % 10;
    int z = count / 100 % 10;

    show_sm(cr, z, pos);
    show_sm(cr, y, Point{pos.x + border.width + 8.0, pos.y});
    show_sm(cr, x, Point{pos.x + border.width + 8.0 + border.width + 8.0, pos.y});
}
