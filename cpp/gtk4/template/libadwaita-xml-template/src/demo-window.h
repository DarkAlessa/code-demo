#pragma once

#include <gtk/gtk.h>
#include <libadwaita-1/adwaita.h>
#include "demo-application.h"

G_BEGIN_DECLS

#define DEMO_WINDOW_TYPE (demo_window_get_type())
G_DECLARE_FINAL_TYPE(DemoWindow, demo_window, DEMO, WINDOW, AdwApplicationWindow)

DemoWindow *demo_window_new(DemoApplication *app);

G_END_DECLS