#ifndef APP_H
#define APP_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/separator.h>
#include <glibmm/ustring.h>

class My_window : public Gtk::Window {
public:
  My_window();
  virtual ~My_window();

protected:
  void click(const Glib::ustring& ss);

  // signal
  sigc::slot<void(const Glib::ustring&)> signal;

  Gtk::Box top_box;
  Gtk::Box group_box_1;
  Gtk::Box group_box_2;

  Gtk::Button button_1;
  Gtk::Button button_2;
  Gtk::Button button_3;
  Gtk::Button button_4;

  Gtk::Separator separator;
};

#endif // APP_H
