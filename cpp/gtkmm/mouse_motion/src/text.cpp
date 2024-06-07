#include "text.h"
#include <glibmm/main.h>
#include <gtkmm/eventcontrollermotion.h>

My_Area::My_Area() : x(0), y(0) {
    set_draw_func(sigc::mem_fun(*this, &My_Area::on_draw));
    auto controller = Gtk::EventControllerMotion::create();
    controller->signal_motion().connect(sigc::mem_fun(*this, &My_Area::on_my_motion));
    add_controller(controller);
}

My_Area::~My_Area() noexcept = default;

void My_Area::on_my_motion(double x, double y) {
    this->x = x;
    this->y = y;
    queue_draw();
}

void My_Area::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, [[maybe_unused]] int width, [[maybe_unused]] int height) {
    cr->save();
    cr->move_to(width / 2.0, height / 2.0);
    cr->line_to(x, y);
    cr->stroke();
    cr->restore();
}
