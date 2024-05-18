#include "my_grid.h"

My_Grid::My_Grid()
: bt_a("Button(0, 0)")
, bt_b("Button(1, 0)")
, bt_c("Button(0 - 1, 1)")
, bt_d("Button(1, 2)")
, bt_e("Button(0, 2)")
{
    set_margin(10);
    set_row_spacing(4);
    set_column_spacing(4);
    set_column_homogeneous();
    attach(bt_a, 0, 0);
    attach(bt_b, 1, 0);
    attach_next_to(bt_c, bt_a, Gtk::PositionType::BOTTOM, 2, 1);
    attach(bt_d, 1, 2);
    attach(bt_e, 0, 2);
}

My_Grid::~My_Grid() noexcept = default;
