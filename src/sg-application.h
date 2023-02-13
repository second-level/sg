#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define SG_TYPE_APPLICATION (sg_application_get_type())

G_DECLARE_FINAL_TYPE (SgApplication, sg_application, TESTGTK, APPLICATION, GtkApplication)

SgApplication *sg_application_new (gchar *application_id,
                                             GApplicationFlags  flags);

G_END_DECLS
