#include "sg-application.h"
#include "gnome-screen-grabber.h"

struct _SgApplication
{
  GtkApplication parent_instance;
};

G_DEFINE_TYPE (SgApplication, sg_application, GTK_TYPE_APPLICATION)

static const GOptionEntry entries[] = {
  { "file", 'f', 0, G_OPTION_ARG_FILENAME, NULL, "Save screenshot directly to this file", "filename" },
  { "include-pointer", 'p', 0, G_OPTION_ARG_NONE, NULL, "Include the pointer with the screenshot", NULL },
  { "use-flash", 's', 0, G_OPTION_ARG_NONE, NULL, "Take screenshot with a flash", NULL },
  { NULL }
};

SgApplication *
sg_application_new (gchar *application_id,
                         GApplicationFlags  flags)
{
  return g_object_new (SG_TYPE_APPLICATION,
                       "application-id", application_id,
                       "flags", flags,
                       NULL);
}

static void
sg_application_finalize (GObject *object)
{
  SgApplication *self = (SgApplication *)object;

  G_OBJECT_CLASS (sg_application_parent_class)->finalize (object);
}

static gint
sg_application_command_line (GApplication            *app,
                                     GApplicationCommandLine *command_line)
{
  gchar *file_arg = NULL;
  gboolean include_pointer_arg = FALSE;
  gboolean use_flash_arg = FALSE;

  GVariantDict *options;
  gint exit_status = EXIT_SUCCESS;
  
  options = g_application_command_line_get_options_dict (command_line);

  g_variant_dict_lookup (options, "file", "^&ay", &file_arg);
  g_variant_dict_lookup (options, "include-pointer", "b", &include_pointer_arg);
  g_variant_dict_lookup (options, "use-flash", "b", &use_flash_arg);

  if (NULL == file_arg)
  {
    exit_status = EXIT_FAILURE;
    goto out;
  }
  
  makeScreenshot(file_arg, include_pointer_arg, use_flash_arg);
  
  out:
  return exit_status;
}

static void
sg_application_class_init (SgApplicationClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

  object_class->finalize = sg_application_finalize;
  app_class->command_line = sg_application_command_line;
}

static void
sg_application_init (SgApplication *self)
{
  g_application_add_main_option_entries (G_APPLICATION (self), entries);
}
