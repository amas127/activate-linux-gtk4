#include <gtk/gtk.h>

#include "Option/Option.h"
#include "Window.h"

int main(int argc, char *argv[]) {
  auto opt = parse_option_from_cli(argc, argv);
  auto app = gtk_application_new("com.gtk4.my.activate.linux",
                                 G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), (void *)&opt);
  auto stat = g_application_run(G_APPLICATION(app), 0, nullptr);
  g_object_unref(app);
  return stat;
}
