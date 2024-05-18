#include "text.h"
#include <glibmm/main.h>
#include <pangomm.h>

My_Area::My_Area() {
	set_draw_func(sigc::mem_fun(*this, &My_Area::on_draw));
}

My_Area::~My_Area() noexcept = default;

void My_Area::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, [[maybe_unused]] int width, [[maybe_unused]] int height) {
	Pango::FontDescription font;
	font.set_family("SauceCodePro NF");
	font.set_size(16 * PANGO_SCALE);
	font.set_weight(Pango::Weight::BOLD);

	auto layout = create_pango_layout("");
	layout->set_font_description(font);


	int text_width = 0;
	int text_height = 0;
	layout->get_pixel_size(text_width, text_height);
	
	cr->move_to(70.0, 60.0);
	layout->set_text("This is normal text");
	layout->show_in_cairo_context(cr);

	cr->move_to(70.0, 120.0);
	layout->set_markup("<span color=\"pink\"></span><span foreground=\"black\" background=\"pink\"> BLACK </span><span foreground=\"pink\" background=\"black\"> PINK </span><span color=\"black\"></span>");
	layout->show_in_cairo_context(cr);
}
