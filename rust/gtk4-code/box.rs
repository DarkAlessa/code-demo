#![windows_subsystem = "windows"]
use gtk::prelude::*;
use gtk::{glib, Application, ApplicationWindow, Button, Box, Orientation, Separator};

const APP_ID: &str = "org.gtk_rs.elsa";

fn main() -> glib::ExitCode {
    let app = Application::builder().application_id(APP_ID).build();
    app.connect_activate(build_ui);
    app.run()
}

fn build_ui(app: &Application) {
    let top_box = Box::new(Orientation::Horizontal, 0);

    let box_left = Box::new(Orientation::Vertical, 6);
    box_left.set_margin_top(10);
    box_left.set_margin_bottom(10);
    box_left.set_margin_start(10);
    box_left.set_margin_end(10);
    box_left.set_width_request(160);
    
    let box_right = Box::new(Orientation::Vertical, 0);
    
    let box_b1 = Box::new(Orientation::Horizontal, 0);
    let box_b2 = Box::new(Orientation::Horizontal, 0);
    let box_b3 = Box::new(Orientation::Horizontal, 0);
    let button1 = Button::with_label("Button 1");
    let button2 = Button::with_label("Button 2");
    let button3 = Button::with_label("Button 3");
    box_b1.append(&button1);
    box_b2.append(&button2);
    box_b3.append(&button3);

    box_left.append(&box_b1);
    box_left.append(&box_b2);
    box_left.append(&box_b3);

    let separator = Separator::new(Orientation::Vertical);

    top_box.append(&box_left);
    top_box.append(&separator);
    top_box.append(&box_right);

    let window = ApplicationWindow::builder()
        .application(app)
        .title("Box & Button Example")
        .default_width(640)
        .default_height(480)
        .child(&top_box)
        .build();

    window.present();
}
