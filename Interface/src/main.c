/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"

int
main (int argc, char *argv[])
{
  GtkWidget *BIwindowG;
  GtkWidget *JDwindowG;
  GtkWidget *BIdialog;
  GtkWidget *JDdialog;
  GtkWidget *RAwindowG;
  GtkWidget *BHwindowG, *TRwindowG, *LoginWindow;
  GtkWidget *image;
  GtkWidget *layout;
  GtkWidget *window;
  GtkWidget *button;
  

#ifdef ENABLE_NLS
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
#endif

  gtk_set_locale ();
  gtk_init (&argc, &argv);

  add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");
/////////////////////////////////////////////////////////////////////////////////////
    LoginWindow = create_LoginWindow ();
    gtk_widget_show_all (LoginWindow);
////////////////////////////////////////////////////////////////////////////////////
  //gtk_window_set_default_background_image("/Img/bg4.jpg");

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */
  //BIwindowG = create_BIwindowG ();
  //gtk_widget_show (BIwindowG);
  //JDwindowG = create_JDwindowG ();
  //gtk_widget_show (JDwindowG);
  //BIdialog = create_BIdialog ();
  //gtk_widget_show (BIdialog);
  //JDdialog = create_JDdialog ();
  //gtk_widget_show (JDdialog);
  //RAwindowG = create_RAwindowG ();
  //gtk_widget_show (RAwindowG);
  //BHwindowG = create_BHwindowG ();
  //gtk_widget_show (BHwindowG);
  //TRwindowG = create_TRwindowG ();
  //gtk_widget_show (TRwindowG);
  //LoginWindow = create_LoginWindow ();
  //gtk_widget_show (LoginWindow);

  gtk_main ();
  return 0;
}
