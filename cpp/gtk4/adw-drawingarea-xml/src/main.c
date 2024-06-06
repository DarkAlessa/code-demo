#include "demo-application.h"
#include <gtk/gtk.h>

int main(int argc, char **argv) {
    return g_application_run(G_APPLICATION(demo_application_new()), argc, argv);
}
