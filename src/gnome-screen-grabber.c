#include <gio/gio.h>

#include "gnome-screen-grabber.h"

void makeScreenshot(gchar *fileName, gboolean cursor, gboolean flash)
{
  g_autoptr(GError) error = NULL;
  GDBusConnection *connection;

  const gchar *method_name;
  GVariant *method_params;

  method_name = "Screenshot";
  method_params = g_variant_new("(bbs)",
                                       cursor,
                                       flash, /* flash */
                                       fileName);

  connection = g_application_get_dbus_connection (g_application_get_default ());
  
  g_dbus_connection_call_sync (connection,
                                 "org.gnome.Shell.Screenshot",
                                 "/org/gnome/Shell/Screenshot",
                                 "org.gnome.Shell.Screenshot",
                                 method_name,
                                 method_params,
                                 NULL,
                                 G_DBUS_CALL_FLAGS_NONE,
                                 -1,
                                 NULL,
                                 &error);
}

