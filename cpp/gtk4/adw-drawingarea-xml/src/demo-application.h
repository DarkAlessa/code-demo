#pragma once

#include <gtk/gtk.h>
#include <libadwaita-1/adwaita.h>

G_BEGIN_DECLS

#define DEMO_APPLICATION_TYPE (demo_application_get_type())
G_DECLARE_FINAL_TYPE(DemoApplication, demo_application, DEMO, APPLICATION, AdwApplication)

DemoApplication *demo_application_new(void);

G_END_DECLS