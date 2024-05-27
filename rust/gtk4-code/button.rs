#![windows_subsystem = "windows"]

use gtk::prelude::*;
use gtk::{glib, Application, ApplicationWindow, Box, Orientation, Button};

const APP_ID: &str = "org.gtk_rs.HelloWorld";

fn main() -> glib::ExitCode {
    let app = Application::builder().application_id(APP_ID).build();
    app.connect_activate(build_ui);

    app.run()
}

fn build_ui(app: &Application) {
    let top_box = Box::new(Orientation::Vertical, 0);

    let box_a = Box::new(Orientation::Horizontal, 6);
    box_a.set_margin_top(10);
    box_a.set_margin_bottom(10);
    box_a.set_margin_start(10);
    box_a.set_margin_end(10);
    box_a.set_hexpand(true);
    
    let box_b = Box::new(Orientation::Horizontal, 6);
    box_b.set_margin_top(10);
    box_b.set_margin_bottom(10);
    box_b.set_margin_start(10);
    box_b.set_margin_end(10);

    let button1 = Button::with_label("Button 1");
    let button2 = Button::with_label("Button 2");
    let button3 = Button::with_label("Button 3");
    let button4 = Button::with_label("Button 4");

    box_a.append(&button1);
    box_a.append(&button2);
    box_b.append(&button3);
    box_b.append(&button4);

    top_box.append(&box_a);
    top_box.append(&box_b);

    /*
     *button.connect_clicked(|button| {
     *    button.set_label("Hello World!");
     *});
     */
    
    let window = ApplicationWindow::builder()
        .application(app)
        .title("ELSA")
        .default_width(400)
        .default_height(320)
        .child(&top_box)
        .build();

    window.present();
}
