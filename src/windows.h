#ifndef WINDOWS_H
#define WINDOWS_H
#include <gtk/gtk.h>
// extern GtkWidget* <name_of_window>;
extern GtkWidget* AABAwindowSupprimer;
extern GtkWidget* AABAwindowAjouter;
extern GtkWidget* AABAwindowModifier;
extern GtkWidget* AABAwindowGererParking;
extern GtkWidget* AABAwindowAttribuerAgent;
extern GtkWidget* current_window;
void windows_init(void);
void windows_show_window(GtkWidget* window);
#endif // WINDOWS_H