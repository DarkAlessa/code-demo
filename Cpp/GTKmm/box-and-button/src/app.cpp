#include "app.h"
#include <iostream>
#include <functional>

My_window::My_window()
: top_box(Gtk::Orientation::VERTICAL, 0),
  group_box_1(Gtk::Orientation::HORIZONTAL, 2),
  group_box_2(Gtk::Orientation::HORIZONTAL, 2),
  button_1("Button 1"),
  button_2("Button 2"),
  button_3("Button 3"),
  button_4("Button 4")
{
  set_title("Demo");
  set_default_size(640, 420);

  // signal
  signal = sigc::mem_fun(*this, &My_window::click);

  button_1.set_expand(false);
  button_1.signal_clicked().connect(sigc::bind(signal, "Hello Button 1"));

  button_2.set_expand(false);
  button_2.signal_clicked().connect(sigc::bind(signal, "Hello Button 2"));

  button_3.set_expand(false);
  button_3.signal_clicked().connect(sigc::bind(signal, "Hello Button 3"));

  button_4.set_expand(false);
  button_4.signal_clicked().connect(sigc::bind(signal, "Hello Button 4"));

  // Group box 1
  group_box_1.set_margin(10);
  group_box_1.append(button_1);
  group_box_1.append(button_2);

  // Group box 2
  group_box_2.set_margin(10);
  group_box_2.append(button_3);
  group_box_2.append(button_4);

  top_box.append(group_box_1);
  top_box.append(separator);
  top_box.append(group_box_2);
  
  set_child(top_box);
}

My_window::~My_window() {}

void My_window::click(const Glib::ustring& ss) {
  std::cout << ss << '\n';
}

